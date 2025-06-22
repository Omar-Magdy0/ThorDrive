#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>
#include "TIM2_sys.h"
#include "core/sys.h"




struct Timer2Config {
    uint8_t prescaler_bits;
    uint8_t ocr2a;
    uint16_t actual_freq;
    int32_t error_ppm;
};


constexpr Timer2Config calculate_timer2_config() {
    constexpr uint32_t prescalers[] = {1, 8, 32, 64, 128, 256, 1024};
    constexpr uint8_t prescaler_bits[] = {
        (1 << CS20),
        (1 << CS21),
        (1 << CS21) | (1 << CS20),
        (1 << CS22),
        (1 << CS22) | (1 << CS20),
        (1 << CS22) | (1 << CS21),
        (1 << CS22) | (1 << CS21) | (1 << CS20)
    };
    
    uint8_t best_idx = 0;
    uint8_t best_ocr = 0;
    uint32_t best_error = UINT32_MAX;
    
    for (uint8_t i = 0; i < 7; i++) {
        const uint32_t ticks_needed = F_CPU / (prescalers[i] * SYSTEM_TICK_HZ);
        if (ticks_needed > 255 || ticks_needed < 1) continue;
        
        const uint32_t actual_freq = F_CPU / (prescalers[i] * ticks_needed);
        const uint32_t error = (actual_freq > SYSTEM_TICK_HZ) 
            ? (actual_freq - SYSTEM_TICK_HZ) 
            : (SYSTEM_TICK_HZ - actual_freq);
        
        if (error < best_error) {
            best_error = error;
            best_idx = i;
            best_ocr = ticks_needed - 1;
        }
    }
    
    const uint16_t actual_freq = F_CPU / (prescalers[best_idx] * (best_ocr + 1));
    const int32_t error_ppm = ((uint16_t)actual_freq - (uint16_t)SYSTEM_TICK_HZ) * 1000000L / SYSTEM_TICK_HZ;
    
    return {
        prescaler_bits[best_idx],
        best_ocr,
        actual_freq,
        error_ppm
    };
}

constexpr Timer2Config TIMER2_CFG = calculate_timer2_config();

// Compile-time validation
static_assert(TIMER2_CFG.ocr2a <= 255, "OCR2A value out of range");
static_assert(SYSTEM_TICK_HZ >= 61 && SYSTEM_TICK_HZ <= 4000000, 
    "Frequency out of achievable range (61Hz-4MHz)");


volatile uint32_t sys_ticks = 0;

void sysTIM_init() {
    // Apply compile-time calculated configuration
    TCCR2A = (1 << WGM21); // CTC mode
    TCCR2B = TIMER2_CFG.prescaler_bits;
    OCR2A = TIMER2_CFG.ocr2a;
    TIMSK2 = (1 << OCIE2A);
	tickerStat.error_ppm = TIMER2_CFG.error_ppm;
	tickerStat.actualFreq = TIMER2_CFG.actual_freq;
    sei();
}

ISR(TIMER2_COMPA_vect) {
    sys_ticks++;
}



uint32_t getTicks(){
    uint32_t ticks_safe;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ticks_safe = sys_ticks;
    }
    return ticks_safe;
}


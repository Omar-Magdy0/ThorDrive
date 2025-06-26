#pragma once
#include <cstdint>
#include <avr/io.h>





enum class ChannelName { A, B };

template<int TimerNum>
class TimPwm;

template<>
class TimPwm<1>{
private:
    enum class Prescaler : uint8_t {
        PS_1 = 0x01,     // CS10
        PS_8 = 0x02,     // CS11
        PS_64 = 0x03,    // CS10 | CS11
        PS_256 = 0x04,   // CS12
        PS_1024 = 0x05   // CS12 | CS10
    };

    struct Timer1Config {
        Prescaler prescaler;
        uint16_t icr1_value;
        uint32_t actual_freq;
        uint16_t resolution;
    };

    // Calculate best Phase Correct PWM settings
    static Timer1Config calculatePhaseCorrectPWM(uint32_t target_freq) {
        constexpr Prescaler prescalers[] = {
            Prescaler::PS_1, Prescaler::PS_8, Prescaler::PS_64, 
            Prescaler::PS_256, Prescaler::PS_1024
        };

        Timer1Config best = {Prescaler::PS_1, 0, 0, 0};

        for (auto ps : prescalers) {
            uint32_t prescale_val = 0;
            switch (ps) {
                case Prescaler::PS_1:    prescale_val = 1; break;
                case Prescaler::PS_8:    prescale_val = 8; break;
                case Prescaler::PS_64:   prescale_val = 64; break;
                case Prescaler::PS_256:  prescale_val = 256; break;
                case Prescaler::PS_1024: prescale_val = 1024; break;
            }

            // Phase Correct formula: f = F_CPU / (2 * N * TOP)
            uint32_t icr1 = (F_CPU / (2UL * prescale_val * target_freq)) - 1;

            // Validate range
            if (icr1 >= 0x20 && icr1 <= 0xFFFF) {  // Practical limits
                if (icr1 > best.resolution) {  // Prefer higher resolution
                    best = {
                        ps,
                        static_cast<uint16_t>(icr1),
                        F_CPU / (2 * prescale_val * (icr1 + 1)),
                        static_cast<uint16_t>(icr1)
                    };
                }
            }
        }
        return best;
    }


public:
    // --- Timer Configuration ---
    static void init(uint32_t frequency_hz) {
        TCCR1A = 0;  // Clear register
        TCCR1B = 0;  // Clear register
        
        // Phase Correct PWM Mode (TOP = ICR1, 10-bit)
        TCCR1A |= (1 << WGM11);
        TCCR1B |= (1 << WGM13);

         Timer1Config config = calculatePhaseCorrectPWM(frequency_hz);
        
        // Set prescaler
        switch (config.prescaler) {
            case Prescaler::PS_1:    TCCR1B |= (1 << CS10); break;
            case Prescaler::PS_8:    TCCR1B |= (1 << CS11); break;
            case Prescaler::PS_64:   TCCR1B |= (1 << CS10) | (1 << CS11); break;
            case Prescaler::PS_256:  TCCR1B |= (1 << CS12); break;
            case Prescaler::PS_1024: TCCR1B |= (1 << CS12) | (1 << CS10); break;
        }
        ICR1 = config.icr1_value;
    }

    static uint16_t getTimMax(){
        return ICR1;
    }
    // --- Channel Class ---
    template<ChannelName Ch>
    class Channel {
    public:
        static void init(bool noInvert){
            if constexpr (Ch == ChannelName::A) {
                if(!noInvert) {
                // Inverting mode (Clear on match, set at BOTTOM)
                    TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
                } else {
                    // Non-inverting mode (Set on match, clear at BOTTOM)
                    TCCR1A |= (1 << COM1A1);
                }
                OCR1A = 0;

            } else if(Ch == ChannelName::B){
                if(!noInvert) {
                // Inverting mode (Clear on match, set at BOTTOM)
                    TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
                } else {
                    // Non-inverting mode (Set on match, clear at BOTTOM)
                    TCCR1A |= (1 << COM1B1);
                }
                OCR1B = 0;
            }

        }
        static void duty(uint16_t value) {
            if constexpr (Ch == ChannelName::A) {
                OCR1A = value;
            } else if(Ch == ChannelName::B){
                OCR1B = value;
            }
        }
    };
};
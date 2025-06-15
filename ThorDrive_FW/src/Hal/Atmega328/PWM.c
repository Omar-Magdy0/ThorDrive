/*
 * GccApplication1.cpp
 *
 * Created: 6/11/2025 4:35:25 PM
 * Author : 20114
 */ 
#include <avr/io.h>
#include "PWM.h"

// Channel definitions for clarity
#define CHANNEL_A 0
#define CHANNEL_B 1

void timer2PWM_Init(uint8_t channel, uint8_t prescaler)
{
	// set PWM mode 
	TCCR2A = (1 << WGM21) | (1 << WGM20);
	TCCR2B = 0;
	if (channel == CHANNEL_A) 
	{
		TCCR2A |= (1 << COM2A1); // Non-inverting on OC2A
		DDRB |= (1 << OC2A_PIN);      // OC2A (PB3) as output
	} 
	else if (channel == CHANNEL_B) {
		TCCR2A |= (1 << COM2B1); // Non-inverting on OC2B
		DDRD |= (1 << OC2B_PIN);      // OC2B (PD3) as output
	}
// set prescaler 
 switch(prescaler)
 {
	 case 1 : TCCR2B |= (1<<CS20);
	 break;
	 case 8 : TCCR2B |= (1<<CS21);
	 break;	
	 case 32 : (TCCR2B |= (1<<CS21)) | (TCCR2B |= (1<<CS20));
	 break;
	 case 62 : TCCR2B |= (1<<CS22);
	 break;
	 case 128 : (TCCR2B |= (1<<CS22)) | (TCCR2B |= (1<<CS20));
	 break;
	 case 256 : (TCCR2B |= (1<<CS22)) | (TCCR2B |= (1<<CS21));
	 break;
	 case 1024 : (TCCR2B |= (1<<CS22)) | (TCCR2B |= (1<<CS21)) | (TCCR2B |= (1<<CS20));
	 break;
	 default:   TCCR2B |= (1 << CS21);
	 break;	  
 }
}

void timer2SetDutyCycle(uint8_t channel, uint8_t duty)
{
	if (channel==CHANNEL_A)
	{
		OCR2A = (duty * 255) / 100;
	}
	else if (channel==CHANNEL_B)
	{
		OCR2B = (duty * 255) / 100;
	}
	
}
void timer2Stop(void)
{

// Clear prescaler bits to stop timer
TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));

}
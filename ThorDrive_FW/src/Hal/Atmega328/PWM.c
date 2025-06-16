/*
 * GccApplication1.cpp
 *
 * Created: 6/11/2025 4:35:25 PM
 * Author : 20114
 */ 
#include "PWM.h"

void PWM_struct::timer2PWM_Init(uint8_t channel, uint8_t prescaler)
{
	// set PWM mode 
	GPIO1.gpio_Pin_write(WGM21,HIGH);
	GPIO1.gpio_Pin_write(WGM20,HIGH);
	TCCR2B = 0;
	if (channel == PWM_CHANNEL_A) 
	{
		GPIO1.gpio_Pin_write(COM2A1,HIGH);
		GPIO1.gpio_Pin_write(OC2A_PIN,HIGH);
	} 
	else if (channel == PWM_CHANNEL_B) {
		GPIO1.gpio_Pin_write(COM2B1,HIGH);
		GPIO1.gpio_Pin_write(OC2B_PIN,HIGH);
	}

	// set prescaler 
    TCCR2B |= prescaler;

	/*
	TCCR2A = (1 << WGM21) | (1 << WGM20);
	TCCR2B = 0;
	if (channel == PWM_CHANNEL_A) 
	{
		TCCR2A |= (1 << COM2A1); // Non-inverting on OC2A
		DDRB |= (1 << OC2A_PIN);      // OC2A (PB3) as output
	} 
	else if (channel == PWM_CHANNEL_B) {
		TCCR2A |= (1 << COM2B1); // Non-inverting on OC2B
		DDRD |= (1 << OC2B_PIN);      // OC2B (PD3) as output
		
	}
		*/

/*
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
	 */
}

void PWM_struct::timer2SetDutyCycle(uint8_t channel, uint8_t duty)
{
	if (channel==PWM_CHANNEL_A)
	{
		OCR2A = (duty * 2.55);
	}
	else if (channel==PWM_CHANNEL_B)
	{
		OCR2B = (duty * 2.55);
	}
	
}
void PWM_struct::timer2Stop(void)
{

// Clear prescaler bits to stop timer
TCCR2B &= ~(7);

}
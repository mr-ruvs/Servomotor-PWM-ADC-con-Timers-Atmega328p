//***************************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Ruben Granados
// Hardware: ATMEGA328P
// Created: 16/04/2024
//***************************************************************************
// Post Lab 5
//***************************************************************************

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "ServoControl/ServoControl.h"
#include "PWM0/PWM0.h"

float adcValue1 = 0;
float adcValue2 = 0;
float adcValue3 = 0;
float dutyCycle = 0;
void ADC_init(void);
uint16_t adcRead(uint8_t);

int main(void)
{
	DDRD = 0xFF;
	ADC_init();
	PWM_init();
	PWM0_init();
    while (1) 
    {
		adcValue1 = adcRead(0);
		servo_writeA(adcValue1);
		_delay_ms(10);
		adcValue2 = adcRead(1);
		servo_writeB(adcValue2);
		_delay_ms(10);
		adcValue3 = adcRead(2);
		dutyCycle = map(adcValue3, 0, 1023, 0, 100);
		PWM0_dcb(dutyCycle, NO_INVERTING);
    }
}
void ADC_init(void){
	ADMUX |= (1<<REFS0);	// VCC REF
	ADMUX &= ~(1<<REFS1);
	ADMUX &= ~(1<<ADLAR);	// 10 bits
	// PRESCALER 128 > 16M/128 = 125KHz
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRA |= (1<<ADEN);	// ADC ON
}
uint16_t adcRead(uint8_t canal){
	ADMUX = (ADMUX & 0xF0)|canal;	// selección de canal		
	ADCSRA |= (1<<ADSC);	// inicia conversión
	while((ADCSRA)&(1<<ADSC));	// hasta finalizar conversión
	return(ADC);	
}

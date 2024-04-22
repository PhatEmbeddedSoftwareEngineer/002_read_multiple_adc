#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include "delay.h"
#include "function_millis.h"
unsigned long now=0;
// configure three adc port a , pa0,pa1,pa4 , combine usart2 and debug, configure by register 
char buffer[1000];
int analogValue,analogValueTwo,analogValueThree;
void sendData(unsigned char c)
{
	USART2->DR =c;
	while((USART2->SR&(1<<6))==0);
	USART2->SR &= ~ (1<<6);
}

int main(void)
{	 
	RCC->APB2ENR |= (1<<9)|(1<<2); // GPIOA AND ADC1
	RCC->APB1ENR |= (1<<17); // USART2
	GPIOA->CRL = 0x44408A00; // 
	GPIOA->ODR |= (1<<3); // PULL-UP
	
	USART2->CR1 |= (1<<13)|(1<<3)|(1<<2); 
	USART2->BRR = 3750;
	RCC->CFGR |= (1<<15); // chia tan so 
	ADC1->SMPR2 |= (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0)|(1<<14)|(1<<13)|(1<<12);// pa0,pa1,pa4
	//ADC1->SQR3 = 0x0001; // PA1
	ADC1->CR2 |= (1<<1)|(1<<0); // enable adc and to start convert , continous converson mode
	ADC1->CR2 |= (1<<1)|(1<<0);
	ADC1->CR2 |= (1<<2)|(1<<1)|(1<<0); // start calib
	delay_init();
	ConfigureTimer3();
	while(1)
	{
		if(millis()-now>=1000)
		{
			now=millis();
			ADC1->SQR3=0x0000;
			DelayMs(5);
			ADC1->CR2 |= (1<<22); 
			while(!(ADC1->SR&(1<<1)));
			analogValue=ADC1->DR;
			sprintf(buffer,"analogValue: %d",analogValue);
			int a=0;
			while(buffer[a]!='\0')
			{
				sendData(buffer[a]);
				a++;
			}
			sendData('\n');
			sendData('\r');
			//DelayMs(1000);
			
			ADC1->SQR3=0x0001;
			DelayMs(5);
			ADC1->CR2 |= (1<<22);
			while(!(ADC1->SR&(1<<1)));
			analogValueTwo=ADC1->DR;
			sprintf(buffer,"analogValue Two: %d",analogValueTwo);
			int b=0;
			while(buffer[b]!='\0')
			{
				sendData(buffer[b]);
				b++;
			}
			sendData('\n');
			sendData('\r');
			//DelayMs(1000);
			
			ADC1->SQR3=0x0004;	
			DelayMs(5);
			ADC1->CR2 |= (1<<22);
			while(!(ADC1->SR&(1<<1)));
			analogValueThree=ADC1->DR;
			sprintf(buffer,"analogValue Three: %d",analogValueThree);
			int c=0;
			while(buffer[c]!='\0')
			{	
				sendData(buffer[c]);
				c++;
			}
			sendData('\n');
			sendData('\r');
			//DelayMs(1000);
		}
	}
}
// ok demo start 
// sensor analogvalueThree has sensor read analog 
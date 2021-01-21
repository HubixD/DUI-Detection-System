#include "led.h"  


#ifdef FRDM_KL05Z
# define LED_N   3
	static PinStruct_Type led[LED_N] = {
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 8},			
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 9},			
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 10}			
	};	
#endif 

typedef enum{BUT1 = 13, BUT2 = 6 , BUT3 = 7, RELAY=0, BUZZER=11 } Peripherals;
	
	
void LED_Init(void) {  
  
  for(int i = 0; i < LED_N; i++) {
    SIM->SCGC5 |= led[i].clk_mask;              
	  led[i].port->PCR[led[i].pin] = PORT_PCR_MUX(1UL); 
	  led[i].gpio->PDDR |= MASK(led[i].pin);            
	  led[i].gpio->PSOR |= MASK(led[i].pin);            
  } /* do for all leds */
}

void Peripherals_Init(void)
{
	SIM->SCGC5 |=  SIM_SCGC5_PORTB_MASK; 				
	PORTB->PCR[BUT1] |= PORT_PCR_MUX(1);      	
	PORTB->PCR[BUT2] |= PORT_PCR_MUX(1);  
	PORTB->PCR[BUT3] |= PORT_PCR_MUX(1);
	PORTB->PCR[RELAY] |= PORT_PCR_MUX(1);
	PORTB->PCR[BUZZER] |= PORT_PCR_MUX(1);

	PORTB->PCR[BUT1] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;	
	PORTB->PCR[BUT2] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;	
	PORTB->PCR[BUT3] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

  PTB->PDDR |=(1<<RELAY);  
  PTB->PDDR |=(1<<BUZZER);  
}

void Peripherals_Reset(void)
{
	PTB->PSOR = (1<<8);    
	PTB->PSOR = (1<<9);
	PTB->PSOR = (1<<10);
	PTB->PSOR = (1<<RELAY);  
	PTB->PSOR = (1<<BUZZER);  

}

void LED_Ctrl(uint8_t red, uint8_t green)
{
	if(red && green)
	{
		PTB->PCOR = (1<<8);	
		PTB->PCOR = (1<<9);
	}
	else if(red)
	{
		PTB->PSOR = (1<<9);
		PTB->PCOR = (1<<8);
	}
	else if(green)
	{
		PTB->PCOR = (1<<9);
		PTB->PSOR = (1<<8);
	}
	else
	{
		PTB->PSOR = (1<<8);
		PTB->PSOR = (1<<9);
	}
}

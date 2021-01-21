#include "DUI.h"


float v = ((float)(((float)2.5) / 4095) );    //2.5 - max voltage at gas sensor , 4095 - 12bit
uint8_t control=0;
float	result;
uint16_t temp;
uint8_t counter=59;
uint8_t working= 1;
char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
float cal_level;
float upper_level;

void DUI_Init()
{
	float mgL = 0.42*v;  		//    0.4/0.94  coeff  0.94 - alc voltage level in room air
	
	
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	
	Welcome();
	
	ADC_Init();
	LED_Init();
	Peripherals_Init();
	
	ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(12);		//  Enable ADC IRQ

	while(1){	
		Program_startup();

		if((PTB->PDIR&(1<<BUTTON1))== 0)	
		{			
			Heatup_procedure();
			while(working)
			{
				if(control)
				{
					result = result*mgL;		//result conversion
					
					counter++;
					if(counter%60 == 0)
						Calibration();
					else
						Normal_mode();
					control=0;
					DELAY(500)
				}
			}
		}
		else if((PTB->PDIR&(1<<BUTTON2))== 0)
		{
			LCD1602_Display("EXIT",1,1,0);
			break;
		}
		else
			continue;
	}
}

void Drunk()
{
	working = 0;
	counter = 0;
	LED_Ctrl(1,0);
	LCD1602_Display("Unable to drive",1,0,0);
	LCD1602_Display("Please get sober",0,0,1);

	PTB->PCOR = (1<<BUZZER);
	DELAY(3000)
	PTB->PSOR = (1<<BUZZER);

	LCD1602_Display("Program will",1,0,0);
	LCD1602_Display("restart in",0,0,1);
	LCD1602_Countdown(60,display);
	LCD1602_ClearAll();
}

void Sober()
{
	LED_Ctrl(0,1);
	DELAY(500)
	LCD1602_Display("Ready to go",1,0,0);
	DELAY(2000)
	LCD1602_Display("Press the",1,0,0);
	LCD1602_Display("Ignition button",0,0,1);
	while(1)		//While loop to determine what button was pressed (Engine ON/OFF)
	{
		if((PTB->PDIR&(1<<BUTTON3))== 0)
		{
			PTB->PCOR = (1<<RELAY);		//Turn ON engine
			LCD1602_Display("Vehicle on",1,0,0);
		}
		else if((PTB->PDIR&(1<<BUTTON2))== 0)
		{
			counter =0;
			working = 0;
			LCD1602_Display("Vehicle off",1,0,0);
			PTB->PSOR = (1<<RELAY);		//Turn OFF engine
			DELAY(1000)
			break;
		}
	}
}

void Calibration()
{
	LCD1602_Display("Calibration",1,0,0);
	LCD1602_Display("Do not blow",0,0,1);
	DELAY(2000)
	cal_level = result + 0.05;
	upper_level = cal_level + 0.3;  	//Every 30s calibration
	counter = counter - 60;
}

void Welcome()
{
	LCD1602_Display("DUI Detection",1,1,0);
	LCD1602_Display("System",0,5,1);
	DELAY(3000)
	LCD1602_ClearAll();
}

void Program_startup()
{
	Peripherals_Reset();	
	LCD1602_Display("Press the button",0,0,0);
	LCD1602_Display("to start",0,0,1);
	working=1;
}

void Heatup_procedure()
{
	LCD1602_Display("Preheat,Please",1,0,0);
	LCD1602_Display("wait for 20s",0,0,1);
	DELAY(20000)
}

void Normal_mode()
{
	sprintf(display,"BAC=%.3f mg/L",result);
	LCD1602_Display(display,1,0,0);

	if(result <=cal_level)    //Idle state
		LED_Ctrl(1,1);
	else if(result > cal_level && result <upper_level)    //Good result 'Sober'
		Sober();
	else
		Drunk();		// 'Drunk'
}

void ADC0_IRQHandler()
{	
	temp = ADC0->R[0];	// Read data
	if(!control)				// Check if result
	{
		result = temp;			// Send new value
		control=1;
	}
	NVIC_EnableIRQ(ADC0_IRQn);
}



























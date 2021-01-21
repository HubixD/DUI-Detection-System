#include "adc.h"
#include "lcd.h"
#include "led.h"


#define BUTTON1 13    //PTB13 - START
#define BUTTON2 6		 //PTB6 - Stop / Stop engine
#define BUTTON3 7		//PTB7 - Ignition
#define RELAY 0
#define BUZZER 11



void DUI_Init();      //Main program flow
void Drunk();					//Procedures if someone is drunk
void Sober();					//Procedures if someone is sober
void Calibration();		// Sensor calibration
void Welcome();				// Welcome menu
void Program_startup();	//default settings
void Heatup_procedure();	//sensor heating up
void Normal_mode();				//waiting for measurement - idle state
void ADC0_IRQHandler();   // ADC results via interrupt

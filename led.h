#include "frdm_bsp.h"

#ifndef LED_H
#define LED_H


typedef struct {
	GPIO_Type 	*gpio;        /* GPIO base pointer */
	PORT_Type 	*port;        /* PORT base pointer */
	uint32_t		clk_mask;     /* Mask for SCGC5 register */
	uint8_t  		pin;          /* Number of PIN */
} PinStruct_Type;


void LED_Init (void);						//LED initialization
void Peripheral_Init (void);		// Rest peripherals initialization
void Peripherals_Reset(void);		// Default peripherals settings
void LED_Ctrl(uint8_t red, uint8_t green);  //LED control for different situations
#endif /* LED_H */

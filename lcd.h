
#ifndef LCD1602_H
#define LCD1602_H

#include "frdm_bsp.h"
#include "i2c.h"


void LCD1602_Init(void);
void LCD1602_Print(char *str);
void LCD1602_ClearAll(void);
void LCD1602_SetCursor(uint8_t col, uint8_t row);
void LCD1602_Backlight(uint8_t state);
void LCD1602_Blink_On(void);
void LCD1602_Blink_Off(void);
void LCD1602_Display(char *str, uint8_t clr, uint8_t col, uint8_t row);
void LCD1602_Countdown(uint8_t num, char display[17]);
#endif  /* LCD1602_H */

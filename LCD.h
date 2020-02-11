/********************************************************************************
 *																				*
 * Module : LCD																	*
 *																				*
 * File Name : LCD.h															*
 *																				*
 * Description : Header File for LCD Driver.									*
 *																				*
 * Author : Youssef Harby														*
 *																				*
 ********************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "gpio.h"
#include "softwareDelay.h"
#include "common_macros.h"
#include "std_types.h"

/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

/*
 * LCD pins
 */
#define RS						PA1
#define RW 						PA2
#define E  						PA3
#define LCD_CTRL_PORT_DIR 		PORTA_DIR
#define LCD_CTRL_PORT 			PORTA_DATA
#define LCD_DATA_PORT_DIR 		PORTA_DIR
#define LCD_DATA_PORT 			PORTA_DATA

/*
 * LCD Commands
 */
#define CLEAR_COMMAND					0x01
#define TWO_LINE_LCD_EIGHT_BIT_MODE 	0x38
#define FOUR_BITS_DATA_MODE_ACTIVATED 	0x02
#define TWO_LINE_LCD_FOUR_BIT_MODE 		0x28
#define CURSOR_OFF 						0x0C
#define CURSOR_ON 						0x0E
#define SET_CURSOR_LOCATION 			0x80

/*
 * Macros for operating mode
 */
#define DATA_BITS_MODE 4
#if(DATA_BITS_MODE == 4)
#define UPPER_PORT_BITS
#endif

/********************************************************************************
 * 								Functions Prototypes							*
 ********************************************************************************/

/*
 * Description : A Function to Initialize the LCD Driver.
 */
void LCD_init(void);

/*
 * Description : A Function to send a Command.
 */
void LCD_sendCommand(uint8_t command);

/*
 * Description : A Function to write data (display character).
 */
void LCD_displayCharacter(uint8_t data);

/*
 * Description : A Function to display a string.
 */
void LCD_displayString(const sint8_t *str);

/*
 * Description : A Function to move the cursor to an exact spot.
 */
void LCD_goToRowColumn(uint8_t row, uint8_t col);

/*
 * Description : A Function to move the cursor to an exact spot and display a string at the spot.
 */
void LCD_displayStringRowColumn(uint8_t row, uint8_t col, const sint8_t* str);

/*
 * Description : A Function to display an integer number.
 */
void LCD_displayInteger(sint32_t num);

/*
 * Description : A Function to Clear the LCD Screen.
 */
void LCD_clearScreen(void);

#endif

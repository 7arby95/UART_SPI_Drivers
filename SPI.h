/*
 * SPI.h
 *
 *  Created on: Feb 9, 2020
 *      Author: Youssef Harby
 */

#ifndef SPI_H_
#define SPI_H_


/*- INCLUDES -----------------------------------------------*/

#include "Std_Types.h"
#include "Common_Macros.h"
#include "gpio.h"
#include "avr/interrupt.h"
#include "softwareDelay.h"

/********************************************************************************
 *							   Preprocessor Macros								*
 ********************************************************************************/


/********************************************************************************
 *								Type Declarations								*
 ********************************************************************************/
typedef enum{
	SPI_SLAVE = 0,
	SPI_MASTER = 1
}SPI_MasterSlaveSelect;

typedef enum{
	SPI_INTERRUPT_DISABLED = 0x00,
	SPI_INTERRUPT_ENABLED = 0x80
}SPI_Mode;

typedef enum{
	SPI_F_OSC_4,
	SPI_F_OSC_16,
	SPI_F_OSC_64,
	SPI_F_OSC_128,
	SPI_F_OSC_2_DOUBLE,
	SPI_F_OSC_8_DOUBLE,
	SPI_F_OSC_32_DOUBLE,
	SPI_F_OSC_64_DOUBLE
}SPI_ClockRateSelect;


typedef struct{
	SPI_MasterSlaveSelect MasterSlaveSelect;
	SPI_Mode Mode;
	SPI_ClockRateSelect ClockRateSelect;
}SPI_ConfigType;

/********************************************************************************
 *								Function Prototypes								*
 ********************************************************************************/

/*
 * Description : A Function to Initialize the SPI Driver.
 */
void SPI_init(const SPI_ConfigType* ConfigPtr);

/*
 * Description : A Function to set the call back function.
 */
void SPI_setCallBack(void(*a_ptr)(void));

/*
 * Description : A Function to send a byte.
 */
void SPI_sendByte(const uint8_t data);

/*
 * Description : A Function to receive a byte.
 */
uint8_t SPI_receiveByte(void);

#endif

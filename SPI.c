/*
 * SPI.c
 *
 *  Created on: Feb 9, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "SPI.h"
#include "SPI_cfg.h"


/*- GLOBAL STATIC VARIABLES --------------------------------*/

static volatile void (*g_SPI_callBackPtr)(void) = NULL;


/*- INTERRUPT SERVICE ROUTINES -----------------------------*/

ISR(SPI_STC_vect)
{
	if(g_SPI_callBackPtr != NULL)
	{
		g_SPI_callBackPtr();
	}
}


/*- APIs IMPLEMENTATION ------------------------------------*/

/*
 * Description : A Function to Initialize the SPI Driver.
 */
void SPI_init(const SPI_ConfigType* ConfigPtr)
{
	/* In case the MCU will be configured as a slave */
	if(ConfigPtr->MasterSlaveSelect == SPI_SLAVE)
	{
		/* select the slave mode and set the pins accordingly */
		gpioPinDirection(SPI_GPIO, SS | MOSI | SCK, INPUT);
		gpioPinDirection(SPI_GPIO, MISO, OUTPUT);
		CLEAR_BIT(SPCR, MSTR);
	}
	/* In case the MCU will be configured as a master */
	else if(ConfigPtr->MasterSlaveSelect == SPI_MASTER)
	{
		/* select the master mode and set the pins accordingly */
		gpioPinDirection(SPI_GPIO, SS | MOSI | SCK, OUTPUT);
		gpioPinDirection(SPI_GPIO, MISO, INPUT);
		SET_BIT(SPCR, MSTR);
	}

	/* Selecting the interrupt mode (enabled of disabled) */
	SPCR = (SPCR & 0x7F) | ConfigPtr->Mode;
	/* Enable the SPI module */
	SET_BIT(SPCR, SPE);

	/* Selecting the clock rate */
	SPCR = (SPCR & 0xFC) | ((ConfigPtr->ClockRateSelect) & 0x03);
	SPSR = (SPSR & 0xFE) | ((ConfigPtr->ClockRateSelect) >> 2);
}

/*
 * Description : A Function to set the call back function.
 */
void SPI_setCallBack(void(*a_ptr)(void))
{
	g_SPI_callBackPtr = (volatile void (*)(void))a_ptr;
}


/*
 * Description : A Function to send a byte.
 */
void SPI_sendByte(const uint8_t data)
{
	/* send the data */
	SPDR = data;
	/* busy-waiting the SPIE bit in the SPCR register in case interrupts are disabled */
	if(BIT_IS_CLEAR(SPCR, SPIE))
	{
		while(BIT_IS_CLEAR(SPSR, SPIF));
	}
}

/*
 * Description : A Function to receive a byte.
 */
uint8_t SPI_receiveByte(void)
{
	/* busy-waiting the SPIE bit in case the interrupts are disabled */
	if(BIT_IS_CLEAR(SPCR, SPIE))
	{
		while(BIT_IS_CLEAR(SPSR, SPIF));
	}
	/* read the data */
	return SPDR;
}

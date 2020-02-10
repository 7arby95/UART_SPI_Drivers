/*
 * SwICU.c
 *
 *  Created on: Jan 29, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES ------------------------------------------------*/

#include "SwICU.h"
#include "avr/interrupt.h"


/*- LOCAL MACROS -------------------------------------------*/

#define INT2		5
#define INT0		6
#define INT1		7


/*- GLOBAL VARIABLES ---------------------------------------*/

volatile uint8_t gu8_swIcuRead = 0;
volatile uint8_t gu8_swIcuFlag = 0;


/*- ISR's --------------------------------------------------*/

ISR(INT2_vect)
{
	/* In case of rising edge detection */
	if(BIT_IS_SET(MCUCSR, 6))
	{
		/* Start timer counter */
		SwICU_Start();
		/* Change edge detection to falling edge detection */
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
	}
	/* In case of falling edge detection */
	else if(BIT_IS_CLEAR(MCUCSR, 6))
	{
		/* Read the current timer counter value */
		SwICU_Read(&gu8_swIcuRead);
		/* Change edge detection to rising edge detection */
		SwICU_SetCfgEdge(SwICU_EdgeRising);
		/* Stop the timer counter */
		SwICU_Stop();
		/* Set a flag to represent that the current operation is done */
		gu8_swIcuFlag = 1;
	}
}

/*- APIs IMPLEMENTATION ------------------------------------*/

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
	/* Initializes timer0 in polling mode */
	timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_256, 0, 0, T0_POLLING);

	gpioPinDirection(GPIOB, BIT2, INPUT);
	gpioPinDirection(GPIOD, BIT0, OUTPUT);
	
	/* Enables external int2 */
	SET_BIT(GICR, INT2);
	
	/* Sets the required edge detection type */
	MCUCSR = (MCUCSR & 0xBF) | a_en_inputCaptureEdge;
	
	/* Enables Global Interrupt Enable bit */
	sei();
}

EN_SwICU_Edge_t SwICU_GetCfgEdge(void)
{
	// BLANK Function
	return 0;
}

/*choose the detecting edge*/
void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
	/* Change the required edge detection type to the selected type */
	MCUCSR = (MCUCSR & 0xBF) | a_en_inputCaptureEdge;
}

void SwICU_Read(volatile uint8_t * a_pu8_capt)
{
	/* Reads the current value of the timer0 */
	*a_pu8_capt = timer0Read();
}

void SwICU_Stop(void)
{
	/* Stops the timer0 */
	timer0Stop();
}

void SwICU_Start(void)
{
	/* Starts the timer0 */
	timer0Start();
}

void SwICU_Enable(void)
{
	// BLANK Function
}

void SwICU_Disable(void)
{
	// BLANK Function
}

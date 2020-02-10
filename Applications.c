/*
 * Applications.c
 *
 *  Created on: Jan 18, 2020
 *      Author: Youssef Harby
 */

/*- INCLUDES -----------------------------------------------*/

#include "registers.h"
#include "gpio.h"
#include "softwareDelay.h"
#include "avr/interrupt.h"
#include "led.h"
#include "pushButton.h"
#include "sevenSeg.h"
#include "timers.h"
#include "dcMotor.h"
#include "SwICU.h"
#include "HwPWM.h"
#include "SPI.h"
#include "UART.h"

/*- LOCAL MACROS -------------------------------------------*/




/*- FUNCTION-LIKE MACROS -----------------------------------*/




/*- ENUMS --------------------------------------------------*/

typedef enum En_GpioReq9State_t{
	GO,
	STOP1,
	GET_READY
}En_GpioReq9State_t;


/*- GLOBAL EXTERN VARIABLES --------------------------------*/


/*- APIs PROTOTYPES ----------------------------------------*/

void GPIO_REQ7(void);
void GPIO_REQ8(void);
void GPIO_REQ9(void);

void app_tx(void);
void app_rx(void);

uint8_t flag = 0;

int main(void)
{
	SPI_ConfigType configType =
	{
			SPI_MASTER,
			SPI_INTERRUPT_DISABLED,
			SPI_F_OSC_4
	};

	gpioPinDirection(GPIOA, BIT0, INPUT);

//	softwareDelayMs(200);

	SPI_init(&configType);

	while(1)
	{
		softwareDelayMs(10);
		if(PORTA_PIN & (1 << 0))
		{
			SPI_sendByte(1);
		}else
		{
			SPI_sendByte(0);
		}
	}



//	UART_ConfigType configtype = {
//			UART_ASYNCHRONOUS_MODE,
//			UART_SENDER_RECEIVER_MODE,
//			UART_EIGHT_BITS,
//			UART_PARITY_DISABLED,
//			UART_ONE_STOP_BIT,
//			UART_INTERRUPT_DISABLED
//	};
//
//	softwareDelayMs(5000);
//
//	UART_init(&configtype);
//
//	while(1)
//	{
//		UART_transmit(1);
//		softwareDelayMs(1000);
//	}


//	SPI_ConfigType configType =
//	{
//			SPI_MASTER,
//			SPI_INTERRUPT_DISABLED,
//			SPI_F_OSC_4
//	};
//
//	softwareDelayMs(2000);
//
//	SPI_init(&configType);
//
//	while(1)
//	{
//		softwareDelayMs(100);
//		SPI_sendByte(1);
//	}
}

/*- APIs IMPLEMENTATION ------------------------------------*/

void app_tx(void)
{

}

void app_rx(void)
{
	flag = 1;
}

void app_spi(void)
{

}


void GPIO_REQ7(void)
{
	uint8_t u8_countUpCounter = 0;
	uint32_t u32_delayCounter = 0;

	sevenSegInit(SEG_0);
	sevenSegInit(SEG_1);

	while(1)
	{
		while(u8_countUpCounter <= 99)
		{
			sevenSegEnable(SEG_0);
			sevenSegWrite(SEG_0, ((u8_countUpCounter / 10) % 10));
			softwareDelayMs(1);
			sevenSegDisable(SEG_0);

			sevenSegEnable(SEG_1);
			sevenSegWrite(SEG_1, (u8_countUpCounter % 10));
			softwareDelayMs(1);
			sevenSegDisable(SEG_1);

			u32_delayCounter++;

			if(u32_delayCounter % 469 == 0)
				u8_countUpCounter++;
		}
	}
}


void GPIO_REQ8(void)
{
	uint8_t u8_appCounter = 0, u8_delayDivider = 20;

	Led_Init(LED_1);
	pushButtonInit(BTN_1);

	while(1)
	{
		u8_delayDivider = 20;
		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			while(pushButtonGetStatus(BTN_1) != Released);
			u8_appCounter++;
			while(u8_appCounter > 0)
			{
				Led_On(LED_1);
				while(u8_delayDivider > 0)
				{
					softwareDelayMs(49);
					if(pushButtonGetStatus(BTN_1) == Pressed)
					{
						softwareDelayMs(300);
						u8_delayDivider += 14;
					}
					u8_delayDivider--;
				}
				Led_Off(LED_1);
				u8_appCounter--;
			}
			break;
		}
	}
}



void GPIO_REQ9(void)
{
	uint8_t u8_currentState = GO;

	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);

	while(1)
	{
		switch(u8_currentState)
		{
		case GO:
			Led_On(LED_1);
			Led_Off(LED_2);
			Led_Off(LED_3);
			u8_currentState = STOP1;
			break;
		case STOP1:
			Led_Off(LED_1);
			Led_On(LED_2);
			Led_Off(LED_3);
			u8_currentState = GET_READY;
			break;
		case GET_READY:
			Led_Off(LED_1);
			Led_Off(LED_2);
			Led_On(LED_3);
			u8_currentState = GO;
			break;
		}
		softwareDelayMs(1000);
	}
}

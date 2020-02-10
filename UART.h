/*
 * UART.h
 *
 *  Created on: Feb 9, 2020
 *      Author: Youssef Harby
 */

#ifndef UART_H_
#define UART_H_

/*- INCLUDES ------------------------------------------------*/

#include "registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "avr/interrupt.h"


/*- PREPROCESSOR MACROS -------------------------------------*/

#define MPCM	0
#define U2X		1
#define PE		2
#define DOR		3
#define FE		4
#define UDRE	5
#define TXC		6
#define RXC		7

#define TXB8	0
#define RXB8	1
#define UCSZ2	2
#define TXEN	3
#define RXEN	4
#define UDRIE	5
#define TXCIE	6
#define RXCIE	7

#define UCPOL	0
#define UCSZ0	1
#define UCSZ1	2
#define USBS	3
#define UPM0	4
#define UPM1	5
#define UMSEL	6
#define URSEL	7


/*- ENUMS ---------------------------------------------------*/

typedef enum{
	UART_ASYNCHRONOUS_MODE = 0x00,
	UART_SYNCHRONOUS_MODE = 0x40
}UART_Mode;

typedef enum{
	UART_SENDER_MODE,
	UART_RECEIVER_MODE,
	UART_SENDER_RECEIVER_MODE
}UART_CommunicationMode;

typedef enum{
	UART_INTERRUPT_DISABLED,
	UART_INTERRUPT_ENABLED
}UART_InterruptMode;

typedef enum{
	UART_FIVE_BITS,
	UART_SIX_BITS,
	UART_SEVEN_BITS,
	UART_EIGHT_BITS,
	UART_NINE_BITS = 0x07
}UART_CharacterSize;

typedef enum{
	UART_PARITY_DISABLED = 0x00,
	UART_EVEN_PARITY = 0x20,
	UART_ODD_PARITY = 0x30
}UART_ParityMode;

typedef enum{
	UART_ONE_STOP_BIT = 0x00,
	UART_TWO_STOP_BITS = 0x08
}UART_StopBits;


/*- STRUCTS AND UNIONS --------------------------------------*/

typedef struct{
	UART_Mode mode;
	UART_CommunicationMode communicationMode;
	UART_CharacterSize charSize;
	UART_ParityMode parityMode;
	UART_StopBits stopBits;
	UART_InterruptMode interruptMode;
}UART_ConfigType;


/*- FUNCTION DECLARATIONS -----------------------------------*/

/*
 * Description: A Function to set call back function for TXC Interrupt.
 */
void UART_TXC_setCallBack(void(*local_ptr)(void));

/*
 * Description: A Function to set call back function for RXC Interrupt.
 */
void UART_RXC_setCallBack(void(*local_ptr)(void));

/*
 * Description: A Function to set call back function for UDRE Interrupt.
 */
void UART_UDRE_setCallBack(void(*local_ptr)(void));

/*
 * Description: A Function to Initialize the UART Driver.
 */
void UART_init(const UART_ConfigType* ConfigPtr);

/*
 * Description: A Function to send a byte.
 */
void UART_transmit(const uint8_t data);

/*
 * Description: A Function to receive a byte.
 */
uint8_t UART_receive(void);

#endif /* UART_H_ */

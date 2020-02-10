/*
 * UART_cfg.h
 *
 *  Created on: Feb 9, 2020
 *      Author: Youssef Harby
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_


/*
 * User Configuration Macros
 */

#define USART_BAUDRATE	9600
#define BAUDPRESCALE	((F_CPU / (USART_BAUDRATE * 8UL)) - 1)


#endif /* UART_CFG_H_ */

/*
 * timersConfig.h
 *
 *  Created on: Feb 9, 2020
 *      Author: Youssef Harby
 */

#ifndef TIMERSCONFIG_H_
#define TIMERSCONFIG_H_


/*
 * User Configuration Macros
 */

#define T0_PWM_GPIO	GPIOD
#define T0_PWM_BIT	BIT0

#define T1_PWM_GPIO	GPIOD
#define T1_PWM_BIT	BIT1

#define T2_PWM_GPIO GPIOD
#define T2_PWM_BIT	BIT2


/* Register TCCR0 bit definitions */
#define FOC0 		7
#define WGM00 		6
#define COM01 		5
#define COM00 		4
#define WGM01		3
#define CS02		2
#define CS01		1
#define CS00		0

/* Registers TCCR1A & TCCR1B bit definitions */
#define COM1A1		7
#define COM1A0		6
#define COM1B1		5
#define COM1B0		4
#define FOC1A		3
#define FOC1B		2
#define WGM11		1
#define WGM10		0
#define ICNC1		7
#define ICES1		6
#define WGM13		4
#define WGM12		3
#define CS12		2
#define CS11		1
#define CS10		0

/* Register TCCR2 bit definitions */
#define FOC2 		7
#define WGM20 		6
#define COM21 		5
#define COM20 		4
#define WGM21		3
#define CS22		2
#define CS21		1
#define CS20		0

/* Register TIFR bit definitions */
#define TOV0		0
#define OCF0		1
#define TOV1		2
#define OCF1B		3
#define OCF1A		4
#define ICF1		5
#define TOV2		6
#define OCF2		7

#define TIMER_MS_DIVISION_FACTOR		64000
#define TIMER_US_DIVISION_FACTOR		1000000

#define SW_PWM_DUTY_CYCLE_RESOLUTION	100


#endif /* TIMERSCONFIG_H_ */

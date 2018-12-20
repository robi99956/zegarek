/*
 * led.h
 *
 *  Created on: 11 gru 2018
 *      Author: Robert
 */

#ifndef APPLICATION_USER_LED_LED_H_
#define APPLICATION_USER_LED_LED_H_

typedef enum _led_mode{LED_TIME, LED_IP, LED_ERROR, LED_ERROR_LOCK} LED_mode_t;

void led_init( TIM_HandleTypeDef * htim, SPI_HandleTypeDef * hspi, GPIO_TypeDef * L_gpio, uint16_t L_pin );
void led_set_mode( LED_mode_t _mode );
void led_show_time( RTC_TimeTypeDef * time );
void led_show_error( uint8_t error );
void led_show_ip( char * ip );

#endif /* APPLICATION_USER_LED_LED_H_ */

/*
 * rtc.h
 *
 *  Created on: 28 wrz 2018
 *      Author: Robert
 */

#ifndef APPLICATION_USER_RTC_RTC_H_
#define APPLICATION_USER_RTC_RTC_H_

#include <stdint.h>

typedef struct
{
  uint8_t sek;
  uint8_t min;
  uint8_t godz;
  uint8_t dzien;
  uint8_t mies;
  uint16_t rok;
  uint8_t dzien_tygodnia;
  uint32_t czas_unix;
} CZAS;

void txt_to_czas( const char * buf, const char * pattern, CZAS * czas );
void czas_to_txt( char * buf, const char * pattern, CZAS * czas );

void rtc_module_init( void );

#endif /* APPLICATION_USER_RTC_RTC_H_ */

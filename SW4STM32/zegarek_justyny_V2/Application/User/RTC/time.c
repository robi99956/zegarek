#include <string.h>

#include "rtc.h"

void txt_to_czas( const char * buf, const char * pattern, CZAS * czas )
{
  uint16_t wagi[6] = {1000, 10, 10, 10, 10, 10};
  memset(czas, 0, sizeof(CZAS));

  while( *pattern && *buf )
  {
    switch(*pattern)
    {
    case 'R': czas->rok += wagi[0]*( *buf-'0' );
      wagi[0] /= 10;
      break;
    case 'M': czas->mies += wagi[1]*( *buf-'0' );
      wagi[1] /= 10;
      break;
    case 'D': czas->dzien += wagi[2]*( *buf-'0' );
      wagi[2] /= 10;
      break;
    case 'g': czas->godz += wagi[3]*( *buf-'0' );
      wagi[3] /= 10;
      break;
    case 'm': czas->min += wagi[4]*( *buf-'0' );
      wagi[4] /= 10;
      break;
    case 's': czas->sek += wagi[5]*( *buf-'0' );
      wagi[5] /= 10;
      break;
    }

    buf++;
    pattern++;
  }
}

void czas_to_txt( char * buf, const char * pattern, CZAS * czas )
{
	uint16_t wagi[6] = {1000, 10, 10, 10, 10, 10};

	while( *pattern )
	{
		switch(*pattern)
		{
		case 'R': *buf = czas->rok/wagi[0] + '0';
			czas->rok %= wagi[0];
			wagi[0] /= 10;
		break;
		case 'M': *buf = czas->mies/wagi[1] + '0';
			czas->mies %= wagi[1];
			wagi[1] /= 10;
		break;
		case 'D': *buf = czas->dzien/wagi[2] + '0';
			czas->dzien %= wagi[2];
			wagi[2] /= 10;
		break;
		case 'g': *buf = czas->godz/wagi[3] + '0';
			czas->godz %= wagi[3];
			wagi[3] /= 10;
		break;
		case 'm': *buf = czas->min/wagi[4] + '0';
			czas->min %= wagi[4];
			wagi[4] /= 10;
		break;
		case 's': *buf = czas->sek/wagi[5] + '0';
			czas->sek %= wagi[5];
			wagi[5] /= 10;
		break;
			default: *buf = *pattern;
		}

		buf++;
		pattern++;
	}
}

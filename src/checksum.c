#include "checksum.h"
#include <stdio.h>
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

void checksum( void *dataptr, size_t bytes, char *value )
{
  /* Fletcher32 checksum */
  uint32_t sum1 = 0xffff, sum2 = 0xffff, result;
  uint16_t *data;
  uint8_t *tail;
  size_t words = bytes / 2;

  data = dataptr;
  while (words)
  {
    unsigned tlen = words > 359 ? 359 : words;
    words -= tlen;
    do { sum2 += sum1 += *data++; } while (--tlen);
    sum1 = (sum1 & 0xffff) + (sum1 >> 16);
    sum2 = (sum2 & 0xffff) + (sum2 >> 16);
  }
  if (bytes % 2)
  {
    // Note that the data pointer has been incremented and points
    // to the last value. Set tail to this location and add the last
    // byte to the total.

    tail = data;
    sum2 += sum1 += *tail;
    sum1 = (sum1 & 0xffff) + (sum1 >> 16);
    sum2 = (sum2 & 0xffff) + (sum2 >> 16);
  }

  sum1 = (sum1 & 0xffff) + (sum1 >> 16);
  sum2 = (sum2 & 0xffff) + (sum2 >> 16);
  result = sum2 << 16 | sum1;

  sprintf(value, "%08X", result);
  return value;
}

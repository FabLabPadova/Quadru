#include "utility.h"

/*
  IP: shex const char rappresentation of hexadecimal number in char array.
  IV: len int shex's length.
  OR: shex converted into integer number.
*/
int conv_hex_to_dec(const char * shex, const unsigned int len) {
  unsigned int dec = 0;
  for (unsigned int i = 0; i < len; i++)
    dec += (_pow(16, len - i - 1)) * ( (shex[i] >= '0' && shex[i] <= '9') * (shex[i] - '0') + (shex[i] >= 'A' && shex[i] <= 'F') * (shex[i] - 'A' + 10) );
  return dec;
}//conv_hex_to_dec

//pow function for integer. So, the original one return result minus 1...?
int _pow (unsigned int base, unsigned int exponent) {
  unsigned int ris = 1;
  for (unsigned int i = 0; i < exponent; i++)
    ris *= base;
  return ris;
}

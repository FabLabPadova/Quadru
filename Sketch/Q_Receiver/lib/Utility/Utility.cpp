#include "Utility.h"

unsigned int conv_hex_to_dec(const char *shex, const unsigned int len){
  unsigned int res = 0;
  for (unsigned int i = 0; i<len; i++)
    res = res << 4 | ((shex[i] >= '0' && shex[i] <= '9') ? (shex[i] - '0') : (shex[i] - 'A' + 10));
  return res;
}//conv_hex_to_dec

#include "utility.h"

unsigned int conv_hex_to_dec(const char *shex, const unsigned int len){
  unsigned int res = 0;
  for (unsigned int i = 0; i<len; i++)
    res = res << 4 | ((shex[i] >= '0' && shex[i] <= '9') ? (shex[i] - '0') : (shex[i] - 'A' + 10));
  return res;
}//conv_hex_to_dec

unsigned int * conv_number_array_bin(const int n, const unsigned int len){
  unsigned int arrTemp[len];
  for (unsigned int i = 0; i<len; i++)
    arrTemp[i] = ((n & (1 << i)) != 0);
  return arrTemp;
}//conv_number_array_bin


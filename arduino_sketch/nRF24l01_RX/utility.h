#ifndef UTILITY_H   // if x.h hasn't been included yet...
#define UTILITY_H

/*
  IP: shex const char rappresentation of hexadecimal number in char array.
  IV: len int shex's length.
  OR: shex converted into integer number.
*/
unsigned int conv_hex_to_dec(const char *shex, const unsigned int len);

/*
  IV: n int number to convert.
  IV: len length of final array.
  OR: correspondent array bit rappresentation of n with len length.
*/
unsigned int * conv_number_array_bin(const int n, const unsigned int len);

#endif 

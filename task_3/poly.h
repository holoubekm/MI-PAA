#ifndef POLY_H
#define POLY_H

#include <assert.h>
#include <stdbool.h>

#define byte unsigned char
#define uint unsigned int
#define uint16 unsigned short

#define BYTES_CNT 10
#define BITS_CNT 80


void zero(byte* out);
void copy(byte* out, byte* in);
void shiftl(byte* out);
void shiftr(byte* out);
void addMod(byte* out, byte* a, byte* b);
void mul(byte* out, byte* a, byte* b);
void add(byte* out, byte* a, byte* b);
void subMod(byte* out, byte* a, byte* b);
void sub(byte* out, byte* a, byte* b);
bool getbit(byte* in, byte bit);
int cmp(const byte* a, const byte* b);
bool geprime(byte* a);
void inv(byte* out, byte* in);
void invMonty(byte* out, byte * in);
void neg(byte* out);
void toMonty(byte* out, byte* a);
void fromMonty(byte* out, byte* a);
void print(const byte* in);
void printHex(const byte* in);


extern byte* prime;
extern byte* nprime;
extern byte* r;
extern byte* rInv;
extern byte* num_three;
extern byte* num_two;
extern byte* num_one;
extern byte* num_zero;

extern byte* ECa;
extern byte* ECb;

#endif //POLY_H
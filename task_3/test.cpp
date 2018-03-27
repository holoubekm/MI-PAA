#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

void setPrime(uint primeIndex) {
	switch(primeIndex) {
		case 0:
		//5915587277
		zero(prime);
		prime[4] = 0x01;
		prime[3] = 0x60;
		prime[2] = 0x98;
		prime[1] = 0xB2;
		prime[0] = 0xCD;
		copy(nprime, prime);
		neg(nprime);
		break;
		
		case 1:
		//3367900313
		zero(prime);
		prime[3] = 0xC8;
		prime[2] = 0xBE;
		prime[1] = 0x14;
		prime[0] = 0x99;
		copy(nprime, prime);
		neg(nprime);
		break;

		case 2:
		//48112959837082048697
		prime[8] = 0x02;
		prime[7] = 0x9B;
		prime[6] = 0xB3;
		prime[5] = 0x92;
		prime[4] = 0x0E;
		prime[3] = 0xF5;
		prime[2] = 0xE9;
		prime[1] = 0x58;
		prime[0] = 0xB9;
		copy(nprime, prime);
		neg(nprime);
		break;

		case 3:
		//36413321723440003717
		prime[8] = 0x01;
		prime[7] = 0xF9;
		prime[6] = 0x56;
		prime[5] = 0x1B;
		prime[4] = 0x2E;
		prime[3] = 0x71;
		prime[2] = 0xA7;
		prime[1] = 0xFA;
		prime[0] = 0x85;
		copy(nprime, prime);
		neg(nprime);
		break;

		default:
		printf("Wrong prime index!\n");
		break;
	}
}

void testCmp() {
	byte* a = (byte*)malloc(BYTES_CNT);
	byte* b = (byte*)malloc(BYTES_CNT);
	zero(a);
	zero(b);
	assert(cmp(a, b) == 0);
	a[0] = 0xFF;
	a[8] = 0xFF;
	b[0] = 0xFF;
	b[8] = 0xFF;
	assert(cmp(a, b) == 0);

	zero(a);
	zero(b);
	a[8] = 0xFF;
	assert(cmp(a, b) > 0);

	zero(a);
	zero(b);
	b[8] = 0xFF;
	assert(cmp(a, b) < 0);

	zero(a);
	zero(b);
	a[4] = 0x01;
	a[0] = 0x01;
	b[4] = 0x01;
	assert(cmp(a, b) > 0);

	zero(a);
	zero(b);
	a[4] = 0x01;
	b[4] = 0x01;
	b[0] = 0x01;
	assert(cmp(a, b) < 0);

	zero(a);
	zero(b);
	memset(a, 0xFF, BYTES_CNT);
	memset(b, 0xFF, BYTES_CNT);
	b[0] = 0xFE;
	assert(cmp(a, b) > 0);

	zero(a);
	zero(b);
	memset(a, 0xFF, BYTES_CNT);
	memset(b, 0xFF, BYTES_CNT);
	a[5] = 0x00;
	b[5] = 0x00;
	assert(cmp(a, b) == 0);

	free(b);
	free(a);
}

void testAdd() {
	byte* a = (byte*)malloc(BYTES_CNT);
	byte* b = (byte*)malloc(BYTES_CNT);
	byte* out = (byte*)malloc(BYTES_CNT);

	setPrime(0);
	zero(a);
	a[4] = 0x01;
	a[3] = 0x24;
	a[2] = 0xFC;
	a[1] = 0x62;
	a[0] = 0x0F;
	zero(b);
	b[3] = 0xC5;
	b[2] = 0xA1;
	b[1] = 0x5F;
	b[0] = 0xF1;
	addMod(out, a, b);
	static const byte res1[] = { 0x33, 0x0F, 0x05, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	assert(cmp(out, res1) == 0);

	setPrime(1);
	zero(a);
	a[3] = 0x5C;
	a[2] = 0x3E;
	a[1] = 0x4D;
	a[0] = 0x76;
	zero(b);
	b[3] = 0xC5;
	b[2] = 0xA1;
	b[1] = 0x5F;
	b[0] = 0xF1;
	addMod(out, a, b);
	static const byte res2[] = { 0xCE, 0x98, 0x21, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	assert(cmp(out, res2) == 0);

	setPrime(2);
	zero(a);
	a[8] = 0x02;
	a[7] = 0x10;
	a[6] = 0xE8;
	a[5] = 0xE1;
	a[4] = 0x90;
	a[3] = 0x6F;
	a[2] = 0x8F;
	a[1] = 0xA5;
	a[0] = 0xCE;

	zero(b);
	b[8] = 0x01;
	b[7] = 0x89;
	b[6] = 0x2F;
	b[5] = 0x54;
	b[4] = 0x78;
	b[3] = 0xA7;
	b[2] = 0x9D;
	b[1] = 0x6D;
	b[0] = 0xB3;
	addMod(out, a, b);
	static const byte res3[] = { 0xC8, 0xBA, 0x43, 0x21, 0xFA, 0xA3, 0x64, 0xFE, 0x00, 0x00 };
	assert(cmp(out, res3) == 0);

	free(out);
	free(b);
	free(a);
}


void testSub() {
	byte* a = (byte*)malloc(BYTES_CNT);
	byte* b = (byte*)malloc(BYTES_CNT);
	byte* out = (byte*)malloc(BYTES_CNT);

	setPrime(0);
	zero(a);
	//4915487247
	a[4] = 0x01;
	a[3] = 0x24;
	a[2] = 0xFC;
	a[1] = 0x62;
	a[0] = 0x0F;
	zero(b);
	//3315687409
	b[3] = 0xC5;
	b[2] = 0xA1;
	b[1] = 0x5F;
	b[0] = 0xF1;
	subMod(out, a, b);
	static const byte res1[] = { 0x1E, 0x02, 0x5B, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	assert(cmp(out, res1) == 0);
	subMod(out, b, a);
	static const byte res2[] = { 0xAF, 0xB0, 0x3D, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
	assert(cmp(out, res2) == 0);

	setPrime(1);
	zero(a);
	a[3] = 0x5C;
	a[2] = 0x3E;
	a[1] = 0x4D;
	a[0] = 0x76;
	zero(b);
	b[3] = 0xC5;
	b[2] = 0xA1;
	b[1] = 0x5F;
	b[0] = 0xF1;
	subMod(out, a, b);
	static const byte res3[] = { 0x1E, 0x02, 0x5B, 0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	assert(cmp(out, res3) == 0);
	subMod(out, b, a);
	static const byte res4[] = { 0x7B, 0x12, 0x63, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	assert(cmp(out, res4) == 0);

	setPrime(2);
	zero(a);
	a[8] = 0x02;
	a[7] = 0x10;
	a[6] = 0xE8;
	a[5] = 0xE1;
	a[4] = 0x90;
	a[3] = 0x6F;
	a[2] = 0x8F;
	a[1] = 0xA5;
	a[0] = 0xCE;

	zero(b);
	b[8] = 0x01;
	b[7] = 0x89;
	b[6] = 0x2F;
	b[5] = 0x54;
	b[4] = 0x78;
	b[3] = 0xA7;
	b[2] = 0x9D;
	b[1] = 0x6D;
	b[0] = 0xB3;
	subMod(out, a, b);
	static const byte res5[] = { 0x1B, 0x38, 0xF2, 0xC7, 0x17, 0x8D, 0xB9, 0x87, 0x00, 0x00 };
	assert(cmp(out, res5) == 0); 
	subMod(out, b, a);
	static const byte res6[] = { 0x9E, 0x20, 0xF7, 0x2D, 0xF7, 0x04, 0xFA, 0x13, 0x02, 0x00 };
	assert(cmp(out, res6) == 0); 

	zero(a);
	zero(b);
	a[0] = 0xFF;
	b[0] = 0;
	subMod(out, a, b);
	assert(out[0] == 0xFF);

	free(out);
	free(b);
	free(a);
}

void testShr() {
	byte* a = (byte*)malloc(BYTES_CNT);
	byte* b = (byte*)malloc(BYTES_CNT);

	zero(a);
	a[8] = 0xCA;
	shiftr(a);
	shiftr(a);
	shiftr(a);
	shiftr(a);
	zero(b);
	b[8] = 0x0C;
	b[7] = 0xA0;
	assert(cmp(a, b) == 0);

	zero(a);
	zero(b);
	a[0] = 0x07;
	b[0] = 0x01;
	shiftr(a);
	shiftr(a);
	assert(cmp(a, b) == 0);

	free(b);
	free(a);
}

void testShl() {
	byte* a = (byte*)malloc(BYTES_CNT);
	byte* b = (byte*)malloc(BYTES_CNT);

	zero(a);
	a[8] = 0xCA;
	shiftl(a);
	shiftl(a);
	shiftl(a);
	shiftl(a);
	zero(b);
	b[9] = 0x0C;
	b[8] = 0xA0;
	assert(cmp(a, b) == 0);

	zero(a);
	zero(b);
	a[0] = 0x07;
	b[0] = 0x1C;
	shiftl(a);
	shiftl(a);
	assert(cmp(a, b) == 0);

	free(b);
	free(a);
}

void testGetbit() {
	byte* a = (byte*)malloc(BYTES_CNT);
	memset(a, 0xAA, BYTES_CNT);
	for(uint x = 0; x < BITS_CNT; x++)
		assert(getbit(a, x) == x % 2);
	memset(a, 0xFF, BYTES_CNT);
	for(uint x = 0; x < BITS_CNT; x++)
		assert(getbit(a, x));
	zero(a);
	for(uint x = 0; x < BITS_CNT; x++)
		assert(!getbit(a, x));
	zero(a);
	a[8] = 0xFF;
	assert(getbit(a, 64));
	free(a);
}

void testMul() {
	byte* a = (byte*)malloc(BYTES_CNT);
	byte* b = (byte*)malloc(BYTES_CNT);
	byte* out = (byte*)malloc(BYTES_CNT);

	setPrime(0);
	zero(a);
	//4915487247
	a[4] = 0x01;
	a[3] = 0x24;
	a[2] = 0xFC;
	a[1] = 0x62;
	a[0] = 0x0F;
	zero(b);
	//3315687409
	b[3] = 0xC5;
	b[2] = 0xA1;
	b[1] = 0x5F;
	b[0] = 0xF1;
	mul(out, a, b);
	static const byte res1[] = { 0x42, 0x83, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	assert(cmp(out, res1) == 0);

	setPrime(2);
	zero(a);
	a[8] = 0x02;
	a[7] = 0x10;
	a[6] = 0xE8;
	a[5] = 0xE1;
	a[4] = 0x90;
	a[3] = 0x6F;
	a[2] = 0x8F;
	a[1] = 0xA5;
	a[0] = 0xCE;

	zero(b);
	b[8] = 0x01;
	b[7] = 0x89;
	b[6] = 0x2F;
	b[5] = 0x54;
	b[4] = 0x78;
	b[3] = 0xA7;
	b[2] = 0x9D;
	b[1] = 0x6D;
	b[0] = 0xB3;
	mul(out, a, b);
	static const byte res2[] = { 0xF2, 0xAD, 0xA3, 0xDE, 0x12, 0xE5, 0xB9, 0x09, 0x01, 0x00 };
	assert(cmp(out, res2) == 0);

	free(out);
	free(b);
	free(a);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "test.h"
#include "poly.h"
#include "ec.h"


byte* prime;
byte* nprime;
byte* r;
byte* rInv;
byte* num_three;
byte* num_two;
byte* num_one;
byte* num_zero;

byte* ECa;
byte* ECb;

byte* out;
byte* tmp1;
byte* tmp2;
byte* tmp3;

void ECalloc() {
	prime = (byte*)malloc(BYTES_CNT);
	nprime = (byte*)malloc(BYTES_CNT);
	r = (byte*)malloc(BYTES_CNT);
	rInv = (byte*)malloc(BYTES_CNT);
	num_three = (byte*)malloc(BYTES_CNT);
	num_two = (byte*)malloc(BYTES_CNT);
	num_one = (byte*)malloc(BYTES_CNT);
	num_zero = (byte*)malloc(BYTES_CNT);

	ECa = (byte*)malloc(BYTES_CNT);
	ECb = (byte*)malloc(BYTES_CNT);
	
	out = (byte*)malloc(BYTES_CNT);
	tmp1 = (byte*)malloc(BYTES_CNT);
	tmp2 = (byte*)malloc(BYTES_CNT);
	tmp3 = (byte*)malloc(BYTES_CNT);
}

void ECinit() {
	zero(num_zero);
	zero(num_one);
	*num_one = 1;
	zero(num_two);
	*num_two = 2;
	zero(num_three);
	*num_three = 3;

	zero(out);
	zero(tmp1);
	zero(tmp2);
	zero(tmp3);
	zero(out);

	zero(prime);
	// *prime = 13;
	prime[9] = 0x62;
	prime[8] = 0xCE;
	prime[7] = 0x51;
	prime[6] = 0x77;
	prime[5] = 0x41;
	prime[4] = 0x2A;
	prime[3] = 0xCA;
	prime[2] = 0x89;
	prime[1] = 0x9C;
	prime[0] = 0xF5;

	copy(nprime, prime);
	neg(nprime);

	zero(r);
	zero(rInv);

	zero(ECa);
	// *ECa = 5;
	ECa[9] = 0x39;
	ECa[8] = 0xC9;
	ECa[7] = 0x5E;
	ECa[6] = 0x6D;
	ECa[5] = 0xDD;
	ECa[4] = 0xB1;
	ECa[3] = 0xBC;
	ECa[2] = 0x45;
	ECa[1] = 0x73;
	ECa[0] = 0x3C;

	zero(ECb);
	// *ECb = 4;
	ECb[9] = 0x1F;
	ECb[8] = 0x16;
	ECb[7] = 0xD8;
	ECb[6] = 0x80;
	ECb[5] = 0xE8;
	ECb[4] = 0x9D;
	ECb[3] = 0x5A;
	ECb[2] = 0x1C;
	ECb[1] = 0x0E;
	ECb[0] = 0xD1;
}

void ECdestroy() {
	free(prime);
	free(nprime);
	free(r);
	free(rInv);
	free(num_three);
	free(num_two);
	free(num_one);
	free(num_zero);
	free(ECa);
	free(ECb);
	free(out);
	free(tmp1);
	free(tmp2);
	free(tmp3);
}

int ECcmp(byte* px, byte* py, byte* qx, byte* qy) {
	if(cmp(px, qx) == 0 && cmp(py, qy) == 0)
		return 0;
	return 1;
}

void ECneg(byte* rx, byte* ry) {
	if(cmp(ry, num_zero) != 0)
		sub(ry, prime, ry);
}

void ECalpha(byte* out, byte* px, byte* py, byte* qx, byte* qy) {
	if(ECcmp(px, py, qx, qy) == 0) {
		mul(tmp1, qx, qx);
		mul(tmp2, tmp1, num_three);
		addMod(tmp1, tmp2, ECa);
		addMod(tmp2, qy, qy);
		inv(tmp3, tmp2);
		mul(out, tmp1, tmp3);
	} else {
		subMod(tmp1, py, qy);
		subMod(tmp2, px, qx);
		inv(tmp3, tmp2);
		mul(out, tmp1, tmp3);
	}
}

void ECaddPoint(byte* rx, byte* ry, byte* px, byte* py, byte* qx, byte* qy) {
	if(cmp(px, qx) == 0 && (cmp(py, qy) != 0 || (cmp(py, num_zero) == 0 && cmp(qy, num_zero) == 0))) {
		copy(rx, num_zero);
		copy(ry, num_zero);
		return;
	}

	if(ECcmp(px, py, num_zero, num_zero) == 0) {
		copy(rx, qx);
		copy(ry, qy);
		return;
	}

	if(ECcmp(qx, qy, num_zero, num_zero) == 0) {
		copy(rx, px);
		copy(ry, py);
		return;
	}

	ECalpha(out, px, py, qx, qy);
	mul(tmp1, out, out);
	subMod(rx, tmp1, px);
	subMod(rx, rx, qx);

	subMod(tmp2, qx, rx);
	mul(ry, tmp2, out);
	subMod(ry, ry, qy);
}

// int main(int argc, char* argv[]) {

// 	alloc();

// 	testAdd();
// 	testSub();
// 	testCmp();
// 	testShl();
// 	testShr();
// 	testGetbit();
// 	testMul();

// 	byte* out = (byte*)malloc(BYTES_CNT);
// 	byte* a = (byte*)malloc(BYTES_CNT);
// 	byte* b = (byte*)malloc(BYTES_CNT);

	// byte* ECpx = (byte*)malloc(BYTES_CNT);
	// byte* ECpy = (byte*)malloc(BYTES_CNT);
	// byte* ECqx = (byte*)malloc(BYTES_CNT);
	// byte* ECqy = (byte*)malloc(BYTES_CNT);
	// byte* ECrx = (byte*)malloc(BYTES_CNT);
	// byte* ECry = (byte*)malloc(BYTES_CNT);


// 	init();

// 	zero(ECpx);
// 	// *ECpx = 1;
// 	zero(ECpy);
// 	// *ECpy = 6;
// 	zero(ECqx);
// 	// *ECqx = 2;
// 	zero(ECqy);
// 	// *ECqy = 3;


	// ECpx[9] = 0x31;
	// ECpx[8] = 0x5D;
	// ECpx[7] = 0x4B;
	// ECpx[6] = 0x20;
	// ECpx[5] = 0x1C;
	// ECpx[4] = 0x20;
	// ECpx[3] = 0x84;
	// ECpx[2] = 0x75;
	// ECpx[1] = 0x05;
	// ECpx[0] = 0x7D;

	// ECpy[9] = 0x03;
	// ECpy[8] = 0x5F;
	// ECpy[7] = 0x3D;
	// ECpy[6] = 0xF5;
	// ECpy[5] = 0xAB;
	// ECpy[4] = 0x37;
	// ECpy[3] = 0x02;
	// ECpy[2] = 0x52;
	// ECpy[1] = 0x45;
	// ECpy[0] = 0x0A;

	// ECqx[9] = 0x06;
	// ECqx[8] = 0x79;
	// ECqx[7] = 0x83;
	// ECqx[6] = 0x4C;
	// ECqx[5] = 0xEF;
	// ECqx[4] = 0xB7;
	// ECqx[3] = 0x21;
	// ECqx[2] = 0x5D;
	// ECqx[1] = 0xC3;
	// ECqx[0] = 0x65;

	// ECqy[9] = 0x40;
	// ECqy[8] = 0x84;
	// ECqy[7] = 0xBC;
	// ECqy[6] = 0x50;
	// ECqy[5] = 0x38;
	// ECqy[4] = 0x8C;
	// ECqy[3] = 0x4E;
	// ECqy[2] = 0x6F;
	// ECqy[1] = 0xDF;
	// ECqy[0] = 0xAB;

// 	zero(ECrx);
// 	zero(ECry);

// 	printf("prime: "); printHex(prime);
// 	printf("ECa: "); printHex(ECa);
// 	printf("ECa: "); printHex(ECb);
// 	printf("\n");
// 	printf("ECpx: "); printHex(ECpx);
// 	printf("ECpy: "); printHex(ECpy);
// 	printf("ECqx: "); printHex(ECqx);
// 	printf("ECqy: "); printHex(ECqy);
// 	// ECneg(ECqx, ECqy);
// 	ECaddPoint(ECrx, ECry, ECpx, ECpy, ECpx, ECpy);
// 	ECaddPoint(ECqx, ECqy, ECpx, ECpy, ECrx, ECry);
// 	ECaddPoint(ECrx, ECry, ECpx, ECpy, ECqx, ECqy);
// 	ECaddPoint(ECqx, ECqy, ECpx, ECpy, ECrx, ECry);
// 	printHex(ECqx);
// 	printHex(ECqy);


// 	free(ECpx);
// 	free(ECpy);
// 	free(ECqx);
// 	free(ECqy);
// 	free(ECrx);
// 	free(ECry);

// 	free(out);
// 	free(a);
// 	free(b);

// 	destroy();
// 	return 0;
// }

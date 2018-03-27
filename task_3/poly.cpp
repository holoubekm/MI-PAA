#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "poly.h"

void mulMonty(byte* out, byte* a, byte* b) {
	assert(out != a);
	assert(out != b);

	zero(out);
	for(byte x = 0; x < BITS_CNT; x++) {
		if(getbit(a, x))
			addMod(out, out, b);
		if(getbit(out, 0))
			add(out, out, prime);
		shiftr(out);
	}

	if(geprime(out))
		subMod(out, out, prime);
}

void inv(byte* out, byte* in) {
	assert(cmp(in, prime) < 0);

	byte* u = (byte*)malloc(BYTES_CNT);
	byte* v = (byte*)malloc(BYTES_CNT);
	byte* r = (byte*)malloc(BYTES_CNT);
	byte* s = (byte*)malloc(BYTES_CNT);
	copy(u, prime);
	copy(v, in);
	zero(r);
	zero(s);
	s[0] = 1;
	int k = 0;
	while(cmp(v, num_zero) > 0) {
		if(!getbit(u, 0)) {
			shiftr(u);
			shiftl(s);
		} else if(!getbit(v, 0)) {
			shiftr(v);
			shiftl(r);
		} else if (cmp(u, v) > 0) {
			sub(u, u, v);
			shiftr(u);
			add(r, r, s);
			shiftl(s);
		} else {
			sub(v, v, u);
			shiftr(v);
			add(s, s, r);
			shiftl(r);
		}
		k++;
	}
	if(cmp(r, prime) >= 0)
		sub(r, r, prime);
	sub(r, prime, r);

	while(k > 0) {
		if(!getbit(r, 0)) {
			shiftr(r);
		} else {
			add(r, r, prime);
			shiftr(r);
		}
		k--;
	}
	copy(out, r);
	free(u);
	free(v);
	free(r);
	free(s);
}

void invMonty(byte* out, byte* in) {
	assert(cmp(in, prime) < 0);

	byte* u = (byte*)malloc(BYTES_CNT);
	byte* v = (byte*)malloc(BYTES_CNT);
	byte* r = (byte*)malloc(BYTES_CNT);
	byte* s = (byte*)malloc(BYTES_CNT);
	copy(u, prime);
	copy(v, in);
	zero(r);
	zero(s);
	s[0] = 1;
	int k = 0;
	while(cmp(v, num_zero) > 0) {
		if(!getbit(u, 0)) {
			shiftr(u);
			shiftl(s);
		} else if(!getbit(v, 0)) {
			shiftr(v);
			shiftl(r);
		} else if (cmp(u, v) > 0) {
			sub(u, u, v);
			shiftr(u);
			add(r, r, s);
			shiftl(s);
		} else {
			sub(v, v, u);
			shiftr(v);
			add(s, s, r);
			shiftl(r);
		}
		k++;
	}
	if(cmp(r, prime) >= 0)
		sub(r, r, prime);
	sub(r, prime, r);

	while(k > 7) {
		if(!getbit(r, 0)) {
			shiftr(r);
		} else {
			add(r, r, prime);
			shiftr(r);
		}
		k--;
	}
	// sub(out, prime, r);
	copy(out, r);
	free(u);
	free(v);
	free(r);
	free(s);
}

void toMonty(byte* out, byte* a) {
	mul(out, a, r);
}

void fromMonty(byte* out, byte* a) {
	// mul(out, a, rInv);
	mulMonty(out, a, num_one);
}

void mul(byte* out, byte* a, byte* b) {
	assert(cmp(a, prime) < 0);
	assert(cmp(b, prime) < 0);
	assert(out != a && out != b);

	//Optimise here!
	zero(out);
	for(byte x = BITS_CNT; x > 0; --x) {
		byte i = x - 1;
		shiftl(out);
		if(geprime(out))
			sub(out, out, prime);
		if(getbit(b, i))
			add(out, out, a);
		if(geprime(out))
			sub(out, out, prime);
	}
}

bool getbit(byte* in, byte bit) {
	assert(bit < 80);

	byte i = bit >> 3;
	byte j = bit % 8;
	return in[i] & (1 << j); 
}

void addMod(byte* out, byte* a, byte* b) {
	assert(cmp(a, prime) < 0);
	assert(cmp(b, prime) < 0);
	//Optimise here
	uint16 tmp;
	bool carry = 0;
	for(byte x = 0; x < BYTES_CNT; x++) {
		tmp = ((uint16)a[x]) + b[x] + carry;
		out[x] = (byte)tmp;
		carry = tmp > 0xff;
	}

	if(geprime(out)) {
		carry = 1;
		for(byte x = 0; x < BYTES_CNT; x++) {
			tmp = ((uint16)out[x]) + nprime[x] + carry;
			out[x] = (byte)tmp;
			carry = tmp > 0xff;
		}
	}
}

void add(byte* out, byte* a, byte* b) {
	//Optimise here
	uint16 tmp;
	bool carry = 0;
	for(byte x = 0; x < BYTES_CNT; x++) {
		tmp = ((uint16)a[x]) + b[x] + carry;
		out[x] = (byte)tmp;
		carry = tmp > 0xff;
	}
}


void subMod(byte* out, byte* a, byte* b) {
	assert(cmp(a, prime) < 0);
	assert(cmp(b, prime) < 0);
	//Optimise here
	uint16 tmp;
	bool carry = 1;
	for(byte x = 0; x < BYTES_CNT; x++) {
		tmp = a[x] + ~((uint16)b[x]) + carry;
		out[x] = (byte)tmp;
		carry = tmp <= 0xff;
	}

	if(!carry) {
		for(byte x = 0; x < BYTES_CNT; x++) {
			tmp = ((uint16)out[x]) + prime[x] + carry;
			out[x] = (byte)tmp;
			carry = tmp > 0xff;
		}
	}
}


void sub(byte* out, byte* a, byte* b) {
	assert(cmp(a, b) >= 0);
	//Optimise here
	uint16 tmp;
	bool carry = 1;
	for(byte x = 0; x < BYTES_CNT; x++) {
		tmp = a[x] + ~((uint16)b[x]) + carry;
		out[x] = (byte)tmp;
		carry = tmp <= 0xff;
	}
}

void shiftl(byte* out) {
	//Optimise here
	bool tmp, over = 0;
	for(byte x = 0; x < BYTES_CNT; x++) {
		tmp = out[x] & 0x80;
		out[x] = (out[x] << 1) + over;
		over = tmp;
	}
}


void shiftr(byte* out) {
	//Optimise here
	bool tmp, under = 0;
	for(byte x = BYTES_CNT; x > 0; --x) {
		byte i = x - 1;
		tmp = out[i] & 0x01;
		out[i] = (out[i] >> 1) + (under << 7);
		under = tmp;
	}
}


bool geprime(byte* a) {
	//optimize here using bit operations
	return cmp(a, prime) >= 0;
}

int cmp(const byte* a, const byte* b) {
	uint i;
	for(byte x = BYTES_CNT; x > 0; --x) {
		i = x - 1;
		if(a[i] > b[i])
			return 1;
		else if(a[i] < b[i])
			return -1;
	}
	return 0;
}

void neg(byte* a) {
	for(byte x = 0; x < BYTES_CNT; x++)
		a[x] = ~a[x];
}

void copy(byte* out, byte* in) {
	memcpy(out, in, BYTES_CNT);
}

void zero(byte* out) {
	memset(out, 0x0, BYTES_CNT);
}

void print(const byte* in) {
	for(byte x = 0; x < BYTES_CNT; x++)
		printf("0x%02x %02d -  ", in[x], in[x]);
	printf("\n");
}

void printHex(const byte* in) {
	for(byte x = 0; x < BYTES_CNT; x++)
		printf("0x%02x ", in[x]);
	printf("\n");
}


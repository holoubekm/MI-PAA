/*
	This Project has been modified by Filip Stepanek <filip.stepanek@fit.cvut.cz>,
	FIT-CTU <www.fit.cvut.cz/en> for the purpose of smartcard education 
	using the SOSSE <http://www.mbsks.franken.de/sosse/html/index.html> 
	created by Matthias Bruestle and files 	from the Chair for Embedded Security (EMSEC), 
	Ruhr-University Bochum <http://www.emsec.rub.de/chair/home/>.
*/


#include "example_PRESENT.h"
#include <avr/io.h>

/**
 *	set the trigger PIN
 */
#define set_pin(port, value) ((port)|=(value))
/**
 *	clear the trigger PIN
 */
#define clear_pin(port, value) ((port)&=(value))

/*...*/

unsigned char buffer[16];

void encrypt_present_rounds(unsigned char *plain, unsigned char *cipher, unsigned char *key, const int rounds) {

	// set trigger PIN
	set_pin(DDRB, 0b10100000);
	set_pin(PORTB, 0b10100000);
	
	//... Initialize ...
	uint8_t round_counter = 1;
	
	uint8_t state[8];
	uint8_t round_key[10];

	// add key
	state[0] = plain[0] ^ key[0];
	state[1] = plain[1] ^ key[1];
	state[2] = plain[2] ^ key[2];
	state[3] = plain[3] ^ key[3];
	state[4] = plain[4] ^ key[4];
	state[5] = plain[5] ^ key[5];
	state[6] = plain[6] ^ key[6];
	state[7] = plain[7] ^ key[7];

	// update key
	round_key[9] = key[6] << 5 | key[7] >> 3;
	round_key[8] = key[5] << 5 | key[6] >> 3;
	round_key[7] = key[4] << 5 | key[5] >> 3;
	round_key[6] = key[3] << 5 | key[4] >> 3;
	round_key[5] = key[2] << 5 | key[3] >> 3;
	round_key[4] = key[1] << 5 | key[2] >> 3;
	round_key[3] = key[0] << 5 | key[1] >> 3;
	round_key[2] = key[9] << 5 | key[0] >> 3;
	round_key[1] = key[8] << 5 | key[9] >> 3;
	round_key[0] = key[7] << 5 | key[8] >> 3;

	char var1 = (round_key[0] & 0x0F);
	uint8_t shift = round_key[0] >> 4;
	char var2 = pgm_read_byte(sbox + shift);

	round_key[0] = var1 | var2;

	round_key[7] ^= round_counter >> 1;
	round_key[8] ^= round_counter << 7;

	// substitution and permutation
	cipher[0] = 
		(pgm_read_byte(sbox_pmt_3 + state[0]) & 0xC0) | 
		(pgm_read_byte(sbox_pmt_2 + state[1]) & 0x30) |
		(pgm_read_byte(sbox_pmt_1 + state[2]) & 0x0C) |
		(pgm_read_byte(sbox_pmt_0 + state[3]) & 0x03);
	cipher[1] = 
		(pgm_read_byte(sbox_pmt_3 + state[4]) & 0xC0) | 
		(pgm_read_byte(sbox_pmt_2 + state[5]) & 0x30) |
		(pgm_read_byte(sbox_pmt_1 + state[6]) & 0x0C) | 
		(pgm_read_byte(sbox_pmt_0 + state[7]) & 0x03);

	cipher[2] = 
		(pgm_read_byte(sbox_pmt_0 + state[0]) & 0xC0) | 
		(pgm_read_byte(sbox_pmt_3 + state[1]) & 0x30) |
		(pgm_read_byte(sbox_pmt_2 + state[2]) & 0x0C) |
		(pgm_read_byte(sbox_pmt_1 + state[3]) & 0x03);
	cipher[3] = 
		(pgm_read_byte(sbox_pmt_0 + state[4]) & 0xC0) | 
		(pgm_read_byte(sbox_pmt_3 + state[5]) & 0x30) |
		(pgm_read_byte(sbox_pmt_2 + state[6]) & 0x0C) |
		(pgm_read_byte(sbox_pmt_1 + state[7]) & 0x03);

	cipher[4] = 
		(pgm_read_byte(sbox_pmt_1 + state[0]) & 0xC0) | 
		(pgm_read_byte(sbox_pmt_0 + state[1]) & 0x30) |
		(pgm_read_byte(sbox_pmt_3 + state[2]) & 0x0C) |
		(pgm_read_byte(sbox_pmt_2 + state[3]) & 0x03);
	cipher[5] = 
		(pgm_read_byte(sbox_pmt_1 + state[4]) & 0xC0) | 
		(pgm_read_byte(sbox_pmt_0 + state[5]) & 0x30) |
		(pgm_read_byte(sbox_pmt_3 + state[6]) & 0x0C) |
		(pgm_read_byte(sbox_pmt_2 + state[7]) & 0x03);

	cipher[6] = 
		(pgm_read_byte(sbox_pmt_2 + state[0]) & 0xC0) | 
		(pgm_read_byte(sbox_pmt_1 + state[1]) & 0x30) |
		(pgm_read_byte(sbox_pmt_0 + state[2]) & 0x0C) |
		(pgm_read_byte(sbox_pmt_3 + state[3]) & 0x03);
	cipher[7] = 
		(pgm_read_byte(sbox_pmt_2 + state[4]) & 0xC0) | 
		(pgm_read_byte(sbox_pmt_1 + state[5]) & 0x30) |
		(pgm_read_byte(sbox_pmt_0 + state[6]) & 0x0C) |
		(pgm_read_byte(sbox_pmt_3 + state[7]) & 0x03);

	for (round_counter = 2; round_counter <= rounds; round_counter++) {
		state[0] = cipher[0] ^ round_key[0];
		state[1] = cipher[1] ^ round_key[1];
		state[2] = cipher[2] ^ round_key[2];
		state[3] = cipher[3] ^ round_key[3];
		state[4] = cipher[4] ^ round_key[4];
		state[5] = cipher[5] ^ round_key[5];
		state[6] = cipher[6] ^ round_key[6];
		state[7] = cipher[7] ^ round_key[7];

		cipher[0] = 
			(pgm_read_byte(sbox_pmt_3 + state[0]) & 0xC0) | 
			(pgm_read_byte(sbox_pmt_2 + state[1]) & 0x30) |
			(pgm_read_byte(sbox_pmt_1 + state[2]) & 0x0C) |
			(pgm_read_byte(sbox_pmt_0 + state[3]) & 0x03);
		cipher[1] = 
			(pgm_read_byte(sbox_pmt_3 + state[4]) & 0xC0) | 
			(pgm_read_byte(sbox_pmt_2 + state[5]) & 0x30) |
			(pgm_read_byte(sbox_pmt_1 + state[6]) & 0x0C) | 
			(pgm_read_byte(sbox_pmt_0 + state[7]) & 0x03);

		cipher[2] = 
			(pgm_read_byte(sbox_pmt_0 + state[0]) & 0xC0) | 
			(pgm_read_byte(sbox_pmt_3 + state[1]) & 0x30) |
			(pgm_read_byte(sbox_pmt_2 + state[2]) & 0x0C) |
			(pgm_read_byte(sbox_pmt_1 + state[3]) & 0x03);
		cipher[3] = 
			(pgm_read_byte(sbox_pmt_0 + state[4]) & 0xC0) | 
			(pgm_read_byte(sbox_pmt_3 + state[5]) & 0x30) |
			(pgm_read_byte(sbox_pmt_2 + state[6]) & 0x0C) |
			(pgm_read_byte(sbox_pmt_1 + state[7]) & 0x03);

		cipher[4] = 
			(pgm_read_byte(sbox_pmt_1 + state[0]) & 0xC0) | 
			(pgm_read_byte(sbox_pmt_0 + state[1]) & 0x30) |
			(pgm_read_byte(sbox_pmt_3 + state[2]) & 0x0C) |
			(pgm_read_byte(sbox_pmt_2 + state[3]) & 0x03);
		cipher[5] = 
			(pgm_read_byte(sbox_pmt_1 + state[4]) & 0xC0) | 
			(pgm_read_byte(sbox_pmt_0 + state[5]) & 0x30) |
			(pgm_read_byte(sbox_pmt_3 + state[6]) & 0x0C) |
			(pgm_read_byte(sbox_pmt_2 + state[7]) & 0x03);

		cipher[6] = 
			(pgm_read_byte(sbox_pmt_2 + state[0]) & 0xC0) | 
			(pgm_read_byte(sbox_pmt_1 + state[1]) & 0x30) |
			(pgm_read_byte(sbox_pmt_0 + state[2]) & 0x0C) |
			(pgm_read_byte(sbox_pmt_3 + state[3]) & 0x03);
		cipher[7] = 
			(pgm_read_byte(sbox_pmt_2 + state[4]) & 0xC0) | 
			(pgm_read_byte(sbox_pmt_1 + state[5]) & 0x30) |
			(pgm_read_byte(sbox_pmt_0 + state[6]) & 0x0C) |
			(pgm_read_byte(sbox_pmt_3 + state[7]) & 0x03);

		round_key[5] ^= round_counter << 2; // do this first, which may be faster

		// use state[] for temporary storage
		state[2] = round_key[9];
		state[1] = round_key[8];
		state[0] = round_key[7];

		round_key[9] = round_key[6] << 5 | round_key[7] >> 3;
		round_key[8] = round_key[5] << 5 | round_key[6] >> 3;
		round_key[7] = round_key[4] << 5 | round_key[5] >> 3;
		round_key[6] = round_key[3] << 5 | round_key[4] >> 3;
		round_key[5] = round_key[2] << 5 | round_key[3] >> 3;
		round_key[4] = round_key[1] << 5 | round_key[2] >> 3;
		round_key[3] = round_key[0] << 5 | round_key[1] >> 3;
		round_key[2] = state[2] << 5 | round_key[0] >> 3;
		round_key[1] = state[1] << 5 | state[2] >> 3;
		round_key[0] = state[0] << 5 | state[1] >> 3;

		char var1 = (round_key[0] & 0x0F);
		uint8_t shift = round_key[0] >> 4;
		char var2 = pgm_read_byte(sbox + shift);
		round_key[0] = var1 | var2;
	}

	// if round is not equal to 31, then do not perform the last adding key operation
	// this can be used in constructing PRESENT based algorithm, such as MAC
	if (31 == rounds) {
		cipher[0] ^= round_key[0];
		cipher[1] ^= round_key[1];
		cipher[2] ^= round_key[2];
		cipher[3] ^= round_key[3];
		cipher[4] ^= round_key[4];
		cipher[5] ^= round_key[5];
		cipher[6] ^= round_key[6];
		cipher[7] ^= round_key[7];
	}

	// clear trigger PIN
	clear_pin(PORTB, 0b01011111);

	//... Copy output ...
}



#include "ec.h"
#include "poly.h"

void setup() {
  ECalloc();
  ECinit();
  randomSeed(analogRead(0));
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("Elliptic curve over GF(p)");
}

void printSer(byte* in) {
	for(uint i = 0; i < BYTES_CNT; i++) {
    if(in[i] < 0x10)
     Serial.print('0');
		Serial.print(in[i], HEX);
    Serial.print(' ');
	 }
}

void readSer(byte* out) {
  byte val, cur, state = 0;
  uint i = 0;
  while(i < BYTES_CNT) {
    while(!Serial.available());
    val = Serial.read();
    if(isalnum(val)) {
      if(val >= '0' && val <= '9') {
        if(!state) {
          cur = val - '0';
          state = 1;
        } else {
          cur <<= 4;
          out[i++] = cur | (val - '0');
          state = 0;
        }
      } else if(val >= 'A'&& val <= 'Z') {
        if(!state) {
          cur = val - '7';
          state = 1;
        } else {
          cur <<= 4;
          out[i++] = cur | (val - '7');
          state = 0;
        }
      }
    }
  }
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("prime: ");
  printSer(prime);
  Serial.print("\nEC  a: ");
  printSer(ECa);
  Serial.print("\nEC  b: ");
  printSer(ECb);
  Serial.println();
  
  byte* out  = (byte*)malloc(BYTES_CNT);
  byte* ECpx = (byte*)malloc(BYTES_CNT);
  byte* ECpy = (byte*)malloc(BYTES_CNT);
  byte* ECqx = (byte*)malloc(BYTES_CNT);
  byte* ECqy = (byte*)malloc(BYTES_CNT);

  ECpx[9] = 0x31;
  ECpx[8] = 0x5D;
  ECpx[7] = 0x4B;
  ECpx[6] = 0x20;
  ECpx[5] = 0x1C;
  ECpx[4] = 0x20;
  ECpx[3] = 0x84;
  ECpx[2] = 0x75;
  ECpx[1] = 0x05;
  ECpx[0] = 0x7D;

  ECpy[9] = 0x03;
  ECpy[8] = 0x5F;
  ECpy[7] = 0x3D;
  ECpy[6] = 0xF5;
  ECpy[5] = 0xAB;
  ECpy[4] = 0x37;
  ECpy[3] = 0x02;
  ECpy[2] = 0x52;
  ECpy[1] = 0x45;
  ECpy[0] = 0x0A;

  ECqx[9] = 0x06;
  ECqx[8] = 0x79;
  ECqx[7] = 0x83;
  ECqx[6] = 0x4C;
  ECqx[5] = 0xEF;
  ECqx[4] = 0xB7;
  ECqx[3] = 0x21;
  ECqx[2] = 0x5D;
  ECqx[1] = 0xC3;
  ECqx[0] = 0x65;

  ECqy[9] = 0x40;
  ECqy[8] = 0x84;
  ECqy[7] = 0xBC;
  ECqy[6] = 0x50;
  ECqy[5] = 0x38;
  ECqy[4] = 0x8C;
  ECqy[3] = 0x4E;
  ECqy[2] = 0x6F;
  ECqy[1] = 0xDF;
  ECqy[0] = 0xAB;

  Serial.print("\nFormat: 10 bytes from lower to higher\n");
  Serial.print("Please send values\n");
  readSer(ECpx);
  Serial.print("Px OK\n");
  readSer(ECpy);
  Serial.print("Py OK\n");
  readSer(ECqx);
  Serial.print("Qx OK\n");
  readSer(ECqy);
  Serial.print("Qy OK\n");
  
  Serial.print("\n\nGoing to make the EC great again!\n");
  printSer(ECpx);
  Serial.print("\nPy: ");
  printSer(ECpy);
  Serial.print("\nQx: ");
  printSer(ECqx);
  Serial.print("\nQy: ");
  printSer(ECqy);
  Serial.println();
  
  zero(ECrx);
  zero(ECry);
  ECaddPoint(ECrx, ECry, ECpx, ECpy, ECqx, ECqy);

  Serial.print("R = (P + Q)\n");
  Serial.print("\nDone:\nRx: ");
  printSer(ECrx);
  Serial.print("\nRy: ");
  printSer(ECry);
  Serial.print("\n\nDeallocating...\n");  
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  ECdestroy();

  free(out);
  free(ECpx);
  free(ECpy);
  free(ECqx);
  free(ECqy);
  free(ECrx);
  free(ECry);

  while(true);
}

#include "ec.h"
#include "poly.h"

void setup() {
  ECalloc();
  ECinit();
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("Elliptic curve over GF(p)");
}

void printSer(byte* in) {
  for(uint i = 1; i <= BYTES_CNT; i++) {
    if(in[BYTES_CNT - i] < 0x10)
     Serial.print('0');
    Serial.print(in[BYTES_CNT - i], HEX);
    Serial.print(' ');
   }
}

void readSer(byte* out) {
  byte val, cur, state = 0;
  uint i = 1;
  while(i <= BYTES_CNT) {
    while(!Serial.available());
    val = Serial.read();
    if(isalnum(val)) {
      if(val >= '0' && val <= '9') {
        if(!state) {
          cur = val - '0';
          state = 1;
        } else {
          cur <<= 4;
          out[BYTES_CNT - i++] = cur | (val - '0');
          state = 0;
        }
      } else if(val >= 'A'&& val <= 'Z') {
        if(!state) {
          cur = val - '7';
          state = 1;
        } else {
          cur <<= 4;
          out[BYTES_CNT - i++] = cur | (val - '7');
          state = 0;
        }
      }
    }
  }
}

void loop() {

  toMonty(num_three_monty, num_three);

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("prime: ");
  printSer(prime);
  Serial.print("\nEC  a: ");
  printSer(ECa);
  Serial.print("\nEC  b: ");
  printSer(ECb);
  Serial.println();
  
  byte* ECpx = (byte*)malloc(BYTES_CNT);
  byte* ECpy = (byte*)malloc(BYTES_CNT);
  byte* ECax = (byte*)malloc(BYTES_CNT);
  byte* ECay = (byte*)malloc(BYTES_CNT);
  byte* ECbx = (byte*)malloc(BYTES_CNT);
  byte* ECby = (byte*)malloc(BYTES_CNT);
  byte* ECqx = (byte*)malloc(BYTES_CNT);
  byte* ECqy = (byte*)malloc(BYTES_CNT);
  byte* ka  = (byte*)malloc(BYTES_CNT);

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

  zero(ka);
  for(uint i = 0; i < BYTES_CNT; i++)
    ka[i] = static_cast<byte>(random(256));

  //zero(ka);
  //ka[0] = 0x02;
  
  Serial.print("\n\nGoing to make the EC great again!\nPx: ");
  printSer(ECpx);
  Serial.print("\nPy: ");
  printSer(ECpy);
  Serial.print("\nka: ");
  printSer(ka);

  zero(ECax);
  zero(ECay);
  digitalWrite(LED_BUILTIN, HIGH);
  ECSquareAndMultiply(ECax, ECay, ECpx, ECpy, ka);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("\n(ka*P).x = Ax: ");
  printSer(ECax);
  Serial.print("\n(ka*P).y = Ay: ");
  printSer(ECay);

  zero(ECbx);
  zero(ECby);
  Serial.print("\nPlease send values of (kb * P) == B\n");
  Serial.print("\nFormat: 10 bytes from higher to lower\n");
  readSer(ECbx);
  printSer(ECbx);
  Serial.print("Bx OK\n");
  readSer(ECby);
  printSer(ECby);
  Serial.print("By OK\n");\
  digitalWrite(LED_BUILTIN, HIGH);
  zero(ECqx);
  zero(ECqy);
  ECSquareAndMultiply(ECqx, ECqy, ECbx, ECby, ka);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Q = ka * B\n");
  Serial.print("\nDone:\nQx: ");
  printSer(ECqx);
  Serial.print("\nQy: ");
  printSer(ECqy);
  Serial.print("\n\nDeallocating...\n");  

  ECdestroy();

  free(ECax);
  free(ECay);
  free(ECbx);
  free(ECby);
  free(ECpx);
  free(ECpy);
  free(ECqx);
  free(ECqy);
  free(ka);

  while(true);
}

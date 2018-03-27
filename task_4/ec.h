
void ECalloc();
void ECinit();
void ECdestroy();

void ECaddPoint(byte* rx, byte* ry, byte* px, byte* py, byte* qx, byte* qy);
int ECcmp(byte* px, byte* py, byte* qx, byte* qy);
void ECalpha(byte* out, byte* px, byte* py, byte* qx, byte* qy);
void ECSquareAndMultiply(byte* rx, byte* ry, byte* px, byte* py, byte* exp);
void ECneg(byte* rx, byte* ry);

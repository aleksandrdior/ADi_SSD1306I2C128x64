#include <Wire.h>
#include <ADi_SSD1306I2C128x64.h>
#define X 128  /*  */
#define Y 8  /*   */
unsigned char state[X][Y], frame[8], Ak[2][Y];
//unsigned char block[8] {0x00, 0x78, 0xCC, 0x84, 0x84, 0xCC, 0x78, 0x00};
unsigned char BS[8] {0, 0, 0, 0, 0, 0, 0, 0};
ADi_SSD1306I2C128x64 oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  oled.ledIni();
  oled.clear();
  prnt();
  state[65][4] = 128;
  state[63][4] = 160;
}

void loop() {
  prnt();
  delay (10);
  play();
}

void prnt () {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 16; x++) {
      for (int z = 0; z < 16; z++) {
        frame[z] = state[x * 8 + z][y];
      }
      if (y < Y && x < X / 8) {
        oled.out(frame);
      }
      else {
        oled.out(BS);
      }
    }
  }
}

void play() {
  for (int x = 0; x < X; x++) {
    for (int y = 0; y < Y; y++) {
      Ak[x % 2][y] = 0;
      for (int z = 0; z < 8; z++) {
        unsigned char Mask = 1;
        if (counter(x, y, z) == 2) {
          Ak[x % 2][y] = Ak[x % 2][y] | Mask << z;
        }
      }
    }
    for (int y = 0; y < Y; y++) {
      state[tor(x - 1)][y] = Ak[(x + 1) % 2][y];
    }
  }
}


int counter(int x, int y, int z) {
  int Count = 0;                 /* Счётчик соседей */
  unsigned char Mask = 1;
  if ((state[x][y] & Mask << z)) {      /* Если бит = 1 */
    return -1;
  }
  if (z > 0)(state[x][y] & Mask << (z - 1)) ? Count++ : 1;        /* Сосед сверху */
  (state[x][y] & Mask << (z + 1)) ? Count++ : 1;          /* Сосед снизу */
  (state[tor(x + 1)][y] & Mask << z) ? Count++ : 1;       /* Сосед справа */
  (state[tor(x + 1)][y] & Mask << (z + 1)) ? Count++ : 1; /* Правый нижний */
  if (z > 0)  (state[tor(x + 1)][y] & Mask << (z - 1)) ? Count++ : 1; /* Правый верхний */
  (state[tor(x - 1)][y] & Mask << z) ? Count++ : 1;       /* Сосед слева */
  (state[tor(x - 1)][y] & Mask << (z + 1)) ? Count++ : 1; /* Левый нижний */
  if (z > 0)(state[tor(x - 1)][y] & Mask << (z - 1)) ? Count++ : 1; /* Левый верхний */
  if (z == 7 && y < Y) {
    (state[x][y + 1] & 1 ) ? Count++ : 1;         /* Сосед снизу */
    (state[tor(x + 1)][y + 1] & 1) ? Count++ : 1; /* Правый нижний */
    (state[tor(x - 1)][y + 1] & 1) ? Count++ : 1; /* Левый нижний */
  }
  if (z == 0 && y > 0) {
    (state[x][y - 1] & 128 ) ? Count++ : 1;         /* Сосед сверху */
    (state[tor(x + 1)][y - 1] & 128) ? Count++ : 1; /* Правый верхний */
    (state[tor(x - 1)][y - 1] & 128) ? Count++ : 1; /* Левый верхний */
  }
  return Count;
}

int tor(int x) {
  x < 0 ? x = X - 1 : 0;
  x == X ? x = 0 : 0;
  return x;
}

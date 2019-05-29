#include <Wire.h>
#include <ADi_SSD1306I2C128x64.h>
#define X 128  /* На экран отображается окно шириной 128 бит максимум */
#define Y 8    /* На экране отображается окно высотой до 8 байт; 8х8 бит максимум */
unsigned char state[X][Y], frame[8], Ak[2][Y];
unsigned char BS[8] {0, 0, 0, 0, 0, 0, 0, 0};
ADi_SSD1306I2C128x64 oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  oled.ledIni();
  oled.clear();
  prnt();
  state[112][6] = 144;
  state[111][6] = 96;
  state[2][4] = 144;
  state[3][4] = 96;
  state[31][2] = 72;
  state[32][2] = 48;
  state[10][0] = 1;
  state[11][0] = 2;
  state[12][0] = 2;
  state[13][0] = 1;
  state[100][6] = 128;
  state[101][6] = 64;
  state[102][6] = 64;
  state[103][6] = 128;
}

void loop() {
  prnt();
  // delay (10);
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
  if (z == 7) {
    (state[x][tube(y + 1)] & 1 ) ? Count++ : 1;         /* Сосед снизу */
    (state[tor(x + 1)][tube(y + 1)] & 1) ? Count++ : 1; /* Правый нижний */
    (state[tor(x - 1)][tube(y + 1)] & 1) ? Count++ : 1; /* Левый нижний */
  }
  if (z == 0) {
    (state[x][tube(y - 1)] & 128 ) ? Count++ : 1;         /* Сосед сверху */
    (state[tor(x + 1)][tube(y - 1)] & 128) ? Count++ : 1; /* Правый верхний */
    (state[tor(x - 1)][tube(y - 1)] & 128) ? Count++ : 1; /* Левый верхний */
  }
  return Count;
}

int tor(int x) {
  x < 0 ? x = X - 1 : 0;
  x == X ? x = 0 : 0;
  return x;
}

int tube(int y) {
  y < 0 ? y = Y - 1 : 0;
  y == Y ? y = 0 : 0;
  return y;
}

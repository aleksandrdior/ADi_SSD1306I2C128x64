#include <Wire.h>
#include <ADi_SSD1306I2C128x64.h>
#define X 16    /* ширина экрана */
#define Y 8     /* высота экрана*/
#define XP 32   /* ширина поля */
#define YP 16   /* высота поля*/
bool state[2][XP][YP];
bool k = 0;     /* чётность */
ADi_SSD1306I2C128x64 oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  oled.ledIni();
  oled.clear();
  /* пульсар СР 48-56-72  */
  state[0][14][7] = 1;
  state[0][15][7] = 1;
  state[0][16][7] = 1;
  state[0][17][7] = 1;
  state[0][18][7] = 1;
  state[0][18][8] = 1;
  state[0][14][8] = 1;
}

void loop() {
  prnt();
  delay (200);
  play();
  k = !k;
}

void prnt () {
  for (int y = 0; y < Y; y++) {
    for (int x = 0; x < X; x++) {
      unsigned char block[8] {0, 0, 0, 0, 0, 0, 0, 0};
      for (int z = 0; z < 4; z++) {
        if (state[k][x * 2 + (z > 1)][y * 2 + !(z % 2)] == 1) {
          block[1 + 4 * (z > 1)] += 14 + 210 * !(z % 2);
          block[2 + 4 * (z > 1)] += 10 + 150 * !(z % 2);
          block[3 + 4 * (z > 1)] += 14 + 210 * !(z % 2);
        }
      }
      oled.out(block);
    }
  }
}

void play() {
  /* Правило B3/S23 клетка рождается, если у неё три соседа, и выживает, если у неё два или три соседа */
  bool buf[XP][YP];
  for (int x = 0; x < XP; x++) {
    for (int y = 0; y < YP; y++) {
      int count = counter(k, x, y);
      if (count == 3) state[!k][x][y] = 1;
      else if (count == 2) state[!k][x][y] = state[k][x][y];
      else state[!k][x][y] = 0;
    }
  }
}

int counter(int k, int x, int y) {
  return state[k][x][tube(y - 1)] + state[k][tor(x + 1)][tube(y - 1)] + state[k][tor(x + 1)][y] + state[k][tor(x + 1)][tube(y + 1)] + state[k][x][tube(y + 1)] + state[k][tor(x - 1)][tube(y + 1)] + state[k][tor(x - 1)][y] + state[k][tor(x - 1)][tube(y - 1)];
}

int tor(int x) {
  x < 0 ? x = XP - 1 : 0;
  x == XP ? x = 0 : 0;
  return x;
}

int tube(int y) {
  y < 0 ? y = YP - 1 : 0;
  y == YP ? y = 0 : 0;
  return y;
}

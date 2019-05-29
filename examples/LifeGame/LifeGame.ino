#include <Wire.h>
#include <ADi_SSD1306I2C128x64.h>
#define X 19  /* отображается окно 16х8 */
#define Y 10  /* по периметру массива 0 */
bool state[X][Y], old[X][Y];
unsigned char block[8] {0x00, 0x78, 0xCC, 0x84, 0x84, 0xCC, 0x78, 0x00};
unsigned char BS[8] {0, 0, 0, 0, 0, 0, 0, 0};
ADi_SSD1306I2C128x64 oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  oled.ledIni();
  oled.clear();
  state[10][3] = 1;
  state[10][5] = 1;
  state[6][3] = 1;
  state[5][5] = 1;
}

void loop() {
  prnt();
  //  delay (100);
  play();
}

void prnt () {
  for (int y = 1; y < 9; y++) {
    for (int x = 1; x < 17; x++) {
      if (state[x][y] && y < Y && x < X) {
        oled.out(block);
      }
      else {
        oled.out(BS);
      }
    }
  }
}

void play() {
  for (int x = 1; x < X - 1; x++) {
    for (int y = 1; y < Y - 1; y++) {
      old[x][y] = state[x][y];
      state[x][y] = 0;
    }
  }
  for (int x = 1; x < X - 1; x++) {
    for (int y = 1; y < Y - 1; y++) {
      if ((old[x][y + 1] + old[x][y - 1] + old[x + 1][y] + old[x - 1][y] + old[x + 1][y + 1] + old[x - 1][y - 1] + old[x + 1][y - 1] + old[x - 1][y + 1]) == 2) {
        state[x][y] = !old[x][y];
      }
    }
  }
}

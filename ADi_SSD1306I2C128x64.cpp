#include <ADi_SSD1306I2C128x64.h>

ADi_SSD1306I2C128x64::ADi_SSD1306I2C128x64() {};

void ADi_SSD1306I2C128x64::ledIni() {
  for (int n = 0; n < sizeof(ledComIni); n++) {
    Wire.beginTransmission(SSD1306_Address);
    Wire.write(SSD1306_Command_Mode);
    Wire.write(ledComIni[n]);
    Wire.endTransmission();
  }
}

void ADi_SSD1306I2C128x64::out(unsigned char dim[8]) {
  Wire.beginTransmission(SSD1306_Address);
  Wire.write(SSD1306_Dats_Mode);
  for (int n = 0; n < 8; n++)
    Wire.write(dim[n]);
  Wire.endTransmission();
}

void ADi_SSD1306I2C128x64::clear() {
  unsigned char blBlock[8] {0, 0, 0, 0, 0, 0, 0, 0};
  for (int n = 0; n < 128; n++) {
    this->out(blBlock);
  }
}

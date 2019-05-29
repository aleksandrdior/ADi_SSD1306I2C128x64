#ifndef ADI_SSD1306I2C128x64_H
#define ADI_SSD1306I2C128x64_H

#include <Wire.h>

#define SSD1306_Address             0x3C
#define SSD1306_Command_Mode        0x80
#define SSD1306_Dats_Mode           0x40
#define SSD1306_MEMORYMODE          0x20 // 2 byte Автоматическая адресация
#define SSD1306_COLUMNADDR          0x21 // 3 byte Адрес колонки
#define SSD1306_PAGEADDR            0x22 // 3 byte Адрес строки (высота строки 8 px)
#define SSD1306_SETSTARTLINE        0x40 // 1 byte See datasheet
#define SSD1306_SETCONTRAST         0x81 // 2 byte Контрастность
#define SSD1306_CHARGEPUMP          0x8D // 2 byte Умножитель напряжения
#define SSD1306_SEGREMAP            0xA1 // 1 byte Развёртка слева/направо
#define SSD1306_DISPLAYALLON_RESUME 0xA4 // 1 byte отображение содержимого RAM
#define SSD1306_NORMALDISPLAY       0xA6 // 1 byte Нет инверсии
#define SSD1306_SETMULTIPLEX        0xA8 // 2 byte See datasheet
#define SSD1306_DISPLAYOFF          0xAE // 1 byte Выключить дисплей
#define SSD1306_DISPLAYON           0xAF // 1 byte Дисплей включен
#define SSD1306_COMSCANDEC          0xC8 // 1 byte Развёртка сверху/вниз
#define SSD1306_SETDISPLAYOFFSET    0xD3 // 2 byte See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5 // 2 byte Частота обновления
#define SSD1306_SETCOMPINS          0xDA // 2 byte Разрешение 0x02-128x32, 0x12-128x64

class ADi_SSD1306I2C128x64 {
  public:
    ADi_SSD1306I2C128x64();
    void ledIni();
    void out(unsigned char dim[8]);
    void clear();
  private:
    unsigned char ledComIni[26] {
      SSD1306_SETMULTIPLEX, 0x3F,
      SSD1306_SETDISPLAYOFFSET, 0x00,
      SSD1306_SETSTARTLINE,
      SSD1306_MEMORYMODE, 0x00,
      SSD1306_COLUMNADDR, 0x00, 0x7F,
      SSD1306_PAGEADDR, 0x00, 0x07,
      SSD1306_SEGREMAP,
      SSD1306_COMSCANDEC,
      SSD1306_SETCOMPINS, 0x12,
      SSD1306_SETCONTRAST, 0x7F,
      SSD1306_NORMALDISPLAY,
      SSD1306_SETDISPLAYCLOCKDIV, 0x20,
      SSD1306_CHARGEPUMP, 0x14,
      SSD1306_DISPLAYALLON_RESUME,
      SSD1306_DISPLAYON
    };
};

# endif /* ADI_SSD1306I2C128x64_H */

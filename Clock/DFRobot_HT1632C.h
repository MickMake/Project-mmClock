/*!
 * @file DFRobot_HT1632.h
 * @brief DFRobot's DFRobot_HT1632C
 * @n DFRobot's LED matrix driver;
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [yuxiang](1137717512@qq.com)
 * @version  V1.0
 * @date  2017-03-30
 */
#ifndef DFROBOT_HT1632C_H_
#define DFROBOT_HT1632C_H_

#if(ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#define FONT_5X4_HEIGHT  5
#define FONT_8X4_HEIGHT  8

#define FONT5X4  0
#define FONT8X4  1


#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

#define DFROBOT_HT1632_READ  0x06
#define DFROBOT_HT1632_WRITE 0x05
#define DFROBOT_HT1632_COMMAND 0x04

#define DFROBOT_HT1632_SYS_DIS 0x00
#define DFROBOT_HT1632_SYS_EN 0x01

#define DFROBOT_HT1632_LED_OFF 0x02
#define DFROBOT_HT1632_LED_ON 0x03

#define DFROBOT_HT1632_BLINK_OFF 0x08
#define DFROBOT_HT1632_BLINK_ON 0x09

#define DFROBOT_HT1632_SLAVE_MODE 0x10
#define DFROBOT_HT1632_MASTER_MODE 0x14

#define DFROBOT_HT1632_INT_RC 0x18
#define DFROBOT_HT1632_EXT_CLK 0x1C

#define DFROBOT_HT1632_PWM_CONTROL 0xA0

#define DFROBOT_HT1632_COMMON_8NMOS  0x20
#define DFROBOT_HT1632_COMMON_16NMOS  0x24
#define DFROBOT_HT1632_COMMON_8PMOS  0x28
#define DFROBOT_HT1632_COMMON_16PMOS  0x2C

#define WIDTHSIZE 24
#define HEIGHTSIZE 8
#define PIXELS_PER_BYTE 8

#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#define GET_ADDR_FROM_X_Y(_x,_y) ((_x)*((HEIGHTSIZE)/(PIXELS_PER_BYTE))+(_y)/(PIXELS_PER_BYTE))

class DFRobot_HT1632C{
public:
	DFRobot_HT1632C(uint8_t data, uint8_t wr, uint8_t RD, uint8_t cs);
	DFRobot_HT1632C(uint8_t data, uint8_t wr, uint8_t cs);
	
	void begin(void);
	void clrPixel(uint16_t i);
  void setPixel(uint16_t i);
	
	void setPixel(uint8_t x, uint8_t y);
	void clrPixel(uint8_t x, uint8_t y);

  void isBlinkEnable(boolean state);
	void isLedOn(boolean state);
  void setPwm(uint8_t pwm);

  void clearScreen();
  void fillScreen();
  void writeScreen();
  void dumpScreen();
	void inLowpower(boolean state);
	
	void drawLine(uint8_t xStart, uint8_t yStart, uint8_t xStop, uint8_t yStop);
	void clrLine(uint8_t xStart, uint8_t yStart, uint8_t xStop, uint8_t yStop);
	
	int getTextWidth(const char text [], int font_end [], uint8_t font_height, uint8_t gutter_space=1);
	
	void drawText(const char text [], int x, int y, const byte font [], int font_end [], uint8_t font_height, uint8_t gutter_space = 1);
	void drawTextStr(const char text [], int x, int y, const byte font [], int font_end [], uint8_t font_height, uint8_t gutter_space = 1);
	
	void setCursor(uint8_t x, uint8_t y);
	void setCursorIndex(uint8_t x, uint8_t y);
	void setFont(uint8_t value);
	
	void print(char value);
	void print(uint8_t value, int base = DEC);
	
	void print(int, int = DEC);
  void print(unsigned int, int = DEC);
		
	void print(const char value[]);
	void printNumber(unsigned long n, uint8_t base);

	void print(double, uint8_t = 2);
	void print(float, uint8_t = 2);
	
	void print(const char str[], uint16_t speed);
	void printStr(const char str[], uint8_t value=0);

private:
	char* strBuffer;
	uint8_t length;
	uint8_t xIndex;
  uint8_t width, height;
	uint8_t xCoordinate, yCoordinate, fontValue;
	uint8_t data_t, cs_t, wr_t, rd_t;
	uint8_t matrix[24]; //24*8/8
	char* matrices;
	void writeCommand(uint8_t cmd);
	void writeBits(uint16_t data, uint8_t length);
	void writeRAM(uint8_t addr, uint8_t data);
	
	void doLength(const char text[]);
	
	void drawImage(const byte * img, uint8_t width_t, uint8_t height_t, int8_t x, int8_t y, int img_offset);
	void drawImageStr(const byte * img, uint8_t width_t, uint8_t height_t, int8_t x, int8_t y, int img_offset);
	int getCharWidth(int font_end [], uint8_t font_height, uint8_t font_index);
	int getCharOffset(int font_end [], uint8_t font_index);
};


extern const byte FONT_8X4 [] PROGMEM;
extern int FONT_8X4_END [];

#endif

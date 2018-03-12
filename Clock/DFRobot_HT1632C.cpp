/*!
 * @file DFRobot_HT1632.cpp
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
#include "DFRobot_HT1632C.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*
const byte FONT_5X4 [] PROGMEM = {
    0b00000000,  //  
    0b11101000,  // !
    0b11000000, 0b00000000, 0b11000000,  // "
    0b01010000, 0b11111000, 0b01010000, 0b11111000, 0b01010000,  // #
    0b00000000, 0b00000000, 0b00000000, 0b00000000,  // $
    0b11001000, 0b11010000, 0b00100000, 0b01011000, 0b10011000,  // %
    0b01010000, 0b10101000, 0b10011000, 0b01011000,  // &
    0b11000000,  // '
    0b01110000, 0b10001000,  // (
    0b10001000, 0b01110000,  // )
    0b10100000, 0b01000000, 0b10100000,  // *
    0b00100000, 0b00100000, 0b11111000, 0b00100000, 0b00100000,  // +
    0b00001000, 0b00010000,  // ,
    0b00100000, 0b00100000, 0b00100000,  // -
    0b00001000,  // .
    0b00001000, 0b00110000, 0b01100000, 0b10000000,  // /
    0b01110000, 0b10001000, 0b01110000,  // 0
    0b01001000, 0b11111000, 0b00001000,  // 1
    0b01001000, 0b10011000, 0b10101000, 0b01001000,  // 2
    0b10101000, 0b10101000, 0b01010000,  // 3
    0b00110000, 0b01010000, 0b11111000, 0b00010000,  // 4
    0b11101000, 0b10101000, 0b10110000,  // 5
    0b01110000, 0b10101000, 0b10101000, 0b00010000,  // 6
    0b10000000, 0b10111000, 0b10100000, 0b11000000,  // 7
    0b01010000, 0b10101000, 0b10101000, 0b01010000,  // 8
    0b01000000, 0b10100000, 0b10101000, 0b01110000,  // 9
    0b01010000,  // :
    0b00001000, 0b01010000,  // ;
    0b00100000, 0b01010000, 0b10001000,  // <
    0b01010000, 0b01010000, 0b01010000,  // =
    0b10001000, 0b01010000, 0b00100000,  // >
    0b01000000, 0b10000000, 0b10011000, 0b01100000,  // ?
    0b01110000, 0b10000000, 0b10110000, 0b10101000, 0b11110000,  // @
    0b01111000, 0b10100000, 0b10100000, 0b01111000,  // A
    0b11111000, 0b10101000, 0b01010000,  // B
    0b01110000, 0b10001000, 0b10001000, 0b01010000,  // C
    0b11111000, 0b10001000, 0b01110000,  // D
    0b11111000, 0b10101000, 0b10001000,  // E
    0b11111000, 0b10100000, 0b10100000,  // F
    0b01110000, 0b10001000, 0b10011000, 0b01010000,  // G
    0b11111000, 0b00100000, 0b00100000, 0b11111000,  // H
    0b10001000, 0b11111000, 0b10001000,  // I
    0b10010000, 0b10001000, 0b11110000,  // J
    0b11111000, 0b00100000, 0b01010000, 0b10001000,  // K
    0b11111000, 0b00001000, 0b00001000,  // L
    0b11111000, 0b01000000, 0b00100000, 0b01000000, 0b11111000,  // M
    0b11111000, 0b01000000, 0b00100000, 0b00010000, 0b11111000,  // N
    0b01110000, 0b10001000, 0b10001000, 0b01110000,  // O
    0b11111000, 0b10100000, 0b01000000,  // P
    0b01110000, 0b10001000, 0b10001000, 0b10010000, 0b01101000,  // Q
    0b11111000, 0b10100000, 0b01011000,  // R
    0b01001000, 0b10101000, 0b10101000, 0b10010000,  // S
    0b10000000, 0b11111000, 0b10000000,  // T
    0b11110000, 0b00001000, 0b00001000, 0b11110000,  // U
    0b11000000, 0b00110000, 0b00001000, 0b00110000, 0b11000000,  // V
    0b11110000, 0b00001000, 0b00110000, 0b00001000, 0b11110000,  // W
    0b11011000, 0b00100000, 0b11011000,  // X
    0b11000000, 0b00111000, 0b11000000,  // Y
    0b10011000, 0b10101000, 0b10101000, 0b11001000,  // Z
    0b11111000, 0b10001000,  // [
    0b10000000, 0b01100000, 0b00110000, 0b00001000,  // \
    0b10001000, 0b11111000,  // ]
    0b01000000, 0b10000000, 0b01000000,  // ^
    0b00001000, 0b00001000, 0b00001000,  // _
};

int FONT_5X4_END [] = {
    1,   2,   5,  10,  14,  19,  23,  24,
   26,  28,  31,  36,  38,  41,  42,  46,
   49,  52,  56,  59,  63,  66,  70,  74,
   78,  82,  83,  85,  88,  91,  94,  98,
  103, 107, 110, 114, 117, 120, 123, 127,
  131, 134, 137, 141, 144, 149, 154, 158,
  161, 166, 169, 173, 176, 180, 185, 190,
  193, 196, 200, 202, 206, 208, 211, 214
};
*/
const byte FONT_8X4 [] PROGMEM = {
  0b00000000,                                                   // SPACE   1
  0b01110000, 0b11111101, 0b01110000,                           // !			 4
  0b11000000, 0b00000000, 0b11000000,                           // "				7
  0b00100100, 0b11111111, 0b00100100, 0b11111111, 0b00100100,   // #				12
  0b00100100, 0b01010010, 0b11011011, 0b01001010, 0b00100100,   // $				17
  0b11000001, 0b11000110, 0b00011000, 0b01100011, 0b10000011,   // %				22
  0b01101110, 0b10010001, 0b10010010, 0b01100101,               // &				26
  0b11000000,                                                   // '				27
  0b00111100, 0b01000010, 0b10000001,                           // (				30
  0b10000001, 0b01000010, 0b00111100,                           // )				33
  0b10100000, 0b01000000, 0b10100000,                           // *				36
  0b00001000, 0b00001000, 0b00111110, 0b00001000, 0b00001000,   // +				41
  0b00000001, 0b00000010,                                       // ,				43
  0b00001000, 0b00001000, 0b00001000,                           // -				46
  0b00000001,                                                   // .				47
  0b00000011, 0b00001100, 0b00110000, 0b11000000,               /* / */
  0b01111110, 0b10110001, 0b10001101, 0b01111110,               // 0
  0b01000001, 0b11111111, 0b00000001,                           // 1
  0b01000011, 0b10000101, 0b10001001, 0b01110001,               // 2
  0b01000010, 0b10001001, 0b10001001, 0b01110110,               // 3
  0b00011100, 0b00100100, 0b01001111, 0b10000100,               // 4
  0b11110001, 0b10010001, 0b10010001, 0b10001110,               // 5
  0b01111110, 0b10001001, 0b10001001, 0b01000110,               // 6
  0b10000000, 0b10000111, 0b10011000, 0b11100000,               // 7
  0b01110110, 0b10001001, 0b10001001, 0b01110110,               // 8
  0b01110010, 0b10001001, 0b10001001, 0b01111110,               // 9
  0b00100010,                                                   // :
  0b00000001, 0b00100010,                                       // ;
  0b00011000, 0b00100100, 0b01000010, 0b10000001,               // <
  0b00010100, 0b00010100, 0b00010100, 0b00010100,               // =
  0b10000001, 0b01000010, 0b00100100, 0b00011000,               // >
  0b01000000, 0b10001101, 0b10001000, 0b01110000,               // ?
  0b01111110, 0b10000001, 0b10111001, 0b10000101, 0b01111100,   // @
  0b01111111, 0b10001000, 0b10001000, 0b01111111,               // A
  0b11111111, 0b10001001, 0b10001001, 0b01110110,               // B
  0b01111110, 0b10000001, 0b10000001, 0b01000010,               // C
  0b11111111, 0b10000001, 0b10000001, 0b01111110,               // D
  0b11111111, 0b10001001, 0b10001001, 0b10000001,               // E
  0b11111111, 0b10010000, 0b10010000, 0b10000000,               // F
  0b01111110, 0b10000001, 0b10001001, 0b01001110,               // G
  0b11111111, 0b00001000, 0b00001000, 0b11111111,               // H
  0b10000001, 0b11111111, 0b10000001,                           // I
  0b10000110, 0b10000001, 0b10000001, 0b11111110,               // J
  0b11111111, 0b00010000, 0b00101000, 0b11000111,               // K
  0b11111111, 0b00000001, 0b00000001, 0b00000001,               // L
  0b01111111, 0b11000000, 0b00110000, 0b11000000, 0b01111111,   // M
  0b11111111, 0b01100000, 0b00011000, 0b00000110, 0b11111111,   // N
  0b01111110, 0b10000001, 0b10000001, 0b01111110,               // O
  0b11111111, 0b10001000, 0b10001000, 0b01110000,               // P
  0b01111110, 0b10000001, 0b10000101, 0b10000010, 0b01111101,   // Q
  0b11111111, 0b10001000, 0b10001100, 0b01110011,               // R
  0b01100010, 0b10010001, 0b10001001, 0b01000110,               // S
  0b10000000, 0b11111111, 0b10000000,                           // T
  0b11111110, 0b00000001, 0b00000001, 0b11111110,               // U
  0b11111110, 0b00000001, 0b00000110, 0b11111000,               // V
  0b11111100, 0b00000011, 0b00011100, 0b00000011, 0b11111100,   // W
  0b10000001, 0b01100110, 0b00011000, 0b01100110, 0b10000001,   // X
  0b11000000, 0b00110000, 0b00001111, 0b00110000, 0b11000000,   // Y
  0b10000011, 0b10001101, 0b10110001, 0b11000001,               // Z
  0b11111111, 0b10000001,                                       // [
  0b11000000, 0b00110000, 0b00001100, 0b00000011,               /* \ */
  0b10000001, 0b11111111,                                       // ]
  0b01000000, 0b10000000, 0b01000000,                           // ^
  0b00000001, 0b00000001, 0b00000001, 0b00000001,               // _
};

int FONT_8X4_END [] = {
       1,   4,   7,  12,  17,  22,  26,  27,
      30,  33,  36,  41,  43,  46,  47,  51,
      55,  58,  62,  66,  70,  74,  78,  82,
      86,  90,  91,  93,  97, 101, 105, 109,
     114, 118, 122, 126, 130, 134, 138, 142,
     146, 149, 153, 157, 161, 166, 171, 175,
     179, 184, 188, 192, 195, 199, 203, 208,
     213, 218, 222, 224, 228, 230, 233, 237
};

DFRobot_HT1632C::DFRobot_HT1632C(uint8_t data, uint8_t wr, uint8_t RD, uint8_t cs){
	data_t = data;
	cs_t = cs;
	wr_t = wr;
	rd_t = rd_t;
	
	for(uint8_t i=0; i < 24; i++){
		matrix[i] = 0;
	}
	matrix[0] = 0x40;
}

DFRobot_HT1632C::DFRobot_HT1632C(uint8_t data, uint8_t wr, uint8_t cs){
	data_t = data;
	cs_t = cs;
	wr_t = wr;
	
	for(uint8_t i=0; i < 24; i++){
		matrix[i] = 0;
	}
	matrix[0] = 0x40;
}

void DFRobot_HT1632C::begin(){
	pinMode(cs_t, OUTPUT); 
  pinMode(wr_t, OUTPUT); 
  pinMode(data_t, OUTPUT);
	
	digitalWrite(cs_t, HIGH);
	digitalWrite(wr_t, HIGH);
	
	writeCommand(DFROBOT_HT1632_SYS_EN);
  writeCommand(DFROBOT_HT1632_LED_ON);
  writeCommand(DFROBOT_HT1632_BLINK_OFF);
  writeCommand(DFROBOT_HT1632_MASTER_MODE);
  writeCommand(DFROBOT_HT1632_INT_RC);
  writeCommand(DFROBOT_HT1632_COMMON_16NMOS);
  writeCommand(DFROBOT_HT1632_PWM_CONTROL | 0xF);
	
	width = 24;
	height = 8;
	xCoordinate = 0;
	yCoordinate = 0;
	fontValue = FONT8X4;
}


void DFRobot_HT1632C::writeCommand(uint8_t cmd){
	uint16_t str = 0;
	str = DFROBOT_HT1632_COMMAND;
	str <<= 8; 
	str |= cmd;
	str <<= 1;
	
	digitalWrite(cs_t, LOW);
	writeBits(str, 12);
	digitalWrite(cs_t, HIGH);
}

void DFRobot_HT1632C::writeBits(uint16_t data, uint8_t length){
	pinMode(data_t, OUTPUT);
	
	for(uint8_t i=length; i>0; i--){  
		digitalWrite(wr_t, LOW);
		if(data & _BV(i-1)){		
			digitalWrite(data_t, HIGH);
		}else{
			digitalWrite(data_t, LOW);
		}
		digitalWrite(wr_t, HIGH);
	}
	
	pinMode(data_t, INPUT);
}

void DFRobot_HT1632C::writeRAM(uint8_t addr, uint8_t data){
	uint16_t str = DFROBOT_HT1632_WRITE;
	str <<= 7;
	str |= addr &0x7f;
	str <<= 4;
	str |= data & 0xf;
	
	digitalWrite(cs_t, LOW);
	writeBits(str, 14);
	digitalWrite(cs_t, HIGH);
}


void DFRobot_HT1632C::writeScreen(){
	digitalWrite(cs_t, LOW);
	writeBits(DFROBOT_HT1632_WRITE,3);	
	writeBits(0, 7);									
	for(uint8_t i=0; i<24; i++){	
		uint16_t str = matrix[i];		
		str <<= 8;  
		writeBits(str, 16);
	}
	digitalWrite(cs_t, HIGH);
}

void DFRobot_HT1632C::fillScreen(){
	for (uint8_t i=0; i<24; i++) {
    matrix[i] = 0xFF;
  }
  this->writeScreen();
}

void DFRobot_HT1632C::clearScreen() {
  for (uint8_t i=0; i<24; i++) {
    matrix[i] = 0;
  }
	free(matrices);
	matrices = NULL;
  this->writeScreen();
}

void DFRobot_HT1632C::isBlinkEnable(boolean state){
	if(state){
		writeCommand(DFROBOT_HT1632_BLINK_ON);
	}else{
		writeCommand(DFROBOT_HT1632_BLINK_OFF);
	}
}

void DFRobot_HT1632C::isLedOn(boolean state){
	if(state){
		writeCommand(DFROBOT_HT1632_LED_ON);
	}else{
		writeCommand(DFROBOT_HT1632_LED_OFF);
	}
}

void DFRobot_HT1632C::inLowpower(boolean state){
	if(state){
		writeCommand(DFROBOT_HT1632_SYS_DIS);
	}else{
		writeCommand(DFROBOT_HT1632_SYS_EN);
	}
}

void DFRobot_HT1632C::setPixel(uint16_t i){
	uint8_t d = _BV(i%8);
	if(d & 0x01)	d = 0x80;
	else if(d & 0x02) d = 0x40;
	else if(d & 0x04) d = 0x20;
	else if(d & 0x08) d = 0x10;
	else if(d & 0x10) d = 0x08;
	else if(d & 0x20) d = 0x04;
	else if(d & 0x40) d = 0x02;
	else if(d & 0x80) d = 0x01;
	
	matrix[i/8] |= d;
}

void DFRobot_HT1632C::clrPixel(uint16_t i){
	uint8_t d = _BV(i%8);
	if(d & 0x01)	d = 0x80;
	else if(d & 0x02) d = 0x40;
	else if(d & 0x04) d = 0x20;
	else if(d & 0x08) d = 0x10;
	else if(d & 0x10) d = 0x08;
	else if(d & 0x20) d = 0x04;
	else if(d & 0x40) d = 0x02;
	else if(d & 0x80) d = 0x01;
	
	matrix[i/8] &= ~d;
}

void DFRobot_HT1632C::setPixel(uint8_t x, uint8_t y){
	if((x<0) || (x>=width) || (y<0) || (y>=height))	return;
	
	matrix[x] |= 0x80>>y;
}

void DFRobot_HT1632C::clrPixel(uint8_t x, uint8_t y){
	if((x<0) || (x>=width) || (y<0) || (y>=height))	return;
	
	matrix[x] &= ~(0x80>>y);
}

void DFRobot_HT1632C::setPwm(uint8_t value){
	if(value > 15) value = 15;
			writeCommand(DFROBOT_HT1632_PWM_CONTROL | value);
}

void DFRobot_HT1632C::drawLine(uint8_t xStart, uint8_t yStart, uint8_t xStop, uint8_t yStop){
	int16_t steep = abs(yStop - yStart) > abs(xStop - xStart);
  if (steep) {
    _swap_int16_t(xStart, yStart);
    _swap_int16_t(xStop, yStop);
  }

  if (xStart > xStop) {
    _swap_int16_t(xStart, xStop);
    _swap_int16_t(yStart, yStop);
  }

  int16_t dx, dy;
  dx = xStop - xStart;
  dy = abs(yStop - yStart);

  int16_t err = dx / 2;
  int16_t ystep;

  if (yStart < yStop) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; xStart<=xStop; xStart++) {
    if (steep) {
      setPixel(yStart, xStart);
    } else {
      setPixel(xStart, yStart);
    }
    err -= dy;
    if (err < 0) {
      yStart += ystep;
      err += dx;
    }
  }
}

void DFRobot_HT1632C::clrLine(uint8_t xStart, uint8_t yStart, uint8_t xStop, uint8_t yStop){
	int16_t steep = abs(yStop - yStart) > abs(xStop - xStart);
  if (steep) {
    _swap_int16_t(xStart, yStart);
    _swap_int16_t(xStop, yStop);
  }

  if (xStart > xStop) {
    _swap_int16_t(xStart, xStop);
    _swap_int16_t(yStart, yStop);
  }

  int16_t dx, dy;
  dx = xStop - xStart;
  dy = abs(yStop - yStart);

  int16_t err = dx / 2;
  int16_t ystep;

  if (yStart < yStop) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; xStart<=xStop; xStart++) {
    if (steep) {
      clrPixel(yStart, xStart);
    } else {
      clrPixel(xStart, yStart);
    }
    err -= dy;
    if (err < 0) {
      yStart += ystep;
      err += dx;
    }
  }
}

void DFRobot_HT1632C::drawImage(const byte * img, uint8_t width_t, uint8_t height_t, int8_t x, int8_t y, int img_offset){
	uint8_t bytesPerColumn = (height_t >> 3) + ((height_t & 0b111)?1:0);
	if(y + height_t < 0 || x + width_t < 0 || y > height || x > width){
		return;
	}
	uint8_t dst_x = x;
	uint8_t src_x = 0;
	while(src_x < width_t){
		if(dst_x < 0){
			src_x++;
			dst_x++;
			continue;
		}else if(dst_x >= width){
			break;
		}
		uint8_t src_y = 0;
		uint8_t dst_y = y;
		while(src_y < height_t){
			if(dst_y < 0){
				src_y -= dst_y;
				dst_y = 0;
				continue;
			}else if(dst_y >= height){
				break;
			}
			
			uint8_t copyInNextStep = 8 - max((src_y & 0b111), (dst_y & 0b111));
			copyInNextStep = min(copyInNextStep, (height - src_y));
			uint8_t dst_copyMask = (0b1 << copyInNextStep) - 1;
			dst_copyMask <<= (8 - (dst_y & 0b111) - copyInNextStep);
			uint8_t copyData = pgm_read_byte(&img[img_offset + (bytesPerColumn * src_x) + (src_y >> 3)]) << (src_y & 0b111);
			copyData >>= (dst_y & 0b111);
			matrix[GET_ADDR_FROM_X_Y(dst_x, dst_y)] =  (matrix[GET_ADDR_FROM_X_Y(dst_x, dst_y)] & ~dst_copyMask) | (copyData & dst_copyMask); 

			src_y += copyInNextStep;
			dst_y += copyInNextStep;
		}
		src_x++;
		dst_x++;
	}
}

void DFRobot_HT1632C::drawImageStr(const byte * img, uint8_t width_t, uint8_t height_t, int8_t x, int8_t y, int img_offset){
	uint8_t bytesPerColumn = (height_t >> 3) + ((height_t & 0b111)?1:0);
	if(y + height_t < 0 || x + width_t < 0 || y > height || x > width){
		return;
	}
	uint8_t dst_x = x;
	uint8_t src_x = 0;
	while(src_x < width_t){
		if(dst_x < 0){
			src_x++;
			dst_x++;
			continue;
		}else if(dst_x >= width){
			break;
		}
		uint8_t src_y = 0;
		uint8_t dst_y = y;
		while(src_y < height_t){
			if(dst_y < 0){
				src_y -= dst_y;
				dst_y = 0;
				continue;
			}else if(dst_y >= height){
				break;
			}
			
			uint8_t copyInNextStep = 8 - max((src_y & 0b111), (dst_y & 0b111));
			copyInNextStep = min(copyInNextStep, (height - src_y));
			uint8_t dst_copyMask = (0b1 << copyInNextStep) - 1;
			dst_copyMask <<= (8 - (dst_y & 0b111) - copyInNextStep);
			uint8_t copyData = pgm_read_byte(&img[img_offset + (bytesPerColumn * src_x) + (src_y >> 3)]) << (src_y & 0b111);
			copyData >>= (dst_y & 0b111);
			matrices[GET_ADDR_FROM_X_Y(dst_x, dst_y)] =  (matrices[GET_ADDR_FROM_X_Y(dst_x, dst_y)] & ~dst_copyMask) | (copyData & dst_copyMask); 

			src_y += copyInNextStep;
			dst_y += copyInNextStep;
		}
		src_x++;
		dst_x++;
	}
}

void DFRobot_HT1632C::drawText(const char text [], int x, int y, const byte font [], int font_end [], uint8_t font_height, uint8_t gutter_space){
	int curr_x = x;
	unsigned int i = 0;
	char currchar;
	
	if(y + font_height < 0 || y >= HEIGHTSIZE){
		return;
	}
	
	while(true){  
		if(text[i] == '\0')
			return;
		
		currchar = text[i] - 32;
		if(currchar >= 65 && currchar <= 90) 
			currchar -= 32; 

		if(currchar < 0 || currchar >= 64) { 
			++i;
			continue; 
		}

		if(curr_x >= WIDTHSIZE){
			break; 
		}
		
		int chr_width = getCharWidth(font_end, font_height, currchar);
		if(curr_x + chr_width + gutter_space >= 0){
			drawImage(font, chr_width, font_height, curr_x, y,  getCharOffset(font_end, currchar));
			for(uint8_t j = 0; j < gutter_space; ++j)
			drawImage(font, 1, font_height, curr_x + chr_width + j, y, 0);
		}
		
		curr_x += chr_width + gutter_space;
		++i;
	}
}

void DFRobot_HT1632C::drawTextStr(const char text [], int x, int y, const byte font [], int font_end [], uint8_t font_height, uint8_t gutter_space){
	int curr_x = x;
	uint8_t i = 0;
	char currchar;
	
	if(y + font_height < 0 || y >= HEIGHTSIZE){
		return;
	}
	
	while(true){  
		if(text[i] == '\0')
			return;
		
		currchar = text[i] - 32;
		if(currchar >= 65 && currchar <= 90) 
			currchar -= 32; 

		if(currchar < 0 || currchar >= 64) { 
			++i;
			continue; 
		}

		if(curr_x >= WIDTHSIZE){
			//break; 
		}
		int chr_width = getCharWidth(font_end, font_height, currchar);
		if(curr_x + chr_width + gutter_space >= 0){
			drawImageStr(font, chr_width, font_height, curr_x, y,  getCharOffset(font_end, currchar));
			for(char j = 0; j < gutter_space; ++j)
			drawImageStr(font, 1, font_height, curr_x + chr_width + j, y, 0);
		}
		
		curr_x += chr_width + gutter_space;
		++i;
	}
}

int DFRobot_HT1632C::getCharWidth(int font_end [], uint8_t font_height, uint8_t font_index) {
	uint8_t bytesPerColumn = (font_height >> 3) + ((font_height & 0b111)?1:0); 

	if(font_index == 0) {
		return font_end[0];
	}

	return (font_end[font_index] - font_end[font_index - 1])/bytesPerColumn;
}

int DFRobot_HT1632C::getCharOffset(int font_end [], uint8_t font_index) {
	if(font_index == 0) {
		return 0;
	}

	return font_end[font_index - 1];
}

int DFRobot_HT1632C::getTextWidth(const char text [], int font_end [], uint8_t font_height, uint8_t gutter_space) {
	int wd = 0;
	uint8_t i = 0;
	char currchar;
	
	while(true){  
		if (text[i] == '\0') {
			return wd - gutter_space;
		}
			
		currchar = text[i] - 32;
		if (currchar >= 65 && currchar <= 90) { 
			currchar -= 32;                    
		}

		if (currchar < 0 || currchar >= 64) {   
			++i;
			continue; 
		}

		wd += getCharWidth(font_end, font_height, currchar) + gutter_space;
		++i;
	}
}

void DFRobot_HT1632C::setCursor(uint8_t x, uint8_t y){
	xIndex = x;
	this->setCursorIndex(x, y);
}

void DFRobot_HT1632C::setCursorIndex(uint8_t x, uint8_t y){
	xCoordinate = x;
	yCoordinate = y;
}

void DFRobot_HT1632C::setFont(uint8_t value){
	fontValue = value;
}

void DFRobot_HT1632C::print(char value){
	char str[5] = {'\0'};
	str[0] = value;
	if(fontValue == FONT8X4)
		this->drawText(str, xCoordinate, yCoordinate, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
	//else if(fontValue == FONT5X4)	this->drawText(str, xCoordinate, yCoordinate, FONT_5X4, FONT_5X4_END, FONT_5X4_HEIGHT);
	else return;
	this->writeScreen();
}

void DFRobot_HT1632C::printNumber(unsigned long n, uint8_t base){
	char buf[8 * sizeof(long) + 1] = {'\0'}; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];
	
	if(base < 2)	base = DEC;
	
	do{
		char c = n % base;
		n /= base;
		*--str = c < 10 ? c + '0' : c + 'A' - 10;
	}while(n);
	
	if(fontValue == FONT8X4)
		this->drawText(str, xCoordinate, yCoordinate, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
	//else if(fontValue == FONT5X4)	this->drawText(str, xCoordinate, yCoordinate, FONT_5X4, FONT_5X4_END, FONT_5X4_HEIGHT);
	else return;
}

void DFRobot_HT1632C::print(uint8_t value, int base){
	this->printNumber((unsigned long) value, base);
	this->writeScreen();
}

void DFRobot_HT1632C::print(int n, int base){
	this->printNumber((unsigned long) n, base);
	this->writeScreen();
}

void DFRobot_HT1632C::print(unsigned int n, int base)
{
  this->printNumber((unsigned long) n, base);
	this->writeScreen();
}

void DFRobot_HT1632C::print(double number, uint8_t digits){
  int index = 0;
	char buf[10] = {'\0'};
	
  if (isnan(number)) return print("nan");
  if (isinf(number)) return print("inf");
  if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0){
     buf[index++] = '-';
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
	
	do{
		char c = int_part % DEC;
		int_part /= DEC;
		buf[index++] =  c + '0';
	}while(int_part);

  if (digits > 0) {
    buf[index++] = '.'; 
  }

  while (digits-- > 0){
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
		char c = toPrint % DEC;
		
		toPrint /= DEC;
		buf[index++] = c + '0';

		
    remainder -= toPrint; 
  } 

	this->print(buf);
	this->writeScreen();
}

void DFRobot_HT1632C::print(float number, uint8_t digits){
	this->print((double)number, digits);
}

void DFRobot_HT1632C::print(const char value[]){
	if(fontValue == FONT8X4)
		this->drawText(value, xCoordinate, yCoordinate, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
	//else if(fontValue == FONT5X4)	this->drawText(value, xCoordinate, yCoordinate, FONT_5X4, FONT_5X4_END, FONT_5X4_HEIGHT);
	this->writeScreen();
}

void DFRobot_HT1632C::printStr(const char str[], uint8_t value){
	if(fontValue == FONT8X4)
		this->drawTextStr(str, xCoordinate, yCoordinate, FONT_8X4, FONT_8X4_END, FONT_8X4_HEIGHT);
}

void DFRobot_HT1632C::print(const char str[], uint16_t speed){
	this->length = strlen(str)*5;
	this->doLength(str);
	
	this->width = length;
	matrices = (char*)malloc(length+24);	
	if(matrices == NULL)	return;
	memset(matrices,'\0',length+24);

	this->setCursorIndex(0,0);
	this->printStr(str);	
	for(uint8_t i=1; i<length+24;i++){	
		for(uint8_t j = xIndex; j<24-xIndex; j++){
			matrix[j] = '\0';
		}
		
		if(i <= 24-xIndex){
			memcpy(&matrix[24-i], &matrices[0], i);
		}else{
			memcpy(&matrix[xIndex], &matrices[i-24+xIndex], 24-xIndex);	
		}
		this->writeScreen();
		delay(speed);
	}
	free(matrices);
  matrices = NULL; 
}

void DFRobot_HT1632C::doLength(const char text[]){
	char currchar;
	uint8_t i = 0;
	
	while(true){  
		if (text[i] == '\0') {
			break;
		}
			
		currchar = text[i] - 32;
		if (currchar >= 65 && currchar <= 90) { 
			currchar -= 32;                    
		}

		if (currchar < 0 || currchar >= 64) {   
			++i;
			continue; 
		}
		switch(currchar){
			case 12:
			case 27:
			case 59:
			case 61:
				this->length -= 2;
				break;
			
			case 0:
			case 7:
			case 14:
			case 26:
				this->length -= 3;
				break;
			
			case 1:
			case 2:
			case 8:
			case 9:
			case 10:
			case 13:
			case 41:
			case 52:
			case 62:
				this->length -= 1;
				break;
			
			case 3:
			case 4:
			case 5:
			case 11:
			case 17:
			case 32:
			case 45:
			case 46:
			case 49:
			case 55:
			case 56:
			case 57:
				this->length += 1;
				break;
		}
		++i;
	}
}







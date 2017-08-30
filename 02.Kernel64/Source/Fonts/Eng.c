/*
 * Eng.c
 *
 *  Created on: 2017. 8. 31.
 *      Author: Yummy
 */

// FontMaker라는 윈도우 응용 프로그램(저자가 직접 만든 프로그램)을 이용해 Bitstream Vera Mono 폰트 - 16pt의 영어버전.

unsigned char g_engFont[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3C,0x7F,0x7F,0x7F,0x7F,0x1C,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0xC1,0x81,0x81,0x81,0x81,0xC3,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x0F,0x03,0x04,0x08,0x70,0x88,0x88,0x88,0x70,0x00,0x00,0x00,
0x00,0x00,0x3C,0x42,0x42,0x42,0x3C,0x08,0x08,0xFF,0x10,0x10,0x10,0x10,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x39,0x2F,0x39,0x21,0x21,0x23,0x27,0x66,0xC0,0x80,0x00,0x00,
0x00,0x00,0x08,0x89,0x5E,0x26,0x42,0x42,0xC3,0x42,0x66,0x7E,0x89,0x08,0x00,0x00,
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x00,0x03,0x07,0x0F,0x3F,0x7F,0x7F,0x3F,0x0F,0x07,0x01,0x00,0x00,0x00,
0x00,0x00,0x08,0x1C,0x0A,0x08,0x08,0x08,0x08,0x08,0x08,0x2A,0x1C,0x08,0x00,0x00,
0x00,0x00,0x00,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x00,0x24,0x00,0x00,0x00,0x00,
0x00,0x00,0x3F,0xC9,0x89,0x89,0xC9,0x39,0x09,0x09,0x09,0x09,0x09,0x09,0x00,0x00,
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x08,0x1C,0x2C,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0F,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0xFF,0x02,0x04,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0xFF,0x40,0x20,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x14,0x14,0x14,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x12,0x12,0x16,0x7F,0x24,0x24,0xFE,0x28,0x48,0x48,0x00,0x00,0x00,
0x00,0x00,0x08,0x08,0x3E,0x49,0x48,0x68,0x3E,0x0B,0x09,0x49,0x3E,0x08,0x08,0x00,
0x00,0x00,0x00,0x60,0x90,0x90,0x62,0x0C,0x30,0x46,0x09,0x09,0x06,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x20,0x20,0x30,0x30,0x49,0x45,0x45,0x62,0x3D,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0C,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x00,0x00,
0x00,0x00,0x30,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x30,0x00,0x00,
0x00,0x00,0x00,0x08,0x49,0x3E,0x1C,0x6B,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x10,0x20,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x02,0x04,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x40,0x00,
0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x49,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x28,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x3E,0x43,0x01,0x01,0x02,0x06,0x0C,0x10,0x20,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x3E,0x41,0x01,0x03,0x1C,0x03,0x01,0x01,0x43,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x06,0x0A,0x1A,0x12,0x22,0x42,0x7F,0x02,0x02,0x02,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0x40,0x40,0x7C,0x42,0x01,0x01,0x01,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0x31,0x60,0x40,0x5E,0x63,0x41,0x41,0x23,0x1E,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x03,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x00,0x00,0x00,
0x00,0x00,0x00,0x3E,0x41,0x41,0x41,0x3E,0x63,0x41,0x41,0x63,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x62,0x41,0x41,0x63,0x3D,0x01,0x03,0x46,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x18,0x18,0x10,0x20,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x0E,0x38,0x40,0x38,0x0E,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x40,0x38,0x0E,0x01,0x0E,0x38,0x40,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x44,0x04,0x0C,0x18,0x10,0x10,0x00,0x10,0x10,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0x33,0x21,0x47,0x49,0x49,0x49,0x49,0x47,0x20,0x30,0x0E,0x00,
0x00,0x00,0x00,0x08,0x14,0x14,0x14,0x14,0x22,0x3E,0x22,0x41,0x41,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0x41,0x41,0x41,0x7E,0x43,0x41,0x41,0x43,0x7E,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,0x00,
0x00,0x00,0x00,0x7C,0x42,0x41,0x41,0x41,0x41,0x41,0x41,0x42,0x7C,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0x21,0x40,0x40,0x40,0x43,0x41,0x41,0x21,0x1E,0x00,0x00,0x00,
0x00,0x00,0x00,0x41,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x41,0x41,0x00,0x00,0x00,
0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x46,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x42,0x44,0x48,0x50,0x70,0x48,0x4C,0x44,0x42,0x41,0x00,0x00,0x00,
0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x63,0x63,0x55,0x55,0x55,0x49,0x41,0x41,0x41,0x41,0x00,0x00,0x00,
0x00,0x00,0x00,0x61,0x61,0x51,0x51,0x49,0x49,0x45,0x45,0x43,0x43,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0x43,0x41,0x41,0x43,0x7E,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1E,0x06,0x02,0x00,
0x00,0x00,0x00,0x7E,0x43,0x41,0x41,0x43,0x7C,0x42,0x41,0x41,0x40,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0x61,0x40,0x40,0x30,0x0E,0x01,0x01,0x43,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x63,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x41,0x41,0x22,0x22,0x22,0x14,0x14,0x14,0x14,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x81,0x81,0x81,0x99,0x5A,0x5A,0x5A,0x24,0x24,0x24,0x00,0x00,0x00,
0x00,0x00,0x00,0x41,0x22,0x14,0x14,0x08,0x14,0x14,0x22,0x22,0x41,0x00,0x00,0x00,
0x00,0x00,0x00,0x41,0x22,0x22,0x14,0x1C,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x03,0x02,0x04,0x08,0x08,0x10,0x20,0x60,0x7F,0x00,0x00,0x00,
0x00,0x00,0x1C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1C,0x00,0x00,
0x00,0x00,0x00,0x40,0x20,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x04,0x02,0x00,
0x00,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x38,0x00,0x00,
0x00,0x00,0x00,0x08,0x14,0x22,0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,
0x00,0x30,0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x02,0x3E,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x00,0x40,0x40,0x40,0x7C,0x64,0x42,0x42,0x42,0x42,0x64,0x5C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x40,0x40,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x02,0x02,0x02,0x3E,0x26,0x42,0x42,0x42,0x42,0x26,0x3A,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3C,0x26,0x42,0x7E,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x0E,0x10,0x10,0x7E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3A,0x26,0x42,0x42,0x42,0x42,0x26,0x3A,0x02,0x22,0x1C,
0x00,0x00,0x40,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00,
0x00,0x00,0x08,0x08,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x7F,0x00,0x00,0x00,
0x00,0x00,0x08,0x08,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x70,
0x00,0x00,0x40,0x40,0x40,0x44,0x48,0x50,0x70,0x48,0x48,0x44,0x42,0x00,0x00,0x00,
0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x7E,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x5C,0x62,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3C,0x66,0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x5C,0x64,0x42,0x42,0x42,0x42,0x64,0x7C,0x40,0x40,0x40,
0x00,0x00,0x00,0x00,0x00,0x3A,0x26,0x42,0x42,0x42,0x42,0x26,0x3A,0x02,0x02,0x02,
0x00,0x00,0x00,0x00,0x00,0x3C,0x32,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x40,0x70,0x0E,0x02,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x10,0x10,0x7E,0x10,0x10,0x10,0x10,0x10,0x10,0x0E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x24,0x24,0x24,0x18,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x81,0x81,0x5A,0x5A,0x5A,0x5A,0x24,0x24,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x42,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x42,0x22,0x24,0x24,0x14,0x18,0x08,0x08,0x08,0x10,0x30,
0x00,0x00,0x00,0x00,0x00,0x7E,0x02,0x04,0x08,0x10,0x20,0x40,0x7E,0x00,0x00,0x00,
0x00,0x00,0x06,0x08,0x08,0x08,0x08,0x08,0x30,0x08,0x08,0x08,0x08,0x08,0x06,0x00,
0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x00,0x00,0x30,0x08,0x08,0x08,0x08,0x08,0x06,0x08,0x08,0x08,0x08,0x08,0x30,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x39,0x46,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x7E,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x22,0x40,0xFC,0x40,0xF8,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x10,0x20,0x00,
0x00,0x00,0x07,0x0C,0x08,0x08,0x08,0x3E,0x08,0x18,0x10,0x10,0x10,0x10,0x30,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x36,0x24,0x48,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6D,0x6D,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x00,0x00,
0x00,0x18,0x18,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x60,0x90,0x90,0x67,0x38,0xC0,0x63,0x94,0x94,0x63,0x00,0x00,0x00,
0x24,0x18,0x00,0x1E,0x61,0x40,0x40,0x30,0x0E,0x01,0x01,0x43,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x18,0x30,0x30,0x18,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0x68,0x48,0x48,0x4F,0x48,0x48,0x48,0x68,0x3F,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x00,
0x24,0x18,0x00,0x7F,0x03,0x02,0x04,0x08,0x08,0x10,0x20,0x60,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x00,
0x00,0x00,0x00,0x7F,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x00,
0x00,0x00,0x04,0x08,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0C,0x0C,0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x12,0x24,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x36,0x36,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x3C,0x3C,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x3A,0x2E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xE9,0x4F,0x4F,0x49,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x24,0x18,0x18,0x00,0x3C,0x42,0x40,0x70,0x0E,0x02,0x42,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x18,0x0C,0x0C,0x18,0x10,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x2C,0x52,0x52,0x5E,0x50,0x50,0x50,0x2E,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x7F,0x00,
0x00,0x24,0x18,0x18,0x00,0x7E,0x02,0x04,0x08,0x10,0x20,0x40,0x7E,0x00,0x00,0x00,
0x00,0x14,0x00,0x41,0x22,0x22,0x14,0x1C,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x1C,0x2A,0x48,0x48,0x48,0x48,0x2A,0x1C,0x08,0x08,0x00,
0x00,0x00,0x00,0x0E,0x19,0x10,0x10,0x10,0x3E,0x10,0x10,0x10,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x41,0x3E,0x22,0x22,0x22,0x3E,0x41,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x41,0x22,0x14,0x77,0x08,0x7F,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x00,0x00,0x3E,0x40,0x60,0x38,0x46,0x42,0x32,0x1C,0x06,0x02,0x7C,0x00,0x00,
0x00,0x00,0x00,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3C,0x42,0x9D,0xA1,0xA1,0x9D,0x42,0x3C,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x02,0x1E,0x22,0x26,0x1A,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x36,0x6C,0x6C,0x36,0x12,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3C,0x42,0xBD,0xA5,0xB9,0xAD,0x42,0x3C,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x24,0x24,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x7F,0x08,0x08,0x00,0x00,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x04,0x04,0x08,0x10,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x04,0x18,0x04,0x04,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x66,0x7F,0x40,0x40,0x40,
0x00,0x00,0x00,0x1F,0x7D,0x7D,0x7D,0x7D,0x1D,0x05,0x05,0x05,0x05,0x05,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x04,0x1C,
0x00,0x00,0x00,0x18,0x08,0x08,0x08,0x08,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x22,0x22,0x22,0x22,0x1C,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x6C,0x36,0x36,0x6C,0x48,0x00,0x00,0x00,0x00,
0x00,0x00,0x60,0x20,0x20,0x20,0x20,0x76,0x38,0xC6,0x06,0x0A,0x12,0x1F,0x02,0x00,
0x00,0x00,0x60,0x20,0x20,0x20,0x20,0x76,0x38,0xDC,0x02,0x02,0x04,0x08,0x1E,0x00,
0x00,0x00,0xF0,0x10,0x60,0x10,0x10,0xE6,0x38,0xC6,0x06,0x0A,0x12,0x1F,0x02,0x00,
0x00,0x00,0x00,0x08,0x08,0x00,0x08,0x08,0x18,0x30,0x20,0x22,0x1C,0x00,0x00,0x00,
0x30,0x18,0x00,0x08,0x14,0x14,0x14,0x14,0x22,0x3E,0x22,0x41,0x41,0x00,0x00,0x00,
0x0C,0x18,0x00,0x08,0x14,0x14,0x14,0x14,0x22,0x3E,0x22,0x41,0x41,0x00,0x00,0x00,
0x18,0x24,0x00,0x08,0x14,0x14,0x14,0x14,0x22,0x3E,0x22,0x41,0x41,0x00,0x00,0x00,
0x3A,0x2E,0x00,0x08,0x14,0x14,0x14,0x14,0x22,0x3E,0x22,0x41,0x41,0x00,0x00,0x00,
0x00,0x14,0x00,0x08,0x14,0x14,0x14,0x14,0x22,0x3E,0x22,0x41,0x41,0x00,0x00,0x00,
0x1C,0x14,0x14,0x08,0x08,0x14,0x14,0x14,0x22,0x3E,0x22,0x63,0x41,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0x28,0x28,0x28,0x4F,0x48,0x78,0x48,0x88,0x8F,0x00,0x00,0x00,
0x00,0x00,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x04,0x02,0x0E,
0x30,0x18,0x00,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x0C,0x18,0x00,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x18,0x24,0x00,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x00,0x14,0x00,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,
0x30,0x18,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,0x00,
0x0C,0x18,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,0x00,
0x18,0x24,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,0x00,
0x00,0x14,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,0x00,
0x00,0x00,0x00,0x7C,0x42,0x41,0x41,0xF1,0x41,0x41,0x41,0x42,0x7C,0x00,0x00,0x00,
0x3A,0x2E,0x00,0x61,0x61,0x51,0x51,0x49,0x49,0x45,0x45,0x43,0x43,0x00,0x00,0x00,
0x30,0x18,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,0x00,
0x0C,0x18,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,0x00,
0x18,0x24,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,0x00,
0x3A,0x2E,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,0x00,
0x00,0x14,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x42,0x24,0x18,0x18,0x24,0x42,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0x23,0x43,0x45,0x4D,0x59,0x71,0x61,0x62,0xBC,0x00,0x00,0x00,
0x30,0x18,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x63,0x3E,0x00,0x00,0x00,
0x0C,0x18,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x63,0x3E,0x00,0x00,0x00,
0x18,0x24,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x63,0x3E,0x00,0x00,0x00,
0x00,0x14,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x63,0x3E,0x00,0x00,0x00,
0x0C,0x18,0x00,0x41,0x22,0x22,0x14,0x1C,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,
0x00,0x00,0x00,0x40,0x7E,0x43,0x41,0x41,0x43,0x7E,0x40,0x40,0x40,0x00,0x00,0x00,
0x00,0x00,0x38,0x44,0x44,0x48,0x50,0x50,0x5C,0x46,0x42,0x42,0x5C,0x00,0x00,0x00,
0x00,0x30,0x10,0x08,0x00,0x1C,0x22,0x02,0x3E,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x1C,0x22,0x02,0x3E,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x18,0x18,0x24,0x00,0x1C,0x22,0x02,0x3E,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x00,0x3A,0x2E,0x00,0x1C,0x22,0x02,0x3E,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x00,0x00,0x14,0x00,0x1C,0x22,0x02,0x3E,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x18,0x24,0x24,0x18,0x00,0x1C,0x22,0x02,0x3E,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x6C,0x12,0x12,0x3E,0x50,0x50,0x50,0x6E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x40,0x40,0x40,0x40,0x22,0x1C,0x04,0x02,0x0E,
0x00,0x30,0x10,0x08,0x00,0x3C,0x26,0x42,0x7E,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x3C,0x26,0x42,0x7E,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x18,0x18,0x24,0x00,0x3C,0x26,0x42,0x7E,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x14,0x00,0x3C,0x26,0x42,0x7E,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
0x00,0x30,0x10,0x08,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x7F,0x00,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x7F,0x00,0x00,0x00,
0x00,0x18,0x18,0x24,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x14,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x7F,0x00,0x00,0x00,
0x00,0x00,0x30,0x3C,0x08,0x3C,0x26,0x42,0x42,0x42,0x42,0x26,0x3C,0x00,0x00,0x00,
0x00,0x00,0x3A,0x2E,0x00,0x5C,0x62,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00,
0x00,0x30,0x10,0x08,0x00,0x3C,0x66,0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x3C,0x66,0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
0x00,0x18,0x18,0x24,0x00,0x3C,0x66,0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
0x00,0x00,0x3A,0x2E,0x00,0x3C,0x66,0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x14,0x00,0x3C,0x66,0x42,0x42,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0xFF,0x00,0x18,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x26,0x46,0x4A,0x52,0x62,0x64,0x7C,0x00,0x00,0x00,
0x00,0x30,0x10,0x08,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x18,0x18,0x24,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x00,0x00,0x14,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x42,0x22,0x24,0x24,0x14,0x18,0x08,0x08,0x08,0x10,0x30,
0x00,0x00,0x40,0x40,0x40,0x5C,0x64,0x42,0x42,0x42,0x42,0x64,0x7C,0x40,0x40,0x40,
0x00,0x00,0x00,0x14,0x00,0x42,0x22,0x24,0x24,0x14,0x18,0x08,0x08,0x08,0x10,0x30};

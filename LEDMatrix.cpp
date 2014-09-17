/**
 * LED Matrix library for http://www.seeedstudio.com/depot/ultrathin-16x32-red-led-matrix-panel-p-1582.html
 * The LED Matrix panel has 32x16 pixels. Several panel can be combined together as a large screen.
 *
 * Coordinate & Connection (Arduino -> panel 0 -> panel 1 -> ...)
 *   (0, 0)                                     (0, 0)
 *     +--------+--------+--------+               +--------+--------+
 *     |   5    |    4   |    3   |               |    1   |    0   |
 *     |        |        |        |               |        |        |<----- Arduino
 *     +--------+--------+--------+               +--------+--------+
 *     |   2    |    1   |    0   |                              (64, 16)
 *     |        |        |        |<----- Arduino
 *     +--------+--------+--------+
 *                             (96, 32)
 *  Copyright (c) 2013 Seeed Technology Inc.
 *  @auther     Yihui Xiong
 *  @date       Nov 8, 2013
 *  @license    MIT
 */

#include "LEDMatrix.h"
#include "Arduino.h"

#if 0
#define ASSERT(e)   if (!(e)) { Serial.println(#e); while (1); }
#else
#define ASSERT(e)
#endif

LEDMatrix::LEDMatrix(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t oe, uint8_t r1, uint8_t stb, uint8_t clk)
{
    this->clk = clk;
    this->r1 = r1;
    this->stb = stb;
    this->oe = oe;
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;

    mask = 0xff;
    state = 0;
}

void LEDMatrix::begin(uint8_t *displaybuf, uint16_t width, uint16_t height)
{
    ASSERT(0 == (width % 32));
    ASSERT(0 == (height % 16));

    this->displaybuf = displaybuf;
    this->width = width;
    this->height = height;

    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(oe, OUTPUT);
    pinMode(r1, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(stb, OUTPUT);

    state = 1;
}

void LEDMatrix::drawPoint(uint16_t x, uint16_t y, uint8_t pixel)
{
    ASSERT(width > x);
    ASSERT(height > y);

    uint8_t *byte = displaybuf + x / 8 + y * width / 8;
    uint8_t  bit = x % 8;

    if (pixel) {
        *byte |= 0x80 >> bit;
    } else {
        *byte &= ~(0x80 >> bit);
    }
}

void LEDMatrix::drawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t pixel)
{
    for (uint16_t x = x1; x < x2; x++) {
        for (uint16_t y = y1; y < y2; y++) {
            drawPoint(x, y, pixel);
        }
    }
}

void LEDMatrix::drawImage(uint16_t xoffset, uint16_t yoffset, uint16_t width, uint16_t height, const uint8_t *image)
{
    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            const uint8_t *byte = image + (x + y * width) / 8;
            uint8_t  bit = 7 - x % 8;
            uint8_t  pixel = (*byte >> bit) & 1;

            drawPoint(x + xoffset, y + yoffset, pixel);
        }
    }
}

void LEDMatrix::clear()
{
    uint8_t *ptr = displaybuf;
    for (uint16_t i = 0; i < (width * height / 8); i++) {
        *ptr = 0x00;
        ptr++;
    }
}

void LEDMatrix::reverse()
{
    mask = ~mask;
}

uint8_t LEDMatrix::isReversed()
{
    return mask;
}

void LEDMatrix::scan()
{
    static uint8_t row = 0;  // from 0 to 15

    if (!state) {
        return;
    }

    uint8_t *head = displaybuf + row * (width / 8);
    for (uint8_t line = 0; line < (height / 16); line++) {
        uint8_t *ptr = head;
        head += width * 2;              // width * 16 / 8

        for (uint8_t byte = 0; byte < (width / 8); byte++) {
            uint8_t pixels = *ptr;
            ptr++;
            pixels = pixels ^ mask;     // reverse: mask = 0xff, normal: mask =0x00
            for (uint8_t bit = 0; bit < 8; bit++) {
                digitalWrite(clk, LOW);
                digitalWrite(r1, pixels & (0x80 >> bit));
                digitalWrite(clk, HIGH);
            }
        }
    }

    digitalWrite(oe, HIGH);              // disable display

    // select row
    digitalWrite(a, (row & 0x01));
    digitalWrite(b, (row & 0x02));
    digitalWrite(c, (row & 0x04));
    digitalWrite(d, (row & 0x08));

    // latch data
    digitalWrite(stb, LOW);
    digitalWrite(stb, HIGH);
    digitalWrite(stb, LOW);

    digitalWrite(oe, LOW);              // enable display

    row = (row + 1) & 0x0F;
}

void LEDMatrix::on()
{
    state = 1;
}

void LEDMatrix::off()
{
    state = 0;
    digitalWrite(oe, HIGH);
}

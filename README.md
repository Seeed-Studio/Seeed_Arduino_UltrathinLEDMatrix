Ultrathin LED Matrix Library
----------------------------

This is an Arduino library for [Ultrathin 32x16 LED Matrix](http://goo.gl/y6VnO6).

[![Ultrathin 32x16 LED Matrix](http://www.seeedstudio.com/document/pics/led.jpg)](http://goo.gl/y6VnO6)

Several panels can be combined together as a large screen.

```
Coordinate & Connection (Arduino -> panel 0 -> panel 1 -> ...)
  (0, 0)                                     (0, 0)
    +--------+--------+--------+               +--------+--------+
    |   5    |    4   |    3   |               |    1   |    0   |
    |        |        |        |               |        |        |<----- Arduino
    +--------+--------+--------+               +--------+--------+
    |   2    |    1   |    0   |                              (64, 16)
    |        |        |        |<----- Arduino
    +--------+--------+--------+
                            (96, 32)
```

#### Pins  
+ A, B, C, D - line select for two 74HC138
+ OE - Ouput Enable(active low) for 74HC595
+ STB - data latch for 74HC595
+ CLK - shift register clock input for 74HC595

If you use the LED matrix with [mbed platform](http://goo.gl/WHtyuH), [another library](https://mbed.org/users/yihui/notebook/ultrathin-32x16-led-matrix/) is for you.


### Usage
```
#include "LEDMatrix.h"

#define WIDTH   32
#define HEIGHT  16

LEDMatrix matrix(4, 5, 6, 7, 8, 9, 10, 11);		// LEDMatrix(a, b, c, d, oe, r1, stb, clk);
uint8_t displaybuf[WIDTH *HEIGHT / 8]; 			// Display Buffer

void setup() {
    matrix.begin(displaybuf, WIDTH, HEIGHT);
}

void loop() {
    static uint32_t lastCountTime = 0;
    static uint8_t count = 0;

    matrix.scan();

    if ((millis() - lastCountTime) > 3000) {
        lastCountTime = millis();
        matrix.drawRect(count + 4, count, 28 - count, 16 - count, 1 - (count & 1));
        count = (count + 1) & 0x0F;
    }
}

```


----

This library is written by Yihui Xiong for seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php).

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>




[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/Ultrathin_LED_Matrix)](https://github.com/igrigorik/ga-beacon)

This is an Arduino library for [Ultrathin 32x16 LED Matrix](http://goo.gl/y6VnO6).

[![Ultrathin 32x16 LED Matrix](http://www.seeedstudio.com/document/pics/led.jpg)](http://goo.gl/y6VnO6)

Several panels can be combined together as a large screen.

```
Coordinate & Connection (Arduino -> panel 0 -> panel 1 -> ...)
  (0, 0)                                     (0, 0)
    +--------+--------+--------+               +--------+--------+
    |   5    |    3   |    1   |               |    1   |    0   |
    |        |        |        |               |        |        |<----- Arduino
    +--------+--------+--------+               +--------+--------+
    |   4    |    2   |    0   |                              (64, 16)
    |        |        |        |<----- Arduino
    +--------+--------+--------+
                            (96, 32)
```

If you use the LED matrix with [mbed platform](http://goo.gl/WHtyuH), [another library](https://mbed.org/users/yihui/notebook/ultrathin-32x16-led-matrix/) is for you.

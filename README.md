LED Matrix library for http://www.seeedstudio.com/depot/ultrathin-16x32-red-led-matrix-panel-p-1582.html
The LED Matrix panel has 32x16 pixels. Several panel can be combined together as a large screen.

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

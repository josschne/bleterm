# bleterm -- BLE terminal program for Nordic Semiconductor devices

bleterm is a nodejs terminal program for BLE UART services. It depends on the
[nrfuart](https://www.npmjs.com/package/nrfuart) and
[noble](https://www.npmjs.com/package/noble) packages for Nordic Semiconductor
BLE UART communcations.

## Install bleterm

```sh
npm install bleterm
```

## Hardware setup

The tested configuration is an Adafruit Bluefruit LE UART Friend connected the
hardware UART interface of an Adafruit Pro Trinket 3V. However, bleterm should
work with all Nordic Semiconductor devices with BLE UART service.

The switch on the BLE UART should be in the UART position, not CMD. 

[Breadboard](images/bletermHW.png)

The Arduino sketch, arduino/cli.ino, must be uploaded to the Pro Trinket. This
is a demo of a small command line interface over the hardware serial interface.
The only command implemented in cli.ino is "blink [0|1|t|f]" which turns the
LED connected to digital pin 13 on and off. This can be used as a template
for implementing commands for complex devices. For example, if Neopixels are
connected to the Pro Trinket, implement commands to switch between effects
such as rainbow, colorWipe, and theaterChase.

## How to use

bleterm is a command line application so run it, wait for it to connect to
a BLE UART device, then start typing. Press Ctrl-D to exit.

* "blink 1" turns on the LED connected to digital pin 13
* "blink 0" turns off the LED connected to digital pin 13
* "blink t" is a synonym for "blink 1"
* "blink f" is a synonym for "blink 0"

The following is a sample session showing how to turn the Pro Trinket LED on
and off.

```
pi@raspi ~/bleterm $ node bleterm.js 
Connected to Adafruit Bluefruit LE
blink 1
blink 0
<CTRL-D>
pi@raspi ~/bleterm $
```

The following is a sample session showing how to get into AT command mode.
Note: You will not see +++ and ATI as you type because the BLE UART does not
echo back the characters. They are shown below for clarity.

When the BLE UART is in AT command mode, the cli.ino sketch does not receive
the characters you type. The BLE UART intercepts the incoming characters. Be
sure to send +++ a second time to make the BLE UART revert to UART data mode.

```
pi@raspi ~/bleterm $ node bleterm.js 
Connected to Adafruit Bluefruit LE
+++
OK
ATI
BLEFRIEND32
nRF51822 QFACA10
365B980BEBABC010
0.6.2
0.6.2
Apr 30 2015
S110 8.0.0, 0.2
OK
+++
OK
<CTRL-D>
pi@raspi ~/bleterm $
```

## License

The MIT License (MIT)

Copyright (c) 2015 bbx10node@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

/*
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
 */

/* jslint node: true */
'use strict';

/*
 * BLE Terminal Terminal program for nRF BLE UART devices.
 *
 * Characters typed on the keyboard (stdin) are sent to the BLE UART.
 * Characters received from the BLE UART are sent to stdout.
 *
 * This has been tested with the Adafruit Bluefruit LE UART Friend but should
 * work with other devices with the Nordic Semiconductor UART service.
 */

/*
 * Setup the BLE nRF UART interface
 */
var nrfuart = require('nrfuart');
var BLE_uart = null;

nrfuart.discoverAll(function(ble_uart) {
  // enable disconnect notifications 
  ble_uart.on('disconnect', function() {
    console.log('disconnected!');
  });

  // connect and setup 
  ble_uart.connectAndSetup(function() {
    BLE_uart = ble_uart;
    ble_uart.readDeviceName(function(devName) {
      console.log('Connected to', devName);
    });

    // Any data received from BLE UART is sent to stdout
    ble_uart.on('data', function(chunk) {
      process.stdout.write(chunk);
    });
  });
});

/*
 * Setup stdin and stdout.
 * Any data received from stdin is sent to BLE UART.
 */
if (process.stdin.isTTY && process.stdout.isTTY) {
  process.stdin.setRawMode(true);

  process.stdin.on('data', function(chunk) {
    if (chunk !== null) {
      if ((chunk.length === 1) && (chunk[0] === 0x04)) {  // Ctrl-D exits
        process.exit(0);
      }
      if (BLE_uart !== null) BLE_uart.write(chunk, function(error) {
        if (error) {
          console.log(error);
        }
      });
    }
  });

  process.stdin.on('error', function() {
    console.log('stdin error');
  });

  process.stdin.on('end', function() {
    console.log('stdin end');
  });
  process.stdout.on('error', function() {
    console.log('stdout error');
  });
}
else {
  console.log('not a tty');
}

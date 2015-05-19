/*

    Simple command line interface (CLI) on Serial port.
  
    This example shows the implementation of a single command named "blink".
    blink takes a single parameter. "blink 1" writes HIGH to pin 13. "blink 0"
    writes LOW to digital pin 13.

    This program has been used with the Adafruit Bluefruit LE UART Friend
    connected to the Adafruit Pro Trinket 3V 12MHz via the Trinket hardware
    UART inteface. The switch on the BLE UART should be in the UART position.

    The Adafruit Bluefruit BLE Connect application UART mode can be used to
    send commands to this sketch. Run the app on iOS or Android then connect to
    the BLE UART in UART mode. Send "blink 1\r" or "blink t\r" then press SEND
    to turn LED #13 on. Note the "\r" means press the RETURN key. If this is
    not done, the CLI sketch will ignore the command. Send "blink 0\r" or
    "blink f\r" to turn the LED off.

    Another way to sends command is using nodejs/Javascript using bleterm.

 */

// Most Arduinos have an LED connected to pin 13
const int BLINKLED = 13;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
    // initialize serial
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    // reserve 200 bytes for the inputString
    inputString.reserve(200);
    // initialize the digital pin as an output.
    pinMode(BLINKLED, OUTPUT);
}

void loop() {
    // analyze the command when the end of line is received 
    if (stringComplete) {
        Serial.println("");

        doCommand(inputString);

        // clear the string for the next command
        inputString = "";
        stringComplete = false;
    }
}

void doCommand(String command) {
    String parameter;
    command.toUpperCase();
    if (command.startsWith("BLINK", 0)) {
        parameter = command.substring(6);
        if (parameter == "1" || parameter == "T") {
            digitalWrite(BLINKLED, HIGH); // turn the LED on (HIGH is the voltage level)
        }
        else if (parameter == "0" || parameter == "F") {
            digitalWrite(BLINKLED, LOW);  // turn the LED off by making the voltage LOW
        }
        else {
            Serial.println("?");
        }
    }
//    else if (command.startsWith("MORECOMMANDS", 0)) {
//    }
    else {
        Serial.println("?");
    }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
    while (!stringComplete && Serial.available()) {
        // get the new byte
        char inChar = (char)Serial.read();
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it
        if ((inChar == '\n') || (inChar == '\r')) {
            Serial.print(inChar);
            stringComplete = true;
        }
        // If there is at least 1 character in the input string, handle 
        // backspace (also known as '\b') and delete (also known as 
        // ASCII 0x7F and DEL).
        else if ((inChar == '\b') || (inChar == 0x7F)) {
            if (inputString.length() > 0 ) { 
                // Erase the last character that the user sees by 
                // move the cursor back 1 character
                // write a blank
                // move the cursor back 1 character
                Serial.print("\b \b");
                // Erase the last character from the inputString
                inputString.remove(inputString.length() - 1);
            }
        }
        else {
            Serial.print(inChar);
            // add it to the inputString
            inputString += inChar;
        }
    }
}

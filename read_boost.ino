/*
 * Pressure Sensor being used purchased from https://www.amazon.com/gp/product/B07L9S65B3/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1
 * Item model number  038906051C
 * Manufacturer Part Number  038906051C
 * OEM Part Number   0281002401, 038 906 051 C, 038906051C 
 * /



#include <Wire.h>
#include <SPI.h>
#include <M5Stack.h>
#include "Free_Fonts.h"

int mapsen = 26; // Set MAP sensor input on Analog port 0 
float psiPabs; // for converting our value in mbar to psi
char charPabs[5]; // for converting our value to a char * so we can draw it on the screen

//position of text
int xpos;
int ypos;

//non blocking delay using millis from https://randomnerdtutorials.com/why-you-shouldnt-always-use-the-arduino-delay-function/
unsigned long previousMillis = 0;
const long interval = 250;

void setup() { 
    Serial1.begin(9600, SERIAL_8N1, 16, 17);
    M5.begin();
    M5.Power.begin();
    M5.Lcd.setTextColor(TFT_RED, TFT_BLACK); // https://github.com/m5stack/M5Stack/tree/master/examples/Advanced/Display/Free_Font_Demo
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.setFreeFont(FM24); //use FreeMono font 24 point...see Free_Fonts.h
    xpos = M5.Lcd.width() / 2; // Half the screen width
    ypos = (M5.Lcd.height() / 2)-24 ; // Half the screen height minus the height of the font seems to get us centered vertically
} 
    
void loop() { 

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      float out_voltage = analogRead(mapsen) / 1000.000000; //esp32 is reading in millivolts so let's convert to volts for our curve to work
  
      // forumula derived from https://www.youtube.com/watch?v=83LuzJTIbAw&list=PLZ73CAxmn6f3F2Muguy2oU4sQEykYiTsw&index=5&t=375s
      float Pabs = 3294.11764705*(out_voltage/4.537143)-279.99999999925;
  
      // pressure in PSI minus standard atmospheric pressure
      psiPabs = (Pabs / 68.948) - 14.696; 
       /*convert Pabs float to a string and draw it 
       * http://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html#ga060c998e77fb5fc0d3168b3ce8771d42
       * https://forum.arduino.cc/index.php?topic=243660.0
       */
      M5.Lcd.drawString(dtostrf(psiPabs,3,2, charPabs), xpos, ypos, GFXFF);
  }
      
    // if we press Button A (left side) turn off the M5
    if(M5.BtnA.wasPressed()) {
      M5.powerOFF();
    }
    M5.update();
}




/* MISC Info on ESP32 Serial connections
 *  
 *  Baud-rates available: 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200, 256000, 512000, 962100
 *  
 *  Protocols available:
 * SERIAL_5N1   5-bit No parity 1 stop bit
 * SERIAL_6N1   6-bit No parity 1 stop bit
 * SERIAL_7N1   7-bit No parity 1 stop bit
 * SERIAL_8N1 (the default) 8-bit No parity 1 stop bit
 * SERIAL_5N2   5-bit No parity 2 stop bits 
 * SERIAL_6N2   6-bit No parity 2 stop bits
 * SERIAL_7N2   7-bit No parity 2 stop bits
 * SERIAL_8N2   8-bit No parity 2 stop bits 
 * SERIAL_5E1   5-bit Even parity 1 stop bit
 * SERIAL_6E1   6-bit Even parity 1 stop bit
 * SERIAL_7E1   7-bit Even parity 1 stop bit 
 * SERIAL_8E1   8-bit Even parity 1 stop bit 
 * SERIAL_5E2   5-bit Even parity 2 stop bit 
 * SERIAL_6E2   6-bit Even parity 2 stop bit 
 * SERIAL_7E2   7-bit Even parity 2 stop bit  
 * SERIAL_8E2   8-bit Even parity 2 stop bit  
 * SERIAL_5O1   5-bit Odd  parity 1 stop bit  
 * SERIAL_6O1   6-bit Odd  parity 1 stop bit   
 * SERIAL_7O1   7-bit Odd  parity 1 stop bit  
 * SERIAL_8O1   8-bit Odd  parity 1 stop bit   
 * SERIAL_5O2   5-bit Odd  parity 2 stop bit   
 * SERIAL_6O2   6-bit Odd  parity 2 stop bit    
 * SERIAL_7O2   7-bit Odd  parity 2 stop bit    
 * SERIAL_8O2   8-bit Odd  parity 2 stop bit    
*/

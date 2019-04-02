/* - - - - -
// FollowSpotDMX - A hardware supported interface to control an LED based follow spot via DMX.
// 
// Copyright (c) 2017 by Relly Mallari, https://github.com/rellymallari/FollowSpotDmx

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program.
If not, see http://www.gnu.org/licenses/

 - - - - -
*/

#include <DMXSerial.h>
//#include <PWMFrequency.h>

// Constants for demo program

const int arduinoPin =   11;  // PWM output pin for Follow Spot.
const int dmxchIntensity =   510; //DMX Intensity Channel
const int dmxchStrobe = 511; //DMX Strobe Channel

// Defaults for Strobe function
unsigned long strobeRate = 0;
unsigned long strobePulseLength = 15;

unsigned long dmxvalIntensity = 0;
unsigned long dmxvalStrobe = 0;

void setup () {
  DMXSerial.init(DMXReceiver);
  
  // set some default values
  DMXSerial.write(dmxchIntensity, 0);
  DMXSerial.write(dmxchStrobe, 0);
  
  // enable pwm outputs
  pinMode(arduinoPin, OUTPUT); // sets the digital pin as output

//  setPwmFrequency(11, 8);

}

void loop() {
  unsigned long lastPacket = DMXSerial.noDataSince();

    dmxvalIntensity = DMXSerial.read(dmxchIntensity);
    dmxvalStrobe = DMXSerial.read(dmxchStrobe);

    if (lastPacket > 5000)
      analogWrite(arduinoPin, 0);  //turn off bulb if no data is received after 5 seconds
    else
    {  
      // If strobe is active
      if (dmxvalStrobe > 0) {
        // Set the strobe rate
        strobeRate = (260 - dmxvalStrobe) * 5;

        //turn on bulb
        analogWrite(arduinoPin, dmxvalIntensity); 
        delay(strobePulseLength);
        //turn off bulb
        analogWrite(arduinoPin, 0);
        delay(strobeRate);
      }
      else
        analogWrite(arduinoPin, dmxvalIntensity);  //on  
    }
}

// End.

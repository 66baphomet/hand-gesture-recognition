/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo finger;
// twelve Servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  finger.attach(9);


    // attaches the servo on pin 9 to the Servo object
}

void loop() {

    finger.write(180); 
    delay(3000);
    finger.write(0); 
    delay(3000);

    
                 // tell servo to go to position in variable 'pos'
                           // waits 15 ms for the servo to reach the posit
}

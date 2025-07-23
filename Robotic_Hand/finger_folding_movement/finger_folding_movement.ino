/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo index_fold;//upper servo

// twelve Servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  index_fold.attach(9);
    // attaches the servo on pin 9 to the Servo object
}

void loop() {

    index_fold.write(0); 
    delay(2000);
    index_fold.write(180);
    delay(2000);

                 // tell servo to go to position in variable 'pos'
                           // waits 15 ms for the servo to reach the posit
}

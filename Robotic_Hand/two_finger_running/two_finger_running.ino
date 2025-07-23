/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo index_right,little_right;//upper servo
Servo index_left, little_left;  //lower servo
// twelve Servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  index_right.attach(9);
  index_left.attach(10);

  little_right.attach(5);
  little_left.attach(6);
    // attaches the servo on pin 9 to the Servo object
}

void loop() {

    index_right.write(0); 
    index_left.write(0);
    little_right.write(0); 
    little_left.write(0);
    delay(2000);
    index_right.write(10); 
    index_left.write(10);
    little_right.write(10); 
    little_left.write(10);
    delay(2000);
    index_right.write(20); 
    index_left.write(20);
    little_right.write(20); 
    little_left.write(20);
    delay(2000);
    index_right.write(10); 
    index_left.write(10);
    little_right.write(10); 
    little_left.write(10);
    delay(2000);

    index_right.write(0); 
    index_left.write(0);
    little_right.write(20); 
    little_left.write(20);
    delay(2000);
    index_right.write(10); 
    index_left.write(10);
    little_right.write(10); 
    little_left.write(10);
    delay(2000);

    
                 // tell servo to go to position in variable 'pos'
                           // waits 15 ms for the servo to reach the posit
}

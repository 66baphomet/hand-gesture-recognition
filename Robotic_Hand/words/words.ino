#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // default I2C address 0x40

#define SERVO_MIN_PULSE  102 // 0 degrees
#define SERVO_MAX_PULSE  491 // 180 degrees

//sidewise movement [25, 20, 15]
//folding movement [180, 0]

//idle[15] = [first 10 servo for sidewise movement from little to thumb, later 5 for folding]

//little[0][1][10], ring[2][3][11], middle[4][5][12], index[6][7][13], thumb[8][9][14]

int idle[15] = {25, 25, 20, 20, 15, 15, 25, 25, 20, 20, 180, 180, 180, 180, 180};
int letters[26][15] = {
/*A*/ {25, 25, 20, 20, 15, 15, 25, 25, 20, 20, 180, 180, 180, 180, 0},//hi
/*B*/ {25, 25, 20, 20, 15, 15, 25, 25, 20, 20, 0, 0, 0, 180, 0},//you
/*C*/ {25, 25, 20, 20, 20, 20, 15, 15, 20, 20, 0, 0, 180, 180, 0},//okay
/*D*/ {40, 40, 30, 30, 20, 20, 25, 25, 20, 20, 180, 180,180, 0, 0},//same
/*E*/ {30, 30, 20, 20, 20, 20, 20, 20, 20, 20, 180, 0, 0, 180, 0},//spiderman
/*F*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 180, 180, 180, 0, 0},
/*G*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 180, 0},
/*H*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 180, 180, 0},
/*I*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 180, 0, 0, 0, 0},
/*J*/ {25, 25, 20, 20, 20, 20, 20, 20, 20, 20, 180, 0, 0, 0, 0},
/*K*/ {20, 20, 20, 20, 25, 25, 15, 15, 20, 20, 0, 0, 180, 180, 180},
/*L*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 180, 180},
/*M*/ {25, 25, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0},
/*N*/ {25, 25, 25, 25, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0},
/*O*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0},
/*P*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 180, 180, 0},
/*Q*/ {20, 20, 20, 20, 20, 20, 20, 20, 25, 25, 0, 0, 0, 180, 180},
/*R*/ {20, 20, 20, 20, 20, 20, 20, 20, 25, 25, 0, 0, 180, 100, 0},
/*S*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0},
/*T*/ {20, 20, 20, 20, 20, 20, 15, 15, 20, 20, 0, 0, 0, 0, 0},
/*U*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 180, 180, 0},
/*V*/ {20, 20, 20, 20, 25, 25, 15, 15, 20, 20, 0, 0, 180, 180, 0},
/*W*/ {20, 20, 25, 25, 20, 20, 15, 15, 20, 20, 0, 180, 180, 180, 0},
/*X*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 180, 0},
/*Y*/ {25, 25, 20, 20, 20, 20, 20, 20, 25, 25, 180, 0, 0, 0, 180},
/*Z*/ {20, 20, 20, 20, 20, 20, 25, 25, 20, 20, 0, 0, 0, 180, 0},
};

void setup() {
  Serial.begin(9600);
  Serial.println("Ready to receive speech...");

  Serial.println("PCA9685 16-Servo Control");

  pwm.begin();
  pwm.setPWMFreq(50);  // Standard 50 Hz for analog servo
  pinMode(LED_BUILTIN, OUTPUT);

  delay(10);

}

uint16_t angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
}

int n = 0;

void driveMotor(int angles[])
{
  // for (int i = 0; i < 16; i++) {
  //   Serial.print("angles[");
  //   Serial.print(i);
  //   Serial.print("] = ");
  //   Serial.println(angles[i]);
  // }

  Serial.println(angles[11]);
  for (int i = 0; i < 16; i++) {
    
    pwm.setPWM(i, 0, angleToPulse(angles[i]));
    delay(50);
  }
  delay(3000);

  Serial.println(idle[11]);

  for (int i = 0; i < 16; i++) {

    pwm.setPWM(i, 0, angleToPulse(idle[i]));
  }
  delay(2000);
}



void loop() {


  if (Serial.available() > 0) {
    String sentence = Serial.readStringUntil('\n');
    // Serial.println(sentence);
    // digitalWrite(LED_BUILTIN, HIGH);

    driveMotor(letters[n]);
    n = n+1;
    if(n>4)
    {
      n = 0;
    }

    // for (int i = 0; i < sentence.length(); i++) {
    //   Serial.println(sentence.charAt(i));
    //   int n = (int)sentence.charAt(i)-65;
    //   Serial.println(n);
    //   if(n>=0)
    //   {
    //     driveMotor(letters[n]);
    //   }
    //   else
    //   {
    //     delay(2000);
    //   }

    
  }

  

}




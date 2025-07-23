#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // default I2C address 0x40

#define SERVO_MIN_PULSE  102 // 0 degrees
#define SERVO_MAX_PULSE  491 // 180 degrees

//sidewise movement [30, 20, 10]
//folding movement [180, 0]

//idle[15] = [first 10 servo for sidewise movement from little to thumb, later 5 for folding]

//little[0][1][10], ring[2][3][11], middle[4][5][12], index[6][7][13], thumb[8][9][14]

int idle[15] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 180, 180, 180, 180, 180};
int letters[26][15] = {
/*A*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 180},
/*B*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 180, 180, 180, 180, 0},
/*C*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 100, 100, 100, 100, 100},
/*D*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 180, 0},
/*E*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0},
/*F*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 180, 180, 180, 0, 0},
/*G*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 180, 0},
/*H*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 180, 180, 0},
/*I*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 180, 0, 0, 0, 0},
/*J*/ {30, 30, 20, 20, 20, 20, 20, 20, 20, 20, 180, 0, 0, 0, 0},
/*K*/ {20, 20, 20, 20, 30, 30, 10, 10, 20, 20, 0, 0, 180, 180, 180},
/*L*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 180, 180},
/*M*/ {30, 30, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0},
/*N*/ {30, 30, 30, 30, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0},
/*O*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 80, 80, 80, 80, 80},
/*P*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 100, 180, 0},
/*Q*/ {20, 20, 20, 20, 20, 20, 20, 20, 30, 30, 0, 0, 0, 180, 180},
/*R*/ {20, 20, 20, 20, 20, 20, 20, 20, 30, 30, 0, 0, 180, 100, 0},
/*S*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0},
/*T*/ {20, 20, 20, 20, 20, 20, 10, 10, 20, 20, 0, 0, 0, 0, 0},
/*U*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 180, 180, 0},
/*V*/ {20, 20, 20, 20, 30, 30, 10, 10, 20, 20, 0, 0, 180, 180, 0},
/*W*/ {20, 20, 30, 30, 20, 20, 10, 10, 20, 20, 0, 180, 180, 180, 0},
/*X*/ {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 180, 0},
/*Y*/ {30, 30, 20, 20, 20, 20, 20, 20, 30, 30, 180, 0, 0, 0, 180},
/*Z*/ {20, 20, 20, 20, 20, 20, 30, 30, 20, 20, 0, 0, 0, 180, 0},
};

void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 16-Servo Control");

  pwm.begin();
  pwm.setPWMFreq(50);  // Standard 50 Hz for analog servos

  delay(10);
}


uint16_t angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
}



void loop() {
  // Example: Set all 16 servos to respective angles
  String sentence = "VWYZMN";

  for (int i = 0; i < sentence.length(); i++) {
    Serial.println(sentence.charAt(i));
    int n = (int)sentence.charAt(i)-65;
    Serial.println(n);
    if(n>=0)
    {
      driveMotor(letters[n]);
    }
    else
    {
      delay(2000);
    }

  }

  //driveMotor(idle);

  //   for (int i = 0; i < 16; i++) {
  //   pwm.setPWM(i, 0, angleToPulse(0));
  // }
  // delay(1000);

  // for (int i = 0; i < 16; i++) {
  //   pwm.setPWM(i, 0, angleToPulse(45));
  // }
  // delay(1000);

  // for (int i = 0; i < 16; i++) {
  //   pwm.setPWM(i, 0, angleToPulse(90));
  // }
  // delay(1000);

  // for (int i = 0; i < 16; i++) {
  //   pwm.setPWM(i, 0, angleToPulse(135));
  // }
  // delay(1000);

  // for (int i = 0; i < 16; i++) {
  //   pwm.setPWM(i, 0, angleToPulse(180));
  // }
  // delay(1000);


}

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
  }
  delay(2000);

  Serial.println(idle[11]);

  for (int i = 0; i < 16; i++) {

    pwm.setPWM(i, 0, angleToPulse(idle[i]));
  }
  delay(2000);
}

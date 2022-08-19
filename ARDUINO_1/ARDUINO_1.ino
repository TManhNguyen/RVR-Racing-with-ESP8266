#include <SoftwareSerial.h>
#include <SpheroRVR.h>


static DriveControl driveControl;

int x = 50;



void setup() {
  rvr.configUART(&Serial);
  driveControl = rvr.getDriveControl();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

void loop() {
  int speed_l = 75;
  int speed_r = 75;
  int off_set = 0;

  int a0 = digitalRead(A0);
  int a1 = digitalRead(A1);
  int a2 = digitalRead(A2);
  int a3 = digitalRead(A3);
  int a4 = digitalRead(A4);

  if (a2 == LOW && a3 == LOW && a4 == LOW) {off_set = 0;  }
  if (a2 == HIGH && a3 == LOW && a4 == LOW) {off_set = -55;}
  if (a2 == LOW && a3 == LOW && a4 == HIGH) {off_set = 55;}
  if (a2 == HIGH && a3 == HIGH && a4 == LOW) {off_set = -75;}
  if (a2 == LOW && a3 == HIGH && a4 == HIGH) {off_set = 75;}
  speed_l = speed_l + off_set;
  speed_r = speed_r - off_set;


  if (a0 == LOW && a1 == LOW) {
    driveControl.setRawMotors(rawMotorModes::off, 0, rawMotorModes::off, 0);
  } if (a0 == LOW && a1 == HIGH) {
    driveControl.setRawMotors(rawMotorModes::forward, speed_l, rawMotorModes::forward, speed_r);
  } if (a0 == HIGH && a1 == LOW) {
    driveControl.setRawMotors(rawMotorModes::reverse, speed_l / 1.2, rawMotorModes::reverse, speed_r / 1.2);
  } if (a0 == HIGH && a1 == HIGH) {
    driveControl.setRawMotors(rawMotorModes::forward, 150, rawMotorModes::forward, 150);
    delay(1500);
    driveControl.setRawMotors(rawMotorModes::off, 0, rawMotorModes::off, 0);
  }

}

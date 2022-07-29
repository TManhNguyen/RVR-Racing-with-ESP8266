#include <SoftwareSerial.h>
#include <SpheroRVR.h>

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


static DriveControl driveControl;

int x = 50;
int filterArray[20];
int last_last_cm = 0;
int last_cm = 0;
int this_cm = 0;
int avg_value = 30;

void setup() {
  //  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  rvr.configUART(&Serial);
  driveControl = rvr.getDriveControl();
}

void loop() {
  for (int sample = 0; sample < 20; sample++) {
    this_cm = sonar.ping_cm();
    filterArray[sample] = this_cm;
  }
  for (int i = 0; i < 19; i++) {
    for (int j = i + 1; j < 20; j++) {
      if (filterArray[i] > filterArray[j]) {
        int swap = filterArray[i];
        filterArray[i] = filterArray[j];
        filterArray[j] = swap;
      }
    }
  }
  long sum = 0;
  for (int sample = 7; sample < 17; sample++) {
    sum += filterArray[sample];
  }
  avg_value = sum / 10;

  if (avg_value == 0 && last_cm == 0 && last_last_cm == 0) {
    //    Serial.println("Turning_____________________________");
    driveControl.setRawMotors(rawMotorModes::forward, 100, rawMotorModes::forward, 75);
    delay(750);
    driveControl.setRawMotors(rawMotorModes::off, 0, rawMotorModes::off, 0);
  }

  if (0 < avg_value && avg_value < 60 && 0 < last_cm && last_cm < 60) {
    int off_set = (60 - avg_value) * 1.3;
    driveControl.setRawMotors(rawMotorModes::forward, 75 - off_set, rawMotorModes::forward, 75 + off_set);
    delay(150);
  }  if (400 >= avg_value && avg_value > 180 && 400 >= last_cm && last_cm > 180) {
    int off_set = (avg_value - 180 * 1.1);
    if (off_set > 50) {
      off_set = 35;
    }
    driveControl.setRawMotors(rawMotorModes::forward, 75 + off_set, rawMotorModes::forward, 75 - off_set);
    delay(150);
  }  if (180 >= avg_value && avg_value > 80 && 180 >= avg_value && last_cm > 80) {
    int off_set = (avg_value - 80) * 1.3;
    if (off_set > 50) {
      off_set = 35;
    }
    driveControl.setRawMotors(rawMotorModes::forward, 75 + off_set, rawMotorModes::forward, 75 - off_set);
    delay(150);
  } if (60 <= this_cm && this_cm <= 80 && 60 <= last_cm && last_cm <= 80) {
    driveControl.setRawMotors(rawMotorModes::forward, 75, rawMotorModes::forward, 75);
  }

  //Clear stack
  last_last_cm = last_cm;
  last_cm = avg_value;

  // print the value to Serial Monitor
  //  Serial.print("average value: ");
  //  Serial.println(avg_value);
}

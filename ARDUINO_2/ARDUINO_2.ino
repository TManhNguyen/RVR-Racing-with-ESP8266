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

void setup() {
//  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  rvr.configUART(&Serial);
  driveControl = rvr.getDriveControl();
}

void loop() {
  for (int sample = 0; sample < 20; sample++) {
    this_cm = sonar.ping_cm();
    filterArray[sample] = this_cm;
    delay(5);
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
  int avg_value = sum / 10;

  if (this_cm > 250 && last_cm > 250 && last_last_cm > 250) {
//    Serial.println("Turning_____________________________");
    driveControl.setRawMotors(rawMotorModes::off, 0, rawMotorModes::off, 0);
    driveControl.setHeading(0);
    driveControl.rollStart(30, 64);
    delay(800);
    driveControl.rollStop(30);
    delay(300);
  }

  int off_set = ((this_cm+last_cm)/2) - ((last_cm+last_last_cm)/2);
  driveControl.setRawMotors(rawMotorModes::forward, 75 + (off_set * 2), rawMotorModes::forward, 75 - (off_set * 2));
  delay(500);

  //Clear stack
  last_last_cm = last_cm;
  last_cm = this_cm;
  this_cm = 0;

  // print the value to Serial Monitor
//  Serial.print("average value: ");
//  Serial.println(avg_value);

}

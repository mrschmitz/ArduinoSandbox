/* 
Servo test sandbox code
*/

#include <Servo.h>

Servo servo_1;

int start_angle = 0; // degrees
int max_angle = 180; // degrees

int sleep_delay = 100; // LED sleep delay in ms between switching directions
int reset_delay = 1000; // delay for a reset (if we need it)

int step_delay = 100; // servo step delay in ms
int step_angle = 90; // degrees

void setup() {
  servo_1.attach(9); // control servo with I/O pin given

  // Reset servo to zero angle
  servo_1.write(start_angle);
  delay(step_delay * 2); // give it time to get there...

  // define LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int angle = start_angle;
  
  // Check servo to make sure it is at start_angle before we do the loop again.
  // If it is NOT (did something not keep up?) set it to the start angle.
  if( servo_1.read() != start_angle) {
    servo_1.write(start_angle);
    delay(reset_delay);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  delay(sleep_delay);
  digitalWrite(LED_BUILTIN, LOW);
  delay(sleep_delay);

  // Rotate from start_angle to max_angle in step_angle steps
  for (angle = start_angle; angle <= max_angle; angle += step_angle) {
    servo_1.write(angle);
    delay(step_delay);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  delay(sleep_delay);
  digitalWrite(LED_BUILTIN, LOW);
  delay(sleep_delay);

  // Rotate from max_angle to start_angle in step_angle steps
  for (angle = max_angle; angle >= start_angle; angle -= step_angle) { 
    servo_1.write(angle);
    delay(step_delay);
  }
}

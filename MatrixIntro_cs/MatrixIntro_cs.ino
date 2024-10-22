/*
  Heart Animation (+ Heartbeat) Sketch
  
  This is based on the default sketch that comes
  shipped with every UNO R4 WiFi board.

  After the setup animation (Tetris-style and a heart)
  is complete, the built-in LED blinks and the heart
  beats infinitely.

  No additional circuit required.

  Originally created 26 Jun 2023
  by Martino Facchin
  See the (original) full documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix

  Modified/forked 2024
  by Cory Schmitz
*/

// include the LED Matrix library from the Uno R4 core:
#include "Arduino_LED_Matrix.h"
// make an instance of the library:
ArduinoLEDMatrix matrix;
//include the "animation.h" header file that stores the frames for the animation 
#include "animation.h"

static bool startup_loaded = false;

void setup() {
  Serial.begin(115200);
  //load frames from the animation.h file
  matrix.loadSequence(frames);
  // start the matrix
  matrix.begin();
  
  // turn on autoscroll to avoid calling next() to show the next frame; the paramenter is in milliseconds
  // matrix.autoscroll(300);

  //play the animation on the matrix
  matrix.play(true);

  //define LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // Indicate we are loading...
  digitalWrite(LED_BUILTIN, HIGH);
}

static void system_heartbeat() {
  /* 
   * Blink the built-in LED and beat the matrix heart
   * with a delay in the loop
   * TODO: Change this to an ISR...
   */

  // Big heart
  digitalWrite(LED_BUILTIN, HIGH);
  matrix.loadFrame(heartbeat[0]);
  delay(500);
  // Little heart
  digitalWrite(LED_BUILTIN, LOW);
  matrix.loadFrame(heartbeat[1]);
  delay(1000);
}

void loop() {
  // Only begin the LED matrix heartbeat after the setup sequence is done
  if( matrix.sequenceDone() ) {
    matrix.play(false);
    startup_loaded = true;
  }

  if (startup_loaded)
    system_heartbeat();
}

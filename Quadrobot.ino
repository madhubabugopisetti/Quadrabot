#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca(0x40);

/* =====================================================
   PCA SERVO LIMITS
   ===================================================== */
#define SERVO_MIN 100
#define SERVO_MID 320
#define SERVO_MAX 524

/* =====================================================
   NEUTRAL & BALANCE
   ===================================================== */
#define NEUTRAL 90

// Coxa preload to shift body forward
#define COXA_NEUTRAL_FWD 100   // front legs
#define COXA_NEUTRAL_BWD 80    // back legs

/* =====================================================
   FEMUR LIFT (PER LEG)
   Rear legs lift LESS because robot is rear-heavy
   ===================================================== */
#define FEMUR_LIFT_LF  60
#define FEMUR_LIFT_RF 120
#define FEMUR_LIFT_LB 100
#define FEMUR_LIFT_RB  80

/* =====================================================
   COXA FORWARD (PER LEG)
   ===================================================== */
#define COXA_FWD_LF 110
#define COXA_FWD_RF  70
#define COXA_FWD_LB 110
#define COXA_FWD_RB  70

/* =====================================================
   TIMING
   ===================================================== */
#define MOVE_DELAY 5
#define STEP_DELAY 80

/* =====================================================
   LOW-LEVEL SERVO CONTROL
   ===================================================== */
void setServo(uint8_t ch, int angle) {
  angle = constrain(angle, 0, 180);
  int pulse;
  if (angle <= 90)
    pulse = map(angle, 0, 90, SERVO_MIN, SERVO_MID);
  else
    pulse = map(angle, 90, 180, SERVO_MID, SERVO_MAX);
  pca.setPWM(ch, 0, pulse);
}

void moveServo(uint8_t ch, int from, int to) {
  if (from < to) {
    for (int a = from; a <= to; a++) {
      setServo(ch, a);
      delay(MOVE_DELAY);
    }
  } else {
    for (int a = from; a >= to; a--) {
      setServo(ch, a);
      delay(MOVE_DELAY);
    }
  }
}

/* =====================================================
   STAND (BALANCED FOR REAR HEAVY BODY)
   ===================================================== */
void stand() {
  // Tibias
  setServo(1,  NEUTRAL);
  setServo(7,  NEUTRAL);
  setServo(10, NEUTRAL);
  setServo(13, NEUTRAL);

  // Femurs
  setServo(3,  NEUTRAL);
  setServo(5,  NEUTRAL);
  setServo(9,  NEUTRAL);
  setServo(15, NEUTRAL);

  // Coxa preload (THIS IS THE KEY FIX)
  setServo(11, COXA_NEUTRAL_FWD); // Left Front
  setServo(14, COXA_NEUTRAL_FWD); // Right Front
  setServo(6,  COXA_NEUTRAL_BWD); // Left Back
  setServo(2,  COXA_NEUTRAL_BWD); // Right Back

  delay(600);
}

/* =====================================================
   STEP FUNCTIONS
   ===================================================== */

// LEFT FRONT
void stepLF() {
  moveServo(9,  NEUTRAL, FEMUR_LIFT_LF);
  moveServo(11, NEUTRAL, COXA_FWD_LF);
  moveServo(9,  FEMUR_LIFT_LF, NEUTRAL);
  moveServo(11, COXA_FWD_LF, NEUTRAL);
}

// RIGHT BACK
void stepRB() {
  moveServo(3, NEUTRAL, FEMUR_LIFT_RB);
  moveServo(2, NEUTRAL, COXA_FWD_RB);
  moveServo(3, FEMUR_LIFT_RB, NEUTRAL);
  moveServo(2, COXA_FWD_RB, NEUTRAL);
}

// RIGHT FRONT
void stepRF() {
  moveServo(15, NEUTRAL, FEMUR_LIFT_RF);
  moveServo(14, NEUTRAL, COXA_FWD_RF);
  moveServo(15, FEMUR_LIFT_RF, NEUTRAL);
  moveServo(14, COXA_FWD_RF, NEUTRAL);
}

// LEFT BACK
void stepLB() {
  moveServo(5, NEUTRAL, FEMUR_LIFT_LB);
  moveServo(6, NEUTRAL, COXA_FWD_LB);
  moveServo(5, FEMUR_LIFT_LB, NEUTRAL);
  moveServo(6, COXA_FWD_LB, NEUTRAL);
}

/* =====================================================
   WALK (REAR-HEAVY SAFE CRAWL)
   ===================================================== */
void walkForward() {
  stepLF(); delay(STEP_DELAY);
  stepRB(); delay(STEP_DELAY * 2); // rear support longer
  stepRF(); delay(STEP_DELAY);
  stepLB(); delay(STEP_DELAY * 2); // rear support longer
}

/* =====================================================
   SETUP & LOOP
   ===================================================== */
void setup() {
  Wire.begin(D2, D1);   // ESP8266 I2C
  pca.begin();
  pca.setPWMFreq(50);
  stand();
}

void loop() {
  walkForward();
}

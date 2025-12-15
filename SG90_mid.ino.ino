#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

// ===== CALIBRATED VALUES =====
#define SERVO_MIN 100
#define SERVO_MID 320    // adjust slightly if needed
#define SERVO_MAX 524
// =============================

void setServoAngle(uint8_t ch, int angle) {
  angle = constrain(angle, 0, 180);
  int pulse;

  if (angle <= 90) {
    pulse = map(angle, 0, 90, SERVO_MIN, SERVO_MID);
  } else {
    pulse = map(angle, 90, 180, SERVO_MID, SERVO_MAX);
  }

  pca.setPWM(ch, 0, pulse);
}

void setup() {
  Serial.begin(115200);

  // I2C for Wemos D1 mini
  Wire.begin(D2, D1);

  pca.begin();
  pca.setPWMFreq(50);

  // Hold servo safely at center
  setServoAngle(0, 90);

  Serial.println("READY");
  Serial.println("Enter angle (0–180) for servo on channel 0:");
}

void loop() {
  if (Serial.available()) {
    int angle = Serial.parseInt();

    if (angle >= 0 && angle <= 180) {
      setServoAngle(0, angle);
      Serial.print("Servo moved to angle: ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid angle. Use 0–180.");
    }

    Serial.readStringUntil('\n');
  }
}

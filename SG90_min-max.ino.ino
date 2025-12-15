#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);     // SDA, SCL

  pca.begin();
  pca.setPWMFreq(50);

  // Stop servo on boot
  pca.setPWM(0, 0, 0);

  Serial.println("Channel 0 servo test");
  Serial.println("Enter PWM value (e.g. 100–600) and press Enter:");
}

void loop() {
  if (Serial.available()) {
    int pulse = Serial.parseInt();

    if (pulse >= 0 && pulse <= 800) {
      pca.setPWM(0, 0, pulse);
      Serial.print("PWM set to: ");
      Serial.println(pulse);
    } else {
      Serial.println("Out of range");
    }

    Serial.readStringUntil('\n');
  }
}

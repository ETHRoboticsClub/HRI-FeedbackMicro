#include <Wire.h>
#include <Adafruit_DRV2605.h>

Adafruit_DRV2605 drv;
const int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  if (!drv.begin()) {
    Serial.println("DRV2605L not found - check SDA/SCL/power");
    while (1);
  }
  drv.useERM();                         // we have a coin ERM motor
  drv.setMode(DRV2605_MODE_REALTIME);   // we set the strength directly
}

void loop() {
  int force = analogRead(sensorPin);    // 0–1023
  int strength = 0;
  if (force > 20) {                     // ignore tiny readings
    strength = map(force, 20, 1023, 40, 127);  // driver takes 0–127
  }
  drv.setRealtimeValue(strength);

  Serial.print("force: "); Serial.print(force);
  Serial.print("  strength: "); Serial.println(strength);
  delay(20);
}
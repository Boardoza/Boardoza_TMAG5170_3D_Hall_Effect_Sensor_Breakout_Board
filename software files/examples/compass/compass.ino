#include <TMAG5170.h>

TMAG5170 mag(5);   // CS = GPIO5 (VSPI SS)

void setup() {
  Serial.begin(115200);
  mag.begin();
  mag.initForEval();
  delay(1000);
}

void loop() {
  Serial.print("X(mT): ");   Serial.println(mag.getX(),  3);
  Serial.print("Y(mT): ");   Serial.println(mag.getY(),  3);
  Serial.print("Z(mT): ");   Serial.println(mag.getZ(),  3);
  Serial.print("Temp(C): "); Serial.println(mag.getTemperature(), 2);
  Serial.print("Angle: ");   Serial.println(mag.getAngle(), 2);
  Serial.println();

  delay(500);
}
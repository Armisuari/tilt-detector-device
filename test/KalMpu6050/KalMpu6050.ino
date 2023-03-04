#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t accX, accY, accZ;
int16_t gyroX, gyroY, gyroZ;

int16_t accX_offset, accY_offset, accZ_offset;
int16_t gyroX_offset, gyroY_offset, gyroZ_offset;

const int num_calibration_samples = 1000;
int samples_collected = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  mpu.initialize();
  mpu.setFullScaleAccelRange(2);
  mpu.setFullScaleGyroRange(250);

  Serial.println("Calibrating MPU6050, please wait...");

  while (samples_collected < num_calibration_samples) {
    mpu.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);

    accX_offset += accX;
    accY_offset += accY;
    accZ_offset += accZ;

    gyroX_offset += gyroX;
    gyroY_offset += gyroY;
    gyroZ_offset += gyroZ;

    samples_collected++;
  }

  accX_offset /= num_calibration_samples;
  accY_offset /= num_calibration_samples;
  accZ_offset /= num_calibration_samples;

  gyroX_offset /= num_calibration_samples;
  gyroY_offset /= num_calibration_samples;
  gyroZ_offset /= num_calibration_samples;

  Serial.println("Calibration completed!");
}

void loop() {
  mpu.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);

  accX -= accX_offset;
  accY -= accY_offset;
  accZ -= accZ_offset;

  gyroX -= gyroX_offset;
  gyroY -= gyroY_offset;
  gyroZ -= gyroZ_offset;

  Serial.print("AccX: ");
  Serial.print(accX);
  Serial.print("   AccY: ");
  Serial.print(accY);
  Serial.print("   AccZ: ");
  Serial.print(accZ);

  Serial.print("   GyroX: ");
  Serial.print(gyroX);
  Serial.print("   GyroY: ");
  Serial.print(gyroY);
  Serial.print("   GyroZ: ");
  Serial.println(gyroZ);
}

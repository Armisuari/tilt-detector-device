#pragma once

#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

unsigned long previousMillis = 0;
const long INTERVAL = 10000;

void sensor_setup()
{
    Wire.begin();

    byte status = mpu.begin();
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    while (status != 0)
    {
    } // stop everything if could not connect to MPU6050

    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);

    mpu.calcOffsets(); // gyro and accelero
    Serial.println("Done!\n");
}

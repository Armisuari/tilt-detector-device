#include <Arduino.h>
#include <WiFi.h>

#include "sensorHandler.hpp"
#include "communication.hpp"

// fitur
// 1. read gyro
// 2. Komunikasi whatsapp
// 3. kalibrasi gyro based on tiang normal

const char *ssid = "Mino";
const char *password = "Minomanusiwa11";

thingESP wifi_set;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  wifi_set.begin(ssid, password);
  setup_thingESP();
  sensor_setup();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // put your main code here, to run repeatedly:
  mpu.update();
  thing.Handle();

  if ((millis() - timer) > 1000)
  { // print data every 10ms
    Serial.print("X : ");
    Serial.print(mpu.getAngleX());
    Serial.print("\tY : ");
    Serial.print(mpu.getAngleY());
    Serial.print("\tZ : ");
    Serial.println(mpu.getAngleZ());
    timer = millis();
  }
}

String HandleResponse(String query)
{

  String mulai = "Selamat Datang, Silahkan Pilih Nomor dibawah ini : \n";
  mulai += "1. cek kemiringan\n";
  mulai += "2. kalibrasi";
  mpu.update();
  String dataa = "Data Kemiringan \n";
  dataa += "X : " + String(mpu.getAngleX()) + "\n";
  dataa += "Y : " + String(mpu.getAngleY()) + "\n";
  dataa += "Z : " + String(mpu.getAngleZ()) + " ";

  if (query == "start")
  {
    return mulai;
  }
  else
    return "Your query was invalid..";
}

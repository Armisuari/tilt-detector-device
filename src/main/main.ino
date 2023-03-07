#include <Arduino.h>
#include <WiFi.h>

#include "sensorHandler.hpp"
#include "communication.hpp"
#include "log_data.hPP"

// fitur
// 1. read gyro
// 2. Komunikasi whatsapp
// 3. kalibrasi gyro based on tiang normal
// 4. download data ke webserver esp32

const char *ssid = "Mino";
const char *password = "Minomanusiwa11";

thingESP wifi_set;
Spiffs spiffs;

String payload;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  wifi_set.begin(ssid, password);
  spiffs.begin();
  setup_thingESP();
  sensor_setup();

  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS mounted successfully");

  server.on("/download", HTTP_GET, handleFileDownload);

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  // put your main code here, to run repeatedly:
  mpu.update();
  thing.Handle();
  
  String data = "X : " + String(mpu.getAngleX()) + "\n";
  data += "|  Y : " + String(mpu.getAngleY()) + "\n";
  data += "|  Z : " + String(mpu.getAngleZ()) + " ";
  Serial.print(data);
  spiffs.save_data(data);

  delay(1000);
  
}

String HandleResponse(String query)
{
  String mulai = "Selamat Datang, Silahkan Pilih Nomor dibawah ini : \n";
  mulai += "1. cek kemiringan\n";
  mulai += "2. link data download";
  mpu.update();
  String dataa = "Data Kemiringan \n";
  dataa += "X : " + String(mpu.getAngleX()) + "\n";
  dataa += "Y : " + String(mpu.getAngleY()) + "\n";
  dataa += "Z : " + String(mpu.getAngleZ()) + " ";
  String tempat = "Copy Link Data\n";
  tempat += "192.168.1.11/download?file=data.txt";
  

  if (query == "start")
  {
    return mulai;
  }
   else if (query == "1")
  {
    return dataa;
  }
     else if (query == "2")
  {
    return tempat;
  }
  else
    return "Your query was invalid..";
}

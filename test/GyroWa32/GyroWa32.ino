#include <WiFi.h>
//#include <ESP8266WiFi.h>
#include <ThingESP.h>
#include "Wire.h"
#include <MPU6050_light.h>

const char* ssid = "Mino";
const char* password = "Minomanusiwa11";

MPU6050 mpu(Wire);
unsigned long timer = 0;

ThingESP32 thing("BossHQ", "botwasaja", "botwasaja12");


unsigned long previousMillis = 0;
const long INTERVAL = 6000; 

void setup() {
  
  Serial.begin(115200);
  
  Wire.begin();
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  thing.SetWiFi(ssid, password);
  thing.initDevice();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");



}
String HandleResponse(String query){

  
   String mulai = "Selamat Datang, Silahkan Pilih Nomor dibawah ini : \n";
   mulai += "1. cek kemiringan\n";
   mulai += "2. kalibrasi";
   mpu.update();
   String dataa = "Data Kemiringan \n";
   dataa += "X : " + String(mpu.getAngleX()) +"\n";
   dataa += "Y : " + String(mpu.getAngleY()) +"\n";
   dataa += "Z : " + String(mpu.getAngleZ()) +" ";

  if (query == "start") {
   
    return mulai;
  }

  else if (query == "1") {
  
    return dataa;
  }
//    else if (query == "2") {
//  
//    return ;
//  }
 
  else return "Your query was invalid..";

}

void loop() {
  mpu.update();
  thing.Handle();

  if((millis()-timer)>1000){ // print data every 10ms
  Serial.print("X : ");
  Serial.print(mpu.getAngleX());
  Serial.print("\tY : ");
  Serial.print(mpu.getAngleY());
  Serial.print("\tZ : ");
  Serial.println(mpu.getAngleZ());
  timer = millis();  
  }

}

#include "SPIFFS.h"
#include <WebServer.h>

WebServer server(80);

void readFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  
}void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Appending to file: %s\r\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("- failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("- message appended");
  } else {
    Serial.println("- append failed");
  }
  file.close();
}

struct Spiffs {
  Spiffs() {}

  void begin() {
    if (!SPIFFS.begin(true)) {
      Serial.println("SPIFFS initialization failed...");
    } else {
      Serial.println(F("SPIFFS initialized... file access enabled..."));
    }
  }

  void save_data(String payload) {
    File file = SPIFFS.open("/data.txt", FILE_WRITE);
    file.print(payload);
    file.close();
  }
    void read_data() {
    readFile(SPIFFS, "/data.txt");
  }

  void append(String payload){
    appendFile(SPIFFS, "/data.txt", payload.c_str());
  }
};

void handleFileDownload() {
  String fileName = server.arg("file");
  File file = SPIFFS.open("/" + fileName, "r");
  if (!file) {
    server.send(404, "text/plain", "File not found.");
    return;
  }
  server.sendHeader("Content-Disposition", "attachment; filename=" + fileName);
  server.streamFile(file, "application/octet-stream");
  file.close();
}

#include <SPI.h>
#include <SD.h>
#include <HTTPClient.h>
#include <WiFi.h>
#define SD_CS 5

//path for sd card
const char* path="/sourceF.txt";

//url for http
const char* url="https://raw.githubusercontent.com/dee362-lab/smart-parking-system/main/highfile";

//wifi credential
const char* username="Wokwi-GUEST";
const char* password="";


//creat the objects
HTTPClient http;

//wificonnection checking
void wificheking(){
    while(WiFi.status()!=WL_CONNECTED){
     Serial.println("conecting wifi..");
    delay(500);
    }
    Serial.println("Wifi is connected");

}
//for downloading the file
void downloadfile(const char* path,const char* url){
  
  http.begin(url);
  SD.begin();
    if (!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }
  int httpres=http.GET();
  if(httpres==200){
    File file=SD.open(path,"w");
    if(!file){
      Serial.println("cannot open the file ");
      return;
    }
        WiFiClient* stream = http.getStreamPtr();
    uint8_t buffer[512];
    size_t size;
    unsigned long start = millis();
    int totalbyte=0;
    

    while (http.connected() && (size = stream->available())) {
      size = stream->read(buffer, sizeof(buffer));
      file.write(buffer, size);
      totalbyte+=size;
    }

    file.close();
    unsigned long duration = millis() - start;
    int speed=totalbyte/duration;
    Serial.printf("File downloaded and saved to SD card in %lu ms\n", duration);
    Serial.printf("total bytes %d \n",totalbyte);
    Serial.printf("total download spedd is %d kBps\n",speed);
  
  }
  else {
    Serial.printf("http error %d",httpres);
  }
  http.end();
}

void readfile(const char* path){
  File file=SD.open(path,"r");
  if(!file){
    Serial.print("cannnot oen the file for reading");
  }
  while(file.available()){
    Serial.write(file.read());
  }
file.close();
}
void setup() {
  Serial.begin(115200);
  WiFi.begin(username,password);
  wificheking();
  downloadfile(path,url);
  readfile(path);
}

void loop() {
}

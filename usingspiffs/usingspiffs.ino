#include<WiFi.h>
#include<SPIFFS.h>
#include<HTTPClient.h>
#include<FS.h>
#include<WiFiClientSecure.h>

const char* path="/sfile.txt";
const char* url="https://raw.githubusercontent.com/dee362-lab/smart-parking-system/main/highfile";
//for wifi connection
const char* Username="Wokwi-GUEST";
const char* password="";

WiFiClientSecure client;
HTTPClient http;


void wificonnect(){
  while(WiFi.status()!=WL_CONNECTED){
    Serial.println("wifi is connectig...");
    delay(500);
  }
  Serial.println("wifi is connected");
}
void downloadfile(const char* path,const char* url){

  http.begin(url);

  int httpres=http.GET();
  Serial.println(httpres);

  if(httpres==200){

    File file=SPIFFS.open(path,"w");


    if(!file){
      Serial.println("cannot open the file");
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
    Serial.printf("File downloaded and saved to SPIFFS in %lu ms\n", duration);
    Serial.printf("total bytes %d \n",totalbyte);
  }
  

 else {

  Serial.printf("http error %d",httpres);

 }
 http.end();
}
void readfile(const char* path){
  File file=SPIFFS.open(path,"r");
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
  Serial.println("Hello, ESP32!");
  WiFi.begin(Username,password);
  client.setInsecure();
  wificonnect();
  delay(500);
  downloadfile(path,url);
  readfile(path);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

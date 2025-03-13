#include<WiFi.h>
#include<SPIFFS.h>
#include<HTTPClient.h>
#include<FS.h>
#include<WiFiClientSecure.h>

// File path to store the downloaded file in SPIFFS
const char* path="/sfile.txt";  
// Github url
const char* url="https://raw.githubusercontent.com/dee362-lab/smart-parking-system/main/highfile";
// Wi-Fi credentials
const char* Username="Wokwi-GUEST";
const char* password="";

// Creating WiFi client and HTTP objects
WiFiClientSecure client;
HTTPClient http;

// Function to connect to Wi-Fi
void wificonnect(){
  if(WiFi.status()!=WL_CONNECTED){
    WiFi.disconnect();
    WiFi.begin(Username, password);// Start Wi-Fi connection
    Serial.println("wifi is connectig");

    int attempts=0;
    while(WiFi.status()!=WL_CONNECTED && attempts<20){// Retry up to 10 times
      attempts+=1;
      delay(500);
      Serial.println(".");
    }
    if(WiFi.status()==WL_CONNECTED){
      Serial.println("\nwifi connected");
    }
    else{
      Serial.println("\nwifi fail to connect");
    }
  }
}
// Function to download and write the file to SPIFFS
void downloadfile(const char* path,const char* url){
 // Check available space on SPIFFS before downloading  
 // Ensure at least 2KB of free space for stable file writing  
  uint64_t freeSpace = SPIFFS.totalBytes() - SPIFFS.usedBytes(); 
  if (freeSpace < 2048) { // Minimum 2KB needed
    Serial.println("Insufficient space on SPIFFS");
    return;}
  int maxtry=3;// Maximum number of retry attempts
  int attempt=0;
  while(attempt<=maxtry){

    http.setTimeout(10000);//timout time for the http request 
    http.begin(client,url);// Begin the HTTP request using secure client

    int httpres=http.GET();// Send GET request

    if(httpres==200){// HTTP success
      // Open file in SPIFFS for writing
      File file=SPIFFS.open(path,"w");
      if(!file){
        Serial.println("cannot open the file");
        return;
      }
      // Get the data stream from the server
      WiFiClient* stream = http.getStreamPtr();
      uint8_t buffer[1024];// Buffer size for reading data
      size_t size;
      unsigned long start = millis();// Start time for measuring download duration
      int totalbyte=0;

      // Read the data stream and write it to the file
      while (http.connected() && (size = stream->available())) {
        size = stream->read(buffer, sizeof(buffer));
        file.write(buffer, size);
        totalbyte+=size;
      }

      file.close();// Close the file after writing
      unsigned long duration = millis() - start;// Calculate time taken
      float speed = (totalbyte/1024)/(duration/1000);//download and write speed
      Serial.printf("download and write speed : %d ",speed);
      Serial.printf("File downloaded and saved to SPIFFS in %lu ms\n", duration);
      Serial.printf("download file size: %d \n",totalbyte);
      break;
  }
  else {
    // If download fails, retry
    Serial.printf("http error %d retrying...\n",httpres);
    attempt+=1;
  
    }
  if(maxtry==attempt){
    Serial.println("HTTP request failed after multiple attempts");
  }
  http.end();// Close the connection
}}
void readfile(const char* path){
  // Open the file in read mode
  File file=SPIFFS.open(path,"r");
  if(!file){
    Serial.print("cannnot oen the file for reading");
  }

  // Read and print file content to Serial Monito
  while(file.available()){
    Serial.write(file.read());
  }

file.close();// Close the file after reading
}

void setup() { 
  Serial.begin(115200);
  wificonnect();//initialize wifi
  delay(500);

  // Initialize SPIFFS file system
  if(!SPIFFS.begin()){
   Serial.println("fail to initialize SPIFFS\n ");
  }

  // Download the file and read it
  downloadfile(path,url);
  readfile(path);
}

void loop() {
  //nothing needed here

}

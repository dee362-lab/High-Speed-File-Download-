# 🚀 High-Speed File Download to SPIFFS on ESP32  

## 📖 Table of Contents  
- [Overview](#-overview)  
- [Technologies Used](#-technologies-used)  
- [Features](#-features)  
- [Setup & Installation](#-setup--installation)  
- [Testing & Validation](#-testing--validation)  
- [License](#-license)  

## 🔍 Overview  
This project implements a high-speed file download and storage system on the ESP32. It downloads a file from a public HTTPS URL and writes it to SPIFFS (SPI Flash File System) with a target download + write speed of at least **400KBps**.  

## 🛠️ Technologies Used  
- **Microcontroller:** ESP32 Dev Kit  
- **File System:** SPIFFS  
- **Network:** Wi-Fi  
- **Protocol:** HTTPS (using `WiFiClientSecure`)  
- **IDE:** Arduino IDE  

## 🚀 Features  
✅ Downloads a file from a public HTTPS URL  
✅ Writes the file to SPIFFS with at least 400KBps speed  
✅ Logs download and write speed  
✅ Handles network failures and retries  

## 🔧 Setup & Installation  
1. **Install ESP32 Board in Arduino IDE:**  
   - Go to **File > Preferences**  
   - Add the following URL in **Additional Board Manager URLs:**  
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to **Tools > Board > Board Manager** and install **"ESP32 by Espressif Systems"**  

2. **Connect the ESP32 to Wi-Fi:**  
   - Modify the following section in the code:  
     ```cpp
     const char* Username = "Your_SSID";
     const char* password = "Your_PASSWORD";
     ```

3. **Upload the Code:**  
   - Open the code in Arduino IDE  
   - Select **"ESP32 Dev Module"** from the board list  
   - Click **Upload**  

4. **Monitor Output:**  
   - Open **Serial Monitor**  
   - Set baud rate to **115200**  

## 🧪 Testing & Validation  
✅ Measure download and write speed using `Serial Monitor`  
✅ Ensure that the download speed meets the 400KBps target  
✅ Test with different file sizes to validate stability  

## 📜 License  
This project is open-source under the [MIT License](LICENSE).  
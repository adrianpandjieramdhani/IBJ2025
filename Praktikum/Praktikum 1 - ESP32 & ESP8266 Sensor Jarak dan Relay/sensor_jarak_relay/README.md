# PRAKTIKUM 1 - Instalasi driver untuk ESP32 & ESP8266 serta uji coba sensor jarak dan relay
Sebelum memulai praktikum, pastikan untuk lakukan instalasi beberapa software penunjang yang akan digunakan selama praktikum. Yaitu:
1. Install dan buka Arduino IDE
https://www.arduino.cc/en/software
2. Install driver ESP32 dan ESP8266
Driver yang digunakan adalah ch340, silakan install dengan link berikut.
https://www.arduined.eu/ch340-windows-10-driver-download/
3. Setelah itu, buka program Arduino IDE, klik Board Manager seperti yang terlampir dalam gambar berikut.
<img width="473" height="426" alt="image" src="https://github.com/user-attachments/assets/4f353ef2-2cf7-46bd-9a96-16fd5e5f4778" />
4. Tambahkan board ESP32 pada board manager (esp32 by Espressif)
5. Tambahkan board ESP8266 (esp8266 by ESP8266)
6. Setelah selesai, tambahkan library yang diinginkan dengan membuka library manager seperti pada gambar berikut.
<img width="448" height="488" alt="image" src="https://github.com/user-attachments/assets/09719a91-6ad0-4a3c-9d0d-7f433556ab48" />
Kemudian cari library yang diperlukan untuk mengoperasikan perangkat yang digunakan dalam IoT kit laboratorium. Beberapa di antaranya:

- DHT11 (DHT sensor library by Adafruit)
- Sparkfun APDS9960 RGB and Gesture Sensor (Arduino APDS9960 by Arduino)
- BH1750 (by Christopher Laws)
- Fingerprint (Adafruit Fingerprint Sensor Library by adafruit)
- RFID (MFRC522 by Github community)
- I2C (LiquidCrystal I2C by Frank de Brabander)
- BMP085 (Adafruit BMP085 Library by Adafruit)

7. Setelah selesai, silakan lanjutkan dengan membuat code (contoh code terlampir dalam folder repository ini).

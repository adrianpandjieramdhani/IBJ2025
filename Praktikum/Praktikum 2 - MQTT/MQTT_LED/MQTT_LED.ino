 // Import Library
#include <WiFi.h>
#include <PubSubClient.h>

 // Setup MQTT di sini, sesuaikan dengan Access Point yang digunakan (Hotspot / WiFi yang digunakan untuk IoT)
 // Pada MQTT, ada beberapa istilah yang perlu dipahami
 // Broker    = Bayangkan broker adalah "kantor pos informasi", sehingga segala informasi yang bertukar di MQTT harus melewati Broker "kantor pos" ini
 // Subscribe = Bayangkan Anda berlangganan pada "kantor pos informasi" ini, sehingga segala publikasi yang diberikan oleh kantor pos informasi akan disampaikan kepada SEMUA
 //             PELANGGAN "kantor pos informasi" ini.
 // Publish   = Ini berarti "menerbitkan" informasi baru ke "kantor pos". Nantinya "kantor pos informasi" akan menerbitkan informasi tersebut ke semua pelanggan yang sudah
 //             berlangganan ke "kantor pos informasi"
const char* ssid = "Username WiFi kamu";
const char* password = "Password WiFi kamu";
 // Setup MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/adrian/in"; // Contoh topic, dibebaskan
const char *topicout = "esp32/adrian/out"; // Contoh topic, dibebaskan
const char *mqtt_username = "username_kamu";
const char *mqtt_password = "password_kamu";
const int mqtt_port = 1883;

 // Setup WiFi client di ESP32
WiFiClient espClient;
PubSubClient client(espClient);

 // Definisikan variable untuk pesan
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

 // Definisikan LED
#define LED_BUILTIN 2

 // Setup (nyalakan) WiFi
void setup_wifi() {
  delay(10);
  // Menyambungkan ke jaringan WiFi terlebih dahulu
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Jika gagal connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  // Jika berhasil connect
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

 // Callback untuk komunikasi melalui topic
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // About You, eh LED hehe
  // Switch on the LED if a 1 was received as first character, jadi LED akan nyala saat value "1" dari payload diterima
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
    // Intinya, ESP menganggap "active" itu pada kondisi voltage LOW, sehingga kita set tegangan LOW untuk "menyalakan" LED.
  } else {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH, kebalikan menyalakan LED.
  }
}

 // Menghubungkan ke client MQTT, lakukan reconnect jika gagal
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "Tes_MQTT";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // PERHATIKAN "TOPIC" yang digunakan (Lihat kembali pada definisi di awal)
      client.publish(topicout, "hello world");
      // ... and resubscribe
      client.subscribe(topic);
    } else { // Notifikasi gagal
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // BUILTIN_LED dibuat menjadi OUTPUT
  Serial.begin(115200);             // Definisikan serial monitor
  setup_wifi();                     // Jalankan fungsi setup_wifi()
  client.setServer(mqtt_broker, mqtt_port); // Nyalakan server mqtt
  client.setCallback(callback); // Nyalakan callback untuk komunikasi
}

void loop() {
  // Jika fungsi client.connected() gagal, lakukan fungsi reconnect()
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Register publikasi pesan di MQTT untuk ditampilkan di serial monitor dan ketika ESP32 melakukan publish, akan muncul dan dilakukan suatu fungsi
  // Sesuai yang sudah didefinisikan sebelumnya
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topicout, msg);
  }

}

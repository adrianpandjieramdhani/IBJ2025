const int trigPin = 5;
const int echoPin = 18;
// Library (kondisional, tambahkan sesuai kebutuhan)
#include <Wire.h>
// Definisikan pin untuk relay
#define RL 16
// Definisikan kecepatan gelombang suara (ultrasonic) dalam cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
// Definisikan variable
long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200);
  // Setup sensor jarak dan relay
  pinMode(trigPin, OUTPUT); // Jadikan trigPin sebagai OUTPUT
  pinMode(echoPin, INPUT); // Jadikan echoPin sebagai INPUT
  pinMode(RL, OUTPUT); // Jadikan Relay sebagai OUTPUT

}

void loop() {
  // Looping untuk sensor jarak
  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set trigPin menjadi HIGH dalam 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca echoPin dengan menghitung travel time gelombang suara dalam microseconds
  duration = pulseIn(echoPin, HIGH);

  // Hitung jarak
  distanceCm = duration * SOUND_SPEED/2;

  // Konversi dalam Inch
  distanceInch = distanceCm * CM_TO_INCH;

  // Print informasi dalam serial monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (Inch): ");
  Serial.println(distanceInch);

  // Conditional statement untuk nyala-mati relay (RL = HIGH jika > 10cm)
  if (distanceCm > 10) {
    digitalWrite(RL, HIGH);
  } else {
    digitalWrite(RL, LOW);
  }

  delay(1000); // Delay 1 detik
}

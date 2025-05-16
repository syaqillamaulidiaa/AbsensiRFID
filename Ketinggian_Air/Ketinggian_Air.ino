// Pin sensor
const int waterLevelPin = A0;   // Sensor water level (analog)
const int trigPin = 9;          // Ultrasonic trig pin
const int echoPin = 10;         // Ultrasonic echo pin

// Variabel untuk ultrasonic
long duration;
float distanceCm;

// Kalibrasi batas sensor water level
const int waterLevelMin = 0;     // Nilai analog saat kering
const int waterLevelMax = 900;   // Nilai analog saat penuh (sesuaikan jika berbeda)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // --- Sensor Water Level (Analog) ---
  int waterLevelValue = analogRead(waterLevelPin);
  float voltage = waterLevelValue * (5.0 / 1023.0);

  // Konversi ke persen
  int waterPercent = map(waterLevelValue, waterLevelMin, waterLevelMax, 0, 100);
  // Batas supaya tidak over/negatif
  waterPercent = constrain(waterPercent, 0, 100);

  // --- Sensor Ultrasonik ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = (duration / 2.0) * 0.0343;

  // --- Tampilkan di Serial Monitor ---
  Serial.print("Water Level Sensor (Analog): ");
  Serial.print(waterLevelValue);
  Serial.print(" | Tegangan: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Ketinggian Air: ");
  Serial.print(waterPercent);
  Serial.print("% | Ultrasonik Jarak: ");
  Serial.print(distanceCm, 1);
  Serial.println(" cm");

  delay(1000); // Delay 1 detik
}

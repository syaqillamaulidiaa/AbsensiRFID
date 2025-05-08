// Pin LED
int ledMerah = 5;
int ledKuning = 6;
int ledHijau = 7;

void setup() {
  // Atur semua pin LED sebagai OUTPUT
  pinMode(ledMerah, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledHijau, OUTPUT);
}

void loop() {
  // --- Merah ON ---
  matikanSemuaLED(); // Pastikan semua mati
  digitalWrite(ledMerah, HIGH); // Hanya merah yang nyala
  delay(100); 

  // --- Kuning ON ---
  matikanSemuaLED();
  digitalWrite(ledKuning, HIGH); // Hanya kuning
  delay(100); 

  // --- Hijau ON ---
  matikanSemuaLED();
  digitalWrite(ledHijau, HIGH); // Hanya hijau
  delay(100); // 

  // --- Kuning ON lagi ---
  matikanSemuaLED();
  digitalWrite(ledKuning, HIGH);
  delay(100);
}

// Fungsi bantu untuk mematikan semua LED
void matikanSemuaLED() {
  digitalWrite(ledMerah, LOW);
  digitalWrite(ledKuning, LOW);
  digitalWrite(ledHijau, LOW);
}

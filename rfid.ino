#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

struct Mahasiswa {
  byte uid[4];
  const char* nama;
  const char* nim;
};

Mahasiswa daftar[] = {
  { {0x8E, 0x36, 0x4B, 0x0}, "Achmad Ayubi", "124203011" },
  { {0xC3, 0xE5, 0x38, 0x16}, "Naina", "123" }
};

const int jumlahTerdaftar = sizeof(daftar) / sizeof(daftar[0]);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Sistem Absensi RFID Siap");
}

bool sama(byte *uid1, byte *uid2) {
  for (byte i = 0; i < 4; i++) {
    if (uid1[i] != uid2[i]) return false;
  }
  return true;
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  Serial.print("UID Terdeteksi: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  bool ditemukan = false;
  for (int i = 0; i < jumlahTerdaftar; i++) {
    if (sama(mfrc522.uid.uidByte, daftar[i].uid)) {
      Serial.println("Status   : Hadir");
      Serial.print("Nama     : ");
      Serial.println(daftar[i].nama);
      Serial.print("NIM      : ");
      Serial.println(daftar[i].nim);
      Serial.print("Waktu    : ");
      Serial.print(millis() / 1000);
      Serial.println(" detik sejak nyala");
      Serial.println("--------------------------");
      ditemukan = true;
      break;
    }
  }

  if (!ditemukan) {
    Serial.println("Kartu belum terdaftar.");
    Serial.println("--------------------------");
  }

  delay(2000);  // beri waktu jeda agar tidak terbaca dua kali
  mfrc522.PICC_HaltA();
}

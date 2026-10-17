#include <Arduino.h>

#define LedRed 8
#define LedGreen 10
#define Buzzer 6
#define Koil A5
#define Koil2 A0

const byte npulse = 12;
const int nmeas = 256;
const int kalibrasi_awal = 50;

long int sumsum = 0;
long int skip = 0;
long int diff = 0;
long int flash_period = 0;
long unsigned int prev_flash = 0;
int loop_count = 0;
bool buzzer_aktif = false;
int normal_count = 0;

void cekBuzzerBC547() {
  Serial.println("Buzzer akan bunyi 1 detik...");
  digitalWrite(LedRed, HIGH);
  tone(Buzzer, 2500);
  delay(1000);
  noTone(Buzzer);
  digitalWrite(Buzzer, LOW);
  digitalWrite(LedRed, LOW);
  Serial.println("Buzzer selesai.");
  Serial.println();
  delay(500);
}

void setup() {
  Serial.begin(9600);
  pinMode(Koil2, OUTPUT);
  digitalWrite(Koil2, LOW);
  pinMode(Koil, INPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(LedRed, LOW);
  digitalWrite(LedGreen, LOW);
  noTone(Buzzer);
  digitalWrite(Buzzer, LOW);

  cekBuzzerBC547();

  Serial.println("=== KALIBRASI DIMULAI ===");
  Serial.println();
}

void loop() {
  if (buzzer_aktif) {
    noTone(Buzzer);
    digitalWrite(Buzzer, LOW);
    delayMicroseconds(500);
  }

  int minval = 2000;
  int maxval = 0;
  long unsigned int sum = 0;

  for (int imeas = 0; imeas < nmeas + 2; imeas++) {
    noInterrupts();
    pinMode(Koil, OUTPUT);
    digitalWrite(Koil, LOW);
    delayMicroseconds(20);
    pinMode(Koil, INPUT);

    for (int ipulse = 0; ipulse < npulse; ipulse++) {
      digitalWrite(Koil2, HIGH);
      delayMicroseconds(3);
      digitalWrite(Koil2, LOW);
      delayMicroseconds(3);
    }
    interrupts();

    int val = analogRead(Koil);
    minval = min(val, minval);
    maxval = max(val, maxval);
    sum += val;

    long unsigned int timestamp = millis();
    byte ledstat = 0;
    if (timestamp < prev_flash + 12) {
      if (diff < 0) ledstat = 2;
    }
    if (timestamp > prev_flash + flash_period) {
      if (diff < 0) ledstat = 2;
      prev_flash = timestamp;
    }
    if (flash_period > 1000) ledstat = 0;

    if (loop_count < kalibrasi_awal) {
      digitalWrite(LedRed, LOW);
      digitalWrite(LedGreen, LOW);
    } else if (ledstat == 2) {
      digitalWrite(LedGreen, LOW);
      digitalWrite(LedRed, HIGH);
    } else {
      digitalWrite(LedRed, LOW);
      digitalWrite(LedGreen, HIGH);
    }
  }

  sum -= minval;
  sum -= maxval;

  if (sumsum == 0) sumsum = sum << 6;
  long int avgsum = (sumsum + 32) >> 6;
  diff = sum - avgsum;
  if (abs(diff) < avgsum >> 10) {
    sumsum = sumsum + sum - avgsum;
    skip = 0;
  } else {
    skip++;
  }
  if (skip > 64) {
    sumsum = sum << 6;
    skip = 0;
    diff = 0;
    flash_period = 1000000;
  }

  if (diff == 0) flash_period = 1000000;
  else flash_period = avgsum / (2 * abs(diff));

  if (loop_count < kalibrasi_awal) loop_count++;

  long int ambang_on  = max(avgsum >> 9, 20L);
  long int ambang_off = max(avgsum >> 11, 5L);

  bool logam_on  = (abs(diff) >= ambang_on)  && (loop_count >= kalibrasi_awal);
  bool logam_off = (abs(diff) < ambang_off)  && (loop_count >= kalibrasi_awal);

  if (logam_on && !buzzer_aktif) {
    tone(Buzzer, 2500);
    buzzer_aktif = true;
    normal_count = 0;
  } else if (logam_on && buzzer_aktif) {
    tone(Buzzer, 2500);
    normal_count = 0;
  } else if (!logam_on) {
    normal_count++;
    if (normal_count >= 10 && buzzer_aktif) {
      noTone(Buzzer);
      digitalWrite(Buzzer, LOW);
      buzzer_aktif = false;
      normal_count = 0;
    }
  }

  if (loop_count < kalibrasi_awal) {
    Serial.print("[KALIBRASI] ");
    Serial.print(loop_count);
    Serial.print("/");
    Serial.print(kalibrasi_awal);
    Serial.print(" baca=");
    Serial.println(sum / nmeas);
  } else if (logam_on) {
    Serial.print("[LOGAM!] baca=");
    Serial.print(sum / nmeas);
    Serial.print(" diff=");
    Serial.print(diff);
    Serial.print(" ambang_on=");
    Serial.print(ambang_on);
    Serial.print(" buzzer=");
    Serial.println(buzzer_aktif ? "ON" : "OFF");
  } else {
    Serial.print("[NORMAL] baca=");
    Serial.print(sum / nmeas);
    Serial.print(" diff=");
    Serial.print(diff);
    Serial.print(" nc=");
    Serial.println(normal_count);
  }
}
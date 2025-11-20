/*
 * ESP8266 Otto Robot - İki Bacaklı Robot Projesi
 * 
 * Bu proje ESP8266 mikrodenetleyici kullanarak iki bacaklı Otto robotun
 * kontrolünü sağlar. Robot 4 adet servo motor kullanır:
 * - Sol bacak kalça servos (pin D1)
 * - Sağ bacak kalça servos (pin D2)
 * - Sol bacak ayak servos (pin D5)
 * - Sağ bacak ayak servos (pin D6)
 * 
 * Otto robot temel hareketleri:
 * - İleri yürüme
 * - Geri yürüme
 * - Sağa dönme
 * - Sola dönme
 * - Dans hareketleri
 * 
 * Konfigürasyon ayarları config.h dosyasında bulunmaktadır.
 */

#include <Servo.h>
#include "config.h"

// Servo motor tanımlamaları
Servo servoLeftHip;    // Sol kalça
Servo servoRightHip;   // Sağ kalça
Servo servoLeftFoot;   // Sol ayak
Servo servoRightFoot;  // Sağ ayak

// Mevcut servo pozisyonları
int leftHipPos = CENTER_POSITION;
int rightHipPos = CENTER_POSITION;
int leftFootPos = CENTER_POSITION;
int rightFootPos = CENTER_POSITION;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(STARTUP_DELAY);
  
  Serial.println("\n\nESP8266 Otto Robot Başlatılıyor...");
  
  // Servo motorları pin'lere bağla
  servoLeftHip.attach(LEFT_HIP_PIN);
  servoRightHip.attach(RIGHT_HIP_PIN);
  servoLeftFoot.attach(LEFT_FOOT_PIN);
  servoRightFoot.attach(RIGHT_FOOT_PIN);
  
  // Başlangıç pozisyonuna getir
  Serial.println("Servoları orta pozisyona getiriliyor...");
  homePosition();
  delay(HOME_RETURN_DELAY);
  
  Serial.println("Otto Robot Hazır!");
  Serial.println("Komutlar: f=ileri, b=geri, l=sola dön, r=sağa dön, d=dans, h=home pozisyon");
}

void loop() {
  // Seri porttan komut bekle
  if (Serial.available() > 0) {
    char command = Serial.read();
    executeCommand(command);
  }
  
  // Demo: Otomatik hareket rutini (opsiyonel)
  // İsterseniz bu kısmı aktif edebilirsiniz
  /*
  Serial.println("İleri yürüme...");
  walkForward(4);
  delay(1000);
  
  Serial.println("Sağa dönme...");
  turnRight(2);
  delay(1000);
  
  Serial.println("Geri yürüme...");
  walkBackward(4);
  delay(1000);
  
  Serial.println("Sola dönme...");
  turnLeft(2);
  delay(1000);
  
  Serial.println("Dans...");
  dance();
  delay(2000);
  */
}

// Komutları çalıştır
void executeCommand(char cmd) {
  switch(cmd) {
    case 'f':
    case 'F':
      Serial.println("İleri yürüme");
      walkForward(DEFAULT_WALK_STEPS);
      break;
    case 'b':
    case 'B':
      Serial.println("Geri yürüme");
      walkBackward(DEFAULT_WALK_STEPS);
      break;
    case 'l':
    case 'L':
      Serial.println("Sola dönme");
      turnLeft(DEFAULT_TURN_STEPS);
      break;
    case 'r':
    case 'R':
      Serial.println("Sağa dönme");
      turnRight(DEFAULT_TURN_STEPS);
      break;
    case 'd':
    case 'D':
      Serial.println("Dans");
      dance();
      break;
    case 'h':
    case 'H':
      Serial.println("Home pozisyonu");
      homePosition();
      break;
    default:
      Serial.println("Bilinmeyen komut");
      break;
  }
}

// Servoları orta pozisyona getir
void homePosition() {
  smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION);
  smoothMove(servoRightHip, rightHipPos, CENTER_POSITION);
  smoothMove(servoLeftFoot, leftFootPos, CENTER_POSITION);
  smoothMove(servoRightFoot, rightFootPos, CENTER_POSITION);
  
  leftHipPos = CENTER_POSITION;
  rightHipPos = CENTER_POSITION;
  leftFootPos = CENTER_POSITION;
  rightFootPos = CENTER_POSITION;
}

// Yumuşak servo hareketi
void smoothMove(Servo &servo, int currentPos, int targetPos) {
  if (currentPos < targetPos) {
    for (int pos = currentPos; pos <= targetPos; pos++) {
      servo.write(pos);
      delay(WALK_SPEED);
    }
  } else {
    for (int pos = currentPos; pos >= targetPos; pos--) {
      servo.write(pos);
      delay(WALK_SPEED);
    }
  }
}

// İleri yürüme fonksiyonu
void walkForward(int steps) {
  for (int i = 0; i < steps; i++) {
    // Sol bacak ileri
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION + STEP_ANGLE);
    leftHipPos = CENTER_POSITION + STEP_ANGLE;
    smoothMove(servoLeftFoot, leftFootPos, CENTER_POSITION - STEP_ANGLE);
    leftFootPos = CENTER_POSITION - STEP_ANGLE;
    delay(STEP_DELAY);
    
    // Sağ bacak ileri
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION - STEP_ANGLE);
    rightHipPos = CENTER_POSITION - STEP_ANGLE;
    smoothMove(servoRightFoot, rightFootPos, CENTER_POSITION + STEP_ANGLE);
    rightFootPos = CENTER_POSITION + STEP_ANGLE;
    delay(STEP_DELAY);
    
    // Geri orta pozisyona
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION);
    leftHipPos = CENTER_POSITION;
    smoothMove(servoLeftFoot, leftFootPos, CENTER_POSITION);
    leftFootPos = CENTER_POSITION;
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION);
    rightHipPos = CENTER_POSITION;
    smoothMove(servoRightFoot, rightFootPos, CENTER_POSITION);
    rightFootPos = CENTER_POSITION;
    delay(STEP_DELAY);
  }
}

// Geri yürüme fonksiyonu
void walkBackward(int steps) {
  for (int i = 0; i < steps; i++) {
    // Sol bacak geri
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION - STEP_ANGLE);
    leftHipPos = CENTER_POSITION - STEP_ANGLE;
    smoothMove(servoLeftFoot, leftFootPos, CENTER_POSITION + STEP_ANGLE);
    leftFootPos = CENTER_POSITION + STEP_ANGLE;
    delay(STEP_DELAY);
    
    // Sağ bacak geri
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION + STEP_ANGLE);
    rightHipPos = CENTER_POSITION + STEP_ANGLE;
    smoothMove(servoRightFoot, rightFootPos, CENTER_POSITION - STEP_ANGLE);
    rightFootPos = CENTER_POSITION - STEP_ANGLE;
    delay(STEP_DELAY);
    
    // Geri orta pozisyona
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION);
    leftHipPos = CENTER_POSITION;
    smoothMove(servoLeftFoot, leftFootPos, CENTER_POSITION);
    leftFootPos = CENTER_POSITION;
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION);
    rightHipPos = CENTER_POSITION;
    smoothMove(servoRightFoot, rightFootPos, CENTER_POSITION);
    rightFootPos = CENTER_POSITION;
    delay(STEP_DELAY);
  }
}

// Sağa dönme fonksiyonu
void turnRight(int steps) {
  for (int i = 0; i < steps; i++) {
    // Her iki bacağı aynı yöne hareket ettir
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION + STEP_ANGLE);
    leftHipPos = CENTER_POSITION + STEP_ANGLE;
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION + STEP_ANGLE);
    rightHipPos = CENTER_POSITION + STEP_ANGLE;
    delay(TURN_DELAY);
    
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION);
    leftHipPos = CENTER_POSITION;
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION);
    rightHipPos = CENTER_POSITION;
    delay(TURN_DELAY);
  }
}

// Sola dönme fonksiyonu
void turnLeft(int steps) {
  for (int i = 0; i < steps; i++) {
    // Her iki bacağı aynı yöne hareket ettir
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION - STEP_ANGLE);
    leftHipPos = CENTER_POSITION - STEP_ANGLE;
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION - STEP_ANGLE);
    rightHipPos = CENTER_POSITION - STEP_ANGLE;
    delay(TURN_DELAY);
    
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION);
    leftHipPos = CENTER_POSITION;
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION);
    rightHipPos = CENTER_POSITION;
    delay(TURN_DELAY);
  }
}

// Dans hareketi
void dance() {
  for (int i = 0; i < DEFAULT_DANCE_CYCLES; i++) {
    // Sağa sola sallanma
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION + 20);
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION - 20);
    delay(DANCE_DELAY);
    
    smoothMove(servoLeftHip, CENTER_POSITION + 20, CENTER_POSITION - 20);
    smoothMove(servoRightHip, CENTER_POSITION - 20, CENTER_POSITION + 20);
    delay(DANCE_DELAY);
  }
  homePosition();
}

/*
 * ESP8266 Otto Robot - WiFi Web Kontrol Versiyonu
 * 
 * Bu versiyon WiFi üzerinden web arayüzü ile robot kontrolü sağlar.
 * Tarayıcıdan robot IP adresine bağlanarak kontrol edebilirsiniz.
 * 
 * KULLANIM:
 * 1. Aşağıdaki WIFI_SSID ve WIFI_PASSWORD değerlerini kendi WiFi ağınıza göre değiştirin
 * 2. Kodu ESP8266'ya yükleyin
 * 3. Seri port monitöründen robot IP adresini öğrenin
 * 4. Tarayıcıdan bu IP adresine bağlanın
 * 5. Web arayüzündeki butonlarla robotu kontrol edin
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include "config.h"

// WiFi ayarları - KENDİ AĞINIZA GÖRE DEĞİŞTİRİN!
const char* WIFI_SSID = "WiFi_Adiniz";        // WiFi ağ adınız
const char* WIFI_PASSWORD = "WiFi_Sifreniz";  // WiFi şifreniz

// Web server (port 80)
ESP8266WebServer server(80);

// Servo motor tanımlamaları
Servo servoLeftHip;
Servo servoRightHip;
Servo servoLeftFoot;
Servo servoRightFoot;

// Mevcut servo pozisyonları
int leftHipPos = CENTER_POSITION;
int rightHipPos = CENTER_POSITION;
int leftFootPos = CENTER_POSITION;
int rightFootPos = CENTER_POSITION;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(STARTUP_DELAY);
  
  Serial.println("\n\nESP8266 Otto Robot WiFi Versiyonu Başlatılıyor...");
  
  // Servo motorları pin'lere bağla
  servoLeftHip.attach(LEFT_HIP_PIN);
  servoRightHip.attach(RIGHT_HIP_PIN);
  servoLeftFoot.attach(LEFT_FOOT_PIN);
  servoRightFoot.attach(RIGHT_FOOT_PIN);
  
  // Başlangıç pozisyonuna getir
  Serial.println("Servoları orta pozisyona getiriliyor...");
  homePosition();
  delay(HOME_RETURN_DELAY);
  
  // WiFi bağlantısı
  Serial.println("\nWiFi'ye bağlanılıyor...");
  Serial.print("SSID: ");
  Serial.println(WIFI_SSID);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi bağlantısı başarılı!");
    Serial.print("IP Adresi: ");
    Serial.println(WiFi.localIP());
    Serial.print("Tarayıcınızda şu adrese gidin: http://");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi bağlantısı başarısız!");
    Serial.println("Lütfen SSID ve şifrenizi kontrol edin.");
  }
  
  // Web server rotaları
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/dance", handleDance);
  server.on("/home", handleHome);
  server.on("/status", handleStatus);
  
  server.begin();
  Serial.println("Web server başlatıldı!");
}

void loop() {
  server.handleClient();
}

// Ana sayfa HTML
void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Otto Robot Kontrol</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); margin: 0; padding: 20px; }";
  html += ".container { max-width: 600px; margin: 0 auto; background: white; border-radius: 20px; padding: 30px; box-shadow: 0 10px 40px rgba(0,0,0,0.3); }";
  html += "h1 { color: #667eea; margin-bottom: 10px; font-size: 2.5em; }";
  html += ".subtitle { color: #666; margin-bottom: 30px; font-size: 1.1em; }";
  html += ".control-grid { display: grid; grid-template-columns: repeat(3, 1fr); gap: 15px; margin: 20px 0; }";
  html += ".btn { padding: 20px; font-size: 18px; border: none; border-radius: 12px; cursor: pointer; ";
  html += "transition: all 0.3s; color: white; font-weight: bold; box-shadow: 0 4px 15px rgba(0,0,0,0.2); }";
  html += ".btn:hover { transform: translateY(-3px); box-shadow: 0 6px 20px rgba(0,0,0,0.3); }";
  html += ".btn:active { transform: translateY(0); }";
  html += ".btn-forward { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); grid-column: 2; }";
  html += ".btn-left { background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%); grid-column: 1; grid-row: 2; }";
  html += ".btn-home { background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%); grid-column: 2; grid-row: 2; }";
  html += ".btn-right { background: linear-gradient(135deg, #43e97b 0%, #38f9d7 100%); grid-column: 3; grid-row: 2; }";
  html += ".btn-backward { background: linear-gradient(135deg, #fa709a 0%, #fee140 100%); grid-column: 2; grid-row: 3; }";
  html += ".btn-dance { background: linear-gradient(135deg, #30cfd0 0%, #330867 100%); grid-column: 1/4; margin-top: 10px; }";
  html += ".status { margin-top: 20px; padding: 15px; background: #f0f0f0; border-radius: 10px; color: #333; }";
  html += ".emoji { font-size: 1.5em; margin-right: 10px; }";
  html += "@keyframes pulse { 0%, 100% { transform: scale(1); } 50% { transform: scale(1.05); } }";
  html += ".pulse { animation: pulse 2s infinite; }";
  html += "</style></head><body>";
  html += "<div class='container'>";
  html += "<h1 class='pulse'>🤖 Otto Robot</h1>";
  html += "<div class='subtitle'>WiFi Kontrol Paneli</div>";
  html += "<div class='control-grid'>";
  html += "<button class='btn btn-forward' onclick='sendCommand(\"/forward\")'>⬆️ İleri</button>";
  html += "<button class='btn btn-left' onclick='sendCommand(\"/left\")'>⬅️ Sol</button>";
  html += "<button class='btn btn-home' onclick='sendCommand(\"/home\")'>🏠 Home</button>";
  html += "<button class='btn btn-right' onclick='sendCommand(\"/right\")'>➡️ Sağ</button>";
  html += "<button class='btn btn-backward' onclick='sendCommand(\"/backward\")'>⬇️ Geri</button>";
  html += "</div>";
  html += "<button class='btn btn-dance' onclick='sendCommand(\"/dance\")'>💃 Dans Et!</button>";
  html += "<div class='status' id='status'>Hazır ✅</div>";
  html += "</div>";
  html += "<script>";
  html += "function sendCommand(cmd) {";
  html += "  document.getElementById('status').innerHTML = 'Komut gönderiliyor... ⏳';";
  html += "  fetch(cmd).then(r => r.text()).then(data => {";
  html += "    document.getElementById('status').innerHTML = data + ' ✅';";
  html += "    setTimeout(() => { document.getElementById('status').innerHTML = 'Hazır ✅'; }, 2000);";
  html += "  }).catch(e => {";
  html += "    document.getElementById('status').innerHTML = 'Hata! ❌';";
  html += "  });";
  html += "}";
  html += "</script></body></html>";
  
  server.send(200, "text/html", html);
}

// Komut işleyicileri
void handleForward() {
  Serial.println("Web: İleri yürüme");
  walkForward(DEFAULT_WALK_STEPS);
  server.send(200, "text/plain", "İleri yürüdü");
}

void handleBackward() {
  Serial.println("Web: Geri yürüme");
  walkBackward(DEFAULT_WALK_STEPS);
  server.send(200, "text/plain", "Geri yürüdü");
}

void handleLeft() {
  Serial.println("Web: Sola dönme");
  turnLeft(DEFAULT_TURN_STEPS);
  server.send(200, "text/plain", "Sola döndü");
}

void handleRight() {
  Serial.println("Web: Sağa dönme");
  turnRight(DEFAULT_TURN_STEPS);
  server.send(200, "text/plain", "Sağa döndü");
}

void handleDance() {
  Serial.println("Web: Dans");
  dance();
  server.send(200, "text/plain", "Dans etti");
}

void handleHome() {
  Serial.println("Web: Home pozisyonu");
  homePosition();
  server.send(200, "text/plain", "Home pozisyonunda");
}

void handleStatus() {
  String status = "{";
  status += "\"leftHip\":" + String(leftHipPos) + ",";
  status += "\"rightHip\":" + String(rightHipPos) + ",";
  status += "\"leftFoot\":" + String(leftFootPos) + ",";
  status += "\"rightFoot\":" + String(rightFootPos);
  status += "}";
  server.send(200, "application/json", status);
}

// ==================== HAREKET FONKSİYONLARI ====================

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

void walkForward(int steps) {
  for (int i = 0; i < steps; i++) {
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION + STEP_ANGLE);
    leftHipPos = CENTER_POSITION + STEP_ANGLE;
    smoothMove(servoLeftFoot, leftFootPos, CENTER_POSITION - STEP_ANGLE);
    leftFootPos = CENTER_POSITION - STEP_ANGLE;
    delay(STEP_DELAY);
    
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION - STEP_ANGLE);
    rightHipPos = CENTER_POSITION - STEP_ANGLE;
    smoothMove(servoRightFoot, rightFootPos, CENTER_POSITION + STEP_ANGLE);
    rightFootPos = CENTER_POSITION + STEP_ANGLE;
    delay(STEP_DELAY);
    
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

void walkBackward(int steps) {
  for (int i = 0; i < steps; i++) {
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION - STEP_ANGLE);
    leftHipPos = CENTER_POSITION - STEP_ANGLE;
    smoothMove(servoLeftFoot, leftFootPos, CENTER_POSITION + STEP_ANGLE);
    leftFootPos = CENTER_POSITION + STEP_ANGLE;
    delay(STEP_DELAY);
    
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION + STEP_ANGLE);
    rightHipPos = CENTER_POSITION + STEP_ANGLE;
    smoothMove(servoRightFoot, rightFootPos, CENTER_POSITION - STEP_ANGLE);
    rightFootPos = CENTER_POSITION - STEP_ANGLE;
    delay(STEP_DELAY);
    
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

void turnRight(int steps) {
  for (int i = 0; i < steps; i++) {
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

void turnLeft(int steps) {
  for (int i = 0; i < steps; i++) {
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

void dance() {
  for (int i = 0; i < DEFAULT_DANCE_CYCLES; i++) {
    smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION + 20);
    smoothMove(servoRightHip, rightHipPos, CENTER_POSITION - 20);
    delay(DANCE_DELAY);
    
    smoothMove(servoLeftHip, CENTER_POSITION + 20, CENTER_POSITION - 20);
    smoothMove(servoRightHip, CENTER_POSITION - 20, CENTER_POSITION + 20);
    delay(DANCE_DELAY);
  }
  homePosition();
}

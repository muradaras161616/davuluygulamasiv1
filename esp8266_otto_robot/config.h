/*
 * ESP8266 Otto Robot - Konfigürasyon Dosyası
 * 
 * Bu dosyada robotun ayarlarını kolayca değiştirebilirsiniz.
 * Değişiklik yaptıktan sonra kodu tekrar ESP8266'ya yüklemelisiniz.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ==================== PIN TANIMLARI ====================
// ESP8266 GPIO pinlerini buradan değiştirebilirsiniz
#define LEFT_HIP_PIN D1      // Sol kalça servo - GPIO5
#define RIGHT_HIP_PIN D2     // Sağ kalça servo - GPIO4
#define LEFT_FOOT_PIN D5     // Sol ayak servo - GPIO14
#define RIGHT_FOOT_PIN D6    // Sağ ayak servo - GPIO12

// Alternatif pin seçenekleri (ihtiyaç halinde kullanabilirsiniz):
// D0 = GPIO16 (NOT: Bu pin servo için önerilmez - özel kullanım)
// D1 = GPIO5
// D2 = GPIO4
// D3 = GPIO0 (NOT: Flash modu için kullanılır - dikkatli kullanın)
// D4 = GPIO2 (NOT: Onboard LED - kullanılabilir ama LED yanıp söner)
// D5 = GPIO14
// D6 = GPIO12
// D7 = GPIO13
// D8 = GPIO15 (NOT: Boot için kullanılır - dikkatli kullanın)

// ==================== SERVO AYARLARI ====================

// Servo merkez pozisyonu (0-180 derece arası)
// Eğer robot dengede durmuyorsa bu değeri ayarlayın
// Genellikle 85-95 arası bir değer uygundur
#define CENTER_POSITION 90

// Adım açısı - Robot ne kadar büyük adım atacak?
// Küçük değer = küçük adımlar, Büyük değer = büyük adımlar
// Önerilen aralık: 20-40 derece
#define STEP_ANGLE 30

// Yürüme hızı (milisaniye cinsinden gecikme)
// Küçük değer = hızlı hareket, Büyük değer = yavaş hareket
// Önerilen aralık: 10-30 ms
#define WALK_SPEED 15

// ==================== HAREKET AYARLARI ====================

// Varsayılan adım sayıları
#define DEFAULT_WALK_STEPS 4      // İleri/geri yürüme için varsayılan adım sayısı
#define DEFAULT_TURN_STEPS 2      // Dönme hareketi için varsayılan adım sayısı
#define DEFAULT_DANCE_CYCLES 3    // Dans hareketinde kaç kez sallanacak

// Adım aralıkları (milisaniye)
#define STEP_DELAY 100            // Her adım arasındaki bekleme süresi
#define TURN_DELAY 200            // Dönme hareketi arasındaki bekleme
#define DANCE_DELAY 300           // Dans hareketi arasındaki bekleme

// ==================== SERİ PORT AYARLARI ====================

// Seri port hızı
#define SERIAL_BAUD_RATE 115200

// Debug mesajları (1 = aktif, 0 = pasif)
#define DEBUG_MODE 1

// ==================== GELİŞMİŞ AYARLAR ====================

// Servo açıları için güvenlik limitleri
#define MIN_SERVO_ANGLE 0
#define MAX_SERVO_ANGLE 180

// Servo hareketi için minimum/maksimum değerler (kalibre edilmiş)
// Servo motorlarınız farklı açıları destekliyorsa değiştirebilirsiniz
#define LEFT_HIP_MIN (CENTER_POSITION - 45)
#define LEFT_HIP_MAX (CENTER_POSITION + 45)
#define RIGHT_HIP_MIN (CENTER_POSITION - 45)
#define RIGHT_HIP_MAX (CENTER_POSITION + 45)
#define LEFT_FOOT_MIN (CENTER_POSITION - 45)
#define LEFT_FOOT_MAX (CENTER_POSITION + 45)
#define RIGHT_FOOT_MIN (CENTER_POSITION - 45)
#define RIGHT_FOOT_MAX (CENTER_POSITION + 45)

// Startup gecikme (ms) - ESP8266'nın başlatılmasını bekle
#define STARTUP_DELAY 1000

// Home pozisyonuna geri dönme gecikmesi
#define HOME_RETURN_DELAY 1000

// ==================== ROBOT TİPİ ====================
// Otto robotun farklı varyantları için ön tanımlı konfigürasyonlar

// Standart Otto
// #define OTTO_STANDARD

// Otto DIY Plus (daha gelişmiş versiyon)
// #define OTTO_DIY_PLUS

// Özel Otto (kendi tasarımınız)
#define OTTO_CUSTOM

// ==================== KALİBRASYON NOTLARI ====================
/*
 * SERVO KALİBRASYONU:
 * 
 * 1. İlk çalıştırmada servo motorları robot gövdesinden sökük olarak test edin
 * 2. 'h' komutu ile home pozisyonuna getirin
 * 3. Servo horn'larını (kolları) 90 derece açıda takın
 * 4. Servo motorları robot gövdesine monte edin
 * 5. Eğer robot eğik duruyorsa CENTER_POSITION değerini ayarlayın
 * 
 * YÜRÜYÜŞ KALİBRASYONU:
 * 
 * 1. STEP_ANGLE ile başlayın (30 derece iyi bir başlangıçtır)
 * 2. 'f' komutu ile ileri yürümeyi test edin
 * 3. Robot sendeliyor mu? → STEP_ANGLE'ı küçültün
 * 4. Robot yeterince ilerlemiyor mu? → STEP_ANGLE'ı büyütün
 * 5. Hareket çok hızlı/yavaş mı? → WALK_SPEED'i ayarlayın
 * 
 * GÜÇ KALİBRASYONU:
 * 
 * 1. Servo motorlar titriyor mu? → Güç kaynağı yetersiz olabilir
 * 2. Robot reset oluyor mu? → Ortak GND bağlantısını kontrol edin
 * 3. Servo motorlar çalışmıyor mu? → 5V bağlantısını kontrol edin
 */

#endif // CONFIG_H

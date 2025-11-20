# ESP8266 Otto Robot - İki Bacaklı Robot Projesi

Bu proje, ESP8266 mikrodenetleyici kullanarak iki bacaklı Otto robotun kontrolünü sağlayan bir Arduino projesidir.

## 📋 Proje Hakkında

Otto Robot, eğitim amaçlı geliştirilmiş, iki bacaklı (bipedal) bir robot platformudur. Bu implementasyon ESP8266 tabanlı mikrodenetleyici ile çalışacak şekilde tasarlanmıştır.

### Özellikler

- ✅ 4 servo motor kontrolü (2 kalça, 2 ayak)
- ✅ İleri/geri yürüme
- ✅ Sağa/sola dönme
- ✅ Dans hareketleri
- ✅ Seri port kontrolü
- ✅ Yumuşak servo hareketleri
- ✅ Türkçe kod yorumları

## 🔧 Gerekli Donanım

### Ana Bileşenler

1. **ESP8266 Geliştirme Kartı** (NodeMCU, Wemos D1 Mini, vb.)
2. **4x Servo Motor** (SG90 veya benzeri - 9g servo motorlar)
3. **Güç Kaynağı** (5V, en az 2A - servo motorlar için)
4. **Jumper Kablolar**
5. **Breadboard** (opsiyonel - test için)

### Opsiyonel Bileşenler

- Otto Robot 3D baskı parçaları
- USB kablosu (programlama için)
- Batarya tutucu (mobil kullanım için)

## 📐 Pin Bağlantıları

| Servo Motor | ESP8266 Pin | GPIO | Açıklama |
|------------|-------------|------|----------|
| Sol Kalça | D1 | GPIO5 | Sol bacak kalça hareketi |
| Sağ Kalça | D2 | GPIO4 | Sağ bacak kalça hareketi |
| Sol Ayak | D5 | GPIO14 | Sol ayak hareketi |
| Sağ Ayak | D6 | GPIO12 | Sağ ayak hareketi |

### Güç Bağlantıları

⚠️ **ÖNEMLİ**: Servo motorlar ESP8266'dan doğrudan beslenmemelidir!

- Servo motorların VCC pinleri → 5V güç kaynağı (+)
- Servo motorların GND pinleri → Ortak GND (ESP8266 GND ile birleştirilmeli)
- ESP8266 → Ayrı USB veya 5V güç kaynağından beslenebilir

```
                    ┌─────────────┐
                    │   ESP8266   │
                    │  (NodeMCU)  │
                    └─────────────┘
                          │
            ┌─────────────┼─────────────┐
            │             │             │
         D1 │          D2 │          D5 │ D6
            │             │             │
    ┌───────┴───┐  ┌──────┴───┐  ┌─────┴─────┐
    │Sol Kalça  │  │Sağ Kalça │  │Sol Ayak   │ etc.
    │  Servo    │  │  Servo   │  │  Servo    │
    └───────────┘  └──────────┘  └───────────┘
         │              │              │
         └──────────────┴──────────────┘
                        │
                   5V Güç (2A+)
```

## 💻 Kurulum

### 1. Arduino IDE Kurulumu

1. [Arduino IDE](https://www.arduino.cc/en/software) indirin ve kurun
2. Arduino IDE'yi açın

### 2. ESP8266 Kart Desteği

1. Arduino IDE'de: **Dosya → Tercihler**
2. "Ek Devre Kartları Yöneticisi URL'leri" alanına ekleyin:
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. **Araçlar → Kart → Kart Yöneticisi**
4. "ESP8266" arayın ve "esp8266 by ESP8266 Community" yükleyin

### 3. Gerekli Kütüphaneler

Bu proje standart Arduino **Servo** kütüphanesini kullanır (Arduino IDE ile birlikte gelir).

### 4. Kodu Yükleme

1. `esp8266_otto_robot.ino` dosyasını Arduino IDE ile açın
2. **Araçlar → Kart** menüsünden ESP8266 kartınızı seçin (örn: "NodeMCU 1.0")
3. **Araçlar → Port** menüsünden doğru COM portunu seçin
4. **Yükle** butonuna tıklayın (→)

## 🎮 Kullanım

### Seri Port Kontrolü

Robot yüklendikten sonra Seri Port Monitörü açın (**Araçlar → Seri Port Monitörü**) ve baud rate'i **115200** olarak ayarlayın.

#### Komutlar

| Komut | Açıklama |
|-------|----------|
| `f` veya `F` | İleri yürü (4 adım) |
| `b` veya `B` | Geri yürü (4 adım) |
| `l` veya `L` | Sola dön (2 adım) |
| `r` veya `R` | Sağa dön (2 adım) |
| `d` veya `D` | Dans yap |
| `h` veya `H` | Home pozisyonuna dön (servo ortalama) |

### Otomatik Demo Modu

Kod içinde yorum satırı olarak bırakılmış otomatik demo modunu aktif etmek için:

1. `loop()` fonksiyonundaki yorum satırlarını (`/*` ve `*/`) kaldırın
2. Kodu tekrar yükleyin
3. Robot otomatik olarak hareket rutini yapacaktır

## ⚙️ Özelleştirme

### Servo Ayarları

`esp8266_otto_robot.ino` dosyasında şu parametreleri değiştirebilirsiniz:

```cpp
#define CENTER_POSITION 90     // Orta konum (0-180 arası)
#define STEP_ANGLE 30          // Adım açısı (büyük = uzun adımlar)
#define WALK_SPEED 15          // Hareket hızı (ms - küçük = hızlı)
```

### Pin Değiştirme

Farklı pinler kullanmak isterseniz:

```cpp
#define LEFT_HIP_PIN D1    // İstediğiniz pin'e değiştirin
#define RIGHT_HIP_PIN D2
#define LEFT_FOOT_PIN D5
#define RIGHT_FOOT_PIN D6
```

### Yeni Hareket Ekleme

Kendi hareket fonksiyonlarınızı ekleyebilirsiniz. Örnek:

```cpp
void myCustomMove() {
  // Kendi hareket kodunuz
  smoothMove(servoLeftHip, leftHipPos, CENTER_POSITION + 45);
  // ...
}
```

## 🔍 Sorun Giderme

### Servo Motor Çalışmıyor

1. ✅ Güç bağlantılarını kontrol edin (5V ve GND)
2. ✅ Ortak GND bağlantısını doğrulayın
3. ✅ Servo motor kabloları doğru pin'lere bağlı mı?
4. ✅ Güç kaynağı yeterli akımı sağlıyor mu? (en az 2A)

### Servo Motorlar Titriyor

1. ✅ `WALK_SPEED` değerini artırın (daha yavaş hareket)
2. ✅ Güç kaynağı kalitesini kontrol edin
3. ✅ Servo motorların mekanik bağlantılarını kontrol edin

### ESP8266 Sürekli Reset Oluyor

1. ✅ Servo motorları ESP8266'nın 3.3V çıkışından beslemeyin
2. ✅ Ayrı 5V güç kaynağı kullanın
3. ✅ Ortak GND bağlantısı yapın

### Kod Yüklenmiyor

1. ✅ Doğru kartı seçtiniz mi? (NodeMCU, Wemos D1, vb.)
2. ✅ Doğru COM portunu seçtiniz mi?
3. ✅ USB kablosu veri aktarımını destekliyor mu?
4. ✅ CH340/CP2102 sürücüleri kurulu mu?

## 📚 Kaynaklar

- [Otto DIY Resmi Websitesi](https://www.ottodiy.com/)
- [ESP8266 Arduino Core Dokümantasyonu](https://arduino-esp8266.readthedocs.io/)
- [Arduino Servo Kütüphanesi](https://www.arduino.cc/reference/en/libraries/servo/)

## 🎯 Gelecek Geliştirmeler

- [ ] WiFi kontrol arayüzü
- [ ] Web tabanlı kumanda
- [ ] Mobil uygulama entegrasyonu
- [ ] Ultrasonik sensör ile engel algılama
- [ ] Bluetooth kontrol
- [ ] Programlanabilir hareket rutinleri
- [ ] Müzik eşliğinde dans

## 🤝 Katkıda Bulunma

Bu proje açık kaynaklıdır. Geliştirmeler ve öneriler için pull request gönderebilirsiniz.

## 📝 Lisans

Bu proje eğitim amaçlı geliştirilmiştir ve özgürce kullanılabilir.

## ⚠️ Güvenlik Notları

1. Servo motorlar çalışırken robota dikkat edin
2. Güç kaynağı bağlantılarını her zaman kontrol edin
3. Kısa devre riskine karşı dikkatli olun
4. İlk testlerde servoları sökülü olarak test edin

## 📧 İletişim

Sorularınız için GitHub Issues kullanabilirsiniz.

---

**İyi eğlenceler! 🤖**

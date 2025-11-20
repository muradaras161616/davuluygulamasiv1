# 🚀 Hızlı Başlangıç Kılavuzu

ESP8266 Otto Robot projesine hoş geldiniz! Bu kılavuz, robotunuzu 15 dakikada çalışır hale getirmenize yardımcı olacak.

## ⚡ 5 Adımda Başlangıç

### Adım 1: Gerekli Donanımı Hazırlayın (5 dk)

Önce bu malzemeleri hazırlayın:
- ✅ ESP8266 NodeMCU (veya Wemos D1 Mini)
- ✅ 4 adet SG90 servo motor
- ✅ 5V 2A güç kaynağı
- ✅ Jumper kablolar
- ✅ USB kablosu (programlama için)

**Toplam Maliyet**: ~250-400 TL

### Adım 2: Arduino IDE Kurulumu (3 dk)

1. **Arduino IDE'yi indirin**: https://www.arduino.cc/en/software
2. **ESP8266 desteğini ekleyin**:
   - Arduino IDE'de: Dosya → Tercihler
   - "Ek Devre Kartları Yöneticisi URL'leri" alanına ekleyin:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Araçlar → Kart → Kart Yöneticisi
   - "ESP8266" arayın ve kurun

3. **Kartınızı seçin**:
   - Araçlar → Kart → ESP8266 Boards → NodeMCU 1.0

### Adım 3: Devreyi Kurun (5 dk)

#### Basit Bağlantı Şeması:

```
ESP8266 Pin  →  Servo Motor
────────────────────────────
D1 (GPIO5)   →  Sol Kalça (Turuncu/Sarı)
D2 (GPIO4)   →  Sağ Kalça (Turuncu/Sarı)
D5 (GPIO14)  →  Sol Ayak (Turuncu/Sarı)
D6 (GPIO12)  →  Sağ Ayak (Turuncu/Sarı)
GND          →  Tüm Servo GND (Kahverengi/Siyah)
```

**ÖNEMLİ**: Servo motorların kırmızı (+5V) pinlerini ayrı bir 5V 2A güç kaynağına bağlayın!

#### Güvenlik Kontrol Listesi:
- [ ] GND'ler birleştirildi mi?
- [ ] Servo motorlar ayrı güç kaynağından besleniyor mu?
- [ ] Kısa devre riski yok mu?

### Adım 4: Kodu Yükleyin (2 dk)

#### Basit Versiyon (Seri Port Kontrol):

1. `esp8266_otto_robot.ino` dosyasını Arduino IDE ile açın
2. Araçlar → Port → COM portunu seçin
3. **Yükle** butonuna tıklayın (→)

#### WiFi Versiyon (Web Kontrol):

1. `esp8266_otto_robot_wifi.ino` dosyasını açın
2. WiFi ayarlarını düzenleyin:
   ```cpp
   const char* WIFI_SSID = "WiFi_Adiniz";
   const char* WIFI_PASSWORD = "WiFi_Sifreniz";
   ```
3. **Yükle** butonuna tıklayın

### Adım 5: Test Edin! (2 dk)

#### Seri Port Versiyonu:
1. Araçlar → Seri Port Monitörü
2. Baud rate: **115200**
3. Komutları gönderin:
   - `f` → İleri
   - `b` → Geri
   - `l` → Sola dön
   - `r` → Sağa dön
   - `d` → Dans
   - `h` → Home

#### WiFi Versiyonu:
1. Seri Port Monitöründen IP adresini okuyun
2. Tarayıcınızda bu IP adresine gidin
3. Web arayüzündeki butonları kullanın!

## 🎯 İlk Test Rutini

```
1. 'h' → Home pozisyonu (tüm servolar ortalanır)
2. 'f' → 4 adım ileri yürü
3. 'l' → Sola dön
4. 'b' → 4 adım geri yürü
5. 'r' → Sağa dön
6. 'd' → Dans et!
```

## ⚙️ Ayarlamalar

Eğer robot düzgün çalışmıyorsa `config.h` dosyasında bu değerleri ayarlayın:

```cpp
#define CENTER_POSITION 90    // Servo orta pozisyonu (85-95 arası deneyin)
#define STEP_ANGLE 30         // Adım büyüklüğü (20-40 arası)
#define WALK_SPEED 15         // Hareket hızı (10-30 arası)
```

## 🐛 Hızlı Sorun Giderme

| Sorun | Çözüm |
|-------|-------|
| ❌ Servo motorlar çalışmıyor | Güç bağlantılarını kontrol edin (5V, GND) |
| ❌ ESP8266 reset oluyor | Ortak GND bağlantısı yapın |
| ❌ Servo motorlar titriyor | WALK_SPEED değerini artırın |
| ❌ Robot sendeliyor | STEP_ANGLE değerini küçültün |
| ❌ WiFi bağlanamıyor | SSID ve şifre doğru mu? |
| ❌ Kod yüklenmiyor | Doğru kartı ve portu seçtiniz mi? |

## 📚 Detaylı Dökümanlar

Daha fazla bilgi için:
- **README.md** - Tam özellikler ve kullanım kılavuzu
- **CIRCUIT.md** - Detaylı devre şemaları ve parça listesi
- **config.h** - Konfigürasyon ayarları ve kalibrasyon

## 🎓 Öğrenme Yolu

### Başlangıç Seviyesi:
1. ✅ Temel seri port kontrolü
2. ✅ Servo motor kalibrasyon
3. ✅ Hareket fonksiyonlarını anlama

### Orta Seviye:
4. ⏭️ WiFi web kontrolü
5. ⏭️ Yeni hareket rutinleri ekleme
6. ⏭️ Config.h parametrelerini optimize etme

### İleri Seviye:
7. ⏭️ Ultrasonik sensör ile engel algılama
8. ⏭️ Mobil uygulama kontrolü
9. ⏭️ Otonom hareket algoritmaları

## 🤝 Yardım ve Destek

Sorun yaşıyorsanız:
1. README.md'deki "Sorun Giderme" bölümüne bakın
2. CIRCUIT.md'deki bağlantı şemalarını kontrol edin
3. GitHub Issues kullanarak soru sorun

## 🎉 Başarılı Oldunuz!

Tebrikler! Otto robotunuz çalışıyor. Artık şunları yapabilirsiniz:

- 🎮 Seri port veya WiFi ile kontrol edin
- 🔧 Hareket parametrelerini optimize edin
- 🎨 Yeni hareket rutinleri ekleyin
- 📱 Mobil uygulama entegrasyonu yapın
- 🤖 Otto'ya yeni yetenekler kazandırın

**İyi eğlenceler! 🤖💫**

---

📌 **İpucu**: İlk defa deneyecekseniz, servo motorları robot gövdesine takmadan önce test edin. Bu şekilde kalibrasyon daha kolay olur!

# 🔍 Sorun Giderme Rehberi

Bu dokümanda Otto Robot projesinde karşılaşabileceğiniz yaygın sorunlar ve çözümleri bulacaksınız.

## 📋 Sorun Kontrol Listesi

Herhangi bir sorunla karşılaştığınızda, bu kontrol listesini sırayla takip edin:

### 1. Donanım Kontrolleri

#### ✅ Güç Kaynağı Kontrolleri
- [ ] 5V güç kaynağı bağlı mı?
- [ ] Güç kaynağı minimum 2A akım sağlayabiliyor mu?
- [ ] Güç kaynağı adaptörü prize takılı mı ve açık mı?
- [ ] ESP8266 USB'den mi yoksa ayrı güçten mi besleniyor?

#### ✅ Servo Motor Kontrolleri
- [ ] Her servo motorun 3 kablosu da bağlı mı? (GND, +5V, Sinyal)
- [ ] Servo motor kabloları doğru pinlere bağlı mı?
  * Sol Kalça → D1
  * Sağ Kalça → D2
  * Sol Ayak → D5
  * Sağ Ayak → D6
- [ ] Servo motorların GND'si ortak GND'ye bağlı mı?
- [ ] Servo motorlar fiziksel olarak hasar görmemiş mi?

#### ✅ ESP8266 Kontrolleri
- [ ] ESP8266 USB kablosu bağlı mı?
- [ ] ESP8266'nın LED'i yanıyor mu?
- [ ] ESP8266 sıcak mı? (Aşırı ısınma varsa güç kes!)
- [ ] ESP8266 ile bilgisayar arasında bağlantı var mı?

#### ✅ Kablo Bağlantıları
- [ ] Tüm jumper kablolar sıkı bağlı mı?
- [ ] Breadboard kullanıyorsanız, pinler doğru deliklerde mi?
- [ ] Kablolarda kopukluk veya hasar var mı?
- [ ] Polarite doğru mu? (+ ve - karışmamış mı?)

### 2. Yazılım Kontrolleri

#### ✅ Arduino IDE Ayarları
- [ ] Doğru kart seçildi mi? (NodeMCU 1.0, Wemos D1, vb.)
- [ ] Doğru COM portu seçildi mi?
- [ ] ESP8266 board paketi kurulu mu?
- [ ] Kod hatasız derleniyor mu?

#### ✅ Konfigürasyon Kontrolleri
- [ ] config.h dosyası doğru değerlere sahip mi?
- [ ] WiFi versiyonunda SSID ve şifre doğru mu?
- [ ] Seri port baud rate 115200 olarak ayarlı mı?

---

## 🚨 Yaygın Sorunlar ve Çözümler

### Sorun 1: Servo Motorlar Hiç Hareket Etmiyor

#### Olası Nedenler:
1. Güç kaynağı bağlı değil veya yetersiz
2. Servo motor bağlantıları yanlış
3. Kod yüklenmemiş veya hatalı

#### Çözüm Adımları:

**Adım 1: Güç Kaynağını Kontrol Edin**
```
Multimetre ile ölçüm yapın:
- Servo +5V pini: 4.8V - 5.2V arası olmalı
- Servo GND pini: 0V olmalı
```

**Adım 2: Bağlantıları Kontrol Edin**
```
Her servo motor için:
1. Kahverengi/Siyah → GND ✓
2. Kırmızı → +5V ✓
3. Turuncu/Sarı → ESP8266 GPIO ✓
```

**Adım 3: Test Kodu Çalıştırın**
Seri Port Monitöründe:
1. Baud rate: 115200
2. 'h' yazıp Enter
3. "Servoları orta pozisyona getiriliyor..." mesajını görmelisiniz

**Adım 4: Tek Tek Test Edin**
```cpp
// Sadece bir servo test kodu
void setup() {
  Servo test;
  test.attach(D1);
  test.write(90);
}
```

---

### Sorun 2: ESP8266 Sürekli Reset Oluyor

#### Belirtiler:
- ESP8266 LED'i sürekli yanıp sönüyor
- Seri portta "Watchdog reset" mesajları
- Kod çalışmaya başlıyor ama sonra restart oluyor

#### Olası Nedenler:
1. Servo motorlar ESP8266'dan besleniyor (YANLIŞ!)
2. Ortak GND bağlantısı yok
3. Güç kaynağı yetersiz

#### Çözüm:

```
Doğru Bağlantı:
┌─────────────┐
│   ESP8266   │
│             │
│  GND ─────┐ │
│           │ │
└───────────┼─┘
            │
            │ (Ortak GND)
            │
       ┌────┴─────┐
       │          │
   ┌───▼──┐   ┌───▼──────────┐
   │Servo │   │5V Güç (2A+)  │
   │ GND  │   │    GND       │
   └──────┘   └──────────────┘
```

**Kritik**: Servo motorların +5V pinleri asla ESP8266'dan beslenmemeli!

---

### Sorun 3: Servo Motorlar Titriyor

#### Belirtiler:
- Servo motorlar sürekli titreyerek duruyor
- Servo motorlar ısınıyor
- Robot dengede duramıyor

#### Olası Nedenler:
1. Hareket hızı çok yüksek
2. Güç kaynağı kalitesiz veya yetersiz
3. Servo motorlar mekanik olarak sıkışmış

#### Çözüm:

**1. Hareket Hızını Ayarlayın**
`config.h` dosyasında:
```cpp
#define WALK_SPEED 20  // 15'ten 20'ye çıkarın (daha yavaş)
```

**2. Güç Kaynağını İyileştirin**
- Kaliteli 5V 2A adaptör kullanın
- 100µF kapasitör ekleyin (servo +5V ve GND arası)
- Kablolar kısa ve kalın olmalı

**3. Mekanik Kontrolü**
- Servo horn'ları gevşetin
- Robot gövdesinde sıkışma var mı kontrol edin
- Servo motorları serbest hareket edebiliyor mu?

---

### Sorun 4: Robot Düzgün Yürümüyor / Sendeliyor

#### Belirtiler:
- Robot dengesiz duruyor
- Yürürken düşüyor veya devrilme riski var
- Bir bacak diğerinden farklı hareket ediyor

#### Çözüm:

**1. Servo Kalibrasyonu**
`config.h` dosyasında CENTER_POSITION ayarlayın:
```cpp
// Deneme yanılma ile optimal değeri bulun
#define CENTER_POSITION 88  // 85-95 arası deneyin
```

**2. Adım Açısını Küçültün**
```cpp
#define STEP_ANGLE 25  // 30'dan 25'e düşürün
```

**3. Manuel Kalibrasyon**
```
1. 'h' komutu ile home pozisyonuna getirin
2. Her servo motor 90° açıda mı kontrol edin
3. Servo horn'larını 90° açıda takın
4. Robot gövdesine monte edin
```

---

### Sorun 5: WiFi'ye Bağlanamıyor

#### Belirtiler:
- "WiFi bağlantısı başarısız" mesajı
- IP adresi görünmüyor
- Web arayüzüne erişilemiyor

#### Çözüm:

**1. WiFi Bilgilerini Kontrol Edin**
```cpp
const char* WIFI_SSID = "Dogru_Ag_Adi";        // Boşluk ve büyük küçük harf önemli!
const char* WIFI_PASSWORD = "Dogru_Sifre123";  // En az 8 karakter
```

**2. WiFi Sinyal Gücünü Test Edin**
- ESP8266'yı router'a yaklaştırın
- 2.4GHz ağ kullanın (5GHz desteklenmez!)
- WiFi şifresi özel karakter içeriyorsa değiştirin

**3. Seri Port Çıktısını İnceleyin**
```
Başarılı bağlantı:
> WiFi'ye bağlanılıyor...
> SSID: MevzuWiFi
> .....
> WiFi bağlantısı başarılı!
> IP Adresi: 192.168.1.100

Başarısız bağlantı:
> WiFi'ye bağlanılıyor...
> ..............................
> WiFi bağlantısı başarısız!
```

---

### Sorun 6: Kod Yüklenmiyor

#### Belirtiler:
- "espcomm_sync failed" hatası
- "espcomm_open failed" hatası
- "error: failed uploading" hatası

#### Çözüm:

**1. Sürücü Kontrolü**
- CH340 veya CP2102 sürücüsü kurulu mu?
- Windows: Aygıt Yöneticisi'nde COM portu görünüyor mu?
- Linux/Mac: `ls /dev/tty*` komutu ile kontrol edin

**2. Port Seçimi**
- Araçlar → Port → Doğru COM portunu seçin
- Birden fazla port varsa hepsini deneyin

**3. Upload Modu**
- NodeMCU genellikle otomatik upload moduna girer
- Manuel mod için: FLASH butonunu basılı tutarak RESET'e basın

**4. USB Kablosu**
- Sadece şarj kablosu değil, VERİ kablosu kullanın
- Farklı bir USB kablosu deneyin
- USB hub kullanıyorsanız, doğrudan PC'ye bağlayın

---

### Sorun 7: Seri Port Monitöründe Garip Karakterler

#### Belirtiler:
- Seri portta anlamsız semboller
- Okunabilir metin yok
- "????????????" gibi karakterler

#### Çözüm:

**Baud Rate Kontrolü**
```
Araçlar → Seri Port Monitörü
Sağ altta: 115200 baud seçin
```

Arduino kodunda:
```cpp
Serial.begin(115200);  // Bu değer aynı olmalı
```

---

## 🔬 İleri Seviye Hata Ayıklama

### Debug Mode Aktif Etme

`config.h` dosyasında:
```cpp
#define DEBUG_MODE 1  // Detaylı loglar için
```

### Servo Pozisyon Takibi

Koda ekleyin:
```cpp
void printPositions() {
  Serial.print("LH:"); Serial.print(leftHipPos);
  Serial.print(" RH:"); Serial.print(rightHipPos);
  Serial.print(" LF:"); Serial.print(leftFootPos);
  Serial.print(" RF:"); Serial.println(rightFootPos);
}
```

### Voltaj Ölçümü

Multimetre ile ölçüm noktaları:
```
1. Servo +5V pini: 4.8-5.2V (ideal: 5.0V)
2. ESP8266 3.3V pini: 3.2-3.4V
3. Güç kaynağı çıkışı: 4.9-5.1V
```

Anormal değerler:
- < 4.5V: Güç kaynağı yetersiz
- > 5.5V: Tehlikeli! Hemen kesin
- Değişken voltaj: Kötü bağlantı veya kalitesiz güç

---

## 📞 Destek

Bu rehber sorununuzu çözmedi mi?

1. **GitHub Issues**: Yeni bir issue açın
2. **README.md**: Detaylı dokümantasyon
3. **CIRCUIT.md**: Devre şemaları
4. **Arduino Forum**: ESP8266 topluluğu

---

## 💡 Önleyici Bakım

### Her Kullanımdan Önce:
- [ ] Tüm bağlantıları kontrol edin
- [ ] Güç kaynağını test edin
- [ ] Servo motorlarda anormallik var mı bakın

### Her Kullanımdan Sonra:
- [ ] Servo motorlar aşırı ısınmış mı kontrol edin
- [ ] Gevşek bağlantıları sıkın
- [ ] Robot gövdesinde hasar var mı inceleyin

### Haftalık Bakım:
- [ ] Tüm vidaları kontrol edin
- [ ] Kablo bağlantılarını yeniden yapın
- [ ] Servo motor açılarını yeniden kalibre edin

---

**İyi şanslar! 🔧🤖**

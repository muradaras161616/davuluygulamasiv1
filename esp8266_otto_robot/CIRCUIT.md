# ESP8266 Otto Robot - Parça Listesi ve Devre Şeması

## 🛒 Parça Listesi (BOM - Bill of Materials)

### Elektronik Bileşenler

| # | Bileşen | Adet | Teknik Özellikler | Tahmini Fiyat (TL) |
|---|---------|------|-------------------|-------------------|
| 1 | ESP8266 NodeMCU | 1 | CP2102, 4MB Flash | 80-120 TL |
| 2 | SG90 Servo Motor | 4 | 9g, 180°, 4.8-6V | 20-30 TL/adet |
| 3 | 5V 2A Güç Adaptörü | 1 | DC 5V, min 2A | 40-60 TL |
| 4 | Breadboard 400 pin | 1 | (opsiyonel - test için) | 15-25 TL |
| 5 | Jumper Kablo Seti | 1 | Erkek-Erkek, Erkek-Dişi | 10-20 TL |
| 6 | Mini USB Kablosu | 1 | Programlama için | 10-15 TL |

**Toplam Tahmini Maliyet**: ~250-400 TL

### Mekanik Bileşenler (Opsiyonel)

| # | Bileşen | Adet | Açıklama |
|---|---------|------|----------|
| 7 | Otto Robot 3D Baskı Parçaları | 1 set | Gövde, bacaklar, ayaklar |
| 8 | M3 Vida Seti | 1 | Montaj için (8-12 adet) |
| 9 | Batarya Tutucu | 1 | 4xAA veya 1x9V (mobil kullanım) |

## 🔌 Devre Bağlantı Şeması

### Temel Bağlantılar

```
┌─────────────────────────────────────────────────────────────────┐
│                        ESP8266 NodeMCU                          │
│                                                                 │
│  ┌────────────────────────────────────────────────────────┐   │
│  │                                                        │   │
│  │  USB │  RST  EN   3V3  GND  D0  D1  D2  D3  D4       │   │
│  │   │                                 │   │   │         │   │
│  └───┼─────────────────────────────────┼───┼───┼─────────┘   │
│      │                                 │   │   │             │
│      │ (Programlama)                   │   │   │             │
│      │                                 │   │   │             │
│      │                          Sinyal │   │   │             │
│      │                          Pinleri│   │   │             │
└──────┼──────────────────────────────────┼───┼───┼─────────────┘
       │                                  │   │   │
       │                                  │   │   │
       │                       ┌──────────┘   │   └──────────┐
       │                       │              │              │
       │                       │    ┌─────────┘              │
       │                       │    │                        │
       │                       ▼    ▼                        ▼
       │                    ┌────────┐                   ┌────────┐
       │                    │ SERVO  │                   │ SERVO  │
       │                    │ Sol    │                   │ Sağ    │
       │                    │ Kalça  │                   │ Kalça  │
       │                    │  (D1)  │                   │  (D2)  │
       │                    └───┬────┘                   └───┬────┘
       │                        │                            │
       │                        └────────┬──────┬────────────┘
       │                                 │      │
       │                                 │      │
       │                              ┌──▼──────▼──┐
       │                              │   GND      │
       │                              │   Ortak    │
       │                              └──┬─────────┘
       │                                 │
       └─────────────────────────────────┘
```

### Tam Bağlantı Şeması

```
                    ┌──────────────────────┐
                    │   5V Güç Kaynağı     │
                    │      (2A Min)        │
                    └──────┬──────┬────────┘
                           │      │
                         +5V     GND
                           │      │
           ┌───────────────┼──────┼───────────────┐
           │               │      │               │
           │     ┌─────────┘      └─────────┐     │
           │     │                          │     │
           │     │   ESP8266 NodeMCU        │     │
           │     │   ┌──────────────┐       │     │
           │     │   │              │       │     │
           │     │   │  D1  D2  D5  D6      │     │
           │     │   │  │   │   │   │       │     │
           │     │   │  │   │   │   │       │     │
           │     │   └──┼───┼───┼───┼───────┘     │
           │     │      │   │   │   │             │
           │     │      │   │   │   │             │
           │     │   [Sinyal Pinleri]             │
           │     │      │   │   │   │             │
       ┌───▼─────▼──┐   │   │   │   │   ┌─────────▼───┐
       │  SERVO 1   │◄──┘   │   │   └──►│  SERVO 4    │
       │ Sol Kalça  │       │   │       │ Sağ Ayak    │
       │ (Orange)   │       │   │       │ (Orange)    │
       └─────┬──────┘       │   │       └──────┬──────┘
             │              │   │              │
             │         ┌────▼───▼────┐         │
             │         │  SERVO 2    │         │
             │         │ Sağ Kalça   │         │
             │         │ (Yellow)    │         │
             │         └──────┬──────┘         │
             │                │                │
             │         ┌──────▼──────┐         │
             │         │  SERVO 3    │         │
             │         │ Sol Ayak    │         │
             │         │ (Green)     │         │
             │         └──────┬──────┘         │
             │                │                │
             └────────────────┴────────────────┘
                              │
                          [Ortak GND]
```

### Servo Motor Pin Açıklaması

Her servo motor 3 pine sahiptir:

| Pin Rengi | Bağlantı | Açıklama |
|-----------|----------|----------|
| 🟤 Kahverengi/Siyah | GND | Toprak (Ortak GND) |
| 🔴 Kırmızı | +5V | Güç kaynağı (+5V, 2A) |
| 🟠 Turuncu/Sarı | Sinyal | ESP8266 GPIO pini (D1,D2,D5,D6) |

## 📋 Adım Adım Montaj

### 1. Breadboard Üzerinde Test

```
     ESP8266 NodeMCU
    ┌─────────────────┐
    │                 │
    │  D1  D2  D5  D6 │
    │  │   │   │   │  │
    └──┼───┼───┼───┼──┘
       │   │   │   │
       │   │   │   └────────┐
       │   │   │            │
       │   │   └──────┐     │
       │   │          │     │
    ┌──▼───▼───┐   ┌──▼─────▼──┐
    │ Servo 1  │   │ Servo 3   │
    │ Servo 2  │   │ Servo 4   │
    └──────────┘   └───────────┘
       │   │           │   │
      GND +5V        GND +5V
       │   │           │   │
       └───┴───────────┴───┘
           │           │
        [Ortak GND] [+5V 2A]
```

### Montaj Adımları:

1. **Güç Bağlantıları (ÖNEMLİ - İLK ADIM)**
   - 5V güç kaynağının GND'sini breadboard'un GND rail'ine bağlayın
   - 5V güç kaynağının +5V'unu breadboard'un +5V rail'ine bağlayın
   - ESP8266'nın GND'sini breadboard'un GND rail'ine bağlayın
   - **DİKKAT**: Servo motorları ESP8266'nın 3.3V veya 5V pininden beslemeyin!

2. **Servo Motor Bağlantıları**
   - Her servo motorun kahverengi/siyah pinini GND rail'e bağlayın
   - Her servo motorun kırmızı pinini +5V rail'e bağlayın
   - Sinyal pinlerini şu şekilde bağlayın:
     * Servo 1 (Sol Kalça) Turuncu → D1
     * Servo 2 (Sağ Kalça) Turuncu → D2
     * Servo 3 (Sol Ayak) Turuncu → D5
     * Servo 4 (Sağ Ayak) Turuncu → D6

3. **Kontrol ve İlk Test**
   - Tüm bağlantıları çift kontrol edin
   - Kısa devre riski olmadığından emin olun
   - Arduino IDE'de kodu yükleyin
   - İlk testte servo motorları takılı değilken test edin

### 2. Kalıcı Montaj (Opsiyonel)

- Servo motorları Otto robot gövdesine monte edin
- Kabloları toparlayın ve düzenleyin
- Güç kaynağını veya bataryayı robot gövdesine yerleştirin
- Vida ve somunlarla servo motorları sabitleyin

## ⚡ Güç Tüketimi

| Bileşen | Akım Tüketimi | Açıklama |
|---------|---------------|----------|
| ESP8266 NodeMCU | 80-170 mA | WiFi aktif/pasif |
| SG90 Servo (hareketsiz) | 10 mA/adet | x4 = 40 mA |
| SG90 Servo (yük altında) | 100-250 mA/adet | x4 = 400-1000 mA |
| **Toplam (Max)** | **~1.2-1.5 A** | Normal çalışma |
| **Önerilen Güç** | **2A** | Güvenli marj |

## 🔋 Güç Kaynağı Seçenekleri

### Sabit Kullanım

- **5V 2A Adaptör** (Önerilen)
- Duvar prizi adaptörü
- Micro USB güç adaptörü

### Mobil Kullanım

- **4x AA Pil (6V)** + 5V regülatör
- **1x 9V Pil** + 5V regülatör (DC-DC düşürücü)
- **Powerbank** (USB çıkışlı, 2A)
- **LiPo Batarya** (7.4V 2S) + 5V BEC/regülatör

## ⚠️ Önemli Uyarılar

1. ❌ **Servo motorları ESP8266'dan beslemeyin** - ESP8266'nın pinleri yeterli akımı sağlayamaz
2. ❌ **Ortak GND yapmayı unutmayın** - ESP8266 ve servo motorların GND'si birleştirilmeli
3. ❌ **Polariteye dikkat edin** - Ters bağlantı servo motorlara ve ESP8266'ya zarar verebilir
4. ✅ **İlk testte mekanik montaj yapmadan test edin** - Servo açıları yanlış ayarlanmışsa zarar görebilir
5. ✅ **Kaliteli güç kaynağı kullanın** - Ucuz adaptörler voltaj düşümüne neden olabilir

## 🔧 Test ve Kalibrasyon

### İlk Test Prosedürü

1. Servo motorları takılı değilken kodu yükleyin
2. Seri port monitörde mesajları kontrol edin
3. Servo motorların hareket ettiğini gözlemleyin
4. `h` (home) komutu ile servo motorları ortalayın
5. Servo motorları robot gövdesine monte edin
6. Tam hareket testleri yapın

### Kalibrasyon

Eğer robot düzgün yürümüyorsa:

1. `CENTER_POSITION` değerini ayarlayın (85-95 arası)
2. `STEP_ANGLE` değerini küçültün veya büyütün
3. `WALK_SPEED` değerini değiştirin (10-30 arası)

## 📞 Destek

Sorunlarınız için:
- Devre bağlantılarını kontrol edin
- README.md dosyasındaki "Sorun Giderme" bölümüne bakın
- GitHub Issues kullanın

---

**Güvenli montajlar! 🔧**

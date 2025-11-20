# ESP8266 Otto Robot - Proje Bilgileri

## 📦 Versiyon: 1.0.0

**Yayın Tarihi**: 20 Kasım 2025

---

## 📄 Proje Özeti

ESP8266 mikrodenetleyici kullanarak iki bacaklı (bipedal) Otto robotun kontrolünü sağlayan açık kaynaklı bir Arduino projesidir.

### 🎯 Proje Hedefleri

- ✅ ESP8266 ile uyumlu, kolay kullanılabilir Otto robot implementasyonu
- ✅ Türkçe dokümantasyon ve kod yorumları
- ✅ Başlangıç seviyesi kullanıcılar için detaylı kılavuzlar
- ✅ Seri port ve WiFi kontrol seçenekleri
- ✅ Genişletilebilir ve özelleştirilebilir kod yapısı

---

## 📚 Döküman Yapısı

### Ana Dosyalar

| Dosya | Açıklama | Satır Sayısı |
|-------|----------|--------------|
| `esp8266_otto_robot.ino` | Ana Arduino sketch (Seri port kontrol) | ~265 |
| `esp8266_otto_robot_wifi.ino` | WiFi web kontrol versiyonu | ~325 |
| `config.h` | Konfigürasyon ayarları | ~126 |

### Dokümantasyon

| Dosya | İçerik | Hedef Kitle |
|-------|--------|-------------|
| `README.md` | Genel proje açıklaması ve kullanım | Tüm kullanıcılar |
| `QUICKSTART.md` | 15 dakikada başlangıç kılavuzu | Yeni başlayanlar |
| `CIRCUIT.md` | Devre şemaları ve parça listesi | Donanım kurulum |
| `TROUBLESHOOTING.md` | Sorun giderme rehberi | Problem çözme |
| `PROJECT_INFO.md` | Proje bilgileri ve changelog | Geliştiriciler |

---

## ✨ Özellikler

### v1.0.0 Özellikleri

#### Temel Hareket Fonksiyonları
- ✅ İleri yürüme (configurable adım sayısı)
- ✅ Geri yürüme (configurable adım sayısı)
- ✅ Sağa dönme
- ✅ Sola dönme
- ✅ Dans hareketi
- ✅ Home pozisyonu (servo ortalama)

#### Kontrol Yöntemleri
- ✅ Seri port üzerinden komut kontrolü
- ✅ WiFi web arayüzü ile kontrol
- ✅ RESTful API desteği

#### Konfigürasyon
- ✅ Ayrı config.h dosyası ile kolay özelleştirme
- ✅ Pin atamaları değiştirilebilir
- ✅ Hareket parametreleri ayarlanabilir
- ✅ Servo kalibrasyon parametreleri

#### Kod Kalitesi
- ✅ Türkçe kod yorumları
- ✅ Temiz ve okunabilir kod yapısı
- ✅ Modüler fonksiyon tasarımı
- ✅ Yumuşak servo hareketleri

#### Dokümantasyon
- ✅ Kapsamlı Türkçe dokümantasyon
- ✅ Detaylı devre şemaları
- ✅ ASCII art diyagramlar
- ✅ Adım adım kurulum kılavuzu
- ✅ Sorun giderme rehberi

---

## 🛠️ Teknik Detaylar

### Desteklenen Donanım

#### Mikrodenetleyiciler
- ESP8266 NodeMCU v1.0
- Wemos D1 Mini
- ESP-12E/F modüller
- Diğer ESP8266 tabanlı kartlar

#### Servo Motorlar
- SG90 (9g micro servo) - Önerilen
- MG90S (metal gear)
- Tower Pro SG90
- Uyumlu 180° servo motorlar

#### Güç Kaynakları
- 5V 2A duvar adaptörü (önerilen)
- 4x AA pil + 5V regülatör
- Powerbank (2A çıkış)
- LiPo batarya + BEC

### Pin Kullanımı

```
ESP8266 GPIO  │  Kullanım      │  Alternatif
──────────────┼────────────────┼─────────────
GPIO5  (D1)   │  Sol Kalça     │  Değiştirilebilir
GPIO4  (D2)   │  Sağ Kalça     │  Değiştirilebilir
GPIO14 (D5)   │  Sol Ayak      │  Değiştirilebilir
GPIO12 (D6)   │  Sağ Ayak      │  Değiştirilebilir
```

### Bellek Kullanımı

```
Sketch kullanımı: ~40KB (ESP8266 4MB Flash)
Global değişkenler: ~2KB RAM
WiFi versiyonu: ~50KB Flash

ESP8266 Kapasitesi:
- Flash: 4MB (NodeMCU)
- RAM: 80KB
- Yeterli alan: ✅
```

### Güç Tüketimi

```
Bileşen           │  Min   │  Typical  │  Max
──────────────────┼────────┼───────────┼──────
ESP8266           │  80mA  │  120mA    │  170mA
Servo x4 (idle)   │  40mA  │  60mA     │  100mA
Servo x4 (load)   │  400mA │  800mA    │  1200mA
──────────────────┼────────┼───────────┼──────
Toplam            │  520mA │  980mA    │  1470mA
```

**Önerilen Güç**: 5V 2A (güvenli marj ile)

---

## 🔄 Changelog

### Version 1.0.0 (2025-11-20)

#### ✨ Yeni Özellikler
- İlk kararlı sürüm
- Seri port kontrol implementasyonu
- WiFi web kontrol implementasyonu
- 6 temel hareket fonksiyonu
- Konfigürasyon dosyası sistemi
- Kapsamlı Türkçe dokümantasyon

#### 📝 Dokümantasyon
- README.md - Genel kullanım kılavuzu
- QUICKSTART.md - Hızlı başlangıç
- CIRCUIT.md - Devre şemaları
- TROUBLESHOOTING.md - Sorun giderme
- PROJECT_INFO.md - Proje bilgileri

#### 🎨 Kod İyileştirmeleri
- Temiz ve modüler kod yapısı
- Yorum satırları eklendi
- Konfigürasyonlar ayrıldı
- Servo hareket optimizasyonu

---

## 🚀 Gelecek Versiyonlar

### Planlanan v1.1.0 Özellikleri
- [ ] Bluetooth kontrol desteği
- [ ] Mobil uygulama örneği
- [ ] Ultrasonik sensör entegrasyonu
- [ ] Engel algılama ve kaçınma
- [ ] Otonom hareket modu

### Planlanan v1.2.0 Özellikleri
- [ ] Sesli komut kontrolü
- [ ] Programlanabilir hareket rutinleri
- [ ] Hareket kaydedici/oynatıcı
- [ ] Çoklu robot senkronizasyonu
- [ ] OLED ekran desteği

### Planlanan v2.0.0 Özellikleri
- [ ] Makine öğrenmesi ile hareket optimizasyonu
- [ ] Computer vision ile nesne takibi
- [ ] IMU/gyro ile denge kontrolü
- [ ] Adaptif yürüyüş algoritması
- [ ] Bozuk zeminde yürüme

---

## 🤝 Katkıda Bulunma

### Nasıl Katkıda Bulunabilirsiniz?

1. **Kod Katkısı**
   - Yeni hareket fonksiyonları ekleyin
   - Hata düzeltmeleri yapın
   - Kod optimizasyonları önerir
   - Yeni sensör/özellik entegrasyonu

2. **Dokümantasyon**
   - Dokümanlarda iyileştirme
   - Çeviri (İngilizce, vb.)
   - Video eğitim içeriği
   - Örnek projeler

3. **Test ve Geri Bildirim**
   - Farklı donanımlarla test edin
   - Hataları rapor edin
   - İyileştirme önerileri
   - Kullanım senaryoları paylaşın

### Katkı Süreci

```
1. Fork yapın
2. Feature branch oluşturun (git checkout -b feature/AmazingFeature)
3. Değişikliklerinizi commit edin (git commit -m 'Add AmazingFeature')
4. Branch'inizi push edin (git push origin feature/AmazingFeature)
5. Pull Request açın
```

---

## 📜 Lisans

Bu proje eğitim amaçlı geliştirilmiştir ve MIT Lisansı altında dağıtılmaktadır.

**MIT License**
```
Copyright (c) 2025 Otto Robot ESP8266 Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

---

## 👥 Katkıda Bulunanlar

- **Ana Geliştirici**: GitHub Copilot
- **Topluluk**: GitHub Contributors
- **İlham**: Otto DIY Community

---

## 🔗 Faydalı Bağlantılar

### Resmi Kaynaklar
- **Otto DIY**: https://www.ottodiy.com/
- **ESP8266 Arduino**: https://arduino-esp8266.readthedocs.io/
- **Arduino Reference**: https://www.arduino.cc/reference/

### Topluluk
- **Arduino Forum**: https://forum.arduino.cc/
- **ESP8266 Community**: https://www.esp8266.com/
- **Otto DIY Forum**: https://www.ottodiy.com/forum

### Öğrenme Kaynakları
- **ESP8266 Başlangıç**: https://randomnerdtutorials.com/esp8266/
- **Servo Motor Kullanımı**: https://www.arduino.cc/en/Tutorial/Sweep
- **Robot Kinematiği**: Bipedal walking tutorials

---

## 📊 Proje İstatistikleri

```
Kod Satırları:
- Arduino (.ino):    ~590 satır
- Header (.h):       ~126 satır
- Dokümantasyon:    ~1200 satır
─────────────────────────────
Toplam:             ~1916 satır

Dosyalar:
- Kod dosyaları:     3 adet
- Dokümantasyon:     5 adet
─────────────────────────────
Toplam:              8 adet

Diller:
- C/C++ (Arduino):   85%
- Markdown:          15%
```

---

## 🎓 Eğitim Amaçları

Bu proje şu konuları öğretmek için tasarlanmıştır:

1. **Mikrodenetleyici Programlama**
   - ESP8266 GPIO kontrolü
   - PWM sinyalleri
   - Seri iletişim

2. **Servo Motor Kontrolü**
   - PWM tabanlı pozisyon kontrolü
   - Yumuşak hareket algoritmaları
   - Çoklu servo senkronizasyonu

3. **Robotik Temelleri**
   - Bipedal (iki bacaklı) hareket
   - Kinematik hesaplamalar
   - Denge ve koordinasyon

4. **IoT (Internet of Things)**
   - WiFi bağlantısı
   - Web server oluşturma
   - RESTful API

5. **Yazılım Geliştirme**
   - Modüler kod yapısı
   - Konfigürasyon yönetimi
   - Dokümantasyon yazımı

---

## 🌟 Teşekkürler

Otto Robot ESP8266 projesini kullandığınız için teşekkürler! 

Sorularınız, önerileriniz veya katkılarınız için GitHub'da iletişime geçebilirsiniz.

**İyi kodlamalar ve robotik maceralar! 🤖🚀**

---

_Son güncelleme: 20 Kasım 2025_

<div align="center">

  <h1>📸 ESP32-CAM Akıllı Masa Güvenlik Sistemi</h1>

  <p>
    <b>Telegram üzerinden kontrol edilebilen, yapay görme tabanlı nesne takip ve güvenlik sistemi.</b>
  </p>

<p>
  <img src="https://img.shields.io/badge/Donanım-ESP32--CAM-orange?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/Yazılım-Arduino%20IDE-00979D?style=for-the-badge&logo=arduino" />
</p>

</div>

---

## 🚀 Proje Hakkında
Bu proje, masanızın üzerindeki değerli eşyaları korumak için tasarlanmıştır. ESP32-CAM modülü, masadaki eşyaların varlığını sürekli kontrol eder ve bir değişiklik (eşyanın alınması vb.) algıladığında size anlık olarak **tarih, saat ve fotoğraf** bilgisi gönderir.

### 🌟 Temel Özellikler
* **📸 Anlık Fotoğraf:** Telegram üzerinden `/foto` komutuyla her an fotoğraf alabilme.
* **🎥 Canlı Yayın:** Yerel ağ üzerinden masayı canlı izleme desteği.
* **⚠️ Akıllı Takip:** Masadaki eşyalar azaldığında veya yer değiştirdiğinde otomatik uyarı.
* **📅 Kayıt Sistemi:** Olay anının tarih ve saat bilgisini SD karta ve Telegram'a raporlama.

---

## 🛠️ Donanım Mimarisi
Proje, yüksek stabilite için **MBR Board (ESP32-CAM Shield)** üzerine inşa edilmiştir.

* **ESP32-CAM:** Ana kontrolcü ve görüntü işleme birimi.
* **MBR Board:** Kolay programlama, stabil voltaj regülasyonu ve güvenli bağlantı sağlar.
* **5V/12V DC Adaptör:** MBR Board üzerindeki regülatör sayesinde geniş güç girişi imkanı.



---

## 📦 Kurulum ve Kullanım

1.  **Bot Oluşturma:** [BotFather](https://t.me/botfather) üzerinden bir Telegram botu oluşturun ve `API Token`ınızı alın.
2.  **Kütüphaneler:** Arduino IDE üzerinden `UniversalTelegramBot` ve `ArduinoJson` kütüphanelerini kurun.
3.  **Ayarlar:** Kod içerisindeki `WIFI_SSID`, `WIFI_PASSWORD` ve `BOT_TOKEN` alanlarını kendi bilgilerinizle doldurun.
4.  **Yükleme:** ESP32-CAM'i FTDI üzerinden bilgisayara bağlayın ve kodu yükleyin.

---

## 🤖 Telegram Komutları
| Komut | Açıklama |
| :--- | :--- |
| `/start` | Hoşgeldin mesajı ve yardım menüsü. |
| `/foto` | O anki masa görüntüsünü yakalar ve gönderir. |
| `/durum` | Sistemin aktiflik durumunu kontrol eder. |
| `/canli` | Canlı yayın linkini paylaşır. |

---


<div align="center">

  <a href="https://github.com/byfisher">
    <img src="https://img.shields.io/badge/GitHub-Profilim-black?style=flat-square&logo=github" />
  </a>
</div>

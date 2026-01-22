#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// --- AYARLAR ---
const char* ssid = "WIFI_ADIN";
const char* password = "WIFI_SIFREN";
const char* BOTtoken = "TELEGRAM_BOT_TOKEN";
const char* CHAT_ID = "CHAT_ID_NUMARAN";

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

unsigned long lastTimeChecked = 0;
int checkDelay = 5000; // 5 saniyede bir eşyayı kontrol et
bool monitoringActive = true;

// Görüntü karşılaştırma için değişkenler
uint32_t lastFrameAverage = 0;
const int threshold = 15; // Değişim hassasiyeti (0-255 arası)

void setup() {
  Serial.begin(115200);
  
  // Kamera Ayarları (AI-THINKER Pinleri)
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5; config.pin_d1 = 18; config.pin_d2 = 19; config.pin_d3 = 21;
  config.pin_d4 = 36; config.pin_d5 = 39; config.pin_d6 = 34; config.pin_d7 = 35;
  config.pin_xclk = 0; config.pin_pclk = 22; config.pin_vsync = 25;
  config.pin_href = 23; config.pin_sscb_sda = 26; config.pin_sscb_scl = 27;
  config.pin_pwdn = 32; config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA; // Hız için düşük çözünürlük
  config.jpeg_quality = 12;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) { Serial.println("Kamera başlatılamadı!"); return; }

  // Wi-Fi Bağlantısı
  WiFi.begin(ssid, password);
  client.setInsecure(); // SSL sertifikasını atla (hız için)
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  
  bot.sendMessage(CHAT_ID, "Sistem Aktif! Masayı izliyorum...", "");
}

// Basit Görüntü Karşılaştırma Fonksiyonu
bool checkObjectMovement() {
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) return false;

  uint32_t currentAverage = 0;
  for (size_t i = 0; i < fb->len; i++) {
    currentAverage += fb->buf[i];
  }
  currentAverage /= fb->len;

  bool changed = false;
  if (lastFrameAverage != 0 && abs((long)currentAverage - (long)lastFrameAverage) > threshold) {
    changed = true;
  }
  
  lastFrameAverage = currentAverage;
  esp_camera_fb_return(fb);
  return changed;
}

void loop() {
  // 1. Eşya Kontrolü
  if (monitoringActive && millis() > lastTimeChecked + checkDelay) {
    if (checkObjectMovement()) {
      bot.sendMessage(CHAT_ID, "UYARI: Masadaki eşya hareket etti veya alındı!", "");
      // Burada fotoğraf gönderme fonksiyonu çağrılabilir
    }
    lastTimeChecked = millis();
  }

  // 2. Telegram Komutlarını Dinle
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while(numNewMessages) {
    for (int i=0; i<numNewMessages; i++) {
      String text = bot.messages[i].text;
      if (text == "/foto") {
        // Fotoğraf çekip gönderme kodu buraya gelecek
      }
    }
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}

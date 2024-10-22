#include <ESP8266WiFi.h>    
#include <ESP8266WebServer.h>

const char* ssid = "Osman"; // WiFi SSID
const char* password = "21032020"; // WiFi şifresi

ESP8266WebServer server(80); // Web sunucusu

// D2 pinini tanımla
const int ledPin = 4;

void handleOn() {
  digitalWrite(ledPin, HIGH); // LED'i yak
  server.send(200, "text/plain", "LED Açık!");
}

void handleOff() {
  digitalWrite(ledPin, LOW); // LED'i söndür
  server.send(200, "text/plain", "LED Kapalı!");
}

void setup() {
  // Seri haberleşme başlat
  Serial.begin(115200);
  
  // D2 pinini çıkış olarak ayarla
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Başlangıçta kapalı durumda olsun
  
  // WiFi ağına bağlan
  WiFi.begin(ssid, password);
  
  // WiFi bağlanana kadar bekle
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi'ye bağlanıyor...");
  }

  // Bağlantı başarılı
  Serial.println("WiFi'ye bağlandı!");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.localIP());

  // Sunucu rotalarını ayarla
  server.on("/on", handleOn);    // LED açma
  server.on("/off", handleOff);  // LED kapama

  // Web sunucusunu başlat
  server.begin();
  Serial.println("Web sunucusu başlatıldı.");
}

void loop() {
  server.handleClient(); // İstemci isteklerini işle
}

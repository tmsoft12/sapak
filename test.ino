#include <ESP8266WiFi.h>    
#include <ESP8266WebServer.h>

const char* ssid = "Osman"; // WiFi SSID
const char* password = "21032020"; // WiFi şifresi

ESP8266WebServer server(80); // Web sunucusu

// LED pinlerini tanımla
const int ledPin1 = 4; // 1. LED
const int ledPin2 = 2; // 2. LED
const int ledPin3 = 3; // 3. LED

void handleOn() {
  String led = server.arg("led"); // LED numarasını al
  if (led == "1") {
    digitalWrite(ledPin1, HIGH); // 1. LED'i yak
    server.send(200, "text/plain", "LED 1 Açık!");
  } else if (led == "2") {
    digitalWrite(ledPin2, HIGH); // 2. LED'i yak
    server.send(200, "text/plain", "LED 2 Açık!");
  } else if (led == "3") {
    digitalWrite(ledPin3, HIGH); // 3. LED'i yak
    server.send(200, "text/plain", "LED 3 Açık!");
  } else {
    server.send(400, "text/plain", "Geçersiz LED numarası!");
  }
}

void handleOff() {
  String led = server.arg("led"); // LED numarasını al
  if (led == "1") {
    digitalWrite(ledPin1, LOW); // 1. LED'i söndür
    server.send(200, "text/plain", "LED 1 Kapalı!");
  } else if (led == "2") {
    digitalWrite(ledPin2, LOW); // 2. LED'i söndür
    server.send(200, "text/plain", "LED 2 Kapalı!");
  } else if (led == "3") {
    digitalWrite(ledPin3, LOW); // 3. LED'i söndür
    server.send(200, "text/plain", "LED 3 Kapalı!");
  } else {
    server.send(400, "text/plain", "Geçersiz LED numarası!");
  }
}

void setup() {
  // Seri haberleşme başlat
  Serial.begin(115200);
  
  // LED pinlerini çıkış olarak ayarla
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  // Başlangıçta tüm LED'leri kapalı durumda olsun
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  
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

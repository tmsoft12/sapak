package main

import (
	"fmt"
	"log"
	"net/http"
)

// ESP8266 IP adresi
const esp8266IP = "http://192.168.100.179" // Buraya ESP8266'nın IP adresini girin

// CORS başlıkları ekleme
func enableCORS(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Access-Control-Allow-Origin", "*") // Tüm kaynaklardan gelen isteklere izin ver
	w.Header().Set("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
	w.Header().Set("Access-Control-Allow-Headers", "Content-Type")
}

// LED'i açmak için istek gönder
func turnOnLED(w http.ResponseWriter, r *http.Request) {
	enableCORS(w, r)
	if r.Method == "OPTIONS" {
		return
	}

	led := r.URL.Query().Get("led")
	if led == "" {
		http.Error(w, "LED parametresi belirtilmedi", http.StatusBadRequest)
		return
	}

	resp, err := http.Get(fmt.Sprintf("%s/on?led=%s", esp8266IP, led))
	if err != nil {
		http.Error(w, "ESP8266'ya bağlanılamadı", http.StatusInternalServerError)
		return
	}
	defer resp.Body.Close()
	fmt.Fprintf(w, "LED %s açıldı!", led)
}

// LED'i kapatmak için istek gönder
func turnOffLED(w http.ResponseWriter, r *http.Request) {
	enableCORS(w, r)
	if r.Method == "OPTIONS" {
		return
	}

	led := r.URL.Query().Get("led")
	if led == "" {
		http.Error(w, "LED parametresi belirtilmedi", http.StatusBadRequest)
		return
	}

	resp, err := http.Get(fmt.Sprintf("%s/off?led=%s", esp8266IP, led))
	if err != nil {
		http.Error(w, "ESP8266'ya bağlanılamadı", http.StatusInternalServerError)
		return
	}
	defer resp.Body.Close()
	fmt.Fprintf(w, "LED %s kapandı!", led)
}

func main() {
	http.HandleFunc("/on", turnOnLED)
	http.HandleFunc("/off", turnOffLED)

	fmt.Println("Sunucu 8080 portunda çalışıyor...")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

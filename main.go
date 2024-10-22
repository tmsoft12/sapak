package main

import (
	"fmt"
	"log"
	"net/http"
)

const esp8266IP = "http://192.168.100.179" // ESP8266'nın IP adresini buraya girin

// LED'i yakmak için istek gönder
func turnOnLED(w http.ResponseWriter, r *http.Request) {
	resp, err := http.Get(esp8266IP + "/on")
	if err != nil {
		http.Error(w, "ESP8266'ya bağlanılamadı", http.StatusInternalServerError)
		return
	}
	defer resp.Body.Close()
	fmt.Fprintf(w, "LED açıldı!")
}

// LED'i söndürmek için istek gönder
func turnOffLED(w http.ResponseWriter, r *http.Request) {
	resp, err := http.Get(esp8266IP + "/off")
	if err != nil {
		http.Error(w, "ESP8266'ya bağlanılamadı", http.StatusInternalServerError)
		return
	}
	defer resp.Body.Close()
	fmt.Fprintf(w, "LED kapandı!")
}

func main() {
	http.HandleFunc("/on", turnOnLED)
	http.HandleFunc("/off", turnOffLED)

	fmt.Println("Sunucu 8080 portunda çalışıyor...")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

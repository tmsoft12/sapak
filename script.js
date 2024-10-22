function toggleButton(buttonId, onUrl, offUrl) {
    const button = document.getElementById(buttonId);
    const isOn = button.classList.contains('on'); // Düğmenin mevcut durumu

    // LED'i aç veya kapat
    const url = isOn ? offUrl : onUrl;

    fetch(url)
        .then(response => {
            if (response.ok) {
                button.classList.toggle('on'); // Düğme durumunu değiştir
                button.classList.toggle('off');
                button.textContent = isOn ? "Düğme Kapalı" : "Düğme Açık"; // Düğme metnini güncelle
            } else {
                console.error("LED açma/kapatma işlemi başarısız oldu.");
            }
        })
        .catch(error => {
            console.error("Bir hata oluştu:", error);
        });
}

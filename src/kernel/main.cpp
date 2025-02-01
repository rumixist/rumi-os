#include "../include/print.h"
#include "../include/keyboard.h"

extern "C" void kernel_main() {
    // Başlangıç mesajını yazdır
    print("Kernel baslatildi kernel version 2!\n");
    print("Klavye girdilerini test ediyorum...\n");

    // Klavye sürücüsünü başlat
    keyboard_init();

    // Sonsuz döngüde klavye girişi al
    while (1) {
        // Klavye girişini al (bu fonksiyon klavye_handler'ı tetikleyecek)
        // Test için ekrana basılan tuşu yazdır
    }
}

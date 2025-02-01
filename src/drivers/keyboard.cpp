#include "../include/keyboard.h"
#include "../include/print.h"
#include "../include/io.h"
#include "../include/memory.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_CMD_PORT  0x64

static uint8_t shift_pressed = 0;
static uint8_t caps_lock = 0;
static char keyboard_buffer[128];
static int buffer_index = 0;

// Küçük harfi büyük harfe dönüştüren basit fonksiyon
char my_toupper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A'; // Küçük harfi büyük harfe dönüştür
    }
    return c; // Eğer zaten büyükse, olduğu gibi bırak
}


static char scancode_to_char(uint8_t scancode) {
    switch (scancode) {
        case 0x1E: return 'a';
        case 0x30: return 'b';
        case 0x2E: return 'c';
        case 0x20: return 'd';
        case 0x12: return 'e';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x17: return 'i';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x32: return 'm';
        case 0x31: return 'n';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x10: return 'q';
        case 0x13: return 'r';
        case 0x1F: return 's';
        case 0x14: return 't';
        case 0x16: return 'u';
        case 0x2F: return 'v';
        case 0x11: return 'w';
        case 0x2D: return 'x';
        case 0x15: return 'y';
        case 0x2C: return 'z';
        case 0x2B: return '1';
        case 0x3E: return '2';
        case 0x3A: return '3';
        case 0x4C: return '4';
        case 0x52: return '5';
        case 0x41: return '6';
        case 0x49: return '7';
        case 0x4A: return '8';
        case 0x51: return '9';
        case 0x48: return '0';
        case 0x39: return ' ';
        case 0x0E: return '\b'; // Backspace
        case 0x1C: return '\n';  // Enter
        case 0x35: return '\t';  // Tab
        case 0x3B: return '\'';  // Single Quote
        case 0x3C: return '-';   // Minus
        case 0x33: return '.';   // Period
        default: return 0;
    }
}

void keyboard_init() {
    // Başlangıçta bir şey yapmaya gerek yok, sadece klavye başlatıldı
    print("Klavye surucusu baslatildi.\n");
}

void keyboard_handler() {
    uint8_t scancode = inb(KEYBOARD_DATA_PORT); // Klavye verisini oku

    if (scancode == 0x2A || scancode == 0x36) {  // Shift tuşuna basıldı
        shift_pressed = 1;
    } else if (scancode == 0xAA || scancode == 0xB6) {  // Shift tuşu bırakıldı
        shift_pressed = 0;
    } else if (scancode == 0x3A) {  // Caps Lock
        caps_lock = !caps_lock;
    }

    char c = scancode_to_char(scancode);
    if (c) {
        // Shift tuşu basılı ise büyük harf, değilse küçük harf
        if (shift_pressed || caps_lock) {
            c = my_toupper(c);
        }

        if (c == '\b') {
            // Backspace, ekrandan son karakteri sil
            if (buffer_index > 0) {
                buffer_index--;
                print_char(c); // Yine de geri tuşu basıldığını ekranda göster
            }
        } else if (c == '\n') {
            // Enter tuşu, yeni satır başlat
            print_char(c);
            keyboard_buffer[buffer_index] = '\0';  // Komutu bitir
            print("Komut: ");
            print(keyboard_buffer);
            buffer_index = 0;  // Buffer'ı temizle
        } else {
            // Normal karakter
            if (buffer_index < 127) {
                keyboard_buffer[buffer_index++] = c;
            }
            print_char(c);
        }
    }

    // IRQ işlemi tamamlandığında PIC'e bitiş komutu gönder
    outb(0x20, 0x20); // End of Interrupt
}

#include "../include/print.h"

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static int row = 0, col = 0;
static char* vga_buffer = (char*)VGA_ADDRESS;

void clear_screen() {
    // Ekranı temizler
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2) {
        vga_buffer[i] = ' ';
        vga_buffer[i + 1] = 0x07; // Varsayılan renk: Gri
    }
    row = 0;
    col = 0;
}

void print_char(char c) {
    if (c == '\n') {
        row++;
        col = 0;
        if (row >= VGA_HEIGHT) {
            row = 0; // Ekran sonu, başa sar
        }
        return;
    }

    if (col >= VGA_WIDTH) {
        col = 0;
        row++;
        if (row >= VGA_HEIGHT) {
            row = 0; // Ekran sonu, başa sar
        }
    }

    int index = (row * VGA_WIDTH + col) * 2;
    vga_buffer[index] = c;
    vga_buffer[index + 1] = 0x07; // Gri renk

    col++;
}

void print(const char *str) {
    // Ekrana bir string yazdırır
    while (*str) {
        print_char(*str++);  // Her karakteri yazdır
    }
}

// memory.cpp
#include "../include/memory.h"

#define MEMORY_SIZE 0x100000 // 1MB

static uint8_t memory[MEMORY_SIZE]; // Kernel için ayrılan bellek
static uint32_t current_index = 0;

void* kmalloc(size_t size) {
    // Bellek yönetimini yalnızca kernel başlatıldıktan sonra yap
    if (current_index + size > MEMORY_SIZE) {
        return nullptr; // Bellek sınırını aştık
    }

    void* ptr = &memory[current_index];
    current_index += size;
    return ptr;
}

void free(void* ptr) {
    // Şu an basit bir free fonksiyonu kullanıyoruz, gelişmiş bellek serbest bırakma işlevi eklenebilir
}

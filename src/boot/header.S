.section .multiboot
.align 4
.multiboot_header:
    .long 0x1BADB002       # Multiboot Magic Number
    .long 0x0              # Flags (Sadece temel boot bilgileri)
    .long - (0x1BADB002 + 0x0)  # Checksum (Magic + Flags + Checksum = 0 olmalı)

.section .text
.global start
.extern kernel_main
start:
    cli                    # Kesintileri kapat
    call kernel_main       # Kernel ana fonksiyonunu çağır
    hlt                    # CPU'yu durdur (buraya gelirse hata var demektir)

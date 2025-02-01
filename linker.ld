OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS {
    . = 1M; /* Kernel bellek adresini 1MB’ye yerleştir */

    .text ALIGN(4K) : {
        *(.multiboot)  /* Multiboot Header buraya */
        *(.text)       /* Kernel kodu buraya */
    }

    .data ALIGN(4K) : { *(.data) }
    .bss  ALIGN(4K) : { *(.bss)  }
}
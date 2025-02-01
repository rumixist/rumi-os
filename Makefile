# Derleyici ve araçlar
CC = i686-linux-gnu-gcc
CXX = i686-linux-gnu-g++
LD = i686-linux-gnu-ld
AS = i686-linux-gnu-as
GRUB = grub-mkrescue
QEMU = qemu-system-i386

# Dosya ve dizinler
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
ISO_DIR = iso
KERNEL_BIN = boot/my_kernel.bin
ISO_NAME = my_kernel.iso
GRUB_CFG = grub.cfg  # Dosyanın proje kök dizininde olduğunu belirtir.

# Derleme bayrakları
CFLAGS = -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE_DIR)
LDFLAGS = -T linker.ld

# Hedefler
all: $(ISO_NAME)

$(KERNEL_BIN): $(SRC_DIR)/boot/header.S $(SRC_DIR)/kernel/main.cpp $(SRC_DIR)/kernel/print.cpp $(SRC_DIR)/drivers/keyboard.cpp $(SRC_DIR)/kernel/memory.cpp
		@echo "Derleme işlemi yapılıyor..."
		mkdir -p $(BUILD_DIR)/boot $(BUILD_DIR)/kernel
		$(AS) -o $(BUILD_DIR)/boot/boot.o $(SRC_DIR)/boot/header.S
		$(CXX) $(CFLAGS) -c $(SRC_DIR)/kernel/main.cpp -o $(BUILD_DIR)/kernel/main.o
		$(CXX) $(CFLAGS) -c $(SRC_DIR)/kernel/print.cpp -o $(BUILD_DIR)/kernel/print.o
		$(CXX) $(CFLAGS) -c $(SRC_DIR)/drivers/keyboard.cpp -o $(BUILD_DIR)/kernel/keyboard.o
		$(CXX) $(CFLAGS) -c $(SRC_DIR)/kernel/memory.cpp -o $(BUILD_DIR)/kernel/memory.o
		$(LD) $(LDFLAGS) -o $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/boot/boot.o $(BUILD_DIR)/kernel/main.o $(BUILD_DIR)/kernel/print.o $(BUILD_DIR)/kernel/keyboard.o $(BUILD_DIR)/kernel/memory.o
		mkdir -p boot
		cp $(BUILD_DIR)/kernel.bin $(KERNEL_BIN)

$(ISO_NAME): $(KERNEL_BIN) $(GRUB_CFG)
		@echo "ISO dosyası oluşturuluyor..."
		mkdir -p $(ISO_DIR)/boot/grub
		cp $(GRUB_CFG) $(ISO_DIR)/boot/grub/
		cp $(KERNEL_BIN) $(ISO_DIR)/boot/
		$(GRUB) -o $(ISO_NAME) $(ISO_DIR)

run: $(ISO_NAME)
		@echo "QEMU ile kernel çalıştırılıyor..."
		$(QEMU) -cdrom $(ISO_NAME)

clean:
		@echo "Geçici dosyalar temizleniyor..."
		rm -rf $(BUILD_DIR) $(ISO_DIR) $(ISO_NAME)
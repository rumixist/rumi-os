# Kernel Project

This is a simple kernel project to demonstrate a basic operating system kernel using C++ and assembly language. It includes features like memory management, basic keyboard input handling, and bootloader integration with GRUB. The kernel is built to run on a virtual machine using QEMU.

## Features
- **Basic Memory Management**: Simple `kmalloc()` for dynamic memory allocation.
- **Keyboard Input**: A basic keyboard input handler.
- **GRUB Bootloader**: Kernel is booted using GRUB.
- **QEMU**: The kernel is tested using QEMU.

## Prerequisites
Before you begin, ensure you have the following installed:

- `i686-linux-gnu-gcc` and `i686-linux-gnu-g++` (Cross-compiler for 32-bit x86)
- `GRUB` for bootloader setup
- `QEMU` for running the virtual machine
- `Make` for building the project

## Setup and Build

1. Clone the repository:
```bash
   git clone https://github.com/rumixist/rumi-os.git
   cd kernel-project
```
2. Build the kernel

```bash
   make
```
2. Create the ISO image
```bash
   make iso
```
3. Run the kernel on QEMU:
```bash
   make run
```
## Troubleshooting
If you encounter issues during the build, ensure the following:

-Check for missing dependencies.
-Verify that all paths in the Makefile are correct.
-If the keyboard driver is not working, ensure that the input handling code is properly implemented and the interrupt is set up correctly.

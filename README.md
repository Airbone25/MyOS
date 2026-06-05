# MyOS
This repo is for my own os

## Tools used
- C
- x86 Assembly and NASM
- GRUB
- QEMU (for testing)

## Prerequisites
- gcc
- NASM (Assembler)
- binutils and make (Linker and build tools)
- GRUB (bootloader)
- QEMU (Virtual Machine to test)

Note: may ask for 'mtools' package for GRUB.

## Installation guide

### Linux (Debian/Ubuntu)
Run the following command to install the required dependencies:
```bash
sudo apt update
sudo apt install build-essential nasm binutils grub-common grub-pc-bin qemu-system-x86 mtools xorriso
```

### Windows
The easiest way to build this on Windows is using WSL (Windows Subsystem for Linux), as we require a Linux-like environment for GRUB and certain build tools.
1. Open PowerShell as Administrator and run: `wsl --install`
2. Restart your computer and set up your Linux distribution (Ubuntu is recommended).
3. Open the WSL terminal and follow the **Linux (Debian/Ubuntu)** installation guide above.


## To test
RUN:
``` bash
make run
```

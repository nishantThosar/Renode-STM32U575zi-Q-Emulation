# STM32U575ZI-Q Renode Emulation

![STM32U575ZI](https://img.shields.io/badge/STM32-U575ZI--Q-blue)
![Renode](https://img.shields.io/badge/Emulator-Renode-green)
![Status](https://img.shields.io/badge/Status-Active-success)

A complete emulation setup for the **STM32U575ZI-Q NUCLEO board** using [Renode](https://renode.io/), an open-source hardware emulation framework. This repository allows you to develop, test, and debug STM32 firmware without physical hardware!

---

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Repository Structure](#repository-structure)
- [Quick Start](#quick-start)
- [Detailed Setup Guide](#detailed-setup-guide)
- [Running the Emulation](#running-the-emulation)
- [Understanding the Files](#understanding-the-files)
- [Creating Your Own Firmware](#creating-your-own-firmware)
- [Troubleshooting](#troubleshooting)
- [Resources](#resources)
- [Contributing](#contributing)
- [License](#license)

---

## 🎯 About

This repository provides everything you need to emulate the **STM32U575ZI-Q** microcontroller in Renode. Whether you're:
- Learning embedded systems without hardware
- Testing firmware in CI/CD pipelines
- Debugging complex multi-board systems
- Prototyping IoT applications

...this setup has you covered!

### What is Renode?

**Renode** is an open-source development framework that lets you run embedded software on virtual hardware. Think of it as a virtual development board on your computer. Benefits include:
- **No Hardware Needed**: Develop and test without physical boards
- **Fast Iteration**: No flashing, instant resets, perfect reproducibility
- **Advanced Debugging**: Full system inspection, time travel debugging
- **Multi-node Networks**: Simulate entire IoT networks on one machine

---

## ✨ Features

This emulation platform includes:

### Functional Peripherals
- ✅ **ARM Cortex-M33 CPU** @ 160 MHz
- ✅ **6 UART/USARTs** (USART1-5, LPUART1) - Fully functional serial communication
- ✅ **GPIO Ports** (A-I) - All 9 ports with 16 pins each
- ✅ **3 User LEDs** (Red, Green, Blue) with visual feedback
- ✅ **Memory**: 2MB Flash + 786KB SRAM

### Mocked Peripherals (Register Access)
- 🔧 SPI (1-3)
- 🔧 I2C (1-4)
- 🔧 Timers (TIM1-17, LPTIM1-4)
- 🔧 ADC, DAC
- 🔧 DMA Controllers
- 🔧 USB, SDMMC, CAN
- 🔧 Cryptographic accelerators (AES, HASH, RNG)

> **Note**: Mocked peripherals appear as memory regions - your code can read/write registers, but complex protocols may need additional implementation.

---

## 📦 Prerequisites

### Required Software

1. **Renode** (v1.13.0 or later)
   - Download from: https://github.com/renode/renode/releases
   - Or use portable version: https://builds.renode.io/

2. **ARM GCC Toolchain** (for building firmware)
   ```bash
   # Ubuntu/Debian
   sudo apt-get install gcc-arm-none-eabi
   
   # macOS (using Homebrew)
   brew install arm-none-eabi-gcc
   
   # Windows
   # Download from: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm
   ```

3. **Git**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install git
   
   # macOS
   brew install git
   ```

### Optional Tools

- **VS Code** with Cortex-Debug extension (for GDB debugging)
- **STM32CubeMX** (for generating peripheral initialization code)

---

## 📁 Repository Structure

```
Renode-STM32U575zi-Q-Emulation/
│
├── basic_run.resc                      # Renode startup script
├── u575_peripherial_documented.repl    # STM32U575ZI platform description
├── main.c                              # Example firmware source
├── linker.ld                           # Linker script for memory layout
├── firmware.elf                        # Pre-compiled example firmware
└── README.md                           # This file
```

---

## 🚀 Quick Start

Get up and running in 3 minutes!

### 1. Clone the Repository

```bash
git clone https://github.com/nishantThosar/Renode-STM32U575zi-Q-Emulation.git
cd Renode-STM32U575zi-Q-Emulation
```

### 2. Install Renode

**Linux (Portable Version)**:
```bash
wget https://builds.renode.io/renode-latest.linux-portable.tar.gz
mkdir renode_portable
tar xf renode-latest.linux-portable.tar.gz -C renode_portable --strip-components=1
export PATH=$PATH:$(pwd)/renode_portable
```

**macOS**:
```bash
# Download .dmg from https://github.com/renode/renode/releases
# Install and add to PATH:
echo 'alias renode="mono /Applications/Renode.app/Contents/MacOS/bin/Renode.exe"' >> ~/.zshrc
source ~/.zshrc
```

**Windows**:
- Download and install the `.msi` package from [Renode Releases](https://github.com/renode/renode/releases)
- The installer will add Renode to your PATH automatically

### 3. Run the Emulation

```bash
renode basic_run.resc
```

That's it! You should see:
- Renode Monitor window opens
- Virtual board starts running
- UART output appears in the terminal
- LED states visible in the UI

---

## 📖 Detailed Setup Guide

### Step 1: Understanding Renode Installation

**Option A: Package Installation (Recommended)**
- Download the appropriate package for your OS from [Renode Releases](https://github.com/renode/renode/releases)
- Install using your package manager (.deb, .rpm, .pkg, .msi)
- Renode will be automatically added to your system PATH

**Option B: Portable Version**
- Download the portable `.tar.gz` archive
- Extract to a directory of your choice
- No installation needed - run directly from the folder
- Useful for testing or when you don't have admin rights

**Verify Installation**:
```bash
renode --version
```

### Step 2: Clone and Explore

```bash
git clone https://github.com/nishantThosar/Renode-STM32U575zi-Q-Emulation.git
cd Renode-STM32U575zi-Q-Emulation

# List files
ls -la
```

### Step 3: Examine the Platform Description

The `.repl` file defines the virtual hardware:

```bash
# View the platform file
cat u575_peripherial_documented.repl
```

This file describes:
- Memory regions (Flash, SRAM)
- Peripherals (UART, GPIO, Timers)
- Interrupt connections
- LED mappings

### Step 4: Review the Startup Script

The `.resc` file is a Renode script that:
- Creates a virtual machine
- Loads the platform description
- Loads your firmware
- Starts execution

```bash
# View the script
cat basic_run.resc
```

---

## 🎮 Running the Emulation

### Method 1: Using the Startup Script

```bash
renode basic_run.resc
```

### Method 2: Manual Step-by-Step

Launch Renode:
```bash
renode
```

In the Renode Monitor, execute:
```
# Create a new machine called "stm32"
mach create "stm32"

# Load the platform description
machine LoadPlatformDescription @u575_peripherial_documented.repl

# Load the firmware
sysbus LoadELF @firmware.elf

# Show the UART output in this terminal
showAnalyzer sysbus.usart1

# Start the emulation
start
```

### Method 3: With GDB Debugging

```bash
# In Renode Monitor
mach create "stm32"
machine LoadPlatformDescription @u575_peripherial_documented.repl
sysbus LoadELF @firmware.elf
machine StartGdbServer 3333
start

# In another terminal
arm-none-eabi-gdb firmware.elf
(gdb) target remote localhost:3333
(gdb) break main
(gdb) continue
```

---

## 📝 Understanding the Files

### 1. `basic_run.resc` - Renode Script

This is your automation script. It runs when you type `renode basic_run.resc`.

**Example content**:
```
# Create virtual machine
mach create "stm32u575"

# Load hardware description
machine LoadPlatformDescription @u575_peripherial_documented.repl

# Load firmware
sysbus LoadELF @firmware.elf

# Enable UART output
showAnalyzer sysbus.usart1

# Start running
start
```

**Common Commands**:
- `mach create "name"` - Create a new virtual machine
- `machine LoadPlatformDescription @file.repl` - Load hardware definition
- `sysbus LoadELF @file.elf` - Load compiled firmware
- `start` - Begin execution
- `pause` - Pause execution
- `quit` - Exit Renode

### 2. `u575_peripherial_documented.repl` - Platform Description

Defines the virtual STM32U575ZI hardware in a declarative format.

**Key sections**:
```
// Define CPU
cpu: CPU.CortexM @ sysbus
    cpuType: "cortex-m33"

// Define Flash memory
flash: Memory.MappedMemory @ sysbus 0x08000000
    size: 0x200000  // 2MB

// Define UART
usart1: UART.STM32F7_USART @ sysbus <0x40013800, +0x400>
    frequency: 160000000
    IRQ -> nvic@61
```

**Format**: REPL (REnode PLatform) - custom DSL for hardware description

### 3. `main.c` - Firmware Source Code

Your C program that runs on the virtual STM32. This is standard embedded C code.

**Typical structure**:
```c
// Include STM32 headers
#include "stm32u575xx.h"

// Main function
int main(void) {
    // Initialize peripherals
    // Your application code here
    
    while(1) {
        // Main loop
    }
}
```

### 4. `linker.ld` - Linker Script

Defines the memory layout and tells the compiler where to place code and data.

**Key sections**:
```ld
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2M
    SRAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 192K
}

SECTIONS
{
    .text : { *(.text*) } > FLASH    /* Code goes to Flash */
    .data : { *(.data*) } > SRAM     /* Data goes to RAM */
    .bss  : { *(.bss*) }  > SRAM     /* Uninitialized data */
}
```

### 5. `firmware.elf` - Compiled Firmware

The binary file that Renode loads and executes. Contains:
- Machine code
- Debug symbols (for GDB)
- Memory layout information

---

## 🛠️ Creating Your Own Firmware

### Step 1: Write Your Code

Create or modify `main.c`:

```c
#include <stdint.h>

// Memory-mapped UART1 registers
#define USART1_BASE 0x40013800
#define USART1_DR   (*(volatile uint32_t*)(USART1_BASE + 0x04))
#define USART1_SR   (*(volatile uint32_t*)(USART1_BASE + 0x00))

// Simple UART transmit function
void uart_putchar(char c) {
    while (!(USART1_SR & 0x80)); // Wait for TXE flag
    USART1_DR = c;
}

void uart_puts(const char* str) {
    while (*str) {
        uart_putchar(*str++);
    }
}

int main(void) {
    // Initialize UART (simplified)
    // In real code, you'd configure clocks, GPIO, etc.
    
    uart_puts("Hello from STM32U575ZI-Q!\r\n");
    
    int counter = 0;
    while (1) {
        uart_puts("Counter: ");
        // Print counter (simplified - no printf)
        counter++;
        
        // Simple delay
        for (volatile int i = 0; i < 1000000; i++);
    }
    
    return 0;
}
```

### Step 2: Compile Your Firmware

**Simple Compilation**:
```bash
arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -O0 -g \
    -T linker.ld \
    -o firmware.elf \
    main.c
```

**With Startup Code** (recommended):
```bash
# Get STM32 startup file
# Usually: startup_stm32u575xx.s

arm-none-eabi-gcc -mcpu=cortex-m33 -mthumb -mfloat-abi=soft \
    -O0 -g -Wall \
    -T linker.ld \
    -o firmware.elf \
    startup_stm32u575xx.s \
    main.c \
    -lc -lm -lnosys
```

**Using Makefile**:
```makefile
# Makefile
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m33 -mthumb -O0 -g -Wall
LDFLAGS = -T linker.ld -lc -lm -lnosys

all: firmware.elf

firmware.elf: main.c startup_stm32u575xx.s
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f firmware.elf
```

Then simply run:
```bash
make
```

### Step 3: Test in Renode

```bash
renode basic_run.resc
```

---

## 🐛 Troubleshooting

### Issue: "Command not found: renode"

**Solution**: Renode is not in your PATH.

```bash
# Find where Renode is installed
which renode

# If not found, add to PATH:
# Linux/macOS:
export PATH=$PATH:/path/to/renode

# Or create an alias:
alias renode='/path/to/renode/renode'

# Make it permanent by adding to ~/.bashrc or ~/.zshrc
```

### Issue: "Could not load file: firmware.elf"

**Solution**: File path issue.

```bash
# Use absolute path
machine LoadELF @/full/path/to/firmware.elf

# Or ensure you're in the right directory
cd /path/to/repo
renode basic_run.resc
```

### Issue: "Address 0x... is not mapped"

**Solution**: Your code is trying to access a peripheral not defined in the `.repl` file.

- Check the address in your code
- Verify it matches the `.repl` definition
- Add missing peripherals to the `.repl` file if needed

### Issue: No UART Output

**Solution**: 

1. Ensure UART is initialized in your code
2. Check the analyzer is shown:
   ```
   showAnalyzer sysbus.usart1
   ```
3. Verify UART clock is configured
4. Check baud rate matches (default is usually auto-detected in Renode)

### Issue: "Error loading .repl file"

**Solution**: Syntax error in platform description.

- Check for missing semicolons
- Verify address format (must be hex: 0x...)
- Ensure proper indentation
- Look for typos in peripheral names

### Issue: Compilation Errors

**Common fixes**:

```bash
# Missing toolchain
sudo apt-get install gcc-arm-none-eabi

# Missing libraries
# Add -lc -lm -lnosys to linker flags

# Linker script not found
# Use -T flag: -T linker.ld
```

### Issue: Emulation Runs Too Fast/Slow

**Solution**: Adjust virtual time.

```
# In Renode Monitor
machine SetAdvanceImmediately true   # Run as fast as possible
machine SetAdvanceImmediately false  # Run in real-time
```

---

## 📚 Resources

### Official Documentation
- [Renode Documentation](https://renode.readthedocs.io/)
- [STM32U575ZI Datasheet](https://www.st.com/resource/en/datasheet/stm32u575zi.pdf)
- [STM32U575ZI Reference Manual](https://www.st.com/resource/en/reference_manual/rm0456-stm32u575585-armbased-32bit-mcus-stmicroelectronics.pdf)
- [ARM Cortex-M33 Documentation](https://developer.arm.com/documentation/ddi0553/latest/)

### Tutorials
- [Renode Getting Started](https://renode.readthedocs.io/en/latest/introduction/using.html)
- [REPL File Format](https://renode.readthedocs.io/en/latest/advanced/platform-description.html)
- [Renode Scripting](https://renode.readthedocs.io/en/latest/basic/machines.html)

### Community
- [Renode GitHub Issues](https://github.com/renode/renode/issues)
- [Renode Gitter Chat](https://gitter.im/renode/community)
- [STM32 Community Forums](https://community.st.com/)

### Example Projects
- [Renode Examples](https://github.com/renode/renode/tree/master/scripts)
- [STM32 Bare Metal Examples](https://github.com/google/stm32_bare_lib)

---

## 🎓 Learning Path for Beginners

### Week 1: Basics
1. Install Renode and ARM toolchain
2. Run the example firmware
3. Modify `main.c` to print different messages
4. Experiment with LED control

### Week 2: Understanding Hardware
1. Study the `.repl` file structure
2. Learn about memory-mapped peripherals
3. Read STM32 reference manual basics
4. Understand the linker script

### Week 3: Advanced Features
1. Set up GDB debugging
2. Create custom `.resc` scripts
3. Add new peripherals to `.repl`
4. Profile code performance

### Week 4: Real Projects
1. Port an existing STM32 project to Renode
2. Create a UART communication protocol
3. Implement interrupt handling
4. Build a multi-board network simulation

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### Reporting Issues
- Use GitHub Issues for bug reports
- Include Renode version, OS, and error messages
- Provide minimal reproducible example

### Adding Features
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Improving Documentation
- Fix typos or unclear instructions
- Add more examples
- Translate to other languages

### Roadmap
- [ ] Add more peripheral examples (I2C, SPI, Timer)
- [ ] Create Robot Framework test suite
- [ ] Add CI/CD integration example
- [ ] Support for STM32CubeMX generated code
- [ ] Docker container for easy setup

---

## 📄 License

This project is open source. Please check the LICENSE file for details.

**Note**: This is an independent project and is not affiliated with or endorsed by STMicroelectronics.

---

## 🙏 Acknowledgments

- **Renode Team** at Antmicro for the amazing emulation framework
- **STMicroelectronics** for STM32 documentation and hardware
- **ARM** for Cortex-M architecture
- **Community contributors** for feedback and improvements

---

## 📞 Contact & Support

- **Repository**: [github.com/nishantThosar/Renode-STM32U575zi-Q-Emulation](https://github.com/nishantThosar/Renode-STM32U575zi-Q-Emulation)
- **Issues**: [GitHub Issues](https://github.com/nishantThosar/Renode-STM32U575zi-Q-Emulation/issues)
- **Author**: Nishant Thosar

---

## ⭐ Star This Repo

If this project helped you, please star it on GitHub! It helps others discover this resource.

[![GitHub stars](https://img.shields.io/github/stars/nishantThosar/Renode-STM32U575zi-Q-Emulation?style=social)](https://github.com/nishantThosar/Renode-STM32U575zi-Q-Emulation)

---

**Happy Emulating! 🚀**

*Last Updated: December 2025*

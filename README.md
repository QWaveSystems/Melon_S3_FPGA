# Melon_S3_FPGA (Open-Source)

![](http://ftp.qwavesys.com/tmp_pics/ms30.jpg)

# A WiFi (ESP8266) FPGA Development Kit by Q-Wave Systems.

In order to support our work please consider supporting it with a donation.

https://www.paypal.me/qwavesystems

**How to get the a developement board**

https://qwavesys.bentoweb.com/en/product/346754/MelonS3?category_id=84967

**Community Support Forums**

https://www.facebook.com/groups/244230302736445/

**Board features:**

**OTA (Over-The-Air) Download.bit file to FPGA over the WiFi**

-Xilinx Spartan 3E FPGA (PQG208) - 500K gates,
(73Kb Distributed RAM, 4 Digital Clock Manager (DCM), 20 Multipliers (18x18), 360 Kb Block RAM)

-Onboard USB-UART (Silicon Labs) CP2104 for Configuration, Debugging and Power.

-WiFi 2.4GHz SoC-WROOM-02, 32-bit MCU (Arduino Compatible) Clock 80MHz, 50KB RAM, Integrated TCP/IP protocol stack.

-Flash 4MB SPI Flash which is 1MB for MCU Firmware and 3MB for FPGA Bit space.

-8 Users LEDs, 4 DIP Switch user button, 1 Reset button

-Onboard FPGA cloxk 50MHz

-GPIOs 56 PINs 3.3V Tolerant - 40 PINs x2 (Raspberry Pi 40 PINs Compatible)

-JTAG Port (*Optional for Program/Debugging)

**Arduino C/C++ compatible Firmware**

Arduino compatible source code for FPGA download functionality and Arduino IDE board package also provided to allowing you to easily modify to program the WROOM-02 using Arduino IDE. 

***Required** "Qwave ESP8266 Board Package" http://ftp.qwavesys.com/lvembedded/package_qwavesys_v2_index.json (*Select the Board : **"Qwave ESP8266 (LabVIEW)**")

![](http://ftp.qwavesys.com/tmp_pics/msc01.png)

**Support programable using LabVIEW and Raspberry Pi Interface (LINX 3.0)**  *For Home/Education Use ONLY.

![](http://ftp.qwavesys.com/tmp_pics/msc02.png)

**Board design files**

PDF https://github.com/QWaveSystems/Melon_S3_FPGA/tree/master/PDF

Schematic & PCB https://github.com/QWaveSystems/Melon_S3_FPGA/tree/master/Schematic_PCB

Firmware (Arduino C/C++) https://github.com/QWaveSystems/Melon_S3_FPGA/tree/master/Firmware

**Xilinx ISE support files**

https://github.com/QWaveSystems/Melon_S3_FPGA/blob/master/UCF%20File/Melon_S3.ucf

**Xilinx ISE project examples**

https://github.com/QWaveSystems/Melon_S3_FPGA/tree/master/Example_VHDL

**LabVIEW FPGA (2014) Examples**

8 bit Counter Example https://github.com/QWaveSystems/Melon_S3_FPGA/tree/master/Example_LabVIEW

8 bit Counter with Raspberry Pi Interface https://github.com/QWaveSystems/Melon_S3_FPGA/tree/master/Example_LabVIEW_RaspberryPi_LINX

![](http://ftp.qwavesys.com/tmp_pics/msc03.png)

**Hardware Pin-Out**

![](http://ftp.qwavesys.com/tmp_pics/msc04.jpg)

**Maintainers:**

Amornthep Phunsin <amornthep@qwavesys.com>

www.qwavesys.com

**LICENSE:**

-Schematics and PCB ﬁles is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.
You should have received a copy of the license along with this work. If not, see: http://creativecommons.org/licenses/by-sa/4.0

-These Arduino C/C++ ESP8266 microcontroller libraries (Firmware) files are provided under the GNU General Public License Version 3 as found at http://opensource.org/licenses/lgpl-3.0.html.

-Melon S3 FPGA Driver for LabVIEW is licensed for Home/Education use ONLY (Non-Commercial purposes)

**********************************************************************************************************

# Melon S3 FPGA Development Board Hardware User Manual

### Table of Contents
- Table of Contents
- Introduction
- Board Overview
- Key Components
- System Block Diagram
- Getting Started
   - Prerequisites
   - Starting the board for the first time
- Component Details
   - FPGA
   - ESP8266 WiFi SoC (Micro-controller)
   - Jumper Setting
   - USB Ports
   - DIP Switches
   - LED Indicators
   - Additional Functionality
- Expansion Connectors
   - Port#1 Expansion Connector
   - Port#2 Speed Expansion Connector
- Power Supply Management Overview
   - Block Diagram
   - Voltage Rails
- Mechanical Specification

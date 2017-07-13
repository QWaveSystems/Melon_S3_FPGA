# A WiFi FPGA Development Kit (OSHW).

![](http://ftp.qwavesys.com/tmp_pics/ms30.jpg)

In order to support our work please consider supporting it with a donation or purchase the dev kit board.

https://www.paypal.me/qwavesystems

**How to get the a developement board**

https://qwavesys.bentoweb.com/en/product/346754/MelonS3?category_id=84967

**Community Support Forums**

https://www.facebook.com/groups/244230302736445/

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
 
- Introduction
   - Specification
- System Block Diagram
- Board Overview
- TX/RX Jumper Setting
- Pin Definition
- Getting Started
   - Prerequisites
   - Starting the board for the first time
- WiFi Uploader (Upload .bit file over the WiFi)
- Programming ESP8266 Firmware
- FPGA Development using Xilinx ISE Webpack
- FPGA Development using LabVIEW FPGA
- FPGA Development using LabVIEW FPGA and LINX 3.0 (Raspberry Pi)
- Mechanical Specification

***

## Introduction

 The Melon S3 FPGA is open-source, expandable development board perfect for the learning digital circuit design and prototyping of your unique ideas. You can customize the capabilities of the FPGA with snap-on 40-pin "Raspberry Pi HAT". There are serveral shilds in the market offers a low cost module that can be purchased off the shelf. These shiled modules can be plugged directly to the Melon S3 FPGA board for the creation of powerful embedded and digital system applications.

- **Specification**

   - OTA (Over-The-Air) Download.bit file to FPGA over the WiFi
   - Xilinx Spartan 3E FPGA (PQG208) - 500K gates,
(73Kb Distributed RAM, 4 Digital Clock Manager (DCM), 20 Multipliers (18x18), 360 Kb Block RAM)
   - Onboard USB-UART (Silicon Labs) CP2104 for Configuration, Debugging and Power.
   - WiFi 2.4GHz SoC-WROOM-02, 32-bit MCU (Arduino Compatible) Clock 80MHz, 50KB RAM, Integrated TCP/IP protocol stack.
   - Flash 4MB SPI Flash which is 1MB for MCU Firmware and 3MB for FPGA Bit space.
   - 8 Users LEDs, 4 DIP Switch user button, 1 Reset button
   - Onboard FPGA cloxk 50MHz
   - GPIOs 56 PINs 3.3V Tolerant - 40 PINs x2 (Raspberry Pi 40 PINs Compatible)
   - JTAG Port (*Optional for Program/Debugging)

[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)

## System Block Diagram

<img src="http://ftp.qwavesys.com/MelonS3/009.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/009.png" width="650"/>

[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)
 
## Board Overview
 
 Front Side
 
<img src="http://ftp.qwavesys.com/MelonS3/melon_front_ID.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/melon_front_ID.png" width="500"/>
 
| Position |    Reference    | Description                                               |
|:--------:|:---------------:|:----------------------------------------------------------|
|    1     |     JTAG Port   | Optional for Programing&Debuging using Xilinx ISE Software|                          |
|    2     |      FPGA      |   Xilinx Spartan 3E 500K                                                |
|    3     |      LEDs      |   x8 LED (Green)         |
|    4     |      DIP SW      |   x4 DIP Switches                                           |
|    5     |      U1001      |   Analog Expansion Connector                              |
|    6     |      U5003      |   WLAN/Bluetooth/GPS                                      |
|    7     |      J901       |   Power Outlet                                            |
|    8     |     CON4101     |   Micro SD Card Socket                                    |
|    9     |     CON6501     |   HDMI Type A Port                                        |
|    10    |     CON7101     |   High Speed Connector                                    |
|    11    |     CON6403     |   Micro USB Type B Connecto                               |
|    12    | LED3201-LED3204 |   Can be defined by user                                  |
|          |     LED3205     |   LED3205 is WLAN LED                                     |
|          |     LED3206     |   LED3206 is Bluetooth LED                                |
|    13    |     CON6402     |   USB Host2 Connector                                     |
|    14    |     CON6401     |   USB Host1 Connector                                     |
|    15    |      SW3201     |   Power Button                                            |
|          |      SW3202     |   Vol up Button                                           |
|          |      SW3203     |   Vol down Button                                         |
|          |      SW3204     |   Reset Button                                            |
|    16    |     ANT5001     |   Bluetooth/WLAN Antenna                                  |
|    17    |     CON5006     |   GPS Antenna connector                                   |
|    18    |     SW3205      |   Switch for Auto boot and USB HOST set                   |

Bottom Side

<img src="http://ftp.qwavesys.com/MelonS3/melon-back_ID.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/melon-back_ID.png" width="500"/>

| Position |    Reference    | Description                                               |
|:--------:|:---------------:|:----------------------------------------------------------|
|    1     |     CON7001     |   Low Speed Expansion Connector                           |
|    2     |      U4001      |   8GB EMMC                                                |
|    3     |      U1001      |   MediaTek X20 MT6797 Soc + 2GB LPDDR3              |

[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)

## Pin Definition

<img src="http://ftp.qwavesys.com/MelonS3/melon_pinout.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/melon_pinout.png" width="300"/>

FPGA Pin Number for Port 1 & Port 2

| Position |    Port 1       | Port 2          |
|:--------:|:---------------:|:---------------:|
|    1     |                 |                 |
|    2     |                 |                 |
|    3     |                 |                 |
|    4     |                 |                 |
|    5     |                 |                 |
|    6     |                 |                 |
|    7     |                 |                 |
|    8     |                 |                 |
|    9     |                 |                 |
|    10    |                 |                 |
|    11    |                 |                 |
|    12    |                 |                 |
|    13    |                 |                 |
|    14    |                 |                 |
|    15    |                 |                 |
|    16    |                 |                 |
|    17    |                 |                 |
|    18    |                 |                 |
|    19    |                 |                 |
|    20    |                 |                 |
|    21    |                 |                 |
|    22    |                 |                 |
|    23    |                 |                 |
|    24    |                 |                 |
|    25    |                 |                 |
|    26    |                 |                 |
|    27    |                 |                 |
|    28    |                 |                 |
|    30    |                 |                 |
|    31    |                 |                 |
|    32    |                 |                 |
|    33    |                 |                 |
|    34    |                 |                 |
|    35    |                 |                 |
|    36    |                 |                 |
|    37    |                 |                 |
|    38    |                 |                 |
|    39    |                 |                 |
|    40    |                 |                 |
   
## Getting Started
 
   - Prerequisites
   - Starting the board for the first time

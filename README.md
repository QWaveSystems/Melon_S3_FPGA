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

 The **Melon S3 FPGA is open-source**, expandable development board perfect for the learning digital circuit design and prototyping of your unique ideas. You can customize the capabilities of the FPGA with snap-on 40-pin "Raspberry Pi HAT". There are serveral shilds in the market offers a low cost module that can be purchased off the shelf. These shiled modules can be plugged directly to the Melon S3 FPGA board for the creation of powerful embedded and digital system applications.

- **Specification**

   - OTA (Over-The-Air) Download.bit file to FPGA over the WiFi
   - **Xilinx Spartan 3E FPGA (PQG208) - 500K gates**,
(73Kb Distributed RAM, 4 Digital Clock Manager (DCM), 20 Multipliers (18x18), 360 Kb Block RAM)
   - Onboard USB-UART (Silicon Labs) CP2104 for Configuration, Debugging and Power.
   - **MCU WROOM-02 (ESP8266), WiFi 2.4GHz + 32-bit MCU (Arduino Compatible)** Clock 80MHz, 50KB RAM, Integrated TCP/IP protocol stack.
   - Flash 4MB SPI Flash which is 1MB for MCU Firmware and 3MB for FPGA Bit space.
   - 8 Users LEDs, 4 DIP Switch user button, 1 Reset button
   - Onboard FPGA clock 50MHz
   - GPIOs 56 PINs **3.3V Tolerant** - 40 PINs x2 (Raspberry Pi 40 PINs Compatible)
   - JTAG Port (*Optional for Program/Debugging)

[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)

## System Block Diagram

<img src="http://ftp.qwavesys.com/MelonS3/009.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/009.png" width="650"/>

[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)
 
## Board Overview
 
 **Front Side**
 
<img src="http://ftp.qwavesys.com/MelonS3/melon_front_ID.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/melon_front_ID.png" width="500"/>
 
| Position |    Reference    | Description                                               |
|:--------:|:---------------:|:----------------------------------------------------------|
|    1     |     JTAG Port   |   Optional for Programing & Debuging using Xilinx ISE Software|
|    2     |      FPGA       |   Xilinx FPGA Spartan 3E 500K|
|    3     |      LEDs       |   x8 LED (Green)|
|    4     |      DIP SWs    |   x4 DIP Switches|
|    5     |      Pwr LED    |   3.3V Power LED (Red)|
|    6     |     XSTOP Jumper|   FPGA code will STOP if Jumper added (Size 2.5"), Using this jumper as a FPGA stop pin (No jumper by default)|
|    7     |   Status LED    |   User define LED (Green) at GPIO15 of ESP8266|
|    8     |     MCU         |   WiFi SoC (ESP8266) Flash 4MB Version|
|    9     |     Oscilator   |   ABRACON 50 MHz onboard oscilator (50ppm)|
|    10    |     LED1        |   User define LED (Green) at GPIO2 of ESP8266, This LED will be flashing during upload firmware to ESP8266|
|    11    |     Reset Btn   |   Reset Button for ESP8266|
|    12    | TX/RX Jumper    |   TX/RX Jumper of ESP8266 and USB CP2104 (Size 2.0"), Refer Jumper setting section|
|    13    |     USB IC      |   CP2104 UART to USB IC|
|    14    |     USB LED     |   USB Plug-in LED Status (VUSB)|
|    15    |     Done LED    |   FPGA Status LED if .bit file downloaded to FPGA without error|
|    16    |     VIN 5V      |   External Power supply +5V can powered the board from this pin|
|    17    |     TX/RX LEDs  |   TX/RX LED Status of USB IC (CP2104)|
|    18    |     USB Connector|   USB Connector for +5V input for powered the board or Debug/Programming port for ESP8266|

[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)

**Bottom Side** (Solder pad jumper for the users are willing to use with **Raspberry Pi Shileds**)

<img src="http://ftp.qwavesys.com/MelonS3/melon-back_ID.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/melon-back_ID.png" width="500"/>

| Position |    Reference    | Description                                               |
|:--------:|:---------------:|:----------------------------------------------------------|
|    1     |     (JP2) RPi 3.3 V Jumper|   Solder pad Jumper is "Open" by Default, But once the Melon FPGA and Raspberry Pi **Shields** stacked together **at P1 Port**, You can powered RPi **Shileds** board at 3.3V P1:1,P1:17 (3V3_RP) by using the power VUSB (5V) or VIN (5V) from Melon FPGA board, by setting the Jumper "Closed (Soldered)", Refer schematic for more information|
|    2     | HSWAP Jumper    |   Set the default state of FPGA Pins, Solder pad jumper is "Open"= Pull-down (by Default), Set the jumper pad to "Closed, (Soldered)"= All the FPGA pins are Pull-Up.|
|    3     |      (JP1) Rpi 5V Jumper  |  Solder pad Jumper is "Open" by Default, But once the Melon FPGA and Raspberry Pi **Shields** are stacked together **at P1 Port**, if you want to powered RPi **Shields**  P1:2,P2:4 (5V_RP) by using the power VUSB (5V) or VIN (5V) from Melon FPGA board, by setting the Jumper "Closed (Soldered)", Refer schematic for more information|

[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)

## TX/RX Jumper Setting

"ESP-PROGRAM" TX/RX Jumper is set to "Open" by Default, In order to re-program ESP8266 firmware, The both jumpers (TX/RX) need to be inserted (Closed).

USB TX/RX and ESP TX/RX pins also routed to FPGA refer the diagram below, You can writed the FPGA code to set jumper internally. In this case you can re-program the ESP8266 firmware without any jumpers.

<img src="http://ftp.qwavesys.com/MelonS3/melon_txrx_set_01.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/melon_txrx_set_01.png" width="500"/>

[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)

## Pin Definition

<img src="http://ftp.qwavesys.com/MelonS3/melon_pinout02.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/melon_pinout02.png" width="500"/>

**Port1**

FPGA Pin Number (Pxx) vs Connector Pins **(RPi shileds can be connected to this port)**

| Description |   Pin Number       | Pin Number          | Description          |
|:--------:|:---------------:|:---------------:|:---------------:|
|    **+3V3_RP** Using with RPi shields need to set solder pad jumper at bottom side    |**1**                 |**2**                 |**+5V_RP** Using with RPi shields need to set solder pad jumper at bottom side|
|    P50     |3                 |**4**                 |**+5V_RP** Using with RPi shields need to set solder pad jumper at bottom side|
|    P49     |5                 |**6**                 |**Ground**|
|    P48     |7                 |8                 |P47|
|    **Ground**     |**9**                |10                 |P42|
|    P41     |11                 |12                 |P40|
|    P39     |13                 |**14**                 |**Ground**|
|    P36     |15                 |16                 |P35|
|    **+3V3_RP** Using with RPi shields need to set solder pad jumper at bottom side     |**17**                 |18                 |P34|
|    P35    |19                 |**20**                 |**Ground**|
|    P31    |21                 |22                 |P30|
|    P29    |23                 |24                 |P28|
|    **Ground**    |**25**                 |26                 |P25|
|    P24    |27                 |28                 |P23|
|    P22    |29                 |**30**                 |**Ground**|
|    P19    |31                 |32                 |P18|
|    P16    |33                 |**34**                 |**Ground**|
|    P15    |35                 |36                 |P12|
|    P11    |37                 |38                 |P9|
|    **Ground**    |**39**                 |40                 |P8|
   
 **Port 1** : The FPGA pin constraints (.ucf) for Xilinx ISE and FPGA IO for LabVIEW aslo provide. 
   
 <img src="http://ftp.qwavesys.com/MelonS3/ucf_p1_02.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/ucf_p1_02.png" width="350"/> <img src="http://ftp.qwavesys.com/MelonS3/ucf_p1_lv.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/ucf_p1_lv.png" width="250"/>   
  
[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)
  
**Port2**

FPGA Pin Number (Pxx) vs Connector Pins

| Description |   Pin Number       | Pin Number          | Description          |
|:--------:|:---------------:|:---------------:|:---------------:|
|    **+3V3**     |**1**                 |**2**                 |**+5V**|
|    P153     |3                 |**4**                 |**+5V**|
|    P152    |5                 |**6**                 |**Ground**|
|    P150     |7                 |8                 |P151|
|    **Ground**     |**9**                |10                 |P147|
|    P146     |11                 |12                 |P145|
|    P144     |13                 |**14**                 |**Ground**|
|    P139     |15                 |16                 |P140|
|    **+3V3**     |**17**                 |18                 |P138|
|    P137   |19                 |**20**                 |**Ground**|
|    P133    |21                 |22                 |P132|
|    P129    |23                 |24                 |P128|
|    **Ground**    |**25**                 |26                 |P127|
|    P126    |27                 |28                 |P123|
|    P122    |29                 |**30**                 |**Ground**|
|    P120    |31                 |32                 |P119|
|    P116    |33                 |**34**                 |**Ground**|
|    P115    |35                 |36                 |P113|
|    P112    |37                 |38                 |P109|
|    **Ground**    |**39**                 |40                 |P108|
   
 **Port 2** : The FPGA pin constraints (.ucf) for Xilinx ISE and FPGA IO for LabVIEW aslo provide.  
   
 <img src="http://ftp.qwavesys.com/MelonS3/ucf_p2.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/ucf_p2.png" width="350"/> <img src="http://ftp.qwavesys.com/MelonS3/ucf_p2_lv.png" data-canonical-src="http://ftp.qwavesys.com/MelonS3/ucf_p2_lv.png" width="250"/>  
 
[Back to top](#melon-s3-fpga-development-board-hardware-user-manual)
 
## Getting Started

- **Starting the board for the first time**

<img src="http://ftp.qwavesys.com/tmp_pics/ms30.jpg" data-canonical-src="http://ftp.qwavesys.com/tmp_pics/ms30.jpg" width="500"/>  

   - Plug-in the USB connector to the computer USB port to powered the board. 
   - Open the Serial Monitor sofware > Select COM port > Pressed the RESET button on the board. This is wha you will get from serial monitor.
   
   
   
   - The WiFi Access Point name like "Melon-xxxxx" will be appear on the network.
   - Connecto the WiFi AP using the default password "88888888"
   - etet
   - trttet
   - etet
   - trttet

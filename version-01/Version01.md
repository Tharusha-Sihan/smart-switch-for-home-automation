# version- 01
<p  float="left">
  <img width="49%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/b0ba6e9c-c5e3-4bdd-a0c7-22152d74e149" />
  <img width="49%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/dcd53d40-d495-44ed-983f-34bfb55d5d9a" />
  </p>

## Block Diagram
<p  align="center">
<img src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/a2c598d2-b17d-406b-b23f-8807925369f4" width="65%" />
</p>

## component selection
After comparing several alternatives, the following components were selected. Their performance, price, availability and reliability were mainly concerned.
+ **ESP32 WROOM 32D :** The ESP32 microcontroller is chosen for its processing capabilities and built-in WIFI connectivity. It offers sufficient computing power to manage the device and efficiently transmit data to the servers. Moreover, the ESP32’s ability to connect with nearby WIFI access points allows for seamless web integration. [Datasheet](https://www.mouser.com/datasheet/2/891/esp-wroom-32_datasheet_en-1223836.pdf)
+ **HLK-PM-03 :** To convert 230V AC supply into 3.3V DC HLK-PM-03 module is chosen due to its compact size, versatility, high reliability, energy efficiency, and ease of integration. This module boasts a remarkably small form factor, making it an ideal choice for space-constrained applications. It is designed for high energy efficiency which aligns perfectly with our goals.[Datasheet](https://datasheet.lcsc.com/szlcsc/1909111105_HI-LINK-HLK-PM24_C399250.pdf)
+ **Mechanical relays :** Despite the relatively low reliability compared to the solid-state relays mechanical relays were chosen due to their low cost.
+ **BS170 :** n-channel MOSFET is chosen for switching relays. It has a high current capacity.[Datasheet](https://www.onsemi.com/pdf/datasheet/mmbf170-d.pdf)
+ **Pull-up Resistors and Capacitors :** The selected pull-up resistors and capacitors are determined based on the ESP32 chip’s data sheet to ensure proper communication and programming.

### BoM
  
| Component | Quantity |
| --------- | ---------|
| ESP32 WROOM 32d | 1 |
|HLK-PM-03 | 1 |
|SRD 3V relay | 3 |
|Varistors 180pF 560volts 10% | 1 |
|Safety Capacitors 275VAC 0.1uF |	1 |
|BS170 n-channel MOSFET	|3|
|push buttonn |	2|
|10kOhm resistors 0805 pkg|	5|
|10uF - tantalum - 3216 mm	|1|
|0.1uF - 0805 pkg	|1|
|220uF - electrolyte|	1|
|100uF (extra) electrolyte|	1|
|1kOhm resistors 0805 pkg	|3|
|3ways terminal blocks 5.08 pitch|	1|
|2 ways terminal block 5.08 pitch|	1|
|3 pin JST connectors|	1|
|4 pin male headers|	1|

## Schematic Design
<p align="center">
<img width="65%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/4c738e9e-342e-4ff3-8e73-abccbfc08be7" />
<img width="65%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/17e704f1-f19b-4a37-86a8-8e3c86f14e0e" />
</p>

## PCB Layout
<p align="center">
<img width ="55%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/572475b5-7ae7-4a01-a0a0-3d669f5fab98"/>
</p>

### Top Layer
<p align="center">
<img width ="55%" src=https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/feddea3c-755d-482b-a493-c083f2a8d2b6"/>
</p>

### Bottom Layer
<p align="center">
<img width="55%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/65f3a132-dff9-43c8-9fa7-5ef9db750afb"/>
</p>

## Enclosure
Initial enclosure design is as follows. 
<p align="center">
<img width="55%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/f33489e4-6ab1-4dd7-a6f6-934a0c7508de" />
</p>

After considering expandability, manufacturability and esthetics aspects initial designs were revised.

<p float="left">
<img width="49%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/7e89755e-0894-40ff-9d6a-7ab46c0910d5"/>
<img width="49%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/19da530a-89c8-4163-9b22-7e2c8ba8d9e3"/>
</p>

## Interface
The user interface is designed with a seamless blend of touch buttons for manual control and a user-friendly web page for remote access and network configuration. 
<p align="center">
<img width="35%" src="https://github.com/Tharusha-Sihan/smart-switch-for-home-automation/assets/116502446/bd5a3aa1-85b7-4484-945f-14315d0df0c9" />
</p>


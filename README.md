# Boardoza TMAG5170 3D Hall-Effect Sensor Breakout Board

The **Boardoza TMAG5170** is a high-precision **3D linear hall-effect sensor breakout board** based on the **Texas Instruments TMAG5170**. This device integrates **three independent Hall sensors (X, Y, and Z axes)** along with a precision signal chain and a 12-bit ADC, enabling accurate magnetic field measurement in compact and high-performance systems.

With support for high-speed **SPI communication (up to 10 MHz)** and sampling rates up to **20 ksps**, the TMAG5170 is ideal for real-time direction sensing applications. Integrated diagnostics, angle calculation (CORDIC engine), and an on-chip temperature sensor provide enhanced reliability and system-level drift compensation. This breakout board is perfect for **industrial automation, robotics, motor control, contactless direction sensing, and smart mechatronic systems.**

## [Click here to purchase!](https://www.ozdisan.com/ureticiler/boardoza)

| Front Side | Back Side |
|:---:|:---:|
| ![TMAG5170 Front](./assets/TMAG5170%20Front.png) | ![TMAG5170 Back](./assets/TMAG5170%20Back.png) |

---

## Key Features

- **High-Precision 3D Magnetic Sensing:** Measures magnetic field on independent X, Y, and Z axes for accurate direction detection.
- **High-Speed SPI Interface:** Supports up to 10 MHz SPI with integrated CRC for secure communication.
- **Integrated Temperature Sensor:** < ±2°C error for system-level thermal compensation.
- **Ultra-Low Power Operation:** 5 nA deep sleep mode and 1.5 µA autonomous wake-up mode.
- **Smart ALERT Pin:** Can trigger conversions or indicate conversion completion.
- **Built-in Diagnostics:** Integrated fault detection and system monitoring features.
- **On-Chip CORDIC Engine:** Provides direct angle calculation with gain and offset correction.

---

## Technical Specifications

**Model:** TMAG5170A1  
**Manufacturer:** Boardoza   
**Manufacturer IC:** Texas Instruments  
**Functions:** 3D Hall-Effect Sensor   
**Input Voltage:** 2.3V – 5.5V DC  
**Interface:** SPI (up to 10 MHz, CRC supported)  
**Magnetic Field Ranges:** ±25 mT / ±50 mT / ±100 mT (selectable)  
**ADC Resolution:** 12-bit  
**Maximum Sampling Rate:** 20 ksps (single axis)  
**Linear Measurement Error:** ±2.6% (max at 25°C)  
**Sensitivity Temperature Drift:** ±2.8% (max)  
**Temperature Sensor Accuracy:** ±2°C (typical)  
**Deep Sleep Current:** 5 nA (typical)  
**Sleep Mode Current:** 1.5 µA (typical)  
**Active Mode Current:** 3.4 mA (typical)  
**Operating Temperature Range:** –40°C to +150°C  
**Board Dimensions:** 20 mm x 20 mm  
 

---

## Board Pinout

### ( J1 ) SPI Connector

| Pin Number | Pin Name | Description |
|:----------:|:--------:|-------------|
| 1 | nCS | Chip Select (Active Low) |
| 2 | MISO | SPI Data Output |
| 3 | MOSI | SPI Data Input |
| 4 | SCLK | SPI Clock |
| 5 | nALERT | Conversion Status / Trigger Output (Active Low) |

### ( J2 ) Power Connector

| Pin Number | Pin Name | Description |
|:----------:|:--------:|-------------|
| 1 | VCC | 2.3V – 5.5V Power Supply Input |
| 2 | GND | Ground Reference |

---

## Board Dimensions

<img src="./assets/TMAG5170 Dimensions.png" alt="TMAG5170 Dimension" width="450"/>

---

## Step Files

[Boardoza TMAG5170.step](./assets/TMAG5170%20Step.step)

---

## Datasheet

[TMAG5170 Datasheet.pdf](./assets/TMAG5170%20Datasheet.pdf)

---

## Version History

- V1.0.0 - Initial Release

---

## Support

- If you have any questions or need support, please contact **support@boardoza.com**

---

## **License**

This repository contains both hardware and software components:

### **Hardware Design**

[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

All hardware design files are licensed under [Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

### **Software/Firmware**

[![BSD-3-Clause][bsd-shield]][bsd]

All software and firmware are licensed under [BSD 3-Clause License][bsd].

[bsd]: https://opensource.org/licenses/BSD-3-Clause
[bsd-shield]: https://img.shields.io/badge/License-BSD%203--Clause-blue.svg


# EV BATTERY MANAGEMENT SYSTEM
## Internship Project Report

**Project Title:** Modular EV Battery Management System Using Embedded C

**Development Environment:** GitHub Codespaces

**Programming Language:** Embedded C (C11)

**Compiler:** GCC

**Target Architecture:** STM32-oriented embedded software

---

## 1. Abstract

The Electric Vehicle Battery Management System (BMS) is designed to monitor battery-cell voltage and identify voltage imbalance in a battery pack.

This project implements a modular software-based BMS using Embedded C. It analyzes simulated battery-cell voltage readings, identifies the weakest and strongest cells, calculates voltage imbalance, and generates an imbalance warning.

The system also implements adaptive threshold calculation based on State of Charge (SoC) and discharge rate, along with voltage imbalance trend analysis.

The battery simulation supports configurations of up to 16 cells.

## 2. Introduction

Battery Management Systems are important components of electric vehicles. They help monitor battery conditions and identify abnormal operating conditions.

Unequal cell voltages can affect battery-pack performance. Therefore, monitoring individual cell voltages and identifying voltage differences is an important BMS function.

This project demonstrates these functions through a software simulation.

## 3. Project Objectives

- Develop a modular BMS using Embedded C.
- Monitor multiple battery-cell voltages.
- Identify the weakest and strongest cells.
- Calculate voltage imbalance in millivolts.
- Implement an adaptive imbalance threshold.
- Track increasing, decreasing, and stable imbalance trends.
- Generate battery imbalance warnings.
- Support a configurable cell count up to 16.

## 4. Hardware and Software Requirements

### Hardware
- No physical hardware is used in the current implementation.
- STM32 is the intended embedded target architecture.

### Software
- GitHub Codespaces
- Visual Studio Code environment
- GCC compiler
- C11 programming standard
- Embedded C

## 5. System Implementation

### 5.1 BMS Core

The BMS Core analyzes the voltage readings received from the battery simulation model.

It identifies:
- Weakest battery cell
- Strongest battery cell
- Voltage imbalance

### 5.2 Voltage Imbalance Calculation

The voltage imbalance is calculated using:

Voltage Imbalance (mV) =
(Strongest Cell Voltage - Weakest Cell Voltage) x 1000

### 5.3 Adaptive Threshold

The threshold is calculated using SoC and discharge rate.

The implemented formula is:

Threshold =
30 + 0.20 x (100 - SoC) + 5 x Discharge Rate

The threshold is limited to a minimum of 20 mV and a maximum of 100 mV.

### 5.4 Trend Analysis

The system compares the current voltage imbalance with the previous imbalance.

It identifies three conditions:
- Increasing
- Decreasing
- Stable

### 5.5 Battery Status

The BMS generates two status conditions:
- NORMAL
- IMBALANCE WARNING

A warning is generated when the calculated imbalance exceeds the adaptive threshold.

## 6. Simulation and Testing

The project uses simulated battery voltage profiles.

The battery model supports up to 16 cells per profile.

The software is compiled using GCC with the C11 standard.

Compilation command:

gcc -std=c11 -Wall -Wextra -I Core Core/bms_core.c Simulation/battery_model.c Simulation/test_bms.c -o bms_test

Execution command:

./bms_test

## 7. Observed Simulation Result

One observed 16-cell profile produced the following results:

| Parameter | Result |
|---|---:|
| Number of cells | 16 |
| Weakest cell | Cell 3 |
| Weakest voltage | 3.650 V |
| Strongest cell | Cell 4 |
| Strongest voltage | 3.880 V |
| Voltage imbalance | 230 mV |
| Adaptive threshold | 39.50 mV |
| SoC | 65% |
| Discharge rate | 0.50 C |
| Trend | Increasing |
| Status | IMBALANCE WARNING |

The measured imbalance is greater than the adaptive threshold, so the BMS generates an imbalance warning.

## 8. Project Advantages

- Modular software architecture
- Configurable battery-cell count
- Easy-to-understand C implementation
- Automatic weakest and strongest cell identification
- Adaptive threshold calculation
- Voltage imbalance trend monitoring
- Software testing without physical battery hardware

## 9. Limitations

- Battery voltage readings are simulated.
- No physical STM32 board has been tested.
- No real battery sensors are connected.
- CAN communication is not yet implemented.
- Cell balancing hardware is not implemented.
- The software is an educational prototype and is not suitable for vehicle safety control.

## 10. Future Scope

- Integrate with an STM32 microcontroller.
- Add real battery voltage and temperature sensors.
- Implement CAN communication.
- Add State of Charge estimation algorithms.
- Implement cell balancing control.
- Develop a graphical battery monitoring interface.
- Perform hardware-in-the-loop testing.

## 11. Conclusion

The project demonstrates a modular software-based EV Battery Management System using Embedded C.

The system successfully compiles and runs in GitHub Codespaces. It analyzes simulated battery-cell voltages, identifies the weakest and strongest cells, calculates voltage imbalance, implements an adaptive threshold, and detects imbalance trends.

The battery simulation has been extended to support up to 16 cells.

This project provides a foundation for future STM32-based battery management system development.

---

## 12. Project Repository

GitHub Repository:

Add your GitHub repository URL here.

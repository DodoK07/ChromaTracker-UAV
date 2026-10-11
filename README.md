# ChromaTracker-UAV 🚁🎯

`ChromaTracker-UAV` is a **2-Axis Pan-Tilt Gimbal Control System** designed for Unmanned Aerial Vehicles (UAVs) to perform real-time visual target tracking.

This project integrates a Python/OpenCV computer vision module with C++ firmware running on a microcontroller, communicating seamlessly via UART (Serial Port).

---

## 🏗️ System Architecture

The project consists of two primary layers:

1. **Firmware (C++):** `src/firmware/`
   * Drives Pan and Tilt stepper motors using a non-blocking timing mechanism.
   * Parses incoming angle commands over the serial port and updates motor positions dynamically.
2. **Computer Vision & Tracking (Python):** `src/tracking/` *(In Development)*
   * Detects and tracks targets from a live camera feed.
   * Calculates the target's angular offset from the center and transmits coordinate commands to the firmware via UART.

---

## 📁 Repository Structure

```text
ChromaTracker-UAV/
├── CAD/                    # 3D Pan-Tilt mechanism models and assembly files
└── SRC/
    └── firmware/           # C++ Firmware Source Files
        ├── StepperMotor.hpp / .cpp  # Motor motion and position control
        ├── CommandParser.hpp / .cpp # Serial UART command parser
        └── main.cpp                 # Non-blocking main control loop

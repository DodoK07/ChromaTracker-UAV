# 🛸 UAV Color Target Detector & Deadzone Tracker

An OpenCV and Python-based computer vision module designed for autonomous UAV target tracking, center coordinate calculation, and direction command generation with dynamic deadzone control.

## 📌 Features
- **Color Segmentation:** HSV-based real-time object extraction.
- **Centroid Calculation:** Instant pixel coordinate tracking `(cx, cy)` of the target.
- **Dynamic Deadzone Filter:** Prevents UAV oscillation by filtering out small center deviations.
- **Modular OOP Structure:** Packaged as a class (`TargetDetector`) for seamless integration with flight controllers (ArduPilot / Pixhawk).

## 🛠️ Requirements & Installation
```bash
pip install opencv-python numpy

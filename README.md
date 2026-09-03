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
## 📐 Mechanical Design & Assembly

The 2-axis Pan-Tilt mechanism was custom-designed in **Autodesk Fusion 360** using reverse-engineering techniques, specifically optimized for UAV/drone payload integration.

<p align="center">
  <img src="assets/gimbal_render1.png" width="80%" title="Pan-Tilt Gimbal Assembly Render" />
</p>

```markdown
### 🛠️ Mechanical & CAD Specifications
- **Format Compatibility:** Source CAD models are provided in both `.STEP` (for universal CAD editing) and `.STL` formats (ready for 3D printing/slicing).
- **Manufacturing:** Optimized for FDM 3D printing with standard PLA/PETG materials.


### Key Mechanical Highlights:
* **Compact & Low-CG Structure:** Designed with an offset horizontal bracket layout to bring the camera's center of mass closer to the rotation axes, minimizing servo torque requirement and dynamic stress.
* **Vibration Reduction:** Rigorous closed-loop bracket geometry reduces high-frequency UAV frame vibrations, ensuring stable image capture for OpenCV processing.
* **Actuator Compatibility:** Custom-fitted for micro servos (e.g., EMAX ES08 / SG90) with tight-tolerance mounting points and smooth articulation limits.

# Hybrid Powertrain Controller (HCU) - 2025 Monza Stress Test

## The objective
A Model-Based Design (MBD) project engineering a complete Hybrid Control Unit (HCU) from concept to C++ code generation, culminating in a stress test against real-world F1 telemetry.

## Project overview
The goal of this project was to move beyond open-loop simulation and build a supervisory control system that handles real-world constraints, energy management logic, and closed-loop validation.

The project evolved through two major iterations:
1. **V1: Production-Ready Baseline**: Validated against standard drive cycles (FTP-75) with C++ code generation.
2. **V2: The Monza Stress Test**: A high-fidelity performance test using 2025 F1 Monza pole telemetry to push the energy management logic to its failure points.

## V2: The Monza Stress Test (Latest Iteration)

**Objective**: Stress test the HCU supervisory logic against the extreme duty cycle of a competitive F1 qualifying lap.

**The Engineering Challenge**
Standard drive cycles like FTP-75 prioritise efficiency. F1 requires maximum deployment. To validate the logic under extreme conditions, I integrated:

- **2025 FIA Power Unit Regulations**: 120kW MGU-K power limit and 4MJ/lap deployment limits.
- **Spatial Reference Environment**: Engineered a closed-loop "Virtual Driver" that tracks track position (via `cumtrapz` telemetry mapping) rather than time, preventing controller drift.
- **Signal Conditioning**: Applied Gaussian smoothing to telemetry inputs to stabilise the PID derivative response.

**Key Results**
- **Logic vs. Safety**: The HCU successfully triggered a hysteresis-guarded transition from "Boost" to "Normal" mode when SoC hit the 20% safety floor (t=5s).
- **Performance Deficit**: The safety intervention caused a 9.52 s lap time deficit, proving that a reactive "Maximum Deployment" strategy is insufficient for competitive racing compared to predictive optimisation.
- **Fidelity Analysis**: The 1-DOF longitudinal plant highlighted the need for dynamic aero and load-sensitive tyre friction modelling to match top-end speed and braking performance.

_See `HCU_V2_Driver.slx` for the full model._

## V1: Architecture & C++ Generation

**Objective**: Design a robust, code-generatable controller for standard driving scenarios.

**System Architecture**:
- **Controller**: Stateflow-based supervisory logic managing torque split, Eco/Boost modes, and safety limits.
- **Plant**: Longitudinal vehicle dynamics model (798 kg) including aerodynamic drag and battery SoC estimation.
- **Validation**: Closed-loop PID driver model tracking the FTP-75 Driving Cycle.

**Control Strategy**:
- **Powertrain**: Hybrid system with 3000N E-Boost and -4000N regenerative braking capability.
- **Energy Management** 
    - **Regen Priority**: Maximises braking energy recovery
    - **SoC Protection**: Hard limit on E-Boost at <20% SoC to prioritise pack longevity.
- **Solver**: Fixed-step 0.001s (Discrete/Continuous hybrid) ensuring compatibility with real-time targets.

## Code Generation
The controller is isolated as an Atomic Subsystem to generate production-ready C++ code using Embedded Coder. This verifies the logic is standalone and ready for ECU deployment.

## Repository Structure
- `HCU_Driver_V2`: The advanced F1 Monza simulation model.
- `verstappen_monza_2025.csv`: Telemetry data used for the spatial reference generation.
- `src/`: Generated C++ code from the V1 controller.
- `Import_F1_Data.m`: Used to import data from CSV to Workspace.
- `maxverstappen_datacollection_monzagp_2025_pole.py`: Get telemetry data from `fastf1` to CSV.

## Future work
- Implement Predictive Energy Management (EM) to reduce the 9.52s Monza deficit.
- Upgrade the plant model to 3-DOF (Longitudinal, Lateral, Yaw) to better capture cornering speeds.
- Integrate thermal constraints for the battery pack.



## F1 Hybrid Control Unit (HCU) – Model-Based Design & C++ Generation 🏎️

### Project Overview
This repository contains a supervisory Hybrid Control Unit (HCU) developed using a Model-Based Design (MBD) workflow. The controller manages the energy split of a Parallel P2 hybrid powertrain (ICE + MGU-K) under 2025 FIA Formula 1 Technical Regulations.

The system was validated through Software-in-the-Loop (SIL) simulation against real-world telemetry from the 2025 Monza Pole Lap.

### Key Technical Highlights:
- **Closed-Loop Virtual Driver:** Implemented an ADAS-style Lookahead Preview Controller to anticipate braking zones and track high-speed telemetry.
- **Dynamic Aerodynamics:** Integrated a custom Drag Reduction System (DRS) into the plant model to simulate low-drag high-speed straights.
- **Production Code Generation:** 100% automated generation of type-safe, Object-Oriented C++ classes using Simulink Embedded Coder (`ert.tlc`).
- **Safety & Compliance:** Hardcoded state-machine logic for FIA-mandated limits (`120kW` power ceiling, `4.0MJ` deployment, and `2.0MJ` regeneration).

### Software Architecture: The MBD Pivot
In early iterations, signal noise caused high-frequency "switch chatter" in the driveline. While manual C++ refactoring initially solved this, I ultimately moved the fix to the correct abstraction layer by implementing a 500N hysteresis band directly within the Stateflow logic.
This ensured that the generated C++ remained perfectly synchronized with the validated physics model, maintaining a single source of truth.

### Performance Validation (Monza Stress Test)
The HCU was subjected to a brutal qualifying duty cycle at Monza. The Software-in-the-Loop (SIL) results confirmed the robustness of the auto-generated code:
| Metric | Result | FIA Limit / Target |
| --- | --- | --- |
| Lap Time | 80.227s | 1:20.216 (Reference) |
| Pace Delta | +1.43s | |
| Max Deployment | 3.10 MJ | < 4.0 MJ |
| MGU-K Regen | 2.00 MJ | 2.0 MJ (Hard Limit) |
| Battery SoC | 90% → 53% | Safety Margin Maintained |

### Repository Structure:
- **/3_Final_Version_F1_Monza_Code:** Contains the production-ready auto-generated `.cpp` and `.h` classes.
- **HCU_V2_Driver.slx:** The main Simulink/Stateflow model including the vehicle plant and lookahead driver.
- **Import_F1_Data.m:** Data processing script for FastF1 telemetry integration.
- **From Simulation to C++.pdf:** Full engineering report detailing the design, math, and verification steps.

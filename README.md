# Hybrid Powertrain Controller (HCU) - 2025 Monza Stress Test

## The objective
Validating a deterministic Hybrid Control Unit (HCU) state machine under extreme energy deficits (`80C` discharge rate) using 2025 Monza Pole Reference telemetry (FastF1)

## The technical challenge

- **Power demand**: `120 kWh` (FIA MGU-K limit).
- **Architecture**: `1.5 kWh` mass-market pack.
- **The constraint**: A `120 kWh` draw on a `1.5 kWh` pack result in an `80C` discharge, hitting physical and thermal limits within one sector.

## Project architecture
- **Python**: Data acquisition via FastF1 and preprocessing for Simulink.
- **Simulink/Stateflow**: Deterministic HCU logic with **hysteresis-guarded derating** strategies.
- **Validation**: Comparing simulated vehicle velocity (yellow) agains Verstappen's pole lap (blue).

## Curent status
**Baseline (Main Branch)**: 1.5 kWh Deterministic DNF at 2537 m.

**Active Feature Branch**: Upscaling to 4.0 kWh for energy sensitvity analysis.

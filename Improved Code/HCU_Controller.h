/**
 * @file HCU_Controller.h
 * @author Edmond-Roland Volosciuc
 * @brief Supervisory Control Logic for Hybrid Powertrain Control Unit (HCU)
 * @details Implements state machine for Eco/Boost/Regen arbitration with 
 * hysteresis protection to prevent actuator chatter.
 */

#ifndef HCU_CONTROLLER_H
#define HCU_CONTROLLER_H

#include <cstdint>

enum class HCUState {
    Eco,    // Motor Force = 0N (ICE only)
    Boost,  // Motor Force = +3000N (Hybrid Assist)
    Regen   // Motor Force = -4000N (Regenerative Braking)
};

class HybridControlUnit {
public:
    HybridControlUnit(); // constructor

    /**
     * @brief Main control step function
     * @param engineForce Current ICE load request (N)
     * @param brake Brake pedal input (0-100%)
     * @param soc Battery State of Charge (0-100%)
     * @return Commanded electric motor force (N)
     */
    double update(double engineForce, double brake, double soc);

    // getter for telemetry/debugging
    HCUState getCurrentState() const;

private:
    HCUState currentState;

    // --- Tuning Parameters ---

    // Actuator Limits
    const double FORCE_BOOST = 3000.0;
    const double FORCE_REGEN = -4000.0;
    const double FORCE_IDLE = 0.0;

    // Logic thresholds
    const double SOC_MIN_LIMIT = 20.0;    // Battery protection (%)

    // Hysteresis: "Boost" Mode Triggers
    // Entering boost at 5500N, but hold it untill 5000n to prevent chatter.
    const double THRESHOLD_BOOST_ENTRY = 5500.0;
    const double THRESHOLD_BOOST_EXIT = 5000.0;
};

#endif // HCU_CONTROLLER_H
/**
 * @file HCU_Controller.cpp
 * @author Edmond-Roland Volosciuc (you@domain.com)
 * @brief Implementation of the Hybrid Control Unit (HCU) state machine
 */

#include "HCU_Controller.h"

//Initialise the system in Eco mode
HybridControlUnit::HybridControlUnit() : currentState(HCUState::Eco) {}

double HybridControlUnit::update(double engineForce, double brake, double soc) {
    // Braking always takes priority over drive torque
    if (brake > 0.0) {
        currentState = HCUState::Regen;
        return FORCE_REGEN;
    }

    // State machine with Hysteresis
    switch (currentState) {
        
        case HCUState::Regen:
            // Exit regen only when braking is fully released
            if (brake == 0.0) {
                currentState = HCUState::Eco;
            }   
        break;
        
        case HCUState::Eco:
            // Enter boost only if:
            // 1) Engine load is high enough (> 5500N)
            // 2) Battery SOC is above minimum limit (> 20%)
            if (engineForce > THRESHOLD_BOOST_ENTRY && soc > SOC_MIN_LIMIT) {
                currentState = HCUState::Boost;
            }
        break;

        case HCUState::Boost:
            // Logic to exit boost mode
            // To prevent chatter, only exit boost when engine load drops
            // below 5000N
            if (engineForce < THRESHOLD_BOOST_EXIT || soc < SOC_MIN_LIMIT) {
                currentState = HCUState::Eco;
            }
        break;
    }

    // Output mapping
    switch (currentState) {
        case HCUState::Eco:
            return FORCE_IDLE;
        case HCUState::Boost:
            return FORCE_BOOST;
        case HCUState::Regen:
            return FORCE_REGEN;
        default:
            return FORCE_IDLE; // Safety fallback
    }
}

HCUState HybridControlUnit::getCurrentState() const {
    return currentState;
}
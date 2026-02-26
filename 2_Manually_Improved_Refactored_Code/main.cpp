/**
 * @file main.cpp
 * @brief Validation Harness for HCU Logic
 * @details Simulates input signals to verify Hysteresis and State Transitions.
 * Compile with: g++ main.cpp HCU_Controller.cpp -o hcu_test
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include "HCU_Controller.h"

using namespace std;

// Helper to print human-readable state names
string stateToString(HCUState s) {
    switch(s) {
        case HCUState::Eco:   return "ECO   (0N)";
        case HCUState::Boost: return "BOOST (+3000N)";
        case HCUState::Regen: return "REGEN (-4000N)";
        default: return "UNKNOWN";
    }
}

int main() {
    // Instantiate Controller
    HybridControlUnit hcu;

    cout << "==========================================================\n";
    cout << "      HCU LOGIC VALIDATION SUITE (SIL TESTING)            \n";
    cout << "==========================================================\n";
    cout << left << setw(15) << "TEST CASE" 
         << setw(15) << "INPUT(N)" 
         << setw(10) << "SOC(%)" 
         << setw(20) << "OUTPUT STATE" 
         << "RESULT" << endl;
    cout << "----------------------------------------------------------\n";

    struct TestCase {
        string name;
        double force;
        double brake;
        double soc;
        HCUState expectedState;
    };

    vector<TestCase> tests = {
        // 1. Idle Condition
        {"Idle",        0.0,    0.0, 90.0, HCUState::Eco},
        
        // 2. Hard Acceleration (Entry Threshold is 5500)
        {"Launch",      6000.0, 0.0, 90.0, HCUState::Boost},
        
        // 3. THE HYSTERESIS TEST (The "Chatter" Fix)
        // Input drops to 5200. Original logic would switch OFF. 
        // Our logic should stay ON because 5200 > 5000 (Exit Threshold).
        {"Throt. Dip",  5200.0, 0.0, 90.0, HCUState::Boost},
        
        // 4. Low Load (Drop below Exit Threshold)
        {"Cruise",      4000.0, 0.0, 90.0, HCUState::Eco},
        
        // 5. Low Battery Override (Even with high force)
        {"Low SoC",     6000.0, 0.0, 15.0, HCUState::Eco},
        
        // 6. Braking Priority
        {"Hard Brake",  6000.0, 100.0, 90.0, HCUState::Regen}
    };

    // Run Tests
    bool allPassed = true;
    for (const auto& t : tests) {
        // Run logic
        hcu.update(t.force, t.brake, t.soc);
        HCUState result = hcu.getCurrentState();

        // Print Output
        cout << left << setw(15) << t.name 
             << setw(15) << t.force 
             << setw(10) << t.soc 
             << setw(20) << stateToString(result);
        
        if (result == t.expectedState) {
            cout << "[PASS]" << endl;
        } else {
            cout << "[FAIL] <--" << endl;
            allPassed = false;
        }
    }

    cout << "----------------------------------------------------------\n";
    if (allPassed) cout << "ALL CHECKS PASSED. LOGIC VALIDATED.\n";
    else           cout << "WARNING: LOGIC ERRORS DETECTED.\n";

    return 0;
}
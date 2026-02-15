#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// --- THE HCU LOGIC (The "Unit" being tested) ---
enum class HCUState {
    Eco,
    Boost,
    Regen
};

class HCU_Controller {
public:
    HCUState currentState = HCUState::Eco;
    double motorForce = 0.0;
    
    // Tuning Parameters
    const double BOOST_ENTRY_THRESHOLD = 5500.0; // Newtons
    const double BOOST_EXIT_THRESHOLD = 5000.0;  // Newtons (Hysteresis)
    const double SOC_MIN = 20.0;                 // % Battery
    
    void step(double engineForce, double brake, double soc) {
        switch (currentState) {
            case HCUState::Eco:
                motorForce = 0.0;
                if (brake > 0) {
                    currentState = HCUState::Regen;
                } else if (engineForce >= BOOST_ENTRY_THRESHOLD && soc > SOC_MIN) {
                    currentState = HCUState::Boost;
                }
                break;
                
            case HCUState::Boost:
                motorForce = 3000.0; // Electric Assist
                if (brake > 0) {
                    currentState = HCUState::Regen;
                } else if (engineForce < BOOST_EXIT_THRESHOLD) {
                    // HYSTERESIS: Only exit if force drops below 5000, not 5500
                    currentState = HCUState::Eco;
                }
                break;
                
            case HCUState::Regen:
                motorForce = -4000.0; // Regenerative Braking
                if (brake == 0) {
                    currentState = HCUState::Eco;
                }
                break;
        }
    }
};

// --- THE TEST HARNESS (The Verification Tool) ---
struct TestCase {
    std::string name;
    double inputForce;
    double inputBrake;
    double inputSoC;
    HCUState initialState;
    HCUState expectedState;
};

void runTests() {
    HCU_Controller hcu;
    std::vector<TestCase> tests = {
        // Name                        Force   Brake   SoC    StartState       ExpectedState
        {"1. Normal Idle",             0,      0,      90,    HCUState::Eco,   HCUState::Eco},
        {"2. Boost Entry (>5500N)",    5600,   0,      90,    HCUState::Eco,   HCUState::Boost},
        {"3. Throttle Dip (5200N)",    5200,   0,      85,    HCUState::Boost, HCUState::Boost}, // The Hysteresis Test!
        {"4. Boost Exit (<5000N)",     4900,   0,      80,    HCUState::Boost, HCUState::Eco},
        {"5. Hard Brake (Regen)",      0,      100,    80,    HCUState::Eco,   HCUState::Regen},
        {"6. Low Battery Block",       6000,   0,      10,    HCUState::Eco,   HCUState::Eco}
    };

    std::cout << "--------------------------------------------------------\n";
    std::cout << "  HCU LOGIC VALIDATION SUITE (SIL TESTING) \n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "| TEST CASE                 | RESULT | STATUS |\n";
    std::cout << "|---------------------------|--------|--------|\n";

    for (const auto& test : tests) {
        // Setup
        hcu.currentState = test.initialState;
        
        // Execute
        hcu.step(test.inputForce, test.inputBrake, test.inputSoC);
        
        // Verify
        bool pass = (hcu.currentState == test.expectedState);
        
        // Print
        std::cout << "| " << std::left << std::setw(25) << test.name 
                  << " | " << (pass ? "Expected" : "FAILED  ") 
                  << " | " << (pass ? "[PASS] " : "[FAIL] ") << "|\n";
    }
    std::cout << "--------------------------------------------------------\n";
}

int main() {
    runTests();
    return 0;
}
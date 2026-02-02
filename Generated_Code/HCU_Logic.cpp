//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: HCU_Logic.cpp
//
// Code generated for Simulink model 'HCU_Logic'.
//
// Model version                  : 1.4
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Mon Feb  2 18:27:34 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "HCU_Logic.h"
#include "rtwtypes.h"

// Named constants for Chart: '<S1>/Hybrid_Controller'
const uint8_T HCU_Logic_IN_Battery_Regen_Mode{ 1U };

const uint8_T HCU_Logic_IN_Boost_Mode{ 2U };

const uint8_T HCU_Logic_IN_Eco_mode{ 3U };

// System initialize for atomic system: '<Root>/HCU_Logic'
void HCU_Logic::HCU_Logic_HCU_Logic_Init(real_T *rty_Motor_Force)
{
  // SystemInitialize for Chart: '<S1>/Hybrid_Controller'
  *rty_Motor_Force = 0.0;
}

// Output and update for atomic system: '<Root>/HCU_Logic'
void HCU_Logic::HCU_Logic_HCU_Logic(real_T rtu_Engineforce, real_T rtu_Brake,
  real_T rtu_SoC, real_T *rty_Motor_Force, DW_HCU_Logic_HCU_Logic_T *localDW)
{
  // Chart: '<S1>/Hybrid_Controller'
  if (localDW->is_active_c3_HCU_Logic == 0U) {
    localDW->is_active_c3_HCU_Logic = 1U;
    localDW->is_c3_HCU_Logic = HCU_Logic_IN_Eco_mode;
    *rty_Motor_Force = 0.0;
  } else {
    switch (localDW->is_c3_HCU_Logic) {
     case HCU_Logic_IN_Battery_Regen_Mode:
      *rty_Motor_Force = -4000.0;
      if (rtu_Brake == 0.0) {
        localDW->is_c3_HCU_Logic = HCU_Logic_IN_Eco_mode;
        *rty_Motor_Force = 0.0;
      }
      break;

     case HCU_Logic_IN_Boost_Mode:
      *rty_Motor_Force = 3000.0;
      if (rtu_Engineforce < 5500.0) {
        localDW->is_c3_HCU_Logic = HCU_Logic_IN_Eco_mode;
        *rty_Motor_Force = 0.0;
      } else if (rtu_Brake > 0.0) {
        localDW->is_c3_HCU_Logic = HCU_Logic_IN_Battery_Regen_Mode;
        *rty_Motor_Force = -4000.0;
      }
      break;

     default:
      // case IN_Eco_mode:
      *rty_Motor_Force = 0.0;
      if ((rtu_Engineforce >= 5500.0) && (rtu_SoC > 20.0)) {
        localDW->is_c3_HCU_Logic = HCU_Logic_IN_Boost_Mode;
        *rty_Motor_Force = 3000.0;
      } else if (rtu_Brake > 0.0) {
        localDW->is_c3_HCU_Logic = HCU_Logic_IN_Battery_Regen_Mode;
        *rty_Motor_Force = -4000.0;
      }
      break;
    }
  }

  // End of Chart: '<S1>/Hybrid_Controller'
}

// Model step function
void HCU_Logic::step()
{
  // Outputs for Atomic SubSystem: '<Root>/HCU_Logic'

  // Inport: '<Root>/Engine force' incorporates:
  //   Inport: '<Root>/Brake'
  //   Inport: '<Root>/SoC'
  //   Outport: '<Root>/Motor_Force'

  HCU_Logic_HCU_Logic(HCU_Logic_U.Gas, HCU_Logic_U.Brake, HCU_Logic_U.SoC,
                      &HCU_Logic_Y.Motor_Force, &HCU_Logic_DW.HCU_Logic_d);

  // End of Outputs for SubSystem: '<Root>/HCU_Logic'
}

// Model initialize function
void HCU_Logic::initialize()
{
  // SystemInitialize for Atomic SubSystem: '<Root>/HCU_Logic'

  // SystemInitialize for Outport: '<Root>/Motor_Force'
  HCU_Logic_HCU_Logic_Init(&HCU_Logic_Y.Motor_Force);

  // End of SystemInitialize for SubSystem: '<Root>/HCU_Logic'
}

// Model terminate function
void HCU_Logic::terminate()
{
  // (no terminate code required)
}

// Constructor
HCU_Logic::HCU_Logic() :
  HCU_Logic_U(),
  HCU_Logic_Y(),
  HCU_Logic_DW(),
  HCU_Logic_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
HCU_Logic::~HCU_Logic() = default;

// Real-Time Model get method
HCU_Logic::RT_MODEL_HCU_Logic_T * HCU_Logic::getRTM()
{
  return (&HCU_Logic_M);
}

//
// File trailer for generated code.
//
// [EOF]
//

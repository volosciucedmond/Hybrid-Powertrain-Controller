//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Hybrid_Controller.cpp
//
// Code generated for Simulink model 'Hybrid_Controller'.
//
// Model version                  : 1.53
// Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
// C/C++ source code generated on : Fri Feb 27 12:59:17 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Hybrid_Controller.h"
#include "rtwtypes.h"

// Named constants for Chart: '<Root>/Hybrid_Controller'
const uint8_T Hybrid_Co_IN_Battery_Regen_Mode{ 1U };

const uint8_T Hybrid_Controller_IN_Boost_Mode{ 2U };

const uint8_T Hybrid_Controller_IN_Eco_mode{ 3U };

// Model step function
void Hybrid_Controller::step()
{
  // Chart: '<Root>/Hybrid_Controller' incorporates:
  //   Inport: '<Root>/Brake'
  //   Inport: '<Root>/Energy_Used'
  //   Inport: '<Root>/SoC'
  //   Inport: '<Root>/Speed'
  //   Inport: '<Root>/Throttle'

  if (Hybrid_Controller_DW.is_active_c3_Hybrid_Controller == 0U) {
    Hybrid_Controller_DW.is_active_c3_Hybrid_Controller = 1U;
    Hybrid_Controller_DW.is_c3_Hybrid_Controller = Hybrid_Controller_IN_Eco_mode;

    // Outport: '<Root>/Motor_Force'
    Hybrid_Controller_Y.Motor_Force = 0.0;
  } else {
    switch (Hybrid_Controller_DW.is_c3_Hybrid_Controller) {
     case Hybrid_Co_IN_Battery_Regen_Mode:
      // Outport: '<Root>/Motor_Force'
      Hybrid_Controller_Y.Motor_Force = -2777.0;
      if ((Hybrid_Controller_U.Brake_Cmd == 0.0) ||
          (Hybrid_Controller_DW.Regen_Energy >= 2.0E+6)) {
        Hybrid_Controller_DW.is_c3_Hybrid_Controller =
          Hybrid_Controller_IN_Eco_mode;

        // Outport: '<Root>/Motor_Force'
        Hybrid_Controller_Y.Motor_Force = 0.0;
      } else {
        Hybrid_Controller_DW.Regen_Energy += 2777.0 *
          Hybrid_Controller_U.Velocity * 0.001;

        // Outport: '<Root>/reg_en' incorporates:
        //   Inport: '<Root>/Speed'

        Hybrid_Controller_Y.reg_en = Hybrid_Controller_DW.Regen_Energy;
      }
      break;

     case Hybrid_Controller_IN_Boost_Mode:
      // Outport: '<Root>/Motor_Force'
      Hybrid_Controller_Y.Motor_Force = 100000.0;
      if ((Hybrid_Controller_U.Acceleration_cmd < 4500.0) ||
          (Hybrid_Controller_U.SoC <= 20.0) || (Hybrid_Controller_U.Energy_Used >=
           4.0E+6) || (Hybrid_Controller_U.Velocity > 77.7) ||
          (Hybrid_Controller_U.Velocity < 27.7)) {
        Hybrid_Controller_DW.is_c3_Hybrid_Controller =
          Hybrid_Controller_IN_Eco_mode;

        // Outport: '<Root>/Motor_Force'
        Hybrid_Controller_Y.Motor_Force = 0.0;
      } else if (Hybrid_Controller_U.Brake_Cmd < 0.0) {
        Hybrid_Controller_DW.is_c3_Hybrid_Controller =
          Hybrid_Co_IN_Battery_Regen_Mode;

        // Outport: '<Root>/Motor_Force'
        Hybrid_Controller_Y.Motor_Force = -2777.0;
      }
      break;

     default:
      // Outport: '<Root>/Motor_Force'
      // case IN_Eco_mode:
      Hybrid_Controller_Y.Motor_Force = 0.0;
      if ((Hybrid_Controller_U.Acceleration_cmd > 5500.0) &&
          (Hybrid_Controller_U.Velocity > 27.7) && (Hybrid_Controller_U.Velocity
           < 77.7) && (Hybrid_Controller_U.SoC > 25.0) &&
          (Hybrid_Controller_U.Energy_Used < 4.0E+6)) {
        Hybrid_Controller_DW.is_c3_Hybrid_Controller =
          Hybrid_Controller_IN_Boost_Mode;

        // Outport: '<Root>/Motor_Force'
        Hybrid_Controller_Y.Motor_Force = 100000.0;
      } else if (Hybrid_Controller_U.Brake_Cmd < 0.0) {
        Hybrid_Controller_DW.is_c3_Hybrid_Controller =
          Hybrid_Co_IN_Battery_Regen_Mode;

        // Outport: '<Root>/Motor_Force'
        Hybrid_Controller_Y.Motor_Force = -2777.0;
      }
      break;
    }
  }

  // End of Chart: '<Root>/Hybrid_Controller'
}

// Model initialize function
void Hybrid_Controller::initialize()
{
  // (no initialization code required)
}

// Model terminate function
void Hybrid_Controller::terminate()
{
  // (no terminate code required)
}

// Constructor
Hybrid_Controller::Hybrid_Controller() :
  Hybrid_Controller_U(),
  Hybrid_Controller_Y(),
  Hybrid_Controller_DW(),
  Hybrid_Controller_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
Hybrid_Controller::~Hybrid_Controller() = default;

// Real-Time Model get method
Hybrid_Controller::RT_MODEL_Hybrid_Controller_T * Hybrid_Controller::getRTM()
{
  return (&Hybrid_Controller_M);
}

//
// File trailer for generated code.
//
// [EOF]
//

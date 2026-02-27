//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Hybrid_Controller.h
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
#ifndef RTW_HEADER_Hybrid_Controller_h_
#define RTW_HEADER_Hybrid_Controller_h_
#include "rtwtypes.h"
#include "Hybrid_Controller_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Class declaration for model Hybrid_Controller
class Hybrid_Controller final
{
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>'
  struct DW_Hybrid_Controller_T {
    real_T Regen_Energy;               // '<Root>/Hybrid_Controller'
    uint8_T is_active_c3_Hybrid_Controller;// '<Root>/Hybrid_Controller'
    uint8_T is_c3_Hybrid_Controller;   // '<Root>/Hybrid_Controller'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_Hybrid_Controller_T {
    real_T Acceleration_cmd;           // '<Root>/Throttle'
    real_T Velocity;                   // '<Root>/Speed'
    real_T SoC;                        // '<Root>/SoC'
    real_T Brake_Cmd;                  // '<Root>/Brake'
    real_T Energy_Used;                // '<Root>/Energy_Used'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_Hybrid_Controller_T {
    real_T Motor_Force;                // '<Root>/Motor_Force'
    real_T reg_en;                     // '<Root>/reg_en'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_Hybrid_Controller_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  Hybrid_Controller(Hybrid_Controller const&) = delete;

  // Assignment Operator
  Hybrid_Controller& operator= (Hybrid_Controller const&) & = delete;

  // Move Constructor
  Hybrid_Controller(Hybrid_Controller &&) = delete;

  // Move Assignment Operator
  Hybrid_Controller& operator= (Hybrid_Controller &&) = delete;

  // Real-Time Model get method
  Hybrid_Controller::RT_MODEL_Hybrid_Controller_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_Hybrid_Controller_T
    *pExtU_Hybrid_Controller_T)
  {
    Hybrid_Controller_U = *pExtU_Hybrid_Controller_T;
  }

  // Root outports get method
  const ExtY_Hybrid_Controller_T &getExternalOutputs() const
  {
    return Hybrid_Controller_Y;
  }

  // model initialize function
  static void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  Hybrid_Controller();

  // Destructor
  ~Hybrid_Controller();

  // private data and function members
 private:
  // External inputs
  ExtU_Hybrid_Controller_T Hybrid_Controller_U;

  // External outputs
  ExtY_Hybrid_Controller_T Hybrid_Controller_Y;

  // Block states
  DW_Hybrid_Controller_T Hybrid_Controller_DW;

  // Real-Time Model
  RT_MODEL_Hybrid_Controller_T Hybrid_Controller_M;
};

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Note that this particular code originates from a subsystem build,
//  and has its own system numbers different from the parent model.
//  Refer to the system hierarchy for this subsystem below, and use the
//  MATLAB hilite_system command to trace the generated code back
//  to the parent model.  For example,
//
//  hilite_system('HCU_V2_Driver/HCU_Logic/Hybrid_Controller')    - opens subsystem HCU_V2_Driver/HCU_Logic/Hybrid_Controller
//  hilite_system('HCU_V2_Driver/HCU_Logic/Hybrid_Controller/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'HCU_V2_Driver/HCU_Logic'
//  '<S1>'   : 'HCU_V2_Driver/HCU_Logic/Hybrid_Controller'

#endif                                 // RTW_HEADER_Hybrid_Controller_h_

//
// File trailer for generated code.
//
// [EOF]
//

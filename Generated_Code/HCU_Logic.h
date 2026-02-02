//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: HCU_Logic.h
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
#ifndef RTW_HEADER_HCU_Logic_h_
#define RTW_HEADER_HCU_Logic_h_
#include "rtwtypes.h"
#include "HCU_Logic_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Class declaration for model HCU_Logic
class HCU_Logic final
{
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>/HCU_Logic'
  struct DW_HCU_Logic_HCU_Logic_T {
    uint8_T is_active_c3_HCU_Logic;    // '<S1>/Hybrid_Controller'
    uint8_T is_c3_HCU_Logic;           // '<S1>/Hybrid_Controller'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_HCU_Logic_T {
    DW_HCU_Logic_HCU_Logic_T HCU_Logic_d;// '<Root>/HCU_Logic'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_HCU_Logic_T {
    real_T Gas;                        // '<Root>/Engine force'
    real_T Brake;                      // '<Root>/Brake'
    real_T Velocity;                   // '<Root>/Velocity'
    real_T SoC;                        // '<Root>/SoC'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_HCU_Logic_T {
    real_T Motor_Force;                // '<Root>/Motor_Force'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_HCU_Logic_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  HCU_Logic(HCU_Logic const&) = delete;

  // Assignment Operator
  HCU_Logic& operator= (HCU_Logic const&) & = delete;

  // Move Constructor
  HCU_Logic(HCU_Logic &&) = delete;

  // Move Assignment Operator
  HCU_Logic& operator= (HCU_Logic &&) = delete;

  // Real-Time Model get method
  HCU_Logic::RT_MODEL_HCU_Logic_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_HCU_Logic_T *pExtU_HCU_Logic_T)
  {
    HCU_Logic_U = *pExtU_HCU_Logic_T;
  }

  // Root outports get method
  const ExtY_HCU_Logic_T &getExternalOutputs() const
  {
    return HCU_Logic_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  HCU_Logic();

  // Destructor
  ~HCU_Logic();

  // private data and function members
 private:
  // External inputs
  ExtU_HCU_Logic_T HCU_Logic_U;

  // External outputs
  ExtY_HCU_Logic_T HCU_Logic_Y;

  // Block states
  DW_HCU_Logic_T HCU_Logic_DW;

  // private member function(s) for subsystem '<Root>/HCU_Logic'
  static void HCU_Logic_HCU_Logic_Init(real_T *rty_Motor_Force);
  static void HCU_Logic_HCU_Logic(real_T rtu_Engineforce, real_T rtu_Brake,
    real_T rtu_SoC, real_T *rty_Motor_Force, DW_HCU_Logic_HCU_Logic_T *localDW);

  // Real-Time Model
  RT_MODEL_HCU_Logic_T HCU_Logic_M;
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
//  hilite_system('HCU_V2_Driver/HCU_Logic')    - opens subsystem HCU_V2_Driver/HCU_Logic
//  hilite_system('HCU_V2_Driver/HCU_Logic/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'HCU_V2_Driver'
//  '<S1>'   : 'HCU_V2_Driver/HCU_Logic'
//  '<S2>'   : 'HCU_V2_Driver/HCU_Logic/Hybrid_Controller'

#endif                                 // RTW_HEADER_HCU_Logic_h_

//
// File trailer for generated code.
//
// [EOF]
//

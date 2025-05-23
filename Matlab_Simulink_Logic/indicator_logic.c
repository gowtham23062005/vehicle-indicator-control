/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: indicator_logic.c
 *
 * Code generated for Simulink model 'indicator_logic'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri May 23 13:01:29 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "indicator_logic.h"
#include "rtwtypes.h"

/* Named constants for Chart: '<Root>/Chart' */
#define indicator_logic_IN_Hazard      ((uint8_T)1U)
#define indicator_logic_IN_Idle        ((uint8_T)2U)
#define indicator_logic_IN_LeftActive  ((uint8_T)3U)
#define indicator_logic_IN_RightActive ((uint8_T)4U)

/* Block states (default storage) */
DW_indicator_logic_T indicator_logic_DW;

/* External inputs (root inport signals with default storage) */
ExtU_indicator_logic_T indicator_logic_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_indicator_logic_T indicator_logic_Y;

/* Real-time model */
static RT_MODEL_indicator_logic_T indicator_logic_M_;
RT_MODEL_indicator_logic_T *const indicator_logic_M = &indicator_logic_M_;

/* Model step function */
void indicator_logic_step(void)
{
  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/LeftBtn'
   *  Inport: '<Root>/RightBtn'
   */
  if (indicator_logic_DW.is_active_c3_indicator_logic == 0) {
    indicator_logic_DW.is_active_c3_indicator_logic = 1U;
    indicator_logic_DW.is_c3_indicator_logic = indicator_logic_IN_Idle;
    indicator_logic_DW.t4 = 0.0;
  } else {
    switch (indicator_logic_DW.is_c3_indicator_logic) {
     case indicator_logic_IN_Hazard:
      if ((indicator_logic_U.LeftBtn || indicator_logic_U.RightBtn) &&
          (indicator_logic_DW.t4 >= 1.0)) {
        indicator_logic_DW.is_c3_indicator_logic = indicator_logic_IN_Idle;
        indicator_logic_DW.t4 = 0.0;
      } else {
        indicator_logic_DW.t4 = ((indicator_logic_M->Timing.clockTick0) * 0.1) +
          0.1;

        /* Outport: '<Root>/LED_Left' incorporates:
         *  Inport: '<Root>/Blink300'
         */
        indicator_logic_Y.LED_Left = indicator_logic_U.Blink300;

        /* Outport: '<Root>/LED_Right' incorporates:
         *  Inport: '<Root>/Blink300'
         */
        indicator_logic_Y.LED_Right = indicator_logic_U.Blink300;
      }
      break;

     case indicator_logic_IN_Idle:
      if (indicator_logic_U.LeftBtn && (!indicator_logic_U.RightBtn) &&
          (indicator_logic_DW.t4 >= 1.0)) {
        indicator_logic_DW.is_c3_indicator_logic = indicator_logic_IN_LeftActive;
        indicator_logic_DW.t4 = 0.0;
      } else if (indicator_logic_U.RightBtn && (!indicator_logic_U.LeftBtn) &&
                 (indicator_logic_DW.t4 >= 1.0)) {
        indicator_logic_DW.is_c3_indicator_logic =
          indicator_logic_IN_RightActive;
        indicator_logic_DW.t4 = 0.0;
      } else if (indicator_logic_U.LeftBtn && indicator_logic_U.RightBtn &&
                 (indicator_logic_DW.t4 >= 1.0)) {
        indicator_logic_DW.is_c3_indicator_logic = indicator_logic_IN_Hazard;
        indicator_logic_DW.t4 = 0.0;
      } else {
        indicator_logic_DW.t4 += 0.1;
      }
      break;

     case indicator_logic_IN_LeftActive:
      if (indicator_logic_U.RightBtn && (indicator_logic_DW.t4 >= 1.0)) {
        indicator_logic_DW.is_c3_indicator_logic =
          indicator_logic_IN_RightActive;
        indicator_logic_DW.t4 = 0.0;
      } else if (indicator_logic_U.LeftBtn && (indicator_logic_DW.t4 >= 1.0)) {
        indicator_logic_DW.is_c3_indicator_logic = indicator_logic_IN_Idle;
        indicator_logic_DW.t4 = 0.0;
      } else {
        indicator_logic_DW.t4 += 0.1;

        /* Outport: '<Root>/LED_Left' incorporates:
         *  Inport: '<Root>/Blink300'
         */
        indicator_logic_Y.LED_Left = indicator_logic_U.Blink300;

        /* Outport: '<Root>/LED_Right' */
        indicator_logic_Y.LED_Right = false;
      }
      break;

     default:
      /* case IN_RightActive: */
      if (indicator_logic_U.LeftBtn && (indicator_logic_DW.t4 >= 1.0)) {
        indicator_logic_DW.is_c3_indicator_logic = indicator_logic_IN_LeftActive;
        indicator_logic_DW.t4 = 0.0;
      } else if (indicator_logic_U.RightBtn && (indicator_logic_DW.t4 >= 1.0)) {
        indicator_logic_DW.is_c3_indicator_logic = indicator_logic_IN_Idle;
        indicator_logic_DW.t4 = 0.0;
      } else {
        indicator_logic_DW.t4 = ((indicator_logic_M->Timing.clockTick0) * 0.1) +
          0.1;

        /* Outport: '<Root>/LED_Right' incorporates:
         *  Inport: '<Root>/Blink300'
         */
        indicator_logic_Y.LED_Right = indicator_logic_U.Blink300;

        /* Outport: '<Root>/LED_Left' */
        indicator_logic_Y.LED_Left = false;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  indicator_logic_M->Timing.clockTick0++;
}

/* Model initialize function */
void indicator_logic_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void indicator_logic_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */

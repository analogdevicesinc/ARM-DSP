/* ----------------------------------------------------------------------
* Copyright (C) 2020-2021 Maxim Integrated Products, Inc., All Rights Reserved.
*
* NOTICE OF MODIFICATIONS
*
* The following modifications have been made to the original source files provided by ARM Limited :
* 	- main function return paths
*	- main function return type
*
* These modifications are licensed under the same Apache 2.0 license as the original code.
* ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
* Copyright (C) 2010-2020 ARM Limited. All rights reserved.
*
* $Date:         23. March 2020
* $Revision:     V1.7.0
*
* Project:       CMSIS DSP Library
* Title:         arm_linear_interp_example_f32.c
*
* Description:   Example code demonstrating usage of sin function
*                and uses linear interpolation to get higher precision
*
* Target Processor: Cortex-M55/Cortex-M7/Cortex-M4/Cortex-M3/Cortex-M0
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
 * -------------------------------------------------------------------- */


/**
 * @ingroup groupExamples
 */

/**
 * @defgroup LinearInterpExample Linear Interpolate Example
 *
 * <b> CMSIS DSP Software Library -- Linear Interpolate Example  </b>
 *
 * <b> Description </b>
 * This example demonstrates usage of linear interpolate modules and fast math modules.
 * Method 1 uses fast math sine function to calculate sine values using cubic interpolation and method 2 uses
 * linear interpolation function and results are compared to reference output.
 * Example shows linear interpolation function can be used to get higher precision compared to fast math sin calculation.
 *
 * \par Block Diagram:
 * \par
 * \image html linearInterpExampleMethod1.gif "Method 1: Sine caluclation using fast math"
 * \par
 * \image html linearInterpExampleMethod2.gif "Method 2: Sine caluclation using interpolation function"
 *
 * \par Variables Description:
 * \par
 * \li \c testInputSin_f32         points to the input values for sine calculation
 * \li \c testRefSinOutput32_f32   points to the reference values caculated from sin() matlab function
 * \li \c testOutput               points to output buffer calculation from cubic interpolation
 * \li \c testLinIntOutput         points to output buffer calculation from linear interpolation
 * \li \c snr1                     Signal to noise ratio for reference and cubic interpolation output
 * \li \c snr2                     Signal to noise ratio for reference and linear interpolation output
 *
 * \par CMSIS DSP Software Library Functions Used:
 * \par
 * - arm_sin_f32()
 * - arm_linear_interp_f32()
 *
 * <b> Refer  </b>
 * \link arm_linear_interp_example_f32.c \endlink
 *
 */


/** \example arm_linear_interp_example_f32.c
  */

#include "arm_math.h"
#include "math_helper.h"
#include "stdint.h"

#if defined(SEMIHOSTING)
#include <stdio.h>
#endif

#define SNR_THRESHOLD           90
#define TEST_LENGTH_SAMPLES     10
#define XSPACING               (0.005f)

/* ----------------------------------------------------------------------
* Test input data for F32 SIN function
* Generated by the MATLAB rand() function
* randn('state', 0)
* xi = (((1/4.18318581819710)* randn(blockSize, 1) * 2* pi));
* --------------------------------------------------------------------*/
float32_t testInputSin_f32[TEST_LENGTH_SAMPLES] =
{
   -0.649716504673081170, -2.501723745497831200,
    0.188250329003310100,  0.432092748487532540,
   -1.722010988459680800,  1.788766476323060600,
    1.786136060975809500, -0.056525543169408797,
    0.491596272728153760,  0.262309671126153390
};

/*------------------------------------------------------------------------------
*  Reference out of SIN F32 function for Block Size = 10
*  Calculated from sin(testInputSin_f32)
*------------------------------------------------------------------------------*/
float32_t testRefSinOutput32_f32[TEST_LENGTH_SAMPLES] =
{
   -0.604960695383043530, -0.597090287967934840,
    0.187140422442966500,  0.418772124875992690,
   -0.988588831792106880,  0.976338412038794010,
    0.976903856413481100, -0.056495446835214236,
    0.472033731854734240,  0.259311907228582830
};

/*------------------------------------------------------------------------------
*  Method 1: Test out Buffer Calculated from Cubic Interpolation
*------------------------------------------------------------------------------*/
float32_t testOutput[TEST_LENGTH_SAMPLES];

/*------------------------------------------------------------------------------
*  Method 2: Test out buffer Calculated from Linear Interpolation
*------------------------------------------------------------------------------*/
float32_t testLinIntOutput[TEST_LENGTH_SAMPLES];

/*------------------------------------------------------------------------------
*  External table used for linear interpolation
*------------------------------------------------------------------------------*/
extern const float arm_linear_interep_table[1884];

/* ----------------------------------------------------------------------
* Global Variables for caluclating SNR's for Method1 & Method 2
* ------------------------------------------------------------------- */
float32_t snr1;
float32_t snr2;

/* ----------------------------------------------------------------------------
* Calculation of Sine values from Cubic Interpolation and Linear interpolation
* ---------------------------------------------------------------------------- */
int main(void)
{
  uint32_t i;
  arm_status status;

  arm_linear_interp_instance_f32 S = {1884, -3.141592653589793238, XSPACING, (float*)&arm_linear_interep_table[0]};

  /*------------------------------------------------------------------------------
  *  Method 1: Test out Calculated from Cubic Interpolation
  *------------------------------------------------------------------------------*/
  for(i=0; i< TEST_LENGTH_SAMPLES; i++)
  {
    testOutput[i] = arm_sin_f32(testInputSin_f32[i]);
  }

  /*------------------------------------------------------------------------------
  *  Method 2: Test out Calculated from Cubic Interpolation and Linear interpolation
  *------------------------------------------------------------------------------*/

  for(i=0; i< TEST_LENGTH_SAMPLES; i++)
  {
      testLinIntOutput[i] = arm_linear_interp_f32(&S, testInputSin_f32[i]);
  }

  /*------------------------------------------------------------------------------
  *            SNR calculation for method 1
  *------------------------------------------------------------------------------*/
  snr1 = arm_snr_f32(testRefSinOutput32_f32, testOutput, 2);

  /*------------------------------------------------------------------------------
  *            SNR calculation for method 2
  *------------------------------------------------------------------------------*/
  snr2 = arm_snr_f32(testRefSinOutput32_f32, testLinIntOutput, 2);

  /*------------------------------------------------------------------------------
  *            Initialise status depending on SNR calculations
  *------------------------------------------------------------------------------*/
  status = (snr2 <= snr1) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;

  if (status != ARM_MATH_SUCCESS)
  {
#if defined (SEMIHOSTING)
    printf("FAILURE\n");
#endif
    return -1;
  }
  else
  {
#if defined (SEMIHOSTING)
    printf("SUCCESS\n");
#endif
    return 1;
  }

  return 0;
}

 /** \endlink */

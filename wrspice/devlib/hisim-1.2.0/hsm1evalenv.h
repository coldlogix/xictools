
/*========================================================================*
 *                                                                        *
 *  Distributed by Whiteley Research Inc., Sunnyvale, California, USA     *
 *                       http://wrcad.com                                 *
 *  Copyright (C) 2017 Whiteley Research Inc., all rights reserved.       *
 *  Author: Stephen R. Whiteley, except as indicated.                     *
 *                                                                        *
 *  As fully as possible recognizing licensing terms and conditions       *
 *  imposed by earlier work from which this work was derived, if any,     *
 *  this work is released under the Apache License, Version 2.0 (the      *
 *  "License").  You may not use this file except in compliance with      *
 *  the License, and compliance with inherited licenses which are         *
 *  specified in a sub-header below this one if applicable.  A copy       *
 *  of the License is provided with this distribution, or you may         *
 *  obtain a copy of the License at                                       *
 *                                                                        *
 *        http://www.apache.org/licenses/LICENSE-2.0                      *
 *                                                                        *
 *  See the License for the specific language governing permissions       *
 *  and limitations under the License.                                    *
 *                                                                        *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES      *
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-        *
 *   INFRINGEMENT.  IN NO EVENT SHALL WHITELEY RESEARCH INCORPORATED      *
 *   OR STEPHEN R. WHITELEY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE       *
 *   USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                        *
 *========================================================================*
 *               XicTools Integrated Circuit Design System                *
 *                                                                        *
 * WRspice Circuit Simulation and Analysis Tool:  Device Library          *
 *                                                                        *
 *========================================================================*
 $Id:$
 *========================================================================*/

/***********************************************************************
 HiSIM (Hiroshima University STARC IGFET Model)
 Copyright (C) 2003 STARC

 VERSION : HiSIM 1.2.0
 FILE : hsm1evalenv.h of HiSIM 1.2.0

 April 9, 2003 : released by STARC Physical Design Group
***********************************************************************/

#ifndef HSM1_EVAL_ENV_H
#define HSM1_EVAL_ENV_H

/* macros and constants used in hsm1eval1_y_z.c */

/*---------------------------------------------------*
* Numerical constants. (macro) 
*-----------------*/

/* machine epsilon */
#if defined(_FLOAT_H) && defined(DBL_EPSILON)
#define C_EPS_M (DBL_EPSILON) 
#else
#define C_EPS_M (2.2204460492503131e-16) 
#endif

/* sqrt(2) */
#define C_SQRT_2 (1.414213562373095e+00) 

/* 1/3 */
#define C_1o3   (3.333333333333333e-01) 
/* 2/3 */
#define C_2o3   (6.666666666666667e-01) 
/* 2^(1/3) */
#define C_2p_1o3    (1.259921049894873e+00) 

/* Pi */
#define C_Pi   (3.141592653589793)
#define C_Pio2 (1.570796326794897)

/* Unit change */
#define C_m2cm    (1.0e2)
#define C_m2cm_p2 (1.0e4)
#define C_m2cm_p1o2 (1.0e1)

/*---------------------------------------------------*
* Physical constants/properties. (macro) 
*-----------------*/
/* Elemental charge */
#define C_QE    (1.6021918e-19) 

/* Boltzmann constant */
#define C_KB    (1.3806226e-23) 

/* Permitivity of Si, SiO2 and vacuum */
#define C_ESI   (1.034943e-12) 
#define C_EOX   (3.453133e-13) 
#define C_VAC   (8.8541878e-14) 

/* Room temperature constants */
#define C_T300  (300e+00)
#define C_b300  (3.868283e+01)
#define C_Eg0   (1.1785e0)

/* Build-in potential */
#define C_Vbi   (1.0e0)

/* Intrinsic carrier density at 300K */
#define C_Nin0  (1.04e+10)


/*---------------------------------------------------*
* Functions. (macro)  Take care of the arguments.
*-----------------*/
#define Fn_Sqr(x)   ( (x)*(x) ) /* x^2 */
#define Fn_Max(x,y) ( (x) >= (y) ? (x) : (y) ) /* max[x,y] */
#define Fn_Min(x,y) ( (x) <= (y) ? (x) : (y) ) /* min[x,y] */
#define Fn_Sgn(x)   ( (x) >= 0  ?  (1) : (-1) )    /* sign[x] */

#endif /* HSM1_EVAL_ENV_H */

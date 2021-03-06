
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

/***************************************************************************
JSPICE3 adaptation of Spice3e2 - Copyright (c) Stephen R. Whiteley 1992
Author: 1992 Stephen R. Whiteley
****************************************************************************/

#include "jjdefs.h"


namespace {
    //
    // Return interpolated Josephson current.
    //
    double jj_ji(const sCKT *ckt, const sJJinstance *inst)
    {
        if (!ckt->CKTstates[0])
            return (0.0);
        double val = ckt->CKTtranDiffs[0]*
            *(ckt->CKTstates[0] + inst->JJcrti)*
            sin(*(ckt->CKTstates[0] + inst->JJphase));
        for (int i = 1; i <= ckt->CKTtranDegree; i++) {
            val += ckt->CKTtranDiffs[i]*
                *(ckt->CKTstates[i] + inst->JJcrti)*
                sin(*(ckt->CKTstates[i] + inst->JJphase));
        }
        return (val);
    }
}


int
JJdev::askInst(const sCKT *ckt, const sGENinstance *geninst, int which,
    IFdata *data)
{
#ifdef WITH_CMP_GOTO
    // Order MUST match parameter definition enum!
    static void *array[] = {
        0, // notused
        &&L_JJ_AREA, 
        &&L_JJ_PI,
        &&L_JJ_OFF,
        &&L_JJ_IC,
        &&L_JJ_ICP,
        &&L_JJ_ICV,
        &&L_JJ_CON,

        &&L_JJ_QUEST_V,
        &&L_JJ_QUEST_CRT,
        &&L_JJ_QUEST_IC,
        &&L_JJ_QUEST_IJ,
        &&L_JJ_QUEST_IG,
        &&L_JJ_QUEST_I,
        &&L_JJ_QUEST_CAP,
        &&L_JJ_QUEST_G0,
        &&L_JJ_QUEST_GN,
        &&L_JJ_QUEST_GS,
        &&L_JJ_QUEST_G1,
        &&L_JJ_QUEST_G2,
        &&L_JJ_QUEST_N1,
        &&L_JJ_QUEST_N2,
        &&L_JJ_QUEST_NP};

    if ((unsigned int)which > JJ_QUEST_NP)
        return (E_BADPARM);
#endif

    const sJJinstance *inst = static_cast<const sJJinstance*>(geninst);

    // Need to override this for non-real returns.
    data->type = IF_REAL;

#ifdef WITH_CMP_GOTO
    void *jmp = array[which];
    if (!jmp)
        return (E_BADPARM);
    goto *jmp;
    L_JJ_AREA:
        data->v.rValue = inst->JJarea;
        return (OK);
    L_JJ_PI:
        data->v.iValue = inst->JJpi;
        return (OK);
    L_JJ_OFF:
        data->type = IF_FLAG;
        data->v.iValue = inst->JJoffGiven;
        return (OK);
    L_JJ_IC:
        data->type = IF_REALVEC;
        data->v.v.vec.rVec = inst->JJinitCnd;
        data->v.v.numValue = 2;
        return (OK);
    L_JJ_ICP:
        data->v.rValue = inst->JJinitPhase;
        return (OK);
    L_JJ_ICV:
        data->v.rValue = inst->JJinitVoltage;
        return (OK);
    L_JJ_CON:
        data->type = IF_INSTANCE;
        data->v.uValue = inst->JJcontrol;
        return (OK);
    L_JJ_QUEST_V:
        data->v.rValue = (ckt->rhsOld(inst->JJposNode) -
            ckt->rhsOld(inst->JJnegNode));
        return (OK);
    L_JJ_QUEST_CRT:
        data->v.rValue = inst->JJcriti;
        return (OK);
    L_JJ_QUEST_IC:
        data->v.rValue = ckt->interp(inst->JJdvdt)*inst->JJcap;
        return (OK);
    L_JJ_QUEST_IJ:
        data->v.rValue = jj_ji(ckt, inst);
        return (OK);
    L_JJ_QUEST_IG:
        data->v.rValue = ckt->interp(inst->JJqpi);
        return (OK);
    L_JJ_QUEST_I:
        data->v.rValue = ckt->interp(inst->JJdvdt)*inst->JJcap +
            jj_ji(ckt, inst) + ckt->interp(inst->JJqpi);
        return (OK);
    L_JJ_QUEST_CAP:
        data->v.rValue = inst->JJcap;
        return (OK);
    L_JJ_QUEST_G0:
        data->v.rValue = inst->JJg0;
        return (OK);
    L_JJ_QUEST_GN:
        data->v.rValue = inst->JJgn;
        return (OK);
    L_JJ_QUEST_GS:
        data->v.rValue = inst->JJgs;
        return (OK);
    L_JJ_QUEST_G1:
        data->v.rValue = inst->JJg1;
        return (OK);
    L_JJ_QUEST_G2:
        data->v.rValue = inst->JJg2;
        return (OK);
    L_JJ_QUEST_N1:
        data->type = IF_INTEGER;
        data->v.iValue = inst->JJposNode;
        return (OK);
    L_JJ_QUEST_N2:
        data->type = IF_INTEGER;
        data->v.iValue = inst->JJnegNode;
        return (OK);
    L_JJ_QUEST_NP:
        data->type = IF_INTEGER;
        data->v.iValue = inst->JJphsNode;
        return (OK);
#else
    switch (which) {
    case JJ_AREA:
        data->v.rValue = inst->JJarea;
        break;
    case JJ_PI:
        data->v.iValue = inst->JJpi;
        break;
    case JJ_OFF:
        data->type = IF_FLAG;
        data->v.iValue = inst->JJoffGiven;
        break;
    case JJ_IC:
        data->type = IF_REALVEC;
        data->v.v.vec.rVec = inst->JJinitCnd;
        data->v.v.numValue = 2;
        break;
    case JJ_ICP:
        data->v.rValue = inst->JJinitPhase;
        break;
    case JJ_ICV:
        data->v.rValue = inst->JJinitVoltage;
        break;
    case JJ_CON:
        data->type = IF_INSTANCE;
        data->v.uValue = inst->JJcontrol;
        break;
    case JJ_QUEST_V:
        data->v.rValue = (ckt->rhsOld(inst->JJposNode) -
            ckt->rhsOld(inst->JJnegNode));
        break;
    case JJ_QUEST_CRT:
        data->v.rValue = inst->JJcriti;
        break;
    case JJ_QUEST_IC:
        data->v.rValue = ckt->interp(inst->JJdvdt)*inst->JJcap;
        break;
    case JJ_QUEST_IJ:
        data->v.rValue = jj_ji(ckt, inst);
        break;
    case JJ_QUEST_IG:
        data->v.rValue = ckt->interp(inst->JJqpi);
        break;
    case JJ_QUEST_I:
        data->v.rValue = ckt->interp(inst->JJdvdt)*inst->JJcap +
            jj_ji(ckt, inst) + ckt->interp(inst->JJqpi);
        break;
    case JJ_QUEST_CAP:
        data->v.rValue = inst->JJcap;
        break;
    case JJ_QUEST_G0:
        data->v.rValue = inst->JJg0;
        break;
    case JJ_QUEST_GN:
        data->v.rValue = inst->JJgn;
        break;
    case JJ_QUEST_GS:
        data->v.rValue = inst->JJgs;
        break;
    case JJ_QUEST_G1:
        data->v.rValue = inst->JJg1;
        break;
    case JJ_QUEST_G2:
        data->v.rValue = inst->JJg2;
        break;
    case JJ_QUEST_N1:
        data->type = IF_INTEGER;
        data->v.iValue = inst->JJposNode;
        break;
    case JJ_QUEST_N2:
        data->type = IF_INTEGER;
        data->v.iValue = inst->JJnegNode;
        break;
    case JJ_QUEST_NP:
        data->type = IF_INTEGER;
        data->v.iValue = inst->JJphsNode;
        break;
    default:
        return (E_BADPARM);
    }
#endif
    return (OK);
}


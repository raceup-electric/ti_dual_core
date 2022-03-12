/*
 *  ======= launch_controller ========
 *  launch_controller target-side implementation
 *
 *  Created on: Mar 5, 2022
 *  Author:     Xhemali
 *  email: xhemali.sheshori1@gmail.com
 */


#include "launch_controller.h"

void launch_control(unsigned long t,double torque[4])
{
    double T_lc1 = p1[LC]*pow(t,7) + p2[LC]*pow(t,6) + p3[LC]*pow(t,5) + p4[LC]*pow(t,4) + p5[LC]*pow(t,3) +p6[LC]*pow(t,2) +  p7[LC]*t + p8[LC];
    double T_lc = 0.5*(T_lc1*(1+tanh(5000*(t1[LC]-t)))+T1[LC]*(1+tanh(5000*(t-t1[LC]))));

    torque[0]=T_lc;
    torque[1]=T_lc;
    torque[2]=T1[LC];
    torque[3]=T1[LC];
}

/*
 * launch_controller.h
 *
 *  Created on: Mar 5, 2022
 *      Author: Xhemali
 *      email: xhemali.sheshori1@gmail.com
 */

#ifndef LAUNCH_CONTROLLER_H_
#define LAUNCH_CONTROLLER_H_

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "F28x_Project.h"

bool is_time_saved = false;
// costanti di funzioni interpolative per parametri dei pneumatici
float LMUX[7] = {1, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4};
double p1[7] = {-167709.21982, -128887.33193, -102973.43698, -21227.406823, -10169.543164, 4702.789202, -122.69393455};
double p2[7] = {250992.51, 202956.27836, 177303.622, 37002.882859, 18756.190367, -14107.845866, -412.41424675};
double p3[7] = {-143804.04127, -122843.78293, -118011.92618, -24456.577, -13079.552283, 15853.433242, 1129.5299741};
double p4[7] = {40602.771041, 36683.244167, 38796.758599, 8044.6453092, 4547.9387097, -8375.0676721 -823.30183881};
double p5[7] = {-5807.4866303, -5558.5974485, -6486.8187203, -1344.9500188, -802.65231003, 2205.8036531, 264.23331923};
double p6[7]  = {394.50001726, 400.01578990, 514.75850004, 108.81048555, 68.83200044, -269.92773412, -36.32269535};
double p7[7]  = {-9.6264785188, -10.40452572, -14.977272811, -3.0569909334, -1.9965152426, 12.592100042, 1.9785504344};
double p8[7] = {0.039393575248, 0.045132982949, 0.071941416147, 0.015311503039, 0.010453215114, -0.094784011717, -0.014306822197};

double nu1 = 1.7977585706847;
double nu2 = 0.000387300865455914;
double nu3 = -3.14517395274217* 1e-6;
double nu4 = 4.64810932510023*1e-9;
double nu5 = -3.5206874715397*1e-12;
double nu6 = 1.31537731918249*1e-15;

double alpha0 = 1;
double alpha1 = 0.000387300865455914;
double alpha2 = -3.14517395274217*1e-6;
double alpha3 = 4.64810932510023*1e-9;
double alpha4 = -3.5206874715397*1e-12;
double alpha5 = 1.31537731918249*1e-15;

//LC = valore di controllo di partenza; 0=grip ideale; 6=grip molto scarso
int LC = 2;// [0, 1, 2, 3, 4, 5, 6]

double t1[7] = {0.49, 0.51, 0.57, 0.63, 0.73, 0.85, 0.91};
double T1[7] = {21, 21, 21,21, 21, 19.5, 16};

extern float posTorqueCandidate[4][4];
extern bool is_launch_inserted;
extern int throttle;
extern int brake;
extern Uint32 time_elapsed;

void launch_control();


#endif /* LAUNCH_CONTROLLER_H_ */

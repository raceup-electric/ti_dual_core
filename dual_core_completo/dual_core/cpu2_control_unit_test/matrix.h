/*
 * matrix.h
 *
 *  Created on: 5 mag 2023
 *      Author: Edp
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "math.h"

int choldc1(double * a, double * p, int n);



void zeros(double * a, int m, int n);

/* C <- A * B */
void mulmat(double * a, double * b, double * c, int arows, int acols, int bcols);

void mulvec(double * a, double * x, double * y, int m, int n);

void mulvecElementWise(double * a, double * b, double *c, int m, int n);

void transpose(double * a, double * at, int m, int n);

/* A <- A + B */
 void accum(double * a, double * b, int m, int n);

/* C <- A + B */
 void add(double * a, double * b, double * c, int n);

/* C <- A - B */
 void sub(double * a, double * b, double * c, int n);

 void negate(double * a, int m, int n);

 void mat_addeye(double * a, int n);

 void mulscal(double * a, double scal, double * b, int m, int n);

 void addscal(double * a, double scal, double *b, int m, int n);

//int choldcsl(double * A, double * a, double * p, int n);
//
//int cholsl(double * A, double * a, double * p, int n);

 double max_vect(double * a, int size);
 double min_vect(double * a, int size);
 double magnitude_squared(double * a, int size);
 double element_sum(double * a, int size);

 double max(double num1, double num2);
 double min(double num1, double num2);
 double saturate(double val, double min, double max);


#endif /* MATRIX_H_ */

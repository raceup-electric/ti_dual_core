/*
 * matrix.h
 *
 *  Created on: 5 mag 2023
 *      Author: Edp
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "math.h"

static int choldc1(double * a, double * p, int n);



static void zeros(double * a, int m, int n);

/* C <- A * B */
static void mulmat(double * a, double * b, double * c, int arows, int acols, int bcols);

static void mulvec(double * a, double * x, double * y, int m, int n);

static void transpose(double * a, double * at, int m, int n);

/* A <- A + B */
static void accum(double * a, double * b, int m, int n);

/* C <- A + B */
static void add(double * a, double * b, double * c, int n);

/* C <- A - B */
static void sub(double * a, double * b, double * c, int n);

static void negate(double * a, int m, int n);

static void mat_addeye(double * a, int n);

//int choldcsl(double * A, double * a, double * p, int n);
//
//int cholsl(double * A, double * a, double * p, int n);


#endif /* MATRIX_H_ */

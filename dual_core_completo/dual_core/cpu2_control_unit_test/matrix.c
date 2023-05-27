/*
 * matrix.c
 *
 *  Created on: 5 mag 2023
 *      Author: Edp
 */

#include "matrix.h"

 int choldc1(double * a, double * p, int n) {
    int i,j,k;
    double sum;

    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            sum = a[i*n+j];
            for (k = i - 1; k >= 0; k--) {
                sum -= a[i*n+k] * a[j*n+k];
            }
            if (i == j) {
                if (sum <= 0) {
                    return 1; /* error */
                }
                p[i] = sqrt(sum);
            }
            else {
                a[j*n+i] = sum / p[i];
            }
        }
    }

    return 0; /* success */
}

 int choldcsl(double * A, double * a, double * p, int n)
{
    int i,j,k; double sum;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i*n+j] = A[i*n+j];
    if (choldc1(a, p, n)) return 1;
    for (i = 0; i < n; i++) {
        a[i*n+i] = 1 / p[i];
        for (j = i + 1; j < n; j++) {
            sum = 0;
            for (k = i; k < j; k++) {
                sum -= a[j*n+k] * a[k*n+i];
            }
            a[j*n+i] = sum / p[j];
        }
    }

    return 0; /* success */
}


 int cholsl(double * A, double * a, double * p, int n)
{
    int i,j,k;
    if (choldcsl(A,a,p,n)) return 1;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            a[i*n+j] = 0.0;
        }
    }
    for (i = 0; i < n; i++) {
        a[i*n+i] *= a[i*n+i];
        for (k = i + 1; k < n; k++) {
            a[i*n+i] += a[k*n+i] * a[k*n+i];
        }
        for (j = i + 1; j < n; j++) {
            for (k = j; k < n; k++) {
                a[i*n+j] += a[k*n+i] * a[k*n+j];
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            a[i*n+j] = a[j*n+i];
        }
    }

    return 0; /* success */
}

 void zeros(double * a, int m, int n)
{
    int j;
    for (j=0; j<m*n; ++j)
        a[j] = 0;
}


/* C <- A * B */
 void mulmat(double * a, double * b, double * c, int arows, int acols, int bcols)
{
    int i, j,l;

    for(i=0; i<arows; ++i)
        for(j=0; j<bcols; ++j) {
            c[i*bcols+j] = 0;
            for(l=0; l<acols; ++l)
                c[i*bcols+j] += a[i*acols+l] * b[l*bcols+j];
        }
}

 void mulvec(double * a, double * x, double * y, int m, int n)
{
    int i, j;

    for(i=0; i<m; ++i) {
        y[i] = 0;
        for(j=0; j<n; ++j)
            y[i] += x[j] * a[i*n+j];
    }
}

void mulvecElementWise(double * a, double * b, double *c, int m, int n) {

int j;
for(j=0; j<m*n; j++)
      c[j] = b[j]*a[j];

}

 void transpose(double * a, double * at, int m, int n)
{
    int i,j;

    for(i=0; i<m; ++i)
        for(j=0; j<n; ++j) {
            at[j*m+i] = a[i*n+j];
        }
}

/* A <- A + B */
 void accum(double * a, double * b, int m, int n)
{
    int i,j;

    for(i=0; i<m; ++i)
        for(j=0; j<n; ++j)
            a[i*n+j] += b[i*n+j];
}

/* C <- A + B */
 void add(double * a, double * b, double * c, int n)
{
    int j;

    for(j=0; j<n; ++j)
        c[j] = a[j] + b[j];
}


/* C <- A - B */
 void sub(double * a, double * b, double * c, int n)
{
    int j;

    for(j=0; j<n; ++j)
        c[j] = a[j] - b[j];
}

 void negate(double * a, int m, int n)
{
    int i, j;

    for(i=0; i<m; ++i)
        for(j=0; j<n; ++j)
            a[i*n+j] = -a[i*n+j];
}

 void mat_addeye(double * a, int n)
{
    int i;
    for (i=0; i<n; ++i)
        a[i*n+i] += 1;
}

void mulscal(double * a, double scal, double *b, int m, int n) {

 int j;
 for(j=0; j<m*n; j++)
         b[j] = scal*a[j];

}

void addscal(double * a, double scal, double *b, int m, int n) {

 int j;
 for(j=0; j<m*n; j++)
         b[j] = scal+a[j];

}

double max_vect(double * a, int size){
    int i;
    double temp = a[0];
    for (i=0; i<size; ++i)
    {
        if (a[i] > temp)
            temp = a[i];
    }
    return temp;
}

double min_vect(double * a, int size){
    int i;
    double temp = a[0];
    for (i=0; i<size; ++i)
    {
        if (a[i] < temp)
            temp = a[i];
    }
    return temp;
}

double magnitude_squared(double * a, int size){
    int i;
    double tot = 0;
    for (i=0; i<size; ++i)
    {
        tot += pow(a[i], 2);
    }
    return tot;
}

double element_sum(double* a, int size){
    int i;
    double tot = 0;
    for (i=0; i<size; ++i)
    {
        tot += a[i];
    }
    return tot;
}



double max(double num1, double num2){

    if(num1>num2)
        return num1;
    return num2;

}

double min(double num1, double num2){

    if(num1>num2)
        return num2;
    return num1;

}


double saturate(double val, double min, double max){

    if(val>max)
        return max;
    if(val<min)
        return min;
    return val;

}

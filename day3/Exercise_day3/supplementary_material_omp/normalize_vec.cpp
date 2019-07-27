{\rtf1\ansi\ansicpg1252\cocoartf1671\cocoasubrtf400
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <cstdlib>\
#include <cmath>\
\
#include <omp.h>\
\
// function to compute the 2-norm of a vector v of length n\
double norm(double *v, int n)\{\
    double norm = 0.;\
\
    for(int i=0; i<n; i++)\
        norm += v[i]*v[i];\
\
    return sqrt(norm);\
\}\
\
// initialise v to values between -10 and 10\
void initialize(double *v, int n)\{\
    for(int i=0; i<n; i++)\
        v[i] = cos(double(i)) * 10.;\
\}\
\
\
void normalize_vector(double *v, int n)\{\
    double norm = 0.;\
\
    // compute the norm of v\
    for(int i=0; i<n; i++)\
        norm += v[i]*v[i];\
    norm = sqrt(norm);\
\
    // normalize v\
    for(int i=0; i<n; i++)\
        v[i] /= norm;\
\}\
\
void normalize_vector_omp(double *v, int n)\
\{\
    double norm = 0.;\
\
    #pragma omp parallel for reduction(+:norm)\
    // compute the norm of v\
    for(int i=0; i<n; i++)\
    \{\
        norm += v[i]*v[i];\
    \}\
    norm = sqrt(norm);\
    #pragma omp parallel shared(norm)\
    \{\
    //inside = omp_get_num_threads();\
\
    #pragma omp for\
    // normalize v\
    for(int i=0; i<n; i++) \{\
        v[i] /= norm;\
    \}\
    \}\
\}\
\
int main( void )\{\
    const int N = 40000000;\
    double *v = (double*)malloc(N*sizeof(double));\
    bool validated = false;\
\
    initialize(v, N);\
    double time_serial = -omp_get_wtime();\
    normalize_vector(v, N);\
    time_serial += omp_get_wtime();\
\
    // chck the answer\
    std::cout << "serial error   : " << fabs(norm(v,N) - 1.) << std::endl;\
\
    int max_threads = omp_get_max_threads();\
    initialize(v, N);\
    double time_parallel = -omp_get_wtime();\
    normalize_vector_omp(v, N);\
    time_parallel += omp_get_wtime();\
\
    // chck the answer\
    std::cout << "parallel error : " << fabs(norm(v,N) - 1.) << std::endl;\
\
    std::cout << max_threads     << " threads" << std::endl;\
    std::cout << "serial     : " << time_serial << " seconds\\t"\
              << "parallel   : " << time_parallel <<  " seconds" << std::endl;\
    std::cout << "speedup    : " << time_serial/time_parallel << std::endl;\
    std::cout << "efficiency : " << (time_serial/time_parallel)/double(max_threads) << std::endl;\
\
    free(v);\
    return 0;\
\}}
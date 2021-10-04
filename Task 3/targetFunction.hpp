#ifndef TARGETFUNCTION_H
#define TARGETFUNCTION_H
#include "subRoutines.hpp"

/*

f(t, y, y')  =  m * y''(t)  +  c * y'(t)  +  k * y(t)  =  F(t)

F(t)  =  a_1*sin(w_1*t) + a_2*sin(w_2*t) + a_3*sin(w_3*t)

y'(0)  =  y(0)  =  0.0



y''(t)  =  f(t, y(t), y'(t))  =  (F(t) - (c * y'(t)  +  k * y(t))) / m

*/

double F(double t, double a_1, double a_2, double a_3, double w_1, double w_2, double w_3){
    return a_1*sin(w_1*t) + a_2*sin(w_2*t) + a_3*sin(w_3*t);
}

double f(double y_k, double dy_k, double F, double m, double c, double k){
    return (F - (c*dy_k  +  k*y_k)) / m;
}



#endif




#ifndef NLSYSTEM_H
#define NLSYSTEM_H
#include "subRoutines.hpp"
/*
NL equation system:

2*(c_3)**2  +  (c_2)**2  +  6*(c_4)**2  - 1.0  =  0
8* (c_3)**3  +  6*(c_3)* (c_2)**2  +  36*(c_3)*(c_2)*(c_4)  +  108*(c_3)* (c_4)**2  - theta_1  =  0
60* (c_3)**4  +  60* (c_3)**2 * (c_2)**2  +  576* (c_3)**2 *(c_3)*(c_4)  +  2232* (c_3)**2 *(c_4)**2  +  252* (c_4)**2 *(c_2)**2  +  1296* (c_4)**3 *(c_2)  +  3348* (c_4)**4  +  24* (c_2)**3 *(c_4)  +  3*(c_2)  - theta_2  =  0


Jacobian (variables: c_2(x), c_3(y), c_4(z))

{ {  2*(c_2),  4*(c_3),  12*(c_4)  },

  {  12*(c_3)*(c_2 + 3*c_4),  
  6*(c_2**2 + 6*c_2*c_4 + 4*c_3**2 + 18*c_4**2),  
  36*c_3*(c_2 + 6*c_4)  },

  {  3 + 120 x y^2 + 72 x^2 z + 576 y^2 z + 504 x z^2 + 1296 z^3, 
  120 x^2 y + 240 y^3 + 1152 x y z + 4464 y z^2, 
  24 x^3 + 576 x y^2 + 504 x^2 z + 4464 y^2 z + 3888 x z^2 + 13392 z^3}
}

*/

double equation1(double &c_2, double &c_3, double &c_4){
    return    2 * pow(c_3, 2.0)  
            +     pow(c_2, 2.0)  
            + 6 * pow(c_4, 2.0)  
            -  1.0;
}

double equation2(double &c_2, double &c_3, double &c_4, double &theta_1){
    return      8 * pow(c_3, 3.0)
            +   6 * (c_3) * pow(c_2, 2.0)  
            +  36 * (c_3) * (c_2) * (c_4)  
            + 108 * (c_3) * pow(c_4, 2.0)  
            -  theta_1;
}

double equation3(double &c_2, double &c_3, double &c_4, double &theta_2){   
    return      60 * pow(c_3, 4.0)
            +   60 * pow(c_3, 2.0) * pow(c_2, 2.0)
            +  576 * pow(c_3, 2.0) * (c_2) * (c_4)
            + 2232 * pow(c_3, 2.0) * pow(c_4, 2.0)
            +  252 * pow(c_4, 2.0) * pow(c_2, 2.0)
            + 1296 * pow(c_4, 3.0) * (c_2)  
            + 3348 * pow(c_4, 4.0)
            +   24 * pow(c_2, 3.0) * (c_4)
            +    3 * (c_2)  
            -  theta_2;
}


Vec NLFunction(double &c_2, double &c_3, double &c_4, double &theta_1, double &theta_2){
    Vec f(3, 0.0);

    f[0] = equation1(c_2, c_3, c_4);
    f[1] = equation2(c_2, c_3, c_4, theta_1);
    f[2] = equation3(c_2, c_3, c_4, theta_2);

    return f;
}


Mat NLJacobian(double &c_2, double &c_3, double &c_4){
    Mat jacobian(3, Vec(3, 0.0));
    
    // first equation
    jacobian[0][0] = 2*(c_2);
    jacobian[0][1] = 4*(c_3);
    jacobian[0][2] = 12*(c_4);
    // second equation
    jacobian[1][0] = 12*(c_3)*(c_2 + 3*c_4);
    jacobian[1][1] = 6*(pow(c_2, 2.0) + 6*c_2*c_4 + 4*pow(c_3, 2.0) + 18*pow(c_4, 2.0));
    jacobian[1][2] = 36*c_3*(c_2 + 6*c_4);
    // third equation
    jacobian[2][0] = 3 + 120*c_2*pow(c_3, 2.0) + 72*pow(c_2, 2.0)*c_4 + 576*pow(c_3, 2.0)*c_4 + 504*c_2*pow(c_4, 2.0) + 1296*pow(c_4, 3.0);
    jacobian[2][1] = 120*pow(c_2, 2.0)*c_3 + 240*pow(c_3, 3.0) + 1152*(c_2)*(c_3)*(c_4) + 4464*(c_3)*pow(c_4, 2.0);
    jacobian[2][2] = 24*pow(c_2, 3.0) + 576*(c_2)*pow(c_3, 2.0) + 504*pow(c_2, 2.0)*(c_4) + 4464*pow(c_3, 2.0)*(c_4) + 3888*(c_2)*pow(c_4, 2.0) + 13392*pow(c_4, 3.0);

    return jacobian;
}

#endif




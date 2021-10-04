#include "targetFunction.hpp"
#include "subRoutines.hpp"

basicResult result_dre;

/* first order derivative approximation */
double richardExtrapolation(double &x, double &delta1, double &delta2, Vec &c){

    double d1, d2, q;
    double in1 = x + delta1;
    double in2 = x + delta2;
    d1 = (targetF(in1, c[0], c[1], c[2], c[3]) - targetF(x, c[0], c[1], c[2], c[3])) / delta1;
    d2 = (targetF(in2, c[0], c[1], c[2], c[3]) - targetF(x, c[0], c[1], c[2], c[3])) / delta2;
    
    // assuming p=1
    // q = delta1 / delta2 -> q^-1 is equal to (delta2 / delta1)
    return d1 + (d1 - d2)/(delta2/delta1 - 1);

}


basicResult mainDerivativeRE(double &a, double &delta1, double &delta2, Vec &constants){
    std::cout << "Richard Extrapolation Derivative selected." << std::endl;
    if(delta1 != 0  &&  delta2 != 0){
        result_dre.estimate = richardExtrapolation(a, delta1, delta2, constants);
    }else{
        std::cout << "." << std::endl;
        result_dre.errors.push_back("DELTA VALUES CANNOT BE ZERO");
    }

    

    return result_dre;

}




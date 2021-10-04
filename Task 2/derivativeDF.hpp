#include "targetFunction.hpp"
#include "subRoutines.hpp"

basicResult result_ddf;

double forwardDiff(double &x, double &delta, Vec &c){
    double in_arg = x + delta;
    return (targetF(in_arg, c[0], c[1], c[2], c[3]) - targetF(x, c[0], c[1], c[2], c[3])) / delta;
}

double backwardDiff(double &x, double &delta, Vec &c){
    double in_arg = x - delta;
    return (targetF(x, c[0], c[1], c[2], c[3]) - targetF(in_arg, c[0], c[1], c[2], c[3])) / delta;
}

double centralDiff(double &x, double &delta, Vec &c){
    double in_arg1 = x + delta;
    double in_arg2 = x - delta;
    return (targetF(in_arg1, c[0], c[1], c[2], c[3]) - targetF(in_arg2, c[0], c[1], c[2], c[3])) / (2.0 * delta);
}


basicResult mainDerivativeDF(int &SUBCOD, double &a, double &delta, Vec &constants){
    
    if(delta == 0){
        std::cout << "Invalid delta. Quitting..." << std::endl;
        result_ddf.errors.push_back("INVALID DELTA: "+std::to_string(delta));
    }else{
        if(SUBCOD == 1){
            std::cout << "Forward Derivative selected." << std::endl;
            result_ddf.estimate = forwardDiff(a, delta, constants);
        }else if(SUBCOD == 2){
            std::cout << "Backward Derivative selected." << std::endl;
            result_ddf.estimate = backwardDiff(a, delta, constants);
        }else if(SUBCOD == 3){
            std::cout << "Central Derivative selected." << std::endl;
            result_ddf.estimate = centralDiff(a, delta, constants);
        }else{
            std::cout << "Invalid sub-method. Quitting..." << std::endl;
            result_ddf.errors.push_back("INVALID SUBCOD ("+std::to_string(SUBCOD)+") FOR DERIVATIVE ICOD.");
        }
    }

    

    return result_ddf;

}




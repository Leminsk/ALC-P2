#include "targetFunction.hpp"
#include "subRoutines.hpp"

basicResult result_root;

/* Newton-Rhapson Root, c is a vector of constants */
double newtonRoot(double &a, double &b, double &TOLm, Vec &c){
    // initial approximation
    double x_k = (a+b)/2;
    double new_x_k;
    double tol_k;
    int max_iter = 1e6;

    size_t i;
    for(i=0;  fabs(b-a) > TOLm  &&  i < max_iter;  ++i){
        new_x_k = x_k  -  targetF(x_k, c[0], c[1], c[2], c[3]) / dF(x_k, c[0], c[1], c[2], c[3]);

        tol_k = fabs(new_x_k - x_k);
        if(tol_k < TOLm){
            std::cout << "Convergence by TOLm reached after " << i << " iterations." << std::endl;
            // save x_k
            return new_x_k;
        }
        x_k = new_x_k;

    }

    std::cout << "WARNING: convergence not reached" << std::endl;
    result_root.errors.push_back("CONVERGENCE NOT REACHED ON NEWTON'S METHOD.\nMAXIMUM NUMBER OF ITERATIONS ("+ std::to_string(max_iter) +") EXCEEDED.");
    return 0;

}

/* Bisection Root, c is a vector of constants */
double bisectionRoot(double &a, double &b, double &TOLm, Vec &c){
    double x_i;
    double f_i;

    size_t i;
    for(i=0; fabs(b-a) > TOLm; ++i){
        x_i = (a+b) / 2.0;
        f_i = targetF(x_i, c[0], c[1], c[2], c[3]);

        if(f_i > 0.0){
            b = x_i;
        }else{
            a = x_i;
        }

    }

    std::cout << "Bisection done after " << std::to_string(i) << " iterations." << std::endl;
    return x_i;
}



basicResult mainRoot(int &SUBCOD, double &a, double &b, double &TOLm, Vec &constants){
    
    if(SUBCOD == 2){
        std::cout << "Newton-Rhapson Root selected." << std::endl;
        result_root.estimate = newtonRoot(a, b, TOLm, constants);
    }else if(SUBCOD == 1){
        std::cout << "Bisection Root selected." << std::endl;
        result_root.estimate = bisectionRoot(a, b, TOLm, constants);
    }else{
        std::cout << "Invalid sub-method. Quitting..." << std::endl;
        result_root.errors.push_back("INVALID SUBCOD ("+std::to_string(SUBCOD)+") FOR ROOT ICOD.");
    }

    return result_root;

}





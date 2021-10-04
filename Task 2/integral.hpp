#include "targetFunction.hpp"
#include "subRoutines.hpp"

basicResult result_integral;

/* Polynomial Quadrature by Trapezoidal Rule 
   (which is probably not a very bright idea trying to approximate a exponential function) */
double polynomialQuadrature(double a, double b, int N, Vec &c){
    
    double L = (b - a) / (double)N;
    double result = targetF(a, c[0], c[1], c[2], c[3]) / 2.0;
    double in_arg;

    for(int i=0; i<N; ++i){
        in_arg = (a + i*L);
        result += 2 * targetF(in_arg, c[0], c[1], c[2], c[3]);
        std::cout << "result: " << result << std::endl;
    }
  
    result *= L / 2.0;

    return result;

}

/* Gauss Legendre Quadrature */
double gaussQuadrature(double &a, double &b, int &N, Vec &c){
    
    double L = b - a;
    Vec abscissas(N, 0.0);
    Vec f_values(N, 0.0);
    double result = 0.0;

    for(int i=0; i<N; ++i){
        // get z_i pre-calculated
        abscissas[i] = ( a + b + (weights_abscissas[N-1][1][i])*L ) / 2.0;
        f_values[i] = targetF(abscissas[i], c[0], c[1], c[2], c[3]);
        
        // get w_i pre-calculated
        result +=  weights_abscissas[N-1][0][i] * f_values[i]; 
        std::cout << "result: " << result << std::endl;
        
    }

    result *=  L / 2.0;

    return result;

}


basicResult mainIntegral(int &SUBCOD, double &a, double &b, int &sample_points, Vec &constants){
    
    if(SUBCOD == 2){
        std::cout << "Polynomial Quadrature Integral selected." << std::endl;
        result_integral.estimate = polynomialQuadrature(a, b, sample_points, constants);
    }else if(SUBCOD == 1){
        std::cout << "Gauss-Legendre Quadrature Integral selected." << std::endl;
        result_integral.estimate = gaussQuadrature(a, b, sample_points, constants);
    }else{
        std::cout << "Invalid sub-method. Quitting..." << std::endl;
        result_integral.errors.push_back("INVALID SUBCOD ("+std::to_string(SUBCOD)+") FOR INTEGRAL ICOD.");
    }

    return result_integral;

}





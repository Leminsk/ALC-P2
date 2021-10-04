#include "subRoutines.hpp"
#include "NLSystem.hpp"

NewtonBroydenResult result_broyden;


bool broydenMethod(double &theta_1, double &theta_2, int order, double &tol){
    // initial solution (x_0: c_2, c_3, c_4)
    Vec x_k = {1.0, 0.0, 0.0};
    // initial exact Jacobian
    Mat B_k = NLJacobian(x_k[0], x_k[1], x_k[2]);

    Vec F(3, 0.0);
    Vec F_new(3, 0.0);
    Vec y_k(3, 0.0);

    Mat J(3, Vec(3, 0.0));
    Mat inv_J(3, Vec(3, 0.0));
    Vec delta_X(3, 0.0);

    Vec product(3, 0.0);
    Vec numerator(3, 0.0);

    double scalar;
    double tol_k = 0.0;
    int max_iter = 1e6;
    bool inv_ok_status;

    for(size_t i=0; i<max_iter; ++i){
        J = B_k;
        F = NLFunction(x_k[0], x_k[1], x_k[2], theta_1, theta_2);
        inv_ok_status = inverse(J, inv_J, order);
        if(!inv_ok_status){
            result_broyden.errors.push_back( "Could not calculate inverse of J at iteration "+std::to_string(i)+". Exiting..." );
            return false;
        }
        // new delta_X
        productMatrixVector(inv_J, F, delta_X);

        // new x_k
        subtractVec(x_k, delta_X, x_k); 

        F_new = NLFunction(x_k[0], x_k[1], x_k[2], theta_1, theta_2);
        // new y_k
        subtractVec(F_new, F, y_k);

        tol_k = absVec(delta_X) / absVec(x_k);
        
        if(tol_k < tol){
            std::cout << "Convergence by TOLm reached." << std::endl;
            // save x_k
            result_broyden.solution = x_k;
            return true;
        }else{
            // new B_k
            productMatrixVector(B_k, delta_X, product);
            subtractVec(y_k, product, numerator);
            scalar = dotProduct(numerator, delta_X) / dotProduct(delta_X, delta_X);
            addScalarToMatrix(B_k, scalar);
        }

    }

    std::cout << "WARNING: convergence not reached" << std::endl;
    result_broyden.errors.push_back("CONVERGENCE NOT REACHED ON BROYDEN'S METHOD.\nMAXIMUM NUMBER OF ITERATIONS ("+ std::to_string(max_iter) +") EXCEEDED.");
    return false;

}


NewtonBroydenResult mainBroydenMethod(double &theta_1, double theta_2, double &TOLm){
    std::cout << "Broyden's Method selected." << std::endl;

    broydenMethod(theta_1, theta_2, 3, TOLm);

    return result_broyden;
}




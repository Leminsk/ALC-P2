#include "subRoutines.hpp"
#include "targetFunction.hpp"


/* 

  y_k = 0
  dy_k = 0

  K1 = f(t_k, y_k, dy_k) * h / 2
  Q = (dy_k + K1/2) * h / 2

  K2 = f(t_k + h/2, y_k + Q, dy_k + K1) * h / 2
  K3 = f(t_k + h/2, y_k + Q, dy_k + K2) * h / 2

  L = (dy_k + K3) * h
  K4 = f(t_k + h, y_k + L, dy_k + 2K3) * h / 2


  y_k =   y_k  +  delta * (x_k' + (K1 + K2 + K3)/3)
  dy_k' = dy_k + (K1 + 2K2 + 2K3 + K4)/3


*/

void miniPrint(std::vector< std::vector<double> > &v){

  std::cout << "Time, Displacement, Velocity, Acceleration" << std::endl;

  for(size_t i=0; i<v.size(); ++i){
    for(size_t j=0; j<v[i].size()-1; ++j){
      std::cout << v[i][j] << ", ";
    }
    std::cout << v[i][v[i].size()-1] << std::endl;
  }

}


std::vector< std::vector<double> > rungeKuttaNystrom(double h, double t_f, 
                       double m, double c, double k, 
                       double a_1, double a_2, double a_3,
                       double w_1, double w_2, double w_3){
    // initial conditions       
    double y_k = 0;
    double dy_k = 0;
    double K1, K2, K3, K4, Q, L;
    double t_k = 0;
    double d2y_k = 0;

    std::vector<double> current_value = {t_k, y_k, dy_k, d2y_k};

    std::vector< std::vector<double> > result;
    result.push_back(current_value);

    for(size_t i=0; i*h < t_f; ++i){
      t_k = i*h;

      K1 = f(y_k, dy_k, F(t_k, a_1, a_2, a_3, w_1, w_2, w_3), m, c, k) * h / 2;
      Q = (dy_k + K1/2) * h / 2;

      K2 = f(y_k + Q, dy_k + K1, F(t_k + h/2, a_1, a_2, a_3, w_1, w_2, w_3), m, c, k) * h / 2;
      K3 = f(y_k + Q, dy_k + K2, F(t_k + h/2, a_1, a_2, a_3, w_1, w_2, w_3), m, c, k) * h / 2;
    
      L = (dy_k + K3) * h;
      K4 = f(y_k + L, dy_k + 2*K3, F(t_k + h, a_1, a_2, a_3, w_1, w_2, w_3), m, c, k) * h / 2;


      y_k = y_k  +  h * (dy_k + (K1 + K2 + K3)/3);
      dy_k = dy_k + (K1 + 2*K2 + 2*K3 + K4)/3;
      d2y_k = f(y_k, dy_k, F(t_k + h, a_1, a_2, a_3, w_1, w_2, w_3), m, c, k);

      current_value = {t_k+h, y_k, dy_k, d2y_k};
      result.push_back(current_value);

    }
    

    //miniPrint(result);
    return result;

}

RKNResult mainRKN(double &step, double &time, std::vector< std::vector<double> > &constants){
    std::vector< std::vector<double> > data;
    data = rungeKuttaNystrom(step, time, 
                    constants[0][0], constants[0][1], constants[0][2],
                    constants[1][0], constants[1][1], constants[1][2],
                    constants[2][0], constants[2][1], constants[2][2]);

    RKNResult result;
    result.data = data;

    return result;

}
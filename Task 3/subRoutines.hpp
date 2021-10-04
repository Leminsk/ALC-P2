#ifndef SUBROUTINES_H
#define SUBROUTINES_H

#include <vector>
#include <iostream>
#include <math.h>
#include <float.h> 
#include <cmath>
#include <limits>
#include <iomanip>
#include <random>
#include <ctime>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// making life a bit simpler
typedef std::vector<double> Vec;
typedef std::vector<Vec> Mat;

struct generalResult{
    std::vector< std::string > errors;
    double determinant;
};

struct iterativeResult{
    std::vector< std::string > errors;
    int total_iterations = 0;
    std::vector<double> TOL_history;
};

struct basicResult{
    double estimate;
    std::vector< std::string > errors;
};

struct NewtonBroydenResult{
    std::vector< std::string > errors;
    Vec solution = {0.0, 0.0, 0.0}; // c_2, c_3, c_4
};

struct RKNResult{
    std::vector< std::vector<double> > data;
    std::vector< std::string > error;
};

/* adds value s to every element of A */
void addScalarToMatrix(Mat &A, double s){
    for(size_t i=0; i<A.size(); ++i){
        for(size_t j=0; j<A[i].size(); ++j){
            A[i][j] += s;
        }
    }
}

/* returns the magnetude(Euclidean norm) of a vector of doubles */
double absVec(Vec &v){
    double square_sum = 0;
    for(size_t i=0; i<v.size(); ++i){
        square_sum  += v[i]*v[i];
    }
    return sqrt(square_sum);
}

/* subtracts values from v by the respective u element and stores in a third vector result (result = v - u) */
void subtractVec(Vec &v, Vec &u, Vec &result){
    for(size_t i=0; i<v.size(); ++i){
        result[i] = v[i] - u[i];
    }
}

/* returns dot product between v and u */
double dotProduct(Vec &v, Vec &u){
    double product = 0.0;
    for(size_t i=0; i<v.size(); ++i){
        product += v[i]*u[i];
    }
    return product;
}

/* returns a vector cross product between v and u ONLY FOR VEC OF SIZE 3 */
Vec crossProductSize3(Vec &v, Vec &u){
    Vec result(3, 0.0);
    result[0] =   v[1] * u[2] - v[2] * u[1];
    result[1] = -(v[0] * u[2] - v[2] * u[0]);
    result[2] =   v[0] * u[1] - v[1] * u[0];
    return result;
}

/* multiplies two matrices and stores in a third matrix */
void productMatrices(Mat &A, Mat &B, Mat &result){
    size_t A_rows = A.size();
    size_t A_columns = A[0].size();
    size_t B_rows = B[0].size();

    for(size_t j=0; j<B_rows; ++j){
        for(size_t i=0; i<A_rows; ++i){

            result[i][j] = 0;
            for(size_t k=0; k<A_columns; ++k){
                result[i][j] += A[i][k] * B[k][j];
            }

        }
    }

}

/* multiplies a matrix and a vector and stores the result in another vector */
void productMatrixVector(Mat &A, Vec &B, Vec &result){
    size_t A_rows = A.size();
    size_t A_columns = A[0].size();

    for(size_t i=0; i<A_rows; ++i){

        result[i] = 0;
        for(size_t k=0; k<A_columns; ++k){
            result[i] += A[i][k] * B[k];
        }

    }

}

/* inverts lower triangular matrix and stores in another matrix */
void invertLowerMat(Mat &L, Mat &L_inv){

    size_t L_rows = L.size();
    double sum;
    for (size_t i=0; i<L_rows; ++i){

        L_inv[i][i] = 1/L[i][i];
        for (size_t j=0; j<i; ++j){

            sum = 0;
            for (size_t k=j; k<i; ++k){
                sum += L[i][k] * L_inv[k][j];
            }

            L_inv[i][j] = -sum * L_inv[i][i];
        }

    }

}


/* used by determinantOfMatrix */
void subMatrix(Mat &A, Mat &temp, int p, int q, int order) {
   int i = 0, j = 0;
   // filling the sub matrix
   for (int row = 0; row < order; row++) {
      for (int col = 0; col < order; col++) {
         // skipping if the current row or column is not equal to the current
         // element row and column
         if (row != p && col != q) {
            temp[i][j++] = A[row][col];
            if (j == order - 1) {
               j = 0;
               i++;
            }
         }
      }
   }
}

/* calculates determinant of A by subdividing the matrix recursively */
double determinantOfMatrix(Mat &A, int order) {
   double determinant = 0;
   if (order == 1) {
      return A[0][0];
   }
   if (order == 2) {
      return (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
   }
   Mat temp(order, Vec(order, 0.0));
   double sign = 1;
   for (int i = 0; i < order; i++) {
      subMatrix(A, temp, 0, i, order);
      determinant += sign * A[0][i] * determinantOfMatrix(temp, order - 1);
      sign = -sign;
   }
   return determinant;
}

// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void getCofactor(Mat &A, Mat &temp, int &p, int &q, int &order){
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < order; row++){
        for (int col = 0; col < order; col++){
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q){
                temp[i][j++] = A[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == order - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }

}

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(Mat &A, Mat &adj, int &order){
    if (order == 1){
        adj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    int sign = 1;
    Mat temp(order, Vec(order, 0.0));
 
    for (int i=0; i<order; i++){
        for (int j=0; j<order; j++){
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, order);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
 
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinantOfMatrix(temp, order-1));
        }
    }

}

// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(Mat &A, Mat &inverse, int order){
    // Find determinant of A[][]
    int det = determinantOfMatrix(A, order);
    if (det == 0){
        std::cout << "Singular matrix, can't find its inverse" << std::endl;
        return false;
    }
 
    // Find adjoint
    Mat adj(order, Vec(order, 0.0));
    adjoint(A, adj, order);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<order; i++)
        for (int j=0; j<order; j++)
            inverse[i][j] = adj[i][j]/float(det);
 
    return true;
}


/* Check if matrix A is diagonally dominant. */
bool diagonallyDominant(Mat &A, int &order){

    for(size_t i=0; i<order; ++i){

        double row_summation = 0;
        double column_summation = 0;
        for(size_t j=0; j<order; ++j){
            if( j!=i ){
                row_summation += std::abs(A[i][j]);
                column_summation += std::abs(A[j][i]);
            }
        }

        if(A[i][i] < row_summation || A[i][i] < column_summation){
            return false;
        }

    }

    // if the loop completes, A is diagonal dominant
    return true;

}

/* calculates determinant of matrix A(=LU) by multiplying the determinant of L by the determinant of U */
double calculateLUDeterminant(Mat &L, Mat &U, int &order){
    double L_determinant = 1;
    double U_determinant = 1;
    for(size_t i=0; i<order; ++i){
        L_determinant *= L[i][i];
        U_determinant *= U[i][i];
    }

    return L_determinant * U_determinant;
}

/* calculates determinant of A based on its eigenvalues */
double eigenDeterminant(Mat &A, Vec &values, int &order){
    double A_det = 1;
    for(size_t i=0; i<order; ++i){
        A_det *= values[i];
    }
    return A_det;
}

/* check if matrix is symmetric */
bool symmetricMatrix(Mat &A){
    int rows = A.size();
    int columns = A[0].size();

    for(size_t i=0; i<rows; ++i){
        for(size_t j=i+1; j<columns; ++j){
            if(A[i][j] != A[j][i]){
                return false;
            }
        }
    }
    return true;

}

/* returns the phi value based on indices of elements of matrix */
double phiAngle(Mat &A, int &i, int &j){

    if(A[i][i] == A[j][j]){
        return M_PI/4;
    }else{
        return atan(  (2 * A[i][j]) / (A[i][i] - A[j][j])  ) / 2; 
    }

}


/* returns a copy transposed of matrix A */
Mat transposeMatrix(Mat &A){
    int rows = A.size();
    int columns = A[0].size();
    Mat result(rows, Vec(columns, 0.0));

    for(size_t i=0; i<rows; ++i){
        result[i][i] = A[i][i];
        for(size_t j=i+1; j<columns; ++j){
            result[i][j] = A[j][i];
            result[j][i] = A[i][j];
        }
    }

    return result;

}

/* creates an identity matrix based on given order */
Mat basicIdentity(int order){
    Mat I(order, Vec(order, 0.0));

    for(size_t i=0; i<order; ++i){
        I[i][i] = 1;
    }

    return I;
}



/* solvig for Y in LY = B (Y being equal to UX) */
void forwardSubstitution(Mat &L, Vec &B, Vec &Y, int &order){
    std::cout << "forward substitution..." << std::endl;

    Y[0] = B[0] / L[0][0];
    for(int i=1; i<order; ++i){
        Y[i] = B[i];

        // only the lower triangle
        for(int j=0; j<=i-1; ++j){
            Y[i] -= L[i][j] * Y[j];
        }

        Y[i] /= L[i][i];
    }

    std::cout << "matrix Y: " << std::endl;
    for(size_t i=0; i<order; ++i){
        std::cout << ", " << std::setprecision(9) << Y[i];
    }
    std::cout << std::endl;

}

/* solving for X in UX = Y (assuming Y has already been calculated) */
void backwardSubstitution(Mat &U, Vec &Y, Vec &X, int &order){
    std::cout << "backward substitution..." << std::endl;

    X[order-1] = Y[order-1] / U[order-1][order-1];
    for(int i=order-2; i>=0; --i){
        X[i] = Y[i];

        // only the upper triangle
        for(int j=i+1; j<=order; ++j){
            X[i] -= U[i][j] * X[j];
        }

        X[i] /= U[i][i];   
    }

}


#endif





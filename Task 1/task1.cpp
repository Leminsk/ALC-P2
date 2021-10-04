#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include "routines.hpp"

const std::string INPUT_FILE_NAME = "main_input.txt";
const std::string OUTPUT_FILE_NAME = "main_output.txt";
const std::string SEPARATOR = ","; // separates the values of rows of the input


int ICOD;  // method code
double theta_1; // parameters for the NL system 
double theta_2; //
double TOLm; // max tolerance for iterative solution


bool success = true;
Vec final_estimation(3, 0.0);
std::vector<std::string> errors;

/* INPUT_FILE.txt description:
    line 0: ICOD -> 1 (Newton), 2 (Broyden)
    line 1: theta_1 and theta_2 (separated  by SEPARATOR)
    line 2: TOLm (max tolerance for iterative solution)
*/


/* OUTPUT_FILE.txt description:
    line 0: printout of input data
    line n: solution for c_2, c_3, and c_4
    line n+*k: possible errors encountered
*/


/*
NL equation system:

2*(c_3)**2  +  (c_2)**2  +  6*(c_4)**2  =  1.0
8* (c_3)**3  +  6*(c_3)* (c_2)**2  +  36*(c_3)*(c_2)*(c_4)  +  108*(c_3)* (c_4)**2  =  theta_1
60* (c_3)**4  +  60* (c_3)**2 * (c_2)**2  +  576* (c_3)**2 *(c_3)*(c_4)  +  2232* (c_3)**2 *(c_4)**2  +  252* (c_4)**2 *(c_2)**2  +  1296* (c_4)**3 *(c_2)  +  3348* (c_4)**4  +  24* (c_2)**3 *(c_4)  +  3*(c_2)  =  theta_2

*/


bool evaluateErrors(std::vector<std::string> errors){
    if( errors.size() == 0 ){
        return true;
    }else{
        return false;
    }
}


/* separates an input_string using its delimiter and returns a new string vector containing the elements inbetween each occurance of the delimiter */
std::vector<std::string> stringSplit(std::string input_string, std::string delimiter){

    std::string input_copy = input_string;
    size_t pos = 0;
    std::string token;
    std::vector<std::string> result;

    while( (pos = input_copy.find(delimiter)) != std::string::npos ){
        result.push_back( input_copy.substr(0, pos) );
        input_copy.erase(0, pos + delimiter.length());
    }
    result.push_back(input_copy);

    return result;
}




/* read from txt, populate variables and set global flags */
void readMainInput(std::string input_file_name){
    std::string line;
    std::ifstream file(input_file_name);
    std::vector<std::string> file_lines;

    // save main input lines to string vector
    while( std::getline(file, line) ){
        file_lines.push_back(line);
    }

    // check for all arguments
    if(file_lines.size() == 3){

        ICOD = stoi(file_lines[0]);

        std::vector<std::string> thetas = stringSplit(file_lines[1], SEPARATOR);
        theta_1 = stod(thetas[0]);
        theta_2 = stod(thetas[1]);

        TOLm = stod(file_lines[2]);

    }else{
        errors.push_back("INCORRECT NUMBER OF ARGUMENTS IN "+INPUT_FILE_NAME);
        // force failure
        ICOD = -1;
    }


}

/* Write the necessary variables to a .txt. Write only errors to output if any exist. */
void writeOutput(std::string output_file_name){

    std::ofstream file;
    file.open(output_file_name);

    if(success){
        file << "INPUT VALUES: \n";
        file << "ICOD: " << ICOD << "\n";
        file << "theta_1: " << theta_1 << "  theta_2: " << theta_2 << "\n";
        file << "TOLm: " << TOLm << "\n";
        file << "Solution found for initial c_2 = 1, c_3 = 0, c_4 = 0: \n" << "{ " << final_estimation[0] << ", " << final_estimation[1] << ", " << final_estimation[2] << " }\n";
    }else{
        file << "Calculation failed. " << "ICOD: " << ICOD << "\n";
        file << "theta_1: " << theta_1 << "  theta_2: " << theta_2 << "\n";
        file << "TOLm: " << TOLm << "\n";
        file << "Initial x: c_2 = 1, c_3 = 0, c_4 = 0: \n";
        for(size_t i=0; i<errors.size(); ++i){
            file << errors[i] << "\n";
        }
    }
    
    file.close();

}

void evaluateICOD(){
    NewtonBroydenResult result;
    switch(ICOD){
        case 1: // NEWTON
            result = mainNewtonMethod(theta_1, theta_2, TOLm);
            errors = result.errors;
            final_estimation = result.solution;
            success = evaluateErrors(errors);
            break;
        case 2: // BROYDEN
            result = mainBroydenMethod(theta_1, theta_2, TOLm);
            errors = result.errors;
            final_estimation = result.solution;
            success = evaluateErrors(errors);
            break;
        default:
            std::cout << "INVALID ICOD FROM: " << INPUT_FILE_NAME << std::endl;
            errors.push_back("INVALID ICOD: "+std::to_string(ICOD));
            success = false;
    } 

}




int main(){
    
    std::cout << "============================================================================" << std::endl;

    readMainInput(INPUT_FILE_NAME);
    
    evaluateICOD();
    
    writeOutput(OUTPUT_FILE_NAME);
        
    std::cout << "============================================================================" << std::endl;
    std::cout << "Task1 main TERMINATED" << std::endl;
    std::cout << "============================================================================" << std::endl;

    // Windows only
    system("pause");

    return 0;
}




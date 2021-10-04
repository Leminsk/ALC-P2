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


int ICOD;   // method code
int SUBCOD; // sub-method code
double a; // interval for ICOD 1 and 2 or value x for ICOD 3 and 4
double b; // interval for ICOD 1 and 2
int sample_points; // amount of sample points for integral ICOD 2
double delta_x_1; // parameters for ICOD 3 and 4
double delta_x_2; // parameters for ICOD 4
double TOLm; // max tolerance for iterative solution
std::vector<double> input_constants; // user inpu; must be 4 constants


bool success = true;
double final_estimation;
std::vector<std::string> errors;
std::vector<std::string> inoutput_values;

/* INPUT_FILE.txt description:
    line 0: ICOD -> 1 (Root), 2 (Integral), 3 (Derivative [finite diff]), 4 (Derivative [Richard Extrapolation])
    ICOD: 1
        line 1: SUBCOD -> 1 (Bisection Method), 2 (Newton's Method)
        line 2: interval [a, b] (separated by SEPARATOR and no brackets)
        line 3: TOLm (max tolerance for iterative solution)
        line 4: c1, c2, c3, c4 (separated by SEPARATOR)
    ICOD: 2
        line 1: SUBCOD -> 1 (Gauss-Legendre Quadrature), 2 (Polynomial[Gaussian] Quadrature)
        line 2: interval [a, b] (separated by SEPARATOR and no brackets)
        line 3: sample points (from 2 to 10)
        line 4: c1, c2, c3, c4 (separated by SEPARATOR)
    ICOD: 3
        line 1: SUBCOD -> 1 (Forward), 2 (Backward), 3 (Central)
        line 2: point x=a
        line 3: delta_x
        line 4: c1, c2, c3, c4 (separated by SEPARATOR)
    ICOD: 4
        line 1: point x=a
        line 2: first delta_x
        line 3: second delta_x
        line 4: c1, c2, c3, c4 (separated by SEPARATOR)
*/


/* OUTPUT_FILE.txt description:
    line 0: printout of input data
    line *n: solution
    line *n+*k: possible errors encountered
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
    if(file_lines.size() == 5){

        ICOD = stoi(file_lines[0]);

        std::vector<std::string> interval;
        std::vector<std::string> constants;

        switch(ICOD){
            case 1:
                SUBCOD = stoi(file_lines[1]);
                interval = stringSplit(file_lines[2], SEPARATOR);
                a = stod(interval[0]);
                b = stod(interval[1]);
                TOLm = stod(file_lines[3]);
                constants = stringSplit(file_lines[4], SEPARATOR);

                if(constants.size() != 4){
                    errors.push_back("ERROR: 4 CONSTANTS ARE REQUIRED. ("+std::to_string(constants.size())+") WERE GIVEN.");
                    ICOD = -1;
                    break;
                }else{
                    for(size_t i=0; i<constants.size(); ++i){
                        input_constants.push_back( stod(constants[i]) );
                    }
                }
                
                inoutput_values.push_back("ICOD: "+std::to_string(ICOD));
                inoutput_values.push_back("SUBCOD: "+std::to_string(SUBCOD));
                inoutput_values.push_back("[a, b]: ["+std::to_string(a)+", "+std::to_string(b)+"]");
                inoutput_values.push_back("TOLm: "+std::to_string(TOLm));
                inoutput_values.push_back("Constants: "+constants[0]+", "+constants[1]+", "+constants[2]+", "+constants[3]);
                break;

            case 2:
                SUBCOD = stoi(file_lines[1]);
                interval = stringSplit(file_lines[2], SEPARATOR);
                a = stod(interval[0]);
                b = stod(interval[1]);
                sample_points = stoi(file_lines[3]);
                constants = stringSplit(file_lines[4], SEPARATOR);

                if(sample_points < 2 || sample_points > 10){
                    errors.push_back("ERROR: AMOUNT OF SAMPLE POINTS IS OUT OF BOUNDS [2, 10]. '"+std::to_string(sample_points)+"' IN FILE.");
                    ICOD = -1;
                    break;
                }
                if(constants.size() != 4){
                    errors.push_back("ERROR: 4 CONSTANTS ARE REQUIRED. ("+std::to_string(constants.size())+") WERE GIVEN.");
                    ICOD = -1;
                    break;
                }else{
                    for(size_t i=0; i<constants.size(); ++i){
                        input_constants.push_back( stod(constants[i]) );
                    }
                }

                inoutput_values.push_back("ICOD: "+std::to_string(ICOD));
                inoutput_values.push_back("SUBCOD: "+std::to_string(SUBCOD));
                inoutput_values.push_back("[a, b]: ["+std::to_string(a)+", "+std::to_string(b)+"]");
                inoutput_values.push_back("Sample Points: "+std::to_string(sample_points));
                inoutput_values.push_back("Constants: "+constants[0]+", "+constants[1]+", "+constants[2]+", "+constants[3]);
                break;

            case 3:
                SUBCOD = stoi(file_lines[1]);
                a = stod(file_lines[2]);
                delta_x_1 = stod(file_lines[3]);
                constants = stringSplit(file_lines[4], SEPARATOR);

                if(constants.size() != 4){
                    errors.push_back("ERROR: 4 CONSTANTS ARE REQUIRED. ("+std::to_string(constants.size())+") WERE GIVEN.");
                    ICOD = -1;
                    break;
                }else{
                    for(size_t i=0; i<constants.size(); ++i){
                        input_constants.push_back( stod(constants[i]) );
                    }
                }

                inoutput_values.push_back("ICOD: "+std::to_string(ICOD));
                inoutput_values.push_back("SUBCOD: "+std::to_string(SUBCOD));
                inoutput_values.push_back("x=a: "+std::to_string(a));
                inoutput_values.push_back("delta_x: "+std::to_string(delta_x_1));
                inoutput_values.push_back("Constants: "+constants[0]+", "+constants[1]+", "+constants[2]+", "+constants[3]);
                break;

            case 4:
                a = stod(file_lines[1]);
                delta_x_1 = stod(file_lines[2]);
                delta_x_2 = stod(file_lines[3]);
                constants = stringSplit(file_lines[4], SEPARATOR);

                if(constants.size() != 4){
                    errors.push_back("ERROR: 4 CONSTANTS ARE REQUIRED. ("+std::to_string(constants.size())+") WERE GIVEN.");
                    ICOD = -1;
                    break;
                }else{
                    for(size_t i=0; i<constants.size(); ++i){
                        input_constants.push_back( stod(constants[i]) );
                    }
                }

                inoutput_values.push_back("ICOD: "+std::to_string(ICOD));
                inoutput_values.push_back("delta_x_1: "+std::to_string(delta_x_1));
                inoutput_values.push_back("delta_x_2: "+std::to_string(delta_x_2));
                inoutput_values.push_back("Constants: "+constants[0]+", "+constants[1]+", "+constants[2]+", "+constants[3]);
                break;

            default:
                break;
        }


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
        for(size_t i=0; i<inoutput_values.size(); ++i){
            file << inoutput_values[i] << "\n";
        }
        file << "Solution found: \n" << std::setprecision(10) << final_estimation << "\n";

    }else{
        file << "Calculation failed. " << "ICOD: " << ICOD << "\n";
        file << "INPUT VALUES: \n";
        for(size_t i=0; i<inoutput_values.size(); ++i){
            file << inoutput_values[i] << "\n";
        }
        file << "ERRORS: \n";
        for(size_t i=0; i<errors.size(); ++i){
            file << errors[i] << "\n";
        }
    }
    
    file.close();

}

void evaluateICOD(){
    basicResult result;
    switch(ICOD){
        case 1: // ROOT
            result = mainRoot(SUBCOD, a, b, TOLm, input_constants);
            errors = result.errors;
            final_estimation = result.estimate;
            success = evaluateErrors(errors);
            break;

        case 2: // INTEGRAL
            result = mainIntegral(SUBCOD, a, b, sample_points, input_constants);
            errors = result.errors;
            final_estimation = result.estimate;
            success = evaluateErrors(errors);
            break;

        case 3: // DERIVATIVE [DF]
            result = mainDerivativeDF(SUBCOD, a, delta_x_1, input_constants);
            errors = result.errors;
            final_estimation = result.estimate;
            success = evaluateErrors(errors);
            break;

        case 4: // DERIVATIVE [RE]
            result = mainDerivativeRE(a, delta_x_1, delta_x_2, input_constants);
            errors = result.errors;
            final_estimation = result.estimate;
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
    std::cout << "Task2 main TERMINATED" << std::endl;
    std::cout << "============================================================================" << std::endl;

    // Windows only
    system("pause");

    return 0;
}




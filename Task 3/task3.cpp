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


double integration_step; // h
double integration_time; // t
std::vector< std::vector<double> > input_constants; // contains the vectors below
std::vector<double> input_constants_m_c_k;          // user input; m, c, k
std::vector<double> input_constants_a;              // user input; a_1, a_2, a_3
std::vector<double> input_constants_w;              // user input; w_1, w_2, w_3


bool success = true;
std::vector< std::vector<double> > estimations; // vec of vec { time, displacement, speed, acceleration }
std::vector<std::string> errors;
std::vector<std::string> inoutput_values;

/* INPUT_FILE.txt description:
    line 0: integration steps
    line 1: integration time
    line 2: m, c, k
    line 3: a_1, a_2, a_3
    line 4: w_1, w_2, w_3
*/


/* OUTPUT_FILE.txt description:
    line 0: printout of input data
    line *n: solution table 
        { time, displacement, speed, acceleration }
    line *n+*k: possible errors encountered
*/




bool evaluateErrors(std::vector<std::string> errors){
    return (errors.size() == 0);
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

        std::vector<std::string> constants;

        integration_step = stod(file_lines[0]);
        integration_time = stod(file_lines[1]);

        constants = stringSplit(file_lines[2], SEPARATOR);
        for(size_t i=0; i<constants.size(); ++i){
            input_constants_m_c_k.push_back( stod(constants[i]) );
        }
        constants = stringSplit(file_lines[3], SEPARATOR);
        for(size_t i=0; i<constants.size(); ++i){
            input_constants_a.push_back( stod(constants[i]) );
        }
        constants = stringSplit(file_lines[4], SEPARATOR);
        for(size_t i=0; i<constants.size(); ++i){
            input_constants_w.push_back( stod(constants[i]) );
        }

        if( input_constants_m_c_k.size() != 3 ){
            errors.push_back("INCORRECT NUMBER OF CONSTANTS 'm, c, k' IN LINE 3");
            success = false;
        }
        if( input_constants_a.size() != 3 ){
            errors.push_back("INCORRECT NUMBER OF CONSTANTS 'a' IN LINE 4");
            success = false;
        }
        if( input_constants_w.size() != 3 ){
            errors.push_back("INCORRECT NUMBER OF CONSTANTS 'w' IN LINE 5");
            success = false;
        }

        if(success){
            input_constants.push_back(input_constants_m_c_k);
            input_constants.push_back(input_constants_a);
            input_constants.push_back(input_constants_w);
        }
        


    }else{
        errors.push_back("INCORRECT NUMBER OF ARGUMENTS IN "+INPUT_FILE_NAME);
        // force failure
        success = false;
    }


}

/* Write the necessary variables to a .txt. Write only errors to output if any exist. */
void writeOutput(std::string output_file_name){

    std::ofstream file;
    file.open(output_file_name);

    if(success){
        file << "INPUT VALUES: \n" << std::setprecision(10);
        file << "m: " << input_constants[0][0] << ", c: " << input_constants[0][1] << ", k: " << input_constants[0][2] << "\n";
        file << "a_1: " << input_constants[1][0] << ", a_2: " << input_constants[1][1] << ", a_3: " << input_constants[1][2] << "\n";
        file << "w_1: " << input_constants[2][0] << ", w_2: " << input_constants[2][1] << ", w_3: " << input_constants[2][2] << "\n";
        file << "Time, Displacement, Velocity, Acceleration \n";
        
        for(size_t i=0; i<estimations.size(); ++i){
            for(size_t j=0; j<estimations[i].size()-1; ++j){
                file << estimations[i][j] << ", ";
            }
            file << estimations[i][estimations[i].size()-1] << "\n";
        }

    }else{
        file << "Calculation failed. \n";
        file << "ERRORS: \n";
        for(size_t i=0; i<errors.size(); ++i){
            file << errors[i] << "\n";
        }
    }
    
    file.close();

}

void evaluateMain(){
    RKNResult result;

    result = mainRKN(integration_step, integration_time, input_constants);
    errors = result.error;
    estimations = result.data;
    success = evaluateErrors(errors);

}




int main(){
    
    std::cout << "============================================================================" << std::endl;

    readMainInput(INPUT_FILE_NAME);
    
    evaluateMain();
    
    writeOutput(OUTPUT_FILE_NAME);
        
    std::cout << "============================================================================" << std::endl;
    std::cout << "Task3 main TERMINATED" << std::endl;
    std::cout << "============================================================================" << std::endl;

    // Windows only
    system("pause");

    return 0;
}




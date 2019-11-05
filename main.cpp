#include <fstream>
#include <iostream>
#include <map>
#include "errors.h"
#include "plugboard.h"
#include "rotor.h"

using namespace std;

enum FileType { plugboard, reflector, rotor_mapping, rotor_pos };

/**
 * This function prints a helpful error message to stderr for a given code.
 * @param error The error.
 * @param type The file type which caused the error.
 */
void print_error(int error_code, FileType type);

/**
 * This function prints a helpful error message for an insufficient number
 * of parameters.
 */
void print_insufficient_params_error();

int main(int argc, char** argv) {

  // Minimum number of command line arguments.
  const int MIN_ARG = 4;

  if (argc < MIN_ARG) {
    print_error(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  Plugboard plugboard;
  map<int, int> plug_mapping;
  int error_code = plugboard.read_plugboard_config(argv[1], plug_mapping);

  if (error_code != NO_ERROR) {
    print_error(error_code, FileType.plugboard);
    return error_code;
  }

  Rotor rotor;
  int rotor_mapping[26] = {};
  int turnover_notches[26] = {};
  
  error_code = rotor.read_rotor_config(argv[3],
				       rotor_mapping,
				       turnover_notches);
  if (error_code != NO_ERROR) {
    print_error(error_code, FileType.rotor_mapping);
    return error_code;
  }
  
  return error_code;
}

void print_error(int error_code, FileType type) {
  switch (error_code) {
  case NO_ERROR:
    break;
  case INSUFFICIENT_NUMBER_OF_PARAMETERS:
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* ";
    cerr << "rotor-positions" << endl;
    break;
  case INVALID_INPUT_CHARACTER:
    cerr << "The message to be encrypted needs to consist of only whitespace ";
    cerr << "or upper case characters."  << endl;
    break;
  case INVALID_INDEX:
    cerr << "The plugboard, rotor and reflector configurations only permit ";
    cerr << "indices in the range 0-25 representing a letter from the ";
    cerr << "alphabet." << endl;
    break;
  case NON_NUMERIC_CHARACTER:
    if (type == plugboard)
      cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
    if (type == rotor_mapping) {
      cerr << "Non-numeric character for mapping in rotor file rotor.rot";
      cerr << endl;
    }
    break;
  case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
    cerr << "The plugboard configuration cannot have contacts mapped to ";
    cerr << "themselves or with more than one other contact." << endl;
    break;
  case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
    cerr << "Incorrect number of parameters in plugboard file plugboard.pb";
    cerr << endl;
    break;
  case INVALID_ROTOR_MAPPING:
    break;
  case NO_ROTOR_STARTING_POSITION:
    break;
  case INVALID_REFLECTOR_MAPPING:
    break;
  case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
    break;
  case ERROR_OPENING_CONFIGURATION_FILE:
    cerr << "A configuration file couldn't be opened or encountered errors ";
    cerr << "during reading." << endl;
    break;
  default:
    break;
  }
}

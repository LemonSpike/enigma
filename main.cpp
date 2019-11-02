#include <fstream>
#include <iostream>
#include "errors.h"
#include "plugboards/plugboard.h"

using namespace std;

/**
 * This function prints a helpful error message to stderr for a given code.
 * @param error The error
 */
void print_error(int error_code);

int main(int argc, char** argv) {

  // Minimum number of command line arguments.
  const int MIN_ARG = 4;

  if (argc < MIN_ARG) {
    print_error(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  Plugboard plugboard;
  int error_code = plugboard.read_plugboard_config(argv[1]);
  if (error_code != NO_ERROR) {
    print_error(error_code);
    return error_code;
  }

  return error_code;
}

void print_error(int error_code) {
  switch (error_code) {
  case NO_ERROR:
    break;
  case INSUFFICIENT_NUMBER_OF_PARAMETERS:
    cerr << "A minimum of three command line arguments are required, in";
    cerr << " addition to the executable filepath." << endl;
    cerr << "The first argument should specify the plugboard's wiring map.";
    cerr << endl;
    cerr << "The second argument should specify the reflector's wiring map.";
    cerr << endl;
    cerr << "The next optional arguments can specify rotor wiring maps.";
    cerr << endl;
    cerr << "The last argument should specify the rotors' initial positions.";
    cerr << endl;
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
  default:
    break;
  }
}

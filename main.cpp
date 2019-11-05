#include <fstream>
#include <iostream>
#include <map>
#include "errors.h"
#include "plugboard.h"
#include "rotor.h"

using namespace std;

enum FileType { comm_line, pb, reflector, rot_mapping, rot_pos };

/**
 * This function prints a helpful error message to stderr for a given code.
 * @param error The error.
 * @param type The file type which caused the error.
 */
void print_error(int error_code, FileType type);

int main(int argc, char** argv) {

  // Minimum number of command line arguments.
  const int MIN_ARG = 4;

  if (argc < MIN_ARG) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* ";
    cerr << "rotor-positions" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  Plugboard plugboard(cerr);
  map<int, int> plug_mapping;
  int error_code = plugboard.read_plugboard_config(argv[1], plug_mapping);

  if (error_code != NO_ERROR) {
    return error_code;
  }

  Rotor rotor(cerr);
  int rotor_mapping[26] = {};
  int turnover_notches[26] = {};

  error_code = rotor.read_rotor_config(argv[3],
				       rotor_mapping,
				       turnover_notches);
  if (error_code != NO_ERROR) {
    print_error(error_code, rot_mapping);
    return error_code;
  }

  return error_code;
}

void print_error(int error_code, FileType type) {
  switch (error_code) {
  case INVALID_INPUT_CHARACTER:
    cerr << "The message to be encrypted needs to consist of only ";
    cerr << "whitespace or upper case characters." << endl;
    break;
  case NON_NUMERIC_CHARACTER:
    if (type == pb)
      cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
    if (type == rot_mapping) {
      cerr << "Non-numeric character for mapping in rotor file rotor.rot";
      cerr << endl;
    }
    break;
  default:
    break;
  }
}

#include "enigma.h"
#include "errors.h"

using namespace std;

int Enigma::read_files() {
  int error_code = plugboard.read_plugboard_config(filenames[1]);

  if (error_code != NO_ERROR) {
    return error_code;
  }

  error_code = read_all_rotors();
  if (error_code != NO_ERROR) {
    print_error(error_code, rot_mapping);
    return error_code;
  }
  return error_code;
}

int Enigma::read_all_rotors() {
  int error = NO_ERROR;
  for (int i = 3; i < number_of_files - 1; ++i) {
    Rotor rotor = Rotor(err_stream, filenames[i]);
    error = rotor.read_rotor_config();
    if (error != NO_ERROR)
      return error;
    rotors.push_back(rotor);
  }
  error = read_rotor_positions();
  return error;
}

int Enigma::read_rotor_positions() {

  char *filename = filenames[number_of_files - 1];

  ifstream input(filename);

  if (input.fail()) {
    err_stream << "Error opening rotor positions file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  FileReader reader(err_stream);

  int error_code = NO_ERROR;
  int counter = 0;
  while (!input.eof()) {
    while (isspace(input.peek()))
      input.get();
    if (input.peek() == EOF)
      break;

    int number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    if (positions.size() >= rotors.size()) {
      err_stream << "Missing rotor initial positions." << endl;
      return INVALID_ROTOR_MAPPING;
    } else
      positions.push_back(number);
    counter++;
  }
  if (counter == 0) {
    err_stream << "No rotor starting positions." << endl;
    return NO_ROTOR_STARTING_POSITION;
  }
  return NO_ERROR;
}

void Enigma::print_error(int error_code, FileType type) {
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

#include "enigma.h"

using namespace std;

char Enigma::encrypt_message(char message) {
  if (rotors.size() > 0)
    rotors[rotors.size() - 1].shift_up();
  return map_through_machine(message);;
}

int Enigma::read_files() {

  // read plugboard.
  int error_code = plugboard.read_plugboard_config(filenames[1]);
  if (error_code != NO_ERROR) {
    print_error(error_code, pb);
    return error_code;
  }

  // read reflector.
  error_code = reflector.read_reflector_config(filenames[2]);
  if (error_code != NO_ERROR) {
    print_error(error_code, rf);
    return error_code;
  }

  // read rotor mappings.
  error_code = read_all_rotors();
  if (error_code != NO_ERROR) {
    print_error(error_code, rot_mapping);
    return error_code;
  }

  // read rotor initial positions.
  error_code = read_rotor_positions();
  if (error_code != NO_ERROR) {
    print_error(error_code, rot_pos);
    return error_code;
  }
  return error_code;
}

/**
 * This function reads all the rotor config files, and stores the
 * configured rotors.
 * @return read_all_rotors The error code is returned.
 */
int Enigma::read_all_rotors() {
  int error = NO_ERROR;
  for (int i = 3; i < number_of_files - 1; ++i) {
    Rotor rotor = Rotor(err_stream, filenames[i]);
    error = rotor.read_rotor_config();
    if (error != NO_ERROR)
      return error;
    rotors.push_back(rotor);
  }
  return error;
}

/**
 * This function reads the rotor initial positions from a file.
 * @return read_rotor_positions The error code is returned.
 */
int Enigma::read_rotor_positions() {

  char *filename = filenames[number_of_files - 1];

  ifstream input(filename);

  if (input.fail()) {
    err_stream << "Error opening rotor positions file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  FileReader reader(err_stream);

  int error_code = NO_ERROR;
  unsigned int counter = 0;
  while (!input.eof()) {
    input >> ws;
    if (input.peek() == EOF)
      break;

    int number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    if (counter == rotors.size()) {
      break;
    } else
      rotors[counter].position = number;
    counter++;
  }
  if (counter == 0 && rotors.size() > 0) {
    err_stream << "No starting position for rotor 0 in rotor position file: ";
    err_stream << "rotor.pos" << endl;
    return NO_ROTOR_STARTING_POSITION;
  }
  return NO_ERROR;
}

/** This function maps the character through the machine.
 * @param input The input character.
 * @return map_through_machine The mapped character.
 */
char Enigma::map_through_machine(char input) {

  int output = plugboard.map_char_input(input);

  for (int i = rotors.size() - 1; i > -1; --i) {
    if (rotors[i].is_at_notch() && i != 0)
      rotors[i - 1].shift_up();
    output = rotors[i].map_forwards(output);
    output = (output - rotors[i].position + NO_OF_LETTERS) % NO_OF_LETTERS;
  }

  output = reflector.map_input(output);

  for (unsigned int i = 0; i < rotors.size(); ++i) {
    output = rotors[i].map_backwards(output);
    output = (output - rotors[i].position + NO_OF_LETTERS) % NO_OF_LETTERS;
  }

  output = plugboard.map_input(output);

  return output + 'A';
}

void Enigma::print_error(int error_code, FileType type) {
  switch (error_code) {
  case INVALID_INPUT_CHARACTER:
    err_stream << "The message to be encrypted needs to consist of only ";
    err_stream << "whitespace or upper case characters." << endl;
    break;
  case NON_NUMERIC_CHARACTER:
    if (type == pb) {
      err_stream << "Non-numeric character in plugboard file plugboard.pb";
      err_stream << endl;
    } else if (type == rot_mapping) {
      err_stream << "Non-numeric character for mapping in rotor file rotor.rot";
      err_stream << endl;
    } else if (type == rot_pos) {
      err_stream << "Non-numeric character in rotor positions file rotor.pos";
      err_stream << endl;
    } else if (type == rf) {
      err_stream << "Non-numeric character in reflector file ";
      err_stream << "reflector.rf" << endl;
    }
    break;
  default:
    break;
  }
}

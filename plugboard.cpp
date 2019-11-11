#include "plugboard.h"

using namespace std;

int Plugboard::read_plugboard_config(const char *filename) {

  ifstream input(filename);

  if (input.fail()) {
    err_stream << "Error opening plugboard configuration file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  FileReader reader(err_stream);

  int error_code = NO_ERROR;
  while (!input.eof()) {
    input >> ws;
    if (input.peek() == EOF)
      return NO_ERROR;

    int first_number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    input >> ws;
    if (input.peek() == EOF) {
      err_stream << "Incorrect number of parameters in plugboard file ";
      err_stream << "plugboard.pb" << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    int second_number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    error_code = check_mapping(first_number, second_number);
    if (error_code != NO_ERROR)
      return error_code;

  }
  return NO_ERROR;
}

/**
 * This function checks for self-connected contacts, and contacts with more
 * than one connection.
 *
 * @param contact_one The position of the new contact as a relative index.
 * @return check_mapping The error code is returned.
 */
int Plugboard::check_mapping(int contact_one,
			     int contact_two) {

  if (contact_one == contact_two || mapping[contact_one] != contact_one ||
      mapping[contact_two] != contact_two) {
    print_configuration_error();
    return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  }
  mapping[contact_one] = contact_two;
  mapping[contact_two] = contact_one;
  return NO_ERROR;
}

/* Prints a helpful error message for an invalid configuration. */
void Plugboard::print_configuration_error() {
  err_stream << "The plugboard configuration cannot have contacts mapped to ";
  err_stream << "themselves or with more than one other contact." << endl;
}

int Plugboard::map_input(char input) {
  return mapping[input - 'A'];
}

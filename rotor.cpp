#include "rotor.h"

using namespace std;

int Rotor::read_rotor_config() {

  ifstream input(filename);

  if (input.fail()) {
    err_stream << "Error opening rotor configuration file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  FileReader reader(err_stream);

  int error_code = NO_ERROR;
  int counter = 0;

  for (int i = 0; i < NO_OF_LETTERS; ++i)
    mapping[i] = -1;

  while (!input.eof()) {
    input >> ws;
    if (input.peek() == EOF)
      break;

    int number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    if (counter >= NO_OF_LETTERS)
      error_code = add_turnover_notch(number, counter);
    else
      error_code = check_mapping(number, counter);
    if (error_code != NO_ERROR)
      return error_code;
    counter++;
  }
  if (counter < 26) {
    err_stream << "Not all inputs mapped in rotor file: rotor.rot" << endl;
    return INVALID_ROTOR_MAPPING;
  }
  return NO_ERROR;
}

/**
 * This function reads notch positions from the input stream.
 * @param number This is the notch position to be stored.
 * @param counter The notch index in the notches array.
 * @return add_turnover_notch This returns an error code or 0 if successful.
 */
int Rotor::add_turnover_notch(int number,
                              int counter) {
  for (unsigned int i = 0; i < notches.size(); i++) {
    if (notches[i] == number) {
      err_stream << "Duplicate notches " << number << " at ";
      err_stream << i << " and " << counter << endl;
      return INVALID_ROTOR_MAPPING;
    }
  }
  notches.push_back(number);
  return NO_ERROR;
}

/**
 * This function checks for letters mapped to the same position, and
 * returns an error if found.
 * @param number The number to be mapped to.
 * @param counter The index position to be mapped.
 * @return check_mapping This returns a non-zero error code if mapping
 * is not valid. Otherwise NO_ERROR is returned.
 */
int Rotor::check_mapping(int number, int counter) {
  for (int i = 0; i < NO_OF_LETTERS; i++) {
    if (mapping[i] == number) {
      err_stream << "Invalid mapping of input " << counter << " to output ";
      err_stream << number << " (output " << number << " is already mapped to";
      err_stream << " from input " << i << ") in rotor.rot" << endl;
      return INVALID_ROTOR_MAPPING;
    }
  }
  mapping[counter] = number;
  return NO_ERROR;
}

int Rotor::map_forwards(int input) {
  return mapping[(input + position) % NO_OF_LETTERS];
}

int Rotor::map_backwards(int input) {
  for (int i = 0; i < NO_OF_LETTERS; ++i) {
    if (mapping[i] == (input + position) % NO_OF_LETTERS)
      return i;
  }
  return INVALID_DIGIT;
}

bool Rotor::is_at_notch() {
  for (unsigned int i = 0; i < notches.size(); ++i) {
    if (notches[i] == position)
      return true;
  }
  return false;
}

void Rotor::shift_up() {
  position = (position + 1) % NO_OF_LETTERS;
}

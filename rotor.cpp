#include <fstream>
#include <iostream>
#include "rotor.h"
#include "file_reader.h"
#include "errors.h"

using namespace std;

const int NO_OF_LETTERS = 26;

int Rotor::read_all_rotors() {
  int error = NO_ERROR;
  for (int i = 0; i < num_rotors; ++i) {
    int rotor_mapping[26] = {};
    int notches[26] = {};
    error = read_rotor_config(filenames[i], rotor_mapping, notches);
    if (error != NO_ERROR)
      break;
    all_mappings[i] = rotor_mapping;
    all_notches[i] = notches;
  }
  error = read_rotor_positions(filenames[num_rotors]);
  return error;
}

int Rotor::read_rotor_positions(char *filename) {

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
      return NO_ERROR;

    int number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    if (sizeof(positions) / sizeof(positions[0]) >= num_rotors)
      error_code = INVALID_ROTOR_MAPPING;
    if (error_code != NO_ERROR)
      return error_code;
    counter++;
  }
  if (counter == 0) {
    err_stream << "No rotor starting positions." << endl;
    return NO_ROTOR_STARTING_POSITION;
  }
  return NO_ERROR;
}

int Rotor::read_rotor_config(char *filename,
			     int mapping[26],
			     int turnover_notches[26]) {

  ifstream input(filename);

  if (input.fail()) {
    err_stream << "Error opening rotor configuration file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  FileReader reader(err_stream);

  int error_code = NO_ERROR;
  int counter = 0;
  while (!input.eof()) {
    while (isspace(input.peek()))
      input.get();
    if (input.peek() == EOF)
      return NO_ERROR;

    int number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    if (sizeof(mapping) / sizeof(mapping[0]) >= NO_OF_LETTERS)
      error_code = add_turnover_notch(number, turnover_notches, counter);
    else
      error_code = check_mapping(number, mapping, counter);
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
 * @param in This is the input file to read the positions from.
 * @param counter The index position to insert into the array.
 * @param turnover_notches This stores the positions of all the notches.
 * @return add_turnover_notch This returns an error code or 0 if successful.
 */
int Rotor::add_turnover_notch(int number,
			      int turnover_notches[26],
			      int counter) {
  for (int i = 0; i < NO_OF_LETTERS; i++) {
    if (turnover_notches[i] == number) {
      err_stream << "Duplicate notches " << number << " at ";
      err_stream << i << " and " << counter << endl;
      return INVALID_ROTOR_MAPPING;
    }
  }
  turnover_notches[counter] = number;
  return NO_ERROR;
}

/**
 * This function checks for letters mapped to the same position, and
 * returns an error if found.
 * @param number The number to be added to the mapping.
 * @param mapping The mapping of letters to zero-based indices.
 * @param counter The index position to insert into the mapping.
 * @return check_mapping This returns a non-zero error code if mapping
 * is not valid. Otherwise NO_ERROR is returned.
 */
int Rotor::check_mapping(int number, int mapping[26], int counter) {
  if (number == counter) {
    err_stream << "Invalid mapping of input " << counter << " to output ";
    err_stream << number << "(output " << number;
    err_stream << " is already mapped to from input ";
    err_stream << counter << ") in" << endl;
    return INVALID_ROTOR_MAPPING;
  }
  for (int i = 0; i < NO_OF_LETTERS; i++) {
    if (mapping[i] == number) {
      err_stream << "Invalid mapping of input " << counter << " to output ";
      err_stream << number << " (output " << number << " is already mapped to";
      err_stream << " from input " << i << ") in" << endl;
      return INVALID_ROTOR_MAPPING;
    }
  }
  mapping[counter] = number;
  return NO_ERROR;
}

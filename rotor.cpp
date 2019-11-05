#include <fstream>
#include <iostream>
#include "rotor.h"
#include "file_reader.h"
#include "errors.h"

using namespace std;

const int NO_OF_LETTERS = 26;

int Rotor::read_rotor_config(char *filename,
			     int mapping[26],
			     int *turnover_notches) {

  ifstream input(filename);

  if (input.fail()) {
    cerr << "Error opening plugboard configuration file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  FileReader reader;

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

    if (sizeof(mapping) / sizeof(mapping[0]) >= NO_OF_LETTERS) {
      error_code = add_turnover_notch(input, turnover_notches);
    } else {
      error_code = check_mapping(number, mapping, counter);
    }
    if (error_code != NO_ERROR)
      return error_code;
    counter++;
  }
  if (counter < 25) {
    cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
    return INVALID_ROTOR_MAPPING;
  }
  return NO_ERROR;
}

/**
 * This function reads notch positions from the input stream.
 * @param in This is the input file to read the positions from.
 * @param turnover_notches This stores the positions of all the notches.
 * @return add_turnover_notch This returns an error code or 0 if successful.
 */
int Rotor::add_turnover_notch(ifstream &in, int *turnover_notches) {
  return NO_ERROR;
}

/**
 * This function checks for letters mapped to the same position, and
 * returns an error if found.
 * @param number The number to be added to the mapping.
 * @param mapping The mapping of letters to zero-based indices.
 * @return check_mapping This returns a non-zero error code if mapping 
 * is not valid. Otherwise NO_ERROR is returned.
 */
int Rotor::check_mapping(int number, int mapping[26], int counter) {
  if (number == counter)
    return INVALID_ROTOR_MAPPING;
  for (int i = 0; i < NO_OF_LETTERS; i++) {
    if (mapping[i] == number) {
      cerr << "Invalid mapping of input " << counter << "to output " << number;
      cerr << "(output " << number << "is already mapped to from input " << i;
      cerr << ") in" << endl; 
      return INVALID_ROTOR_MAPPING;
    }
  }
  return NO_ERROR;
}

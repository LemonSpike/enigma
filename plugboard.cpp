#include <iostream>
#include <fstream>
#include <map>
#include "../errors.h"
#include "../file_reader/file_reader.h"
#include "plugboard.h"

using namespace std;

int Plugboard::read_plugboard_config(const char *filename,
				     map<int, int> mapping) {

  ifstream input(filename);

  if (input.fail()) {
    cerr << "Error opening plugboard configuration file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  FileReader reader;

  int error_code = NO_ERROR;
  while (!input.eof()) {
    while (isspace(input.peek()))
      input.get();
    if (input.peek() == EOF)
      return NO_ERROR;

    int first_number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    while (isspace(input.peek()))
      input.get();
    if (input.peek() == EOF)
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

    int second_number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    error_code = check_mapping(first_number, second_number, mapping);
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
 * @param mapping The mapping of contacts expressed between indices.
 * @return check_mapping The error code is returned.
 */
int Plugboard::check_mapping(int contact_one,
			     int contact_two,
                             map<int, int> mapping) {
  
  if (contact_one == contact_two)
    return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;

  map<int, int>::iterator iter;
  for ( iter = mapping.begin(); iter != mapping.end(); iter++) {
    if (iter->first == contact_one || iter->second == contact_one)
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    if (iter->first == contact_two || iter->second == contact_two)
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  }
  mapping[contact_one] = contact_two;
  return NO_ERROR;
}
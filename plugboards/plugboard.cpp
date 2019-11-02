#include <iostream>
#include <fstream>
#include <map>
#include "../errors.h"
#include "plugboard.h"

using namespace std;

const int INVALID_DIGIT = -1;

int Plugboard::read_plugboard_config(const char *filename) {

  ifstream input(filename);

  if (input.fail()) {
    cerr << "Error opening plugboard configuration file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  map<int, int> mapping;

  int error_code = NO_ERROR;
  while (!input.eof()) {
    while (isspace(input.peek()))
      input.get();
    if (input.peek() == EOF)
      return NO_ERROR;

    int first_number = read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    while (isspace(input.peek()))
      input.get();
    if (input.peek() == EOF)
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

    int second_number = read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    error_code = check_mapping(first_number, second_number, mapping);
    if (error_code != NO_ERROR)
      return error_code;

  }
  return NO_ERROR;
}

/**
 * This function reads a 1-2 digit number from an input file stream.
 *
 *  @param in The input file stream.
 *  @param error_code The error code is updated if the number was not
 *  valid, or the filestream couldn't be opened.
 *  @return read_number The integer value of the number is returned if
 *  successful, or INVALID_DIGIT if not.
 */
int Plugboard::read_number(ifstream& in, int& error_code) {
  char first = get_character(in, error_code);
  if (error_code != NO_ERROR)
    return INVALID_DIGIT;
  int first_digit = get_digit(first, error_code);
  if (error_code != NO_ERROR)
    return INVALID_DIGIT;

  char second = get_character(in, error_code);
  if (error_code != NO_ERROR)
    return INVALID_DIGIT;
  if (isspace(second) || in.eof())
    return first_digit;
  int second_digit = get_digit(second, error_code);
  if (error_code != NO_ERROR)
    return INVALID_DIGIT;

  char next = get_character(in, error_code);
  if (error_code != NO_ERROR)
    return INVALID_DIGIT;
  if (isspace(next) || in.eof()) {
    int result = first_digit*10 + second_digit;
    error_code = (result < 26) ? NO_ERROR : INVALID_INDEX;
    return (error_code == NO_ERROR) ? result : INVALID_DIGIT;
  } else if (next < '0' || next > '9') {
    error_code = NON_NUMERIC_CHARACTER;
    return INVALID_DIGIT;
  } else {
    error_code = INVALID_INDEX;
    return INVALID_DIGIT;
  }
}

/**
 * This function reads a character from the input file stream.
 *
 * @param in The input file stream.
 * @param error_code The error code is updated if error occurs.
 * @return get_character The read character is returned.
 */
char Plugboard::get_character(ifstream& in, int& error_code) {
  char character = in.get();
  if (in.fail()) {
    error_code = ERROR_OPENING_CONFIGURATION_FILE;
    return '\0';
  }
  return character;
}

/**
 * This function converts a character to a digit, checking if it is a
 * valid digit.
 *
 * @param value The character value to be converted.
 * @param error_code The error code is updated if an error occurs.
 * @return get_digit The converted character is returned.
 */
int Plugboard::get_digit(char value, int &error_code) {
  int number = value - '0';
  if (number < 0 || number > 9) {
    error_code = NON_NUMERIC_CHARACTER;
    return INVALID_DIGIT;
  }
  return number;
}

/**
 * This function checks for self-connected contacts, and contacts with more
 * than one connection.
 *
 * @param contact_one The position of contact one as a relative index.
 * @param contact_two The position of contact two as a relative index.
 * @param mapping The mapping of contacts expressed between indices.
 * @return check_mapping The error code is returned.
 */
int Plugboard::check_mapping(int contact_one, int contact_two,
                             map<int, int> &mapping) {
  if (contact_one == contact_two)
    return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;

  map<int, int>::iterator iter;
  for (iter = mapping.begin(); iter != mapping.end(); iter++) {
    if (iter->first == contact_one || iter->second == contact_one)
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    if (iter->first == contact_two || iter->second == contact_two)
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  }
  mapping[contact_one] = contact_two;
  return NO_ERROR;
}

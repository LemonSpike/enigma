#include <fstream>
#include "file_reader.h"
#include "errors.h"
#include "constants.h"

using namespace std;

int FileReader::read_number(ifstream& in, int& error_code) {
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
    if (error_code == INVALID_INDEX) {
      err_stream << "The plugboard, rotor and reflector configurations only ";
      err_stream << "permit indices in the range 0-25 representing a letter ";
      err_stream << "from the alphabet." << endl;
    }
    return (error_code == NO_ERROR) ? result : INVALID_DIGIT;
  } else if (next < '0' || next > '9') {
    error_code = NON_NUMERIC_CHARACTER;
    return INVALID_DIGIT;
  } else {
    error_code = INVALID_INDEX;
    err_stream << "The plugboard, rotor and reflector configurations only ";
    err_stream << "permit indices in the range 0-25 representing a letter from";
    err_stream << " the alphabet." << endl;
    return INVALID_DIGIT;
  }
}

char FileReader::get_character(ifstream& in, int& error_code) {
  char character = in.get();
  if (in.fail()) {
    error_code = ERROR_OPENING_CONFIGURATION_FILE;
    err_stream << "Error opening configuration file.";
    return EOF;
  }
  return character;
}

int FileReader::get_digit(char value, int &error_code) {
  int number = value - '0';
  if (number < 0 || number > 9) {
    error_code = NON_NUMERIC_CHARACTER;
    return INVALID_DIGIT;
  }
  return number;
}

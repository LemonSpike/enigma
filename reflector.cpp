#include "reflector.h"

using namespace std;

int Reflector::read_reflector_config(const char *filename) {

  ifstream input(filename);

  if (input.fail()) {
    err_stream << "Error opening reflector configuration file.";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  FileReader reader(err_stream);

  int error_code = NO_ERROR;
  int counter = 0;
  while (!input.eof()) {
    input >> ws;
    if (input.peek() == EOF)
      break;

    int first_number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    input >> ws;
    if (input.peek() == EOF) {
      err_stream << "Incorrect number of parameters in reflector file ";
      err_stream << "reflector.rf" << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    int second_number = reader.read_number(input, error_code);
    if (error_code != NO_ERROR)
      return error_code;

    error_code = check_mapping(first_number, second_number);
    if (error_code != NO_ERROR)
      return error_code;
    counter++;
  }
  if (counter < 13) {
    err_stream << "Incorrect number of parameters in reflector file ";
    err_stream << "reflector.rf" << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  return NO_ERROR;
}

/**
 * This checks the mapping doesn't contain duplicate mappings before updating
 * the mapping array.
 * @param first_number The number to be mapped.
 * @param second_numbr The mapped number.
 * @return check_mapping The error code is returned.
 */
int Reflector::check_mapping(int first_number, int second_number) {
  if (mapping[first_number] != -1 || first_number == second_number) {
    err_stream << "The reflector configuration cannot have contacts mapped to ";
    err_stream << "themselves or with more than one other contact." << endl;
    return INVALID_REFLECTOR_MAPPING;
  }
  mapping[first_number] = second_number;
  mapping[second_number] = first_number;
  return NO_ERROR;
}

int Reflector::map_input(int input) {
  return mapping[input];
}

#ifndef FILE_READER_H
#define FILE_READER_H
#include <fstream>

using namespace std;

/* Helper class to read numbers from input files. */
class FileReader {

  ostream &err_stream;

public:

  /**
   * This initializes FileReader with the correct error stream.
   * @param stream The error stream.
   * @return FileReader The FileReader with the correct error stream.
   */
 FileReader(ostream &stream): err_stream(stream) {}

  /**
   * This function reads a 1-2 digit number from an input file stream.
   *
   *  @param in The input file stream.
   *  @param error_code The error code is updated if the number was not
   *  valid, or the filestream couldn't be opened.
   *  @return read_number The integer value of the number is returned if
   *  successful, or INVALID_DIGIT if not.
   */
  int read_number(ifstream& in, int& error_code);

  /**
   * This function reads a character from the input file stream.
   *
   * @param in The input file stream.
   * @param error_code The error code is updated if error occurs.
   * @return get_character The read character is returned.
   */
  char get_character(ifstream& in, int& error_code);

  /**
   * This function converts a character to a digit, checking if it is a
   * valid digit.
   *
   * @param value The character value to be converted.
   * @param error_code The error code is updated if an error occurs.
   * @return get_digit The converted character is returned.
   */
  int get_digit(char value, int &error_code);
};

#endif

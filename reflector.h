#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <iostream>
#include "constants.h"
#include "errors.h"
#include "file_reader.h"

using namespace std;

class Reflector {

  int mapping[NO_OF_LETTERS];
  ostream &err_stream;

public:
 /**
  * This function initialises a Reflector with the stderr stream.
  * @param stream the stderr stream.
  * @return Reflector The class instance.
  */
 Reflector(ostream &stream): err_stream(stream) {
    for (int i = 0; i < NO_OF_LETTERS; ++i)
      mapping[i] = -1;
  }

 /**
  * This function reads a reflector config from a file with filename.
  * It updates the mapping if the config is valid, and otherwise
  * returns an error code.
  *
  * @param filename File path of reflector configuration.
  * @return read_reflector_config An error code is returned. This is
  * non-zero if error arises, or zero otherwise.
  */
  int read_reflector_config(const char *filename);

 /**
  * This function maps an input to another index.
  * @param input The input to be mapped.
  * @return map_input The mapped input.
  */
  int map_input(int input);

private:
  int check_mapping(int contact_one,
		    int contact_two);

};

#endif

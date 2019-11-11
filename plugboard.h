#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <iostream>
#include <fstream>
#include "errors.h"
#include "file_reader.h"
#include "constants.h"

using namespace std;

/* This class reads the plugboard config files and checks if they're
   valid. */
class Plugboard {

  int mapping[NO_OF_LETTERS];
  ostream &err_stream;

public:
/**
 * This function initialises a Plugboard with the stderr stream.
 * @param stream the stderr stream.
 * @return Plugboard The class instance.
 */
 Plugboard(ostream& stream): err_stream(stream) {
   for (int i = 0; i < NO_OF_LETTERS; ++i)
     mapping[i] = i;
 }

 /**
  * This function reads a plugboard config from a file with filename.
  * it updates the mapping if the config is valid, and otherwise
  * returns an error code.
  *
  * @param filename File path of plugboard configuration.
  * @return read_plugboard_config An error code is returned. This is
  * non-zero if error arises, or zero otherwise.
  */
  int read_plugboard_config(const char *filename);

 /**
  * This function maps a character to an index.
  * @param input The character to be mapped.
  * @return map_input The mapped character.
  */
  int map_input(char input);

private:
  int check_mapping(int contact_one,
		    int contact_two);
  void print_configuration_error();
};

#endif

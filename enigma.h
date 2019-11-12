#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <vector>
#include "reflector.h"
#include "rotor.h"
#include "file_reader.h"
#include "plugboard.h"
#include "errors.h"

using namespace std;

enum FileType { comm_line, pb, rf, rot_mapping, rot_pos };

class Enigma {

 /**
  * This function prints a helpful error message to stderr for a given code.
  * @param error The error.
  * @param type The file type which caused the error.
  */
  void print_error(int error_code, FileType type);

  ostream &err_stream;
  char **filenames;
  int number_of_files;
  Plugboard plugboard;
  vector<Rotor> rotors;
  Reflector reflector;

  int read_all_rotors();
  int read_rotor_positions();
  char map_through_machine(char input);

 public:
/**
 * This constructor intialises the class with filename arguments.
 * @param stream The stderr stream.
 * @param argv The array of string filenames.
 * @param num_files The number of string filenames.
 * @return Enigma The Enigma machine class.
 */
 Enigma(ostream &stream, char **argv, int num_files):
  err_stream(stream), filenames(argv), number_of_files(num_files),
    plugboard(Plugboard(err_stream)), reflector(Reflector(err_stream)) {
  };

 /**
  * This function reads the config files and sets up the Enigma components.
  * (namely the rotor mappings, initial positions, plugboard mappings
  * and reflector mappings).
  * @return read_files An error code if a reading error occurred.
  */
  int read_files();

 /**
  * This function passes rotates the rightmost rotor, and then
  * passes a character through the machine.
  * @param message The character to be mapped.
  * @return encrypt_message The encrypted character.
  */
  char encrypt_message(char message);
};

#endif

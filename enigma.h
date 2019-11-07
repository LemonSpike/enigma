#ifndef ENIGMA_H
#define ENIGMA_H

#include "rotor.h"
#include "file_reader.h"
#include "plugboard.h"
#include<iostream>
#include<vector>

using namespace std;

enum FileType { comm_line, pb, reflector, rot_mapping, rot_pos };

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

 public:
 Enigma(ostream &stream, char **argv, int num_files):
  err_stream(stream), filenames(argv), number_of_files(num_files),
    plugboard(Plugboard(err_stream)) {
  };

  int read_files();
  int read_all_rotors();
  int read_rotor_positions();
  char *encrypt_message(char *message);
};

#endif

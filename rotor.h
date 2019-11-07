#ifndef ROTOR_H
#define ROTOR_H
#include <iostream>
#include <vector>

using namespace std;

const int NO_OF_LETTERS = 26;

/* This class reads rotor configuration files. */
class Rotor {

  ostream &err_stream;
  char *filename;
  int mapping[NO_OF_LETTERS];
  vector<int> notches;

public:

  int position;
  /*
   * This function initialises the rotor with the mapping in the file.
   * @param The standard err stream.
   * @param filename The filepath to the input config file.
   * @return Rotor A rotor with initialised mappings.
   */
  Rotor(ostream& stream, char *filename):
  err_stream(stream), filename(filename) {};

  /**
   * This function reads the rotor configuration from a file, and
   * returns an error if failed.
   * @return read_rotors_config The error code is returned. If
   * unsuccessful, this is a non-zero error code.
   */
  int read_rotor_config();

  /*
   * This function maps a character index forward through the rotor.
   * @param input Input to be mapped.
   * @return map_forwards The mapped input.
   */
  int map_forwards(int input);

  /*
   * This function maps a input backwards through the rotor.
   * @param input Input to be mapped.
   * @return map_backwards The mapped input.
   */
  int map_backwards(int input);

  /*
   * This function checks if the position is at the notch.
   * @return is_at_notch Returns a bool indicating if we're at the notch.
   */
  bool is_at_notch();

 /**
  * This rotates the rotor one position up.
  */
  void shift_up();
private:
  int add_turnover_notch(int number, int counter);
  int check_mapping(int number, int counter);
};

#endif

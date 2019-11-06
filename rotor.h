#include <iostream>
using namespace std;

/* This class reads rotor configuration files. */
class Rotor {

  ostream &err_stream;
  char **filenames;
  int **all_mappings = 0;
  int **all_notches = 0;
  int num_rotors;
  int *positions;

public:

 Rotor(ostream& stream, char **argv, int number_of_rotors):
  err_stream(stream), filenames(argv), num_rotors(number_of_rotors) {
    positions = new int[num_rotors];
  };

  ~Rotor() {
    delete[] positions;
  }

  int read_all_rotors();

  int read_rotor_positions(char *filename);

  /**
   * This function reads the rotor configuration from a file, and
   * returns an error if failed.
   * @param filename The filepath to the input config file.
   * @param mapping The mapping of each letter to another by zero-based
   * index.
   * @param turnover_notches The zero-based index of the notches on the
   * rotors.
   * @return read_rotors_config The error code is returned. If
   * unsuccessful, this is a non-zero error code.
   */
  int read_rotor_config(char *filename,
			int mapping[26],
			int *turnover_notches);

private:
  int add_turnover_notch(int number, int turnover_notches[26], int counter);
  int check_mapping(int number, int mapping[26], int counter);
};

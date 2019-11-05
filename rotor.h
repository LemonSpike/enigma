#include <iostream>
using namespace std;

/* This class reads rotor configuration files. */
class Rotor {

  ostream &err_stream;

public:

 Rotor(ostream& stream): err_stream(stream) {}

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
  int add_turnover_notch(ifstream &in, int *turnover_notches);
  int check_mapping(int number, int mapping[26], int counter);
};

#include <fstream>
#include <iostream>
#include "errors.h"
#include "plugboards/plugboard.h"

using namespace std;

int main(int argc, char** argv) {

  // Minimum number of command line arguments.
  const int MIN_ARG = 4;

  if (argc < MIN_ARG) {
    cerr << "A minimum of three command line arguments are required, in";
    cerr << " addition to the executable filepath." << endl;
    cerr << "The first argument should specify the plugboard's wiring map.";
    cerr << endl;
    cerr << "The second argument should specify the reflector's wiring map.";
    cerr << endl;
    cerr << "The next optional arguments can specify rotor wiring maps.";
    cerr << endl;
    cerr << "The last argument should specify the rotors' initial positions.";
    cerr << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  Plugboard plugboard;
  int error_code = plugboard.read_plugboard_config(argv[1]);

  return error_code;
}

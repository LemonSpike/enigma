#include <iostream>
#include "errors.h"
#include "enigma.h"

using namespace std;

int main(int argc, char** argv) {

  // Minimum number of command line arguments.
  const int MIN_ARG = 4;

  if (argc < MIN_ARG) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* ";
    cerr << "rotor-positions" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  Enigma enigma(cerr, argv, argc);

  int read = enigma.read_files();
  if (read != NO_ERROR)
    return read;
  char *message = "ZA";
  char *encrypted = enigma.encrypt_message(message);
  cout << encrypted << endl;

  cout << enigma.encrypt_message(encrypted) << endl;
  return NO_ERROR;
}

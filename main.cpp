#include <iostream>
#include <ctype.h>
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

  // Read configuration files to set up the machine.
  Enigma enigma(cerr, argv, argc);

  int read = enigma.read_files();
  if (read != NO_ERROR)
    return read;

  // Read through the input stream.
  char message;
  while (cin >> ws >> message && !cin.eof()) {
    if (!isupper(message)) {
      cerr << message << " is not a valid input character (input characters ";
      cerr << "must be upper case letters A-Z)!" << endl;
      return INVALID_INPUT_CHARACTER;
    }
    char encrypted = enigma.encrypt_message(message);
    cout << encrypted;
  }
  cout << endl;

  return NO_ERROR;
}

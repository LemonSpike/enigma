#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include <map>

using namespace std;

/* This class reads the plugboard config files and checks if they're 
   valid. */
class Plugboard {

public:
 /**
  * This function reads a plugboard config from a file with filename.
  * it updates the mapping if the config is valid, and otherwise
  * returns an error code. 
  *
  * @param filename File path of plugboard configuration.
  * @param mapping Key mapping of plugboard configuration.
  * @return read_plugboard_config An error code is returned. This is
  * non-zero if error arises, or zero otherwise.
  */
  int read_plugboard_config(const char *filename);

private:
  int read_number(ifstream& in, int& error_code);

  char get_character(ifstream& in, int& error_code);

  int get_digit(char value, int &error_code);

  int check_mapping(int contact_one,
		    int contact_two,
		    map<int, int> &mapping);
};

#endif

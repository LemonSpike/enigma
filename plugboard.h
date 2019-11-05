#ifndef PLUGBOARD_H
#define PLUGBOARD_H
#include <map>
using namespace std;

/* This class reads the plugboard config files and checks if they're
   valid. */
class Plugboard {

  ostream &err_stream;

public:
/**
 * This function initialises a Plugboard with the stderr stream.
 * @param stream the stderr stream.
 * @return Plugboard The class instance.
 */
 Plugboard(ostream& stream): err_stream(stream) {}

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
  int read_plugboard_config(const char *filename, map<int, int> mapping);

private:
  int check_mapping(int contact_one,
		    int contact_two,
		    map<int, int> mapping);
  void print_configuration_error();
};

#endif

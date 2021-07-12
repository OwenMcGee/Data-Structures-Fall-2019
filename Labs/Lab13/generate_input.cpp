#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>


// ================================================================= 
// ================================================================= 

// Info on command line arguments
void usage() {
    std::cerr << "Usage: <executable_name> <input count> <string length>  > output_file" << std::endl;
    exit(1);
}

// =================================================================
// =================================================================

// Create a random string of the specified length for testing
std::string random_string(int length) {
  std::string s = "";
  for (int i = 0; i < length; i++) {
    char c = 'a' + rand()%26;
    s += c;
  }
  return s;
}

// =================================================================
// =================================================================

int main(int argc, char* argv[]) {

  // parse the command line arguments
  if (argc != 3) {
    std::cerr << "Error: wrong number of arguments." << std::endl;
    usage();
  }

  int input_count = atoi(argv[1]);
  int string_length = atoi(argv[2]);

  srand(37);
  // using the time as a seed
  //srand(time(0));

  for (int i = 0; i < input_count; i++) {
    std::cout << random_string(string_length) << "\n";
  }

  return 0;
}

// =================================================================

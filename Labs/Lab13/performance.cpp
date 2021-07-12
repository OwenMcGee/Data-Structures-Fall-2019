#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>



// Info on command line arguments
void usage() {
  std::cerr << "Usage: <executable_name> <data structure> <operation>   < input_file   > output_file" << std::endl;
  std::cerr << "Usage:    <data structure> = vector, list, bst, priority_queue, hash_table" << std::endl;
  std::cerr << "Usage:    <operation>      = sort, remove_dups, mode" << std::endl;
  exit(1);
}


// prototypes of the functions that perform the operations
void vector_test(const std::string &operation, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count);
void list_test(const std::string &operation, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count);
void bst_test(const std::string &operation, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count);
void priority_queue_test(const std::string &operation, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count);
void hash_table_test(const std::string &operation, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count);


// ===================================================================================================

int main(int argc, char* argv[]) {

  // timing mechanism
  clock_t before_operation, after_operation;

  // parse the command line arguments
  if (argc != 3) {
    std::cerr << "Error: wrong number of arguments." << std::endl;
    usage();
  }
  std::string data_structure = argv[1];
  std::string operation = argv[2];

  // mark the time before we start
  before_operation = clock();

  int input_count;
  int output_count;
  
  // perform the operation
  if (data_structure == "vector") 
    vector_test(operation,std::cin,std::cout,input_count,output_count);
  else if (data_structure == "list")
    list_test(operation,std::cin,std::cout,input_count,output_count);
  else if (data_structure == "bst")  // STL set or map
    bst_test(operation,std::cin,std::cout,input_count,output_count);
  else if (data_structure == "priority_queue")
    priority_queue_test(operation,std::cin,std::cout,input_count,output_count);
  else if (data_structure == "hash_table")  // STL unordered_set or unordered_map
    hash_table_test(operation,std::cin,std::cout,input_count,output_count);
  else {
    std::cerr << "Error: unknown data structure: " << data_structure << std::endl;
    usage();
    exit(0);
  }

  // mark the time once we are done
  after_operation = clock();

  // print statistics
  double operation_time = double(after_operation-before_operation)/CLOCKS_PER_SEC;
  std::cerr << "operation time:     " << operation_time << std::endl;
  std::cerr << "input/output ratio: " << input_count << ":" << output_count << std::endl;
  return 0;
}

// ===================================================================================================

void vector_test(const std::string &operation, std::istream &istr, std::ostream &ostr, int &input_count, int &output_count) {

  // for all cases, simply put the data into a vector
  std::vector<std::string> vec;
  std::string s;
  input_count = 0;
  while (istr >> s) {
    vec.push_back(s);
    input_count++;
  }
  
  if (operation == "sort") {
    // use the vector sort algorithm
    sort(vec.begin(),vec.end());
    output_count = input_count;
    for (int i = 0; i < output_count; i++)
      ostr << vec[i] << "\n";

  } else if (operation == "remove_dups") {
    // don't reorder the elements, just do all pairwise comparisons
    output_count = 0;
    for (int i = 0; i < input_count; i++) {
      bool dup = false;
      for (int j = 0; j < i-1; j++) {
	if (vec[i] == vec[j]) {
	  dup = true;
	  break;
	}
      }
      // if it has not already been added to the output list
      if (!dup) {
	ostr << vec[i] << "\n";
	output_count++;
      }
    }

  } else if (operation == "mode") {
    // use the vector sort algorithm
    sort(vec.begin(),vec.end());
    int current_count = 1;
    std::string mode;
    int mode_count = 0;
    // keep track of two pointers into the structure
    std::vector<std::string>::iterator current = vec.begin();
    ++current;
    std::vector<std::string>::iterator previous = vec.begin();
    for (; current != vec.end(); ++current, ++previous) {
      if (*current == *previous) {
	// if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = *previous;
        mode_count = current_count;
        current_count = 1;
      } else {
        current_count = 1;
      }
    }
    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = *previous;
      mode_count = current_count;
    }
    // save the mode to the output vector
    output_count = 1;
    ostr << mode << "\n";
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
    exit(0);
  }
}

// ===================================================================================================

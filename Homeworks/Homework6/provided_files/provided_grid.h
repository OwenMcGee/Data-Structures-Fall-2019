#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class Grid {

public:

  // constructor loads the input puzzle board
  Grid (const std::string &filename);

  // simple accessors
  int width() { return endpoints[0].size(); }
  int height() { return endpoints.size(); }

  // print an ASCII art representation of the board
  void print();


  // A temporary hack to demonstrate how the print function works for solved boards
  void hardcoded_solution(const std::string &filename);
  
private:

  // a helper function for print
  char print_center(int i, int j);
  
  // a simple representation of the input puzzle
  std::vector<std::string> endpoints;

  // a representation of the solution paths
  //
  // NOTE note that the dimensions are off by one of the endpoints.
  // We have 1 fewer row of vertical path edges and 1 fewer column of
  // horizontal path edges.
  std::vector<std::string> verticals;
  std::vector<std::string> horizontals;
};

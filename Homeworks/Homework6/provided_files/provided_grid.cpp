#include "provided_grid.h"
#include <cassert>


// =============================================================================

// constructor loads the input puzzle board
Grid::Grid(const std::string &filename) {

  std::ifstream istr(filename);
  assert (istr.good());
  
  std::string s;
  while (istr >> s) { endpoints.push_back(s); }

  // initially all of the vertical and horizontal edges are blank!
  //
  // NOTE note that the dimensions are off by one of the endpoints.
  // We have 1 fewer row of vertical path edges and 1 fewer column of
  // horizontal path edges.
  verticals = std::vector<std::string>(height()-1,std::string(width(),' '));
  horizontals = std::vector<std::string>(height(),std::string(width()-1,' '));
}

// =============================================================================

void Grid::print() {

  // loop over the rows of the grid
  for (int j = 0; j < height(); j++) {

    // first print the horizontal cell boundaries
    for (int i = 0; i < width(); i++) {
      char bar = (j==0) ? '-' : ' ';
      char vertical = (j != 0) ? verticals[j-1][i] : bar;
      std::cout << "+" << bar << vertical << bar;
    }
    std::cout << "+" << std::endl;
    
    // then print 3 rows for the middle of each cell
    for (int k = 0; k < 3; k++) {

      for (int i = 0; i < width(); i++) {
        
        // what symbol should be printed in the center of this cell?
        char center = print_center(i,j);

        // what horizontal path edges run through this cell?
        char horizontal_left = (k == 1 && i != 0) ? horizontals[j][i-1] : ' ';
        char horizontal_right = (k == 1 && i+1 < width()) ? horizontals[j][i] : ' ';
        // the left edge of the cell
        char side = (i==0) ? '|' : horizontal_left;

        // do the printing
        if (k == 0) center = (j != 0) ? verticals[j-1][i] : ' ';
        if (k == 2) center = (j+1 < height()) ? verticals[j][i] : ' ';
        std::cout << side << horizontal_left << center << horizontal_right;
      }

      // the right edge of the whole grid
      std::cout << "|" << std::endl;
    }
  }

  // the lower edge of the whole grid
  for (int i = 0; i < width(); i++) {
    std::cout << "+" << std::string(3,'-');
  }
  std::cout << "+" << std::endl;
}

char Grid::print_center(int i, int j) {
  assert (i >= 0 && i < width());
  assert (j >= 0 && j < height());

  if (endpoints[j][i] != '.') { return endpoints[j][i]; }
  
  // if this is not an endpoint or bridge cell, look at the 4 edges
  // if any of them is a path, take that color for the center
  
  char up    = (j == 0)          ? ' ' : verticals  [j-1][i  ];
  char down  = (j == height()-1) ? ' ' : verticals  [j  ][i  ];
  char left  = (i == 0)          ? ' ' : horizontals[j  ][i-1];
  char right = (i == width()-1)  ? ' ' : horizontals[j  ][i  ];

  char center = up;
  if (center == ' ') center = down;
  if (center == ' ') center = right;
  if (center == ' ') center = left;
  return center;
}


// =============================================================================

// OBVIOUSLY, THIS IS NOT HOW YOU ARE SUPPOSED TO SOLVE THE ASSIGNMENT!
// this is for print function demonstration purposes only

void Grid::hardcoded_solution(const std::string &filename) {
  
  if (filename == "puzzle_1.txt") {
    horizontals[1][1] = 'b';
    horizontals[1][2] = 'b';

    horizontals[0][0] = 'a';
    horizontals[0][1] = 'a';
    horizontals[0][2] = 'a';
    horizontals[2][0] = 'a';
    horizontals[2][1] = 'a';
    horizontals[2][2] = 'a';
    verticals[0][0] = 'a';
    verticals[1][0] = 'a';
  }


  else if (filename == "puzzle_2.txt") {
    horizontals[2][0] = 'c';
    verticals[1][0] = 'c';

    horizontals[0][0] = 'a';
    horizontals[0][1] = 'a';
    horizontals[2][2] = 'a';
    verticals[0][2] = 'a';
    verticals[1][2] = 'a';
  
    horizontals[1][1] = 'b';
    horizontals[1][2] = 'b';
    verticals[0][3] = 'b';
  }

  else {
    std::cout << "ERROR: no hardcoded solution for " << filename << std::endl;
    exit(0);
  }

}


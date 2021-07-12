#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

//
// This is a standalone program for plotting star & line files (both
// input & output).  No changes should be necessary to this file.
//
//   g++ -g -Wall -Wextra plot_stars.cpp -o plot.out
//
//   ./plot.out Ursa_Minor.txt Ursa_Minor.html
//   ./plot.out example_input.txt example_input.html
//   ./plot.out example_output.txt example_output.html
//

// =================================================================
// Simple classes to hold the data from the stars & lines files

class Star_Data {
public:
  float x;
  float y;
  float apparent_magnitude;
  std::string name;
};

class Line_Data {
public:
  std::string name_a;
  std::string name_b;
};


// =================================================================
// Helper functions to prepare the SVG file

// Setup a black screen sized 1000x1000 to draw on
void draw_begin(std::ostream &ostr) {
  ostr << "<?xml version=\"1.0\" standalone=\"no\"?>" << std::endl;
  ostr << "<svg width=\"1000\" height=\"1000\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
  ostr << "<polygon points= \"0,0 0,1000 1000,1000 1000,0\" style=\"fill:#000000\" />" << std::endl;
}

// Draw the lines of the constellation with thin red lines
void draw_lines(std::ostream &plot_str,
                std::vector<Star_Data> &star_data, std::vector<Line_Data> &line_data) {
  for (unsigned int i = 0; i < line_data.size(); i++) {
    int a = -1;
    int b = -1;
    // find the indices of these vertices within the star vector
    for (unsigned int j = 0; j < star_data.size(); j++) {
      if (star_data[j].name == line_data[i].name_a) a = j;
      if (star_data[j].name == line_data[i].name_b) b = j;
    }
    assert (a != -1);
    assert (b != -1);
    // draw the line
    plot_str << "<line x1=\"" << star_data[a].x << "\" y1=\"" << star_data[a].y
             << "\" x2=\""    << star_data[b].x << "\" y2=\"" << star_data[b].y
             << "\" stroke=\"#ff0000\" stroke-width=\"1\" />" << std::endl;
  }
}

// Draw the stars of the contellations with white circles
void draw_stars(std::ostream &plot_str, std::vector<Star_Data> &star_data) {
  for (unsigned int i = 0; i < star_data.size(); i++) {

    // all unknown / unreliable star magnitudes (value is -1) are drawn with radius 2
    float radius = 2;
    if (star_data[i].apparent_magnitude > 0) {
      // scale the radius by the apparent magnitude
      // note: smaller magnitudes are brighter stars (bigger circles)
      radius = 8 / (star_data[i].apparent_magnitude);
      if (radius > 10) radius = 10;
      if (radius < 1) radius = 1;
    }
    // draw the circle
    plot_str << "<circle cx = \"" << star_data[i].x
             << "\" cy = \"" << star_data[i].y
             << "\" r = \"" << radius
             << "\" style=\"fill:#ffffff\" />" << std::endl;
  }
}

void draw_end(std::ostream &ostr) {
  ostr << "</svg>" << std::endl;
}


// =================================================================

int main(int argc, char* argv[]) {

  // This program expects 2 arguments, the input filename and the
  // output filename
  assert (argc == 3);
  std::ifstream istr(argv[1]);
  assert (istr.good());

  // load the data
  std::vector<Star_Data> star_data;
  std::vector<Line_Data> line_data;
  std::string token;
  while (istr >> token) {
    if (token == "star") {
      Star_Data sd;
      istr >> sd.x >> sd.y >> sd.apparent_magnitude >> sd.name;
      star_data.push_back(sd);
    } else if (token == "line") {
      Line_Data ld;
      istr >> ld.name_a >> ld.name_b;
      line_data.push_back(ld);
    } else if (token == "constellation") {
      // ignore the constellation name
      istr >> token;
    } else {
      assert(0);
    }
  }
  
  // plot the data
  std::ofstream plot_str(argv[2]);
  assert (plot_str.good());
  draw_begin(plot_str);
  draw_lines(plot_str,star_data,line_data);
  draw_stars(plot_str,star_data);
  draw_end(plot_str);
}

// =================================================================

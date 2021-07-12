#ifndef _constellation_h_
#define _constellation_h_

#include <list>
#include "star.h"

class Constellation{
	private:
		std::string name;
		std::list<Star> stars;
		std::list<std::pair<std::string,std::string>> lines;
	public:
		//constructor
		Constellation(std::string name_): name(name_){}

		//mutator methods
		void addStar(Star star) {stars.push_back(star);}
		void addLine(std::pair<std::string,std::string> line) {lines.push_back(line);}

		//accessor methods
		std::string getName() const {return name;}
		std::list<Star> getStars() const {return stars;}
		std::list<std::pair<std::string,std::string>> getLines() const {return lines;};

};



#endif
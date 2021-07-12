#ifndef _star_h_
#define _star_h_

#include <string>


class Star{
	public:
		//constructor
		Star(): xCoord(-1), yCoord(-1), brightness(-1), name(""), newName("") {}
		Star(double xCoord_, double yCoord_, double brightness_, std::string name_): xCoord(xCoord_), yCoord(yCoord_), brightness(brightness_), name(name_), newName("") {}

		//mutator methods
		void setBrightness(double brightness_) {brightness=brightness_;}
		void setName(std::string name_) {name=name_;}
		void setNewName(std::string newName_) {newName=newName_;}
		void solidifyName() {name=newName; newName="";}

		//accessor methods
		double x() const{return xCoord;}
		double y() const{return yCoord;}
		double getBrightness() const {return brightness;}
		std::string getName() const {return name;}
		std::string getNewName() const {return newName;}
	private:
		double xCoord;
		double yCoord;
		double brightness;
		std::string name;
		std::string newName;
};


#endif
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "constellation.h"





/*returns a double representing the multiplier for the difference between
  the lines drawn between center and outer1, and center and outer2.
  ex. if the distance between outer1 and center is twice as far as
  the distance between outer2 and center, 2.0 will be returned
*/
double getRelativeLength(Star & center, Star & outer1, Star & outer2){
	double length1= sqrt(abs(pow((outer1.x()-center.x()),2)+pow((outer1.y()-center.y()),2)));
	double length2= sqrt(abs(pow((outer2.x()-center.x()),2)+pow((outer2.y()-center.y()),2)));
	return length1/length2;
}




//use law of cosines to determine the angle about "center" using relative lengths
double getAngle(Star & center, Star & outer1, Star & outer2){
	std::cout<<center.x()<<" "<<outer1.x()<<" "<<outer2.x()<<" "<<center.y()<<" "<<outer1.y()<<" "<<outer2.y()<<"\n\n";
	double angle;
	//obtain relative lengths (the line across from "center" being assumed as 1 unit long)
	double outer1Length=getRelativeLength(outer1, center, outer2);
	double outer2Length=getRelativeLength(outer2, center, outer1);

	std::cout<<outer1Length<<" "<<outer2Length<<"\n\n";
	//the *180/atan(1)*4 converts from radians to degrees
	angle=acos((pow(outer1Length,2)+pow(outer2Length,2)-1)/(2*outer1Length*outer2Length)) * 180 / (atan(1)*4);
	std::cout<<angle<<"\n\n";
	return angle;
}


//compares two sets of three stars, returns false if the relative lengths, angles, recorded brightnesses and recorded names are
//within acceptable limits / align with recorded data
bool checkComparable(Star center, Star outer1, Star outer2, Star constCenter, Star constOuter1, Star constOuter2, double epsilon){
	//check the angles between the stars are within acceptable limits
	if(abs(getAngle(center, outer1, outer2) - getAngle(constCenter, constOuter1, constOuter2)) >= epsilon){
		return false;
	}
	//check the relative lengths between the stars are within acceptable limits
	if(abs(getRelativeLength(center, outer1, outer2) - getRelativeLength(constCenter, constOuter1, constOuter2)) >= epsilon){
		return false;
	}
	//check that all stars are unique
	if(center.x()==outer1.x() && center.y() == outer1.y()){
		return false;
	}
	if(center.x()==outer2.x() && center.y() == outer2.y()){
		return false;
	}
	if(outer2.x()==outer1.x() && outer2.y() == outer1.y()){
		return false;
	}
	if(constCenter.x()==constOuter1.x() && constCenter.y() == constOuter1.y()){
		return false;
	}
	if(constCenter.x()==constOuter2.x() && constCenter.y() == constOuter2.y()){
		return false;
	}
	if(constOuter2.x()==constOuter1.x() && constOuter2.y() == constOuter1.y()){
		return false;
	}
	//check the stars' measured brightness is either unknown/unreliable or the same as/nearly the recorded brightness
	if(center.getBrightness() != -1 && center.getBrightness() - constCenter.getBrightness() >= epsilon){
		return false;
	}
	if(outer1.getBrightness() != -1 && outer1.getBrightness() - constOuter1.getBrightness() >= epsilon){
		return false;
	}
	if(outer2.getBrightness() != -1 && outer2.getBrightness() - constOuter2.getBrightness() >= epsilon){
		return false;
	}
	//check the stars' names are either placeholders or the same as the recorded name
	if((center.getName().substr(0,5) != "STAR_" && center.getName() != constCenter.getName()) || (center.getNewName() != "" && center.getNewName() != constCenter.getName())){
		return false;
	}
	if((outer1.getName().substr(0,5) != "STAR_" && outer1.getName() != constOuter1.getName()) || (outer1.getNewName() != "" && outer1.getNewName() != constOuter1.getName())){
		return false;
	}
	if((outer2.getName().substr(0,5) != "STAR_" && outer2.getName() != constOuter2.getName()) || (outer2.getNewName() != "" && outer2.getNewName() != constOuter2.getName())){
		return false;
	}
	std::cout<<"PASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\n\n";
	std::cout<<"extra info: "<<getAngle(center, outer1, outer2) - getAngle(constCenter, constOuter1, constOuter2)<<"\n\nend\n\n";
	return true;
}





bool checkRest(std::list<Star>::iterator iter, std::string outputFile, std::list<Star> constStars, std::list<Star> stars, Star center, Star outer2, Star constCenter, Star constOuter2Temp, double epsilon, Constellation constellation){
	std::ofstream ostr(outputFile);
	assert(ostr.good());
	bool found;
	for(std::list<Star>::iterator constOuter1Iter=iter; constOuter1Iter!= constStars.end(); constOuter1Iter++){
		found=false;
		for(std::list<Star>::iterator outer1Iter=stars.begin(); outer1Iter!=stars.end(); outer1Iter++){
			if(checkComparable(center, *outer1Iter, outer2, constCenter, *constOuter1Iter, constOuter2Temp, epsilon)){
				//adjusts the brightness and name of the newly found star
				outer1Iter->setBrightness(constOuter1Iter->getBrightness());
				outer1Iter->setNewName(constOuter1Iter->getName());

				found=true;
				break;
			}
		}
		if(found==false){
			break;
		}
	}


	if(found!=false){


		std::cout<<"FOUND CONSTELLATION "<<constellation.getName()<<"\n";
		ostr<<"constellation   "<<constellation.getName()<<"\n";
		for(std::list<Star>::iterator outputIter=stars.begin(); outputIter!=stars.end(); outputIter++){
			if(outputIter->getNewName() != ""){
				std::cout<<"assigning  "<<outputIter->getName()<<"  "<<outputIter->getNewName()<<"\n";
				outputIter->solidifyName();
			}
			ostr<<"star   "<<std::setw(6)<<std::right<<std::fixed<<std::setprecision(2)<<outputIter->x()<<"   "<<std::right<<std::setw(6)<<outputIter->y()<<"   "<<std::setw(5)<<outputIter->getBrightness()<<"   "<<std::left<<outputIter->getName()<<"\n";
		}

		std::list<std::pair<std::string,std::string>> lines=constellation.getLines();
		ostr<<std::setw(1);
		for(std::list<std::pair<std::string,std::string>>::iterator linesIter=lines.begin(); linesIter!=lines.end(); linesIter++){
			ostr<<"line   "<<linesIter->first<<"   "<<linesIter->second<<"\n";
		}

		return true;
	}

	for(std::list<Star>::iterator outputIter=stars.begin(); outputIter!=stars.end(); outputIter++){
		outputIter->setNewName("");
		outputIter->setBrightness(-1);
	}


	return false;


}





/*compares the list of stars against each given constellation to attempt to find a match. If a match is found,
  updates the stars names' and brightness, and prints out the changes and the found constellation
*/
void analyzeCharts(std::list<Star> & stars, std::list<Constellation> & constellations, std::string & outputFile){
	//acceptable error between angle, distance, and brightness (if applicable)
	const double epsilon=0.01;



	//go through all given constellations
	for(std::list<Constellation>::iterator constellationsIter=constellations.begin(); constellationsIter!=constellations.end(); constellationsIter++){
		std::list<Star> constStars=constellationsIter->getStars();
		std::list<Star>::iterator iter=constStars.begin();
		Star constCenter=*iter;
		iter++;
		Star constOuter1=*iter;
		iter++;
		Star constOuter2Temp=*iter;
		iter++;

		//find the stars that match the first three in the constellation (if they exist)
		//the first two of which will later be used as a constant to compare against
		Star center;
		Star outer2;
		bool foundFirstThree=false;
		for(std::list<Star>::iterator centerIter=stars.begin(); centerIter!=stars.end() && foundFirstThree==false; centerIter++){
			for(std::list<Star>::iterator outer1Iter=stars.begin(); outer1Iter!=stars.end() && foundFirstThree==false; outer1Iter++){
				for(std::list<Star>::iterator outer2Iter=stars.begin(); outer2Iter!=stars.end() && foundFirstThree==false; outer2Iter++){
					if(centerIter!=outer1Iter && centerIter!=outer2Iter && outer1Iter!=outer2Iter){
						if(checkComparable(*centerIter, *outer1Iter, *outer2Iter, constCenter, constOuter1, constOuter2Temp, epsilon)){
							//adjusts the brightness and names of the three stars
							centerIter->setBrightness(constCenter.getBrightness());
							centerIter->setNewName(constCenter.getName());
							outer1Iter->setBrightness(constOuter1.getBrightness());
							outer1Iter->setNewName(constOuter1.getName());
							outer2Iter->setBrightness(constOuter2Temp.getBrightness());
							outer2Iter->setNewName(constOuter2Temp.getName());
							center=*centerIter;
							outer2=*outer2Iter;

							std::cout<<centerIter->getName()<<" "<<outer1Iter->getName()<<" "<<outer2Iter->getName()<<"\n\n";

							if(checkRest(iter, outputFile, constStars, stars, center, outer2, constCenter, constOuter2Temp, epsilon, *constellationsIter)==true){
								return;
							}
						}
					}
				}
			}
		}


	}

	std::cout<<"No matching constellation found\n";



}





int main(int argc, char* argv[]) {
	std::list<Star> stars;
	std::list<Constellation> constellations;
	std::string outputFile;

	for(int i=1;i<argc;i++){
		if(std::string(argv[i])=="-i" || std::string(argv[i])=="--input"){
			assert(argc>i+1);
			std::ifstream istr((std::string(argv[i+1])));
			assert(istr.good());

			std::string inStr;
			while(istr>>inStr){
				double x;
				double y;
				double brightness;
				std::string name;

				assert(inStr=="star");
				istr>>inStr;
				x=std::stod(inStr);
				istr>>inStr;
				y=std::stod(inStr);
				istr>>inStr;
				brightness=std::stod(inStr);
				istr>>inStr;
				name=inStr;
				Star newStar(x, y, brightness, name);
				stars.push_back(newStar);
			}
			i++;
		}
		else if(std::string(argv[i])=="-o" || std::string(argv[i])=="--output"){
			assert (argc>i+1);
			outputFile=std::string(argv[i+1]);
			i++;
		}
		else if(std::string(argv[i])=="-l"){
			assert (argc>i+1);
			std::ifstream istr((std::string(argv[i+1])));
			assert(istr.good());

			std::string inStr;
			istr>>inStr;
			assert(inStr=="constellation");
			istr>>inStr;
			Constellation newConst(inStr);
			while(istr>>inStr){
				if(inStr=="star"){
					double x;
					double y;
					double brightness;
					std::string name;

					istr>>inStr;
					x=std::stod(inStr);
					istr>>inStr;
					y=std::stod(inStr);
					istr>>inStr;
					brightness=std::stod(inStr);
					istr>>inStr;
					name=inStr;
					Star newStar(x, y, brightness, name);
					newConst.addStar(newStar);
				}
				else{
					assert(inStr=="line");
					std::string first;
					std::string second;

					istr>>inStr;
					first=inStr;
					istr>>inStr;
					second=inStr;
					std::pair<std::string, std::string> newLine(first, second);
					newConst.addLine(newLine);
				}
			}

			constellations.push_back(newConst);
			i++;
		}
		else{
			std::cout << "ERROR: UNKNOWN ARGUMENT '" << argv[i] << "'" << std::endl;
			exit(1);
		}
	}

	assert(outputFile!="");
	analyzeCharts(stars, constellations, outputFile);
	exit(0);
}

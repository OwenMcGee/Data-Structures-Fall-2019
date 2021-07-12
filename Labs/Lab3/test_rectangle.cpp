#include <iostream>
#include "Point2D.h"
#include "Rectangle.h"

int main(){


	Point2D testPoint(2,4);
	std::cout<<testPoint.x()<<'\n';
	std::cout<<testPoint.y()<<'\n';
	testPoint.set(5,10);
	std::cout<<testPoint.x()<<'\n';
	std::cout<<testPoint.y()<<'\n';

	Point2D testPoint2(10,15);
	Rectangle testRectangle(testPoint, testPoint2);
	print_rectangle(testRectangle);
	if(testRectangle.is_point_within(testPoint)){
		std::cout<<"true\n";
	}
	else{
		std::cout<<"false\n";
	}

	if(testRectangle.add_point(Point2D(100,100))){
		std::cout<<"true\n";
	}
	else{
		std::cout<<"false\n";
	}

	if(testRectangle.add_point(Point2D(7,12))){
		std::cout<<"true\n";
	}
	else{
		std::cout<<"false\n";
	}

	if(testRectangle.is_point_within(Point2D(100,100))){
		std::cout<<"true\n";
	}
	else{
		std::cout<<"false\n";
	}

	if(testRectangle.is_point_within(Point2D(7,12))){
		std::cout<<"true\n";
	}
	else{
		std::cout<<"false\n";
	}


	Rectangle testRectangle2(Point2D(0,50), Point2D(50,100));
	testRectangle2.add_point(Point2D(25,75));


	std::vector<Point2D> testingVector;
	testingVector=points_in_both(testRectangle,testRectangle2);
	for(unsigned int i=0;i<testingVector.size();i++){
		std::cout<<testingVector[i].x()<<" "<<testingVector[i].y()<<"\n";
	}

	return 0;
}
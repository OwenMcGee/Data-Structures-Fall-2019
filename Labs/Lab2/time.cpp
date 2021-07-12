#include <iostream>
#include <sstream>
#include <algorithm>
#include "time.h"

Time::Time(){
	hour=0;
	minute=0;
	second=0;
//	std::cout<<"Default constructor called\n";
}

Time::Time(int hr, int min, int sec){
	hour=hr;
	minute=min;
	second=sec;
//	std::cout<<"Constructor with values called, hour: "<<hour<<" ,minute: "<<minute<<" ,second: "<<second<<"\n";
}

Time::Time(const Time &timeToCopy){
	hour=timeToCopy.getHour();
	minute=timeToCopy.getMinute();
	second=timeToCopy.getSecond();
//	std::cout<<"Copy constructor called, hour: "<<hour<<" ,minute: "<<minute<<" ,second: "<<second<<"\n";
}

int Time::getHour() const{
	return hour;
}

int Time::getMinute() const{
	return minute;
}

int Time::getSecond() const{
	return second;
}

void Time::setHour(int hr){
	hour=hr;
}

void Time::setMinute(int min){
	minute=min;
}

void Time::setSecond(int sec){
	second=sec;
}

void Time::PrintAMPM() const{
	std::string finalOutput="";

	if(hour>12)
		finalOutput=std::to_string(hour-12)+":";
	else if(hour==0)
		finalOutput="12:";
	else
		finalOutput=std::to_string(hour)+":";
	
	if(minute<10)
		finalOutput+="0";
	finalOutput+=std::to_string(minute)+":";

	if(second<10)
		finalOutput+="0";
	finalOutput+=std::to_string(second)+" ";

	if(hour<12||hour==24||(hour==12&&minute==0&&second==0))
		finalOutput+="am";
	else
		finalOutput+="pm";
//||(hour==12&&(minute>0||second>0))
//	std::cout<<"Test: minutes: "<<minute<<"\n";
	std::cout<<finalOutput+"\n";
}

bool IsEarlierThan(const Time& t1, const Time& t2){
	if(t1.getHour()<t2.getHour())
		return true;
	else if(t1.getHour()>t2.getHour())
		return false;
	else{
		if(t1.getMinute()<t2.getMinute())
			return true;
		else if(t1.getMinute()>t2.getMinute())
			return false;
		else{
			if(t1.getSecond()<t2.getSecond())
				return true;
			else
				return false;
		}
	}
}






std::string triangle="";
for(int i=0;i<height;i++){
	std::string line="";
	for(int j=0;j<height-i;j++){
		line+=" ";
	}
	line+="*";
	for(int j=height+1;j<height+i;j++){
		line+="a";
	}
	line+="*";
	triangle+=line+="\n";
}



std::string triangle(height-1,'*');
for(int i=1;i<height-1;i++){
	std::string line(height-i,'*');
	for(int j=height;j<height+i;j++){
		line+="a";
	}
	line+="*";
	triangle+="\n"+line;
}
std::string stars(height*2-1,'*');
triangle+="\n"+stars;





0=0
1=1
2=3
3=5
4=7
5=9
6
7
8
9

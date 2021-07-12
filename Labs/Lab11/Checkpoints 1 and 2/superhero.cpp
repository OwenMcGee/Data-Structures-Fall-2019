#include <string>
#include "superhero.h"

Superhero::Superhero(const std::string & name_,const std::string & identity_,const std::string & power_){
	name=name_;
	identity=identity_;
	power=power_;
	good=true;
}

bool Superhero::operator==(std::string guess){
	return guess==identity;
}


bool Superhero::operator!=(std::string guess){
	return guess!=identity;
}

bool Superhero::operator>(const Superhero & hero){
	return name<hero.getName();
}

void Superhero::operator-(){
	good=!good;
}


std::ostream& operator<<(std::ostream & outStr, const Superhero & hero){
	return outStr<<"Superhero "<<hero.getName()<<" has power "<<hero.getPower()<<"\n";
}

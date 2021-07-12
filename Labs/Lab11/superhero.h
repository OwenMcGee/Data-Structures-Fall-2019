#ifndef _superhero_h_
#define _superhero_h_
#include <string>
#include <ostream>


class Superhero{
	public:
		Superhero(const std::string & name_,const std::string & identity_,const std::string & power_);

		std::string getName() const{return name;};
		std::string getPower() const{return power;};
		bool isGood() const{return good;};

		bool operator==(std::string guess);
		bool operator!=(std::string guess);
		bool operator>(const Superhero & otherHero);

		void operator-();


	private:
		bool good;
		std::string name;
		std::string identity;
		std::string power;
};

std::ostream& operator<<(std::ostream & outStr, const Superhero & hero);



#endif
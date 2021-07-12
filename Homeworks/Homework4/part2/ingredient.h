#ifndef _ingredient_h_
#define _ingredient_h_

#include <string>

class Ingredient{
	private:
		std::string name;
		int units;
	public:
		Ingredient(std::string nm, int amount);

		//accessors
		std::string getName() const{return name;};
		int getUnits() const{return units;};

		void add(int amount){units+=amount;};
		void subtract(int amount){units-=amount;};
		std::string print() const;
};

bool compareQuantityFirst(const Ingredient & ingred1, const Ingredient & ingred2);
bool compareAlphabetically(const Ingredient & ingred1, const Ingredient & ingred2);

#endif
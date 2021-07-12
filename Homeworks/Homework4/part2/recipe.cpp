#include "recipe.h"
#include <iostream>
#include <list>
#include <string>


void Recipe::addIngredient(std::string ingredientName, int units){
	Ingredient newIngredient(ingredientName, units);
	ingredients.push_back(newIngredient);
}

void Recipe::printRecipe(std::ostream & outStr) {

	ingredients.sort(compareAlphabetically);

	//also sort right now (or maybe have another method that sorts, whatever)
	outStr<<"To make "<<name<<", mix together:\n";
	std::list<Ingredient>::iterator iter=ingredients.begin();
	while(iter!=ingredients.end()){
		outStr<<"  "<<(*iter).print();
		iter++;
	}
}

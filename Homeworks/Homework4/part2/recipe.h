#ifndef _recipe_h_
#define _recipe_h_

#include "ingredient.h"
#include <iostream>
#include <list>
#include <string>

class Recipe{
	private:
		std::string name;
		std::list<Ingredient> ingredients;
	public:
		Recipe();
		Recipe(std::string nm):name(nm){};		//is this the right syntax?

		std::string getName() const{return name;};
		std::list<Ingredient> getIngredients() const{return ingredients;};

		void addIngredient(std::string ingredientName, int units);
		void printRecipe(std::ostream & outStr) ;

};


#endif
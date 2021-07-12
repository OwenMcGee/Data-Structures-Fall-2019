#ifndef _kitchen_h_
#define _kitchen_h_
#include "ingredient.h"
#include "recipe.h"
#include <iostream>
#include <list>
#include <string>

class Kitchen{
	private:
		std::list<Ingredient> ingredients;
	public:
		void addIngredient(std::string ingredientName, int units);
		void printIngredients(std::ostream & outStr);
		void make(const Recipe & recipe,std::ostream & outStr);

};


#endif
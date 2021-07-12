#include "kitchen.h"
#include "recipe.h"		//CHECK IF I NEED THESE OR IF THE .H COVERS IT
#include "ingredient.h"
#include <iostream>
#include <list>
#include <string>


void Kitchen::addIngredient(std::string ingredientName, int units){
	std::list<Ingredient>::iterator iter=ingredients.begin();
	while(iter!=ingredients.end()){
		if((*iter).getName()==ingredientName){
			(*iter).add(units);
			return;
		}
		iter++;
	}
	ingredients.push_back(Ingredient(ingredientName, units));
}

void Kitchen::printIngredients(std::ostream & outStr){

	ingredients.sort(compareQuantityFirst);

	//SORT HERE
	outStr<<"In the kitchen:\n";
	std::list<Ingredient>::iterator iter=ingredients.begin();
	while(iter!=ingredients.end()){
		outStr<<"  "<<(*iter).print();
		iter++;
	}

}


void Kitchen::make(const Recipe & recipe,std::ostream & outStr){
	std::list<Ingredient> recipeIngredients=recipe.getIngredients();
	std::list<Ingredient> needToBuy;
	std::list<Ingredient>::iterator iter1=recipeIngredients.begin();	
	std::list<Ingredient>::iterator iter2;
	bool haveEnough=true;

	while(iter1!=recipeIngredients.end()){
		iter2=ingredients.begin();
		bool foundMatch=false;
		while(iter2!=ingredients.end()){
			if((*iter2).getName()==(*iter1).getName()){
				foundMatch=true;
				if((*iter2).getUnits()<(*iter1).getUnits()){
					needToBuy.push_back(Ingredient((*iter1).getName(),(*iter1).getUnits()-(*iter2).getUnits()));
					haveEnough=false;
					break;
				}
			}
			iter2++;
		}
		if(!foundMatch){
			haveEnough=false;
			needToBuy.push_back(Ingredient((*iter1).getName(), (*iter1).getUnits()));
		}
		iter1++;
	}

	if(!haveEnough){
		needToBuy.sort(compareAlphabetically);
		outStr<<"Cannot make "<<recipe.getName()<<", need to buy:\n";
		std::list<Ingredient>::iterator needIter=needToBuy.begin();
		while(needIter!=needToBuy.end()){
			outStr<<"  "<<(*needIter).print();
			needIter++;
		}
	}
	else{
		iter1=recipeIngredients.begin();
		while(iter1!=recipeIngredients.end()){
			iter2=ingredients.begin();
			while(iter2!=ingredients.end()){
				if((*iter2).getName()==(*iter1).getName()){
					(*iter2).subtract((*iter1).getUnits());
					if((*iter2).getUnits()==0){
						ingredients.erase(iter2);
					}
					break;
				}
				iter2++;
			}
			iter1++;
		}
		outStr<<"Made "<<recipe.getName()<<"\n";
	}



}

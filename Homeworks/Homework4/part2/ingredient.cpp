#include "ingredient.h"
#include <list>
#include <string>

Ingredient::Ingredient(std::string nm, int amount){
	name=nm;
	units=amount;
}


/*
void Ingredient::add(int amount){
	units+=amount;
}
*/

//this SHOULD PROBABLY BE CONST
std::string Ingredient::print() const{
	std::string output=std::to_string(units);
	output+=" unit";
	if(units!=1){
		output+="s";
	}
	output+=" of ";
	output+=name;
	output+="\n";
	return output;
}

bool compareQuantityFirst(const Ingredient & ingred1, const Ingredient & ingred2){
	if(ingred1.getUnits()<ingred2.getUnits()){
		return true;
	}
	else if(ingred1.getUnits()>ingred2.getUnits()){
		return false;
	}
	else{
		if(ingred1.getName()<ingred2.getName()){
			return true;
		}
		else{
			return false;
		}
	}	
}

bool compareAlphabetically(const Ingredient & ingred1, const Ingredient & ingred2){
	if(ingred1.getName()<ingred2.getName()){
		return true;
	}
	else{
		return false;
	}
}
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "team.h"
#include "player.h"

Team::Team(){
	name="";
	wins=0;
	losses=0;
	ties=0;
	penalties=0;
	goals=0;
}

Team::Team(std::string teamName){
	name=teamName;
	wins=0;
	losses=0;
	ties=0;
	penalties=0;
	goals=0;
}


void Team::incrementWins(){
	wins++;
}

void Team::incrementLosses(){
	losses++;
}

void Team::incrementTies(){
	ties++;
}

void Team::incrementPenalties(){
	penalties++;
}

void Team::incrementGoals(){
	goals++;
}

std::string Team::getName() const{
	return name;
}

int Team::getGoals() const{
	return goals;
}

std::ostringstream Team::printTeam() const{
	std::ostringstream output (std::ostringstream::ate);
	output<<std::setw(20)<<std::left<<name;
	output<<" "<<std::setw(3)<<std::right<<wins;
	output<<" "<<std::setw(3)<<std::right<<losses;
	output<<" "<<std::setw(3)<<std::right<<ties;
	output<<"   "<<std::fixed<<std::setprecision(2)<<calculateWinPercentage();
	output<<"   "<<std::setw(5)<<std::right<<calculateTotalGoals();
	output<<"   "<<std::setw(9)<<std::right<<calculateTotalPenalties();
	output<<"\n";
	return output;
}


double Team::calculateWinPercentage() const{
	return (double)(wins+(double)ties*.5)/(double)(wins+losses+ties);
}

int Team::calculateTotalGoals() const{
	int goals=0;
	for(int i=0;i<players.size();i++){
		goals+=players[i].getGoals();
	}
	return goals;
}

int Team::calculateTotalPenalties() const{
	int penalties=0;
	for(int i=0;i<players.size();i++){
		penalties+=players[i].getPenalties();
	}
	return penalties;
}

//necessary to allow for sorting
bool operator<(const Team& first, const Team& second){
	if(first.calculateWinPercentage()>second.calculateWinPercentage()){
		return true;
	}
	else if(first.calculateWinPercentage()<second.calculateWinPercentage()){
		return false;
	}
	else{
		if(first.getGoals()>second.getGoals()){
			return true;
		}
		else if(first.getGoals()<second.getGoals()){
			return false;
		}
		else{
			return(first.getName()<second.getName());
		}
	}
}
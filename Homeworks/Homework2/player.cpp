#include <iomanip>
#include <sstream>
#include <iostream>
#include "player.h"

Player::Player(){
	name="";
	team="";
	goals=0;
	assists=0;
	penalties=0;
}

Player::Player(std::string playerName, std::string teamName){
	name=playerName;
	team=teamName;
	goals=0;
	assists=0;
	penalties=0;
}

void Player::incrementGoals(){
	goals++;
}

void Player::incrementAssists(){
	assists++;
}

void Player::incrementPenalties(){
	penalties++;
}

std::string Player::getName() const{
	return name;
}

int Player::getGoals() const{
	return goals;
}

int Player::getAssists() const{
	return assists;
}

int Player::getPenalties() const{
	return penalties;
}

//outputs the Player's information
std::ostringstream Player::print() const{
	std::ostringstream output (std::ostringstream::ate);

	output<<std::setw(30)<<std::left<<name;
	output<<" "<<std::setw(21)<<std::left<<team;
	output<<" "<<std::setw(5)<<std::right<<goals;
	output<<"    "<<std::setw(7)<<std::right<<assists;
	output<<"    "<<std::setw(9)<<std::right<<penalties;
	output<<"\n";
	return output;
}

//necessary to allow for sorting
bool operator< (const Player& first, const Player& second){
	if((first.getGoals()+first.getAssists())>(second.getGoals()+second.getAssists())){
		return true;
	}
	else if((first.getGoals()+first.getAssists())<(second.getGoals()+second.getAssists())){
		return false;
	}
	else{
		if(first.getPenalties()<second.getPenalties()){
			return true;
		}
		else if(first.getPenalties()>second.getPenalties()){
			return false;
		}
		else{
			return (first.getName()<second.getName());
		}
	}
}
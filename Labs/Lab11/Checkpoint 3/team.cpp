#include <cassert>
#include <algorithm>
#include "team.h"
#include "superhero.h"

bool isvowel(char c) {
	if (!isalpha(c)) return false;
	char c2 = tolower(c);
	return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
	return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
	if (superheroes.size() == 0) 
		return "";
	std::string answer;
	std::list<Superhero>::const_iterator itr;
	for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
		char first_consonant = ' ';
		char first_vowel = ' ';
		std::string true_identity = itr->getTrueIdentity();
		for (unsigned int j = 0; j < true_identity.size(); j++) {
			if (first_consonant == ' ' && isconsonant(true_identity[j]))
				first_consonant = tolower(true_identity[j]);
			if (first_vowel == ' ' && isvowel(true_identity[j]))
				first_vowel = tolower(true_identity[j]);
		}
		answer.push_back(first_consonant);
		answer.push_back(first_vowel);
	}

	answer[0] = toupper(answer[0]);
	return answer;
}

void Team::operator+=(const Superhero &a){
	superheroes.push_back(a);
}

void Team::operator-=(const Superhero &a){
	std::list<Superhero>::iterator iter=superheroes.begin();

	while(iter!=superheroes.end()){
		if(*iter==a.getName()){
			superheroes.erase(iter);
			break;
		}
		iter++;
	}


}

Team operator+(const Team &a, const Superhero &b){
	Team newTeam=a;
	newTeam+=b;
	return newTeam;
}

Team operator+(const Superhero &a, const Superhero &b){
	Team newTeam;
	newTeam+=a;
	newTeam+=b;
	return newTeam;
}

Team operator+(const Team &a, const Team &b){
	Team newTeam;
	std::list<Superhero>::const_iterator iter=a.getSuperheroes().begin();
	while(iter!=a.getSuperheroes().end()){
		newTeam+=*iter;
		iter++;
	}
	iter=b.getSuperheroes().begin();
	while(iter!=b.getSuperheroes().end()){
		newTeam+=*iter;
		iter++;
	}
	return newTeam;
}

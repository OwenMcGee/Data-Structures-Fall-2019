#ifndef __team_h_
#define __team_h_

#include <vector>
#include "player.h"

class Team{
	private:
		std::vector<Player> players;
		std::string name;
		int wins;
		int losses;
		int ties;
		int penalties;
		int goals;
	public:
		Team();
		Team(std::string teamName);

		//mutators
		void incrementWins();
		void incrementLosses();
		void incrementTies();
		void incrementPenalties();
		void incrementGoals();

		//accessors
		std::string getName() const;
		int getGoals() const;

		//calculations
		double calculateWinPercentage() const;
		int calculateTotalGoals() const;
		int calculateTotalPenalties() const;

		//print data table
		std::ostringstream printTeam() const;
};
//operator< to allow sorting
bool operator< (const Team& first, const Team& second);

#endif
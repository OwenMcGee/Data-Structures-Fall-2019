#ifndef __player_h_
#define __player_h_


class Player{
	private:
		std::string name;
		std::string team;
		int goals;
		int assists;
		int penalties;
	public:
		Player();
		Player(std::string playerName, std::string teamName);

		//mutators
		void incrementGoals();
		void incrementAssists();
		void incrementPenalties();

		//accessors
		std::string getName() const;
		int getGoals() const;
		int getAssists() const;
		int getPenalties() const;

		//toString
		std::ostringstream print() const;
};

//operator< to allow sorting
bool operator< (const Player& first, const Player& second);

#endif
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "team.h"
#include "player.h"

//takes in a team's name  and the list of all teama
//if the team exists already, returns their location in the list
//otherwise creates the team and returns their new location
int accessTeam(std::string teamName, std::vector<Team>& teams){
	for(int i=0;i<teams.size();i++){
		if(teams[i].getName()==teamName){
			return i;
		}
	}
	teams.push_back(Team(teamName));
	return teams.size();
}

//takes in a player's name and team and the list of all players
//if the player exists already, returns their location in the list
//otherwise creates the player and returns their new location
Player accessPlayer(std::vector<Player>& players, std::string playerName, std::string teamName){
	for(int i=0;i<players.size();i++){
		if(players[i].getName()==playerName){
			return players[i];
		}
	}
	players.push_back(Player(playerName,teamName));
	return players.back();
}

//takes in an ifstream and fills the players vector with all relevant
//information relating to a player printout
void playerStatsReading(std::ifstream & inStr, std::vector<Player> & players){
	std::string teamName;
	Player currentPlayer;
	std::string currentInput;
	bool moreToRead=true;

	//skip past useless information (could be done with a loop but this is nice and visual)
	//also checks that there are in fact words to be read
	if(inStr>>currentInput){
		inStr>>currentInput;
		inStr>>currentInput;
		inStr>>currentInput;
		inStr>>currentInput;
		inStr>>currentInput;
		inStr>>currentInput;
		inStr>>currentInput;
	}
	else
		return;

	//looping through one or more games, gathering relevant information
	while(moreToRead){
		if(currentInput=="Period"){
			inStr>>currentInput;
			inStr>>currentInput;
		}
		else if(currentInput=="Overtime"){
			inStr>>currentInput;
		}
		else if(currentInput=="Final"){
			inStr>>currentInput;
			inStr>>currentInput;
			inStr>>currentInput;
			inStr>>currentInput;
			inStr>>currentInput;
			if(inStr>>currentInput){
				inStr>>currentInput;
				inStr>>currentInput;
				inStr>>currentInput;
				inStr>>currentInput;
				inStr>>currentInput;
				inStr>>currentInput;
			}
			else{
				moreToRead=false;
			}
		}
		else{
			inStr>>currentInput;
			teamName=currentInput;
			inStr>>currentInput;
			if(currentInput=="penalty"){
				inStr>>currentInput;
				currentPlayer=accessPlayer(players, currentInput, teamName);
				currentPlayer.incrementPenalties();
				inStr>>currentInput;
				inStr>>currentInput;
				inStr>>currentInput;
			}
			else if(currentInput=="goal"){
				inStr>>currentInput;
				currentPlayer=accessPlayer(players, currentInput, teamName);
				currentPlayer.incrementGoals();
				inStr>>currentInput;
				if(currentInput=="("){
					inStr>>currentInput;
					while(currentInput!=")"){
						currentPlayer=accessPlayer(players, currentInput, teamName);
						currentPlayer.incrementAssists();
						inStr>>currentInput;
					}
					inStr>>currentInput;
				}
			}
		}
	}
}



void teamStatsReading(std::ifstream & inStr, std::vector<Team> & teams){

	int team1Index;
	int team2Index;
	int currentTeamIndex;
	std::string currentInput;
	bool moreToRead=true;

	if(inStr>>currentInput){
		inStr>>currentInput;
		inStr>>currentInput;
		inStr>>currentInput;
		inStr>>currentInput;
		team1Index=accessTeam(currentInput, teams);
		inStr>>currentInput;
		inStr>>currentInput;
		team2Index=accessTeam(currentInput, teams);
		inStr>>currentInput;
	}
	else
		return;

	//loops through one or more games, gathering relevant information
	while(moreToRead){
		if(currentInput=="Period"){
			inStr>>currentInput;
			inStr>>currentInput;
		}
		else if(currentInput=="Overtime"){
			inStr>>currentInput;
		}
		else if(currentInput=="Final"){
			int score1, score2;
			inStr>>currentInput;
			team1Index=accessTeam(currentInput, teams);
			inStr>>currentInput;
			score1=std::stoi((std::string)currentInput);
			inStr>>currentInput;
			team2Index=accessTeam(currentInput, teams);
			inStr>>currentInput;
			score2=std::stoi((std::string)currentInput);	
			if(score1>score2){
				teams[team1Index].incrementWins();
				teams[team2Index].incrementLosses();
			}
			else if(score1<score2){
				teams[team1Index].incrementLosses();
				teams[team2Index].incrementWins();
			}
			else{
				teams[team1Index].incrementTies();
				teams[team2Index].incrementTies();
			}
			if(inStr>>currentInput){
				inStr>>currentInput;
				inStr>>currentInput;
				inStr>>currentInput;
				team1Index=accessTeam(currentInput, teams);
				inStr>>currentInput;
				inStr>>currentInput;
				team2Index=accessTeam(currentInput, teams);
			}
			else{
				moreToRead=false;
			}
		}
		else{
			if(inStr>>currentInput){
				if(currentInput==teams[team1Index].getName()){
					currentTeamIndex=team1Index;
				}
				else{
					currentTeamIndex=team2Index;
				}
				inStr>>currentInput;
				if(currentInput=="penalty"){
					teams[currentTeamIndex].incrementPenalties();
					inStr>>currentInput;
					inStr>>currentInput;
					inStr>>currentInput;
					inStr>>currentInput;
				}
				else if(currentInput=="goal"){
					teams[currentTeamIndex].incrementWins();
					inStr>>currentInput;
					inStr>>currentInput;
					if(currentInput=="("){
						while(currentInput!=")"){
							inStr>>currentInput;
						}
						inStr>>currentInput;
					}
				}
			}
			else{
				moreToRead=false;
			}
		}
	}
}





int main(int argc, char* argv[]){
	//acceptable strings to trigger the three statistic options
	const std::string teamTrigger="--team_stats";
	const std::string playerTrigger="--player_stats";
	const std::string customTrigger="--custom_stats";
	//checks number of arguments
	if(argc!=4){
		std::cerr<<"Incorrect number of arguments\n";
		exit(1);
	}
	//verify input stream successful
	std::ifstream inStr(argv[1]);
	if (!inStr.good()) {
    	std::cerr << "Can't open " << argv[1] << " to read.\n";
    	exit(1);
  	}
  	//verify output stream successfull
	std::ofstream outStr(argv[2]);
	if (!outStr.good()) {
	    std::cerr << "Can't open " << argv[2] << " to write.\n";
		exit(1);
	}

	//vectors to be filled with relevant information for printouts
	std::vector<Team> teams;
	std::vector<Player> players;


	//0 for team stats, 1 for player stats, 2 for custom stats
	std::string typeString=std::string(argv[3]);
	if(typeString==teamTrigger){
		teamStatsReading(inStr, teams);
//		std::sort(teams[0],teams[teams.size()],operator<);

		outStr<<"Team Name              W   L   T   Win\%   Goals   Penalties\n";
		for(int i=0;i<teams.size();i++){
			outStr<<teams[i].printTeam().str();
		}
	}
	else if(typeString==playerTrigger){
		playerStatsReading(inStr, players);
//		players.sort();

		outStr<<"Player Name                    Team                 Goals    Assists    Penalties\n";
		for(int i=0;i<players.size();i++){
			outStr<<players[i].print().str();
		}

	}
	else if(typeString==customTrigger){
		outStr<<"I sort of crashed and burned this week, so instead of a working program I have a joke! What do you do with a blue whale?\n\n\n\n\n\nYou cheer it up!";
	}
	else{
		std::cerr<<"Invalid data table request\n";
	}

	return 0;	
}











currentWord="4:20.69";


double s;
currentWord[0];


s=4;

string tempStr=currentWord[2]+currentWord[3];

s+=(stod(tempStr)/60);

tempStr=currentWord[5]+currentWord[6];
s+=stod(tempStr)/1000;





4.5923

4:(.5923*60)
#include <iostream>
#include <fstream>
#include <vector>



//returns true if the word is able to fit on the line, false otherwise
bool addToLine(std::string &word, std::vector<std::string> &line, int length){
	//if a word is longer than the entire line, truncate the word after one line's worth of characters
	//	and set the removed characters to the next line
	if(word.size()>length){
		if(line.empty()){
			line.push_back(word.substr(0,length-1)+"-");
			word=word.substr(length-1);
		}
		return false;
	}
	//if the word is not longer than a full line
	else{
		for(int i=0;i<line.size();i++){
			length-=1+line[i].size();
		}
		length-=word.size();
		if(length<0){
			return false;
		}
		line.push_back(word);
		return true;
	}
}


//takes in a vector of strings, an int representing the type of alignment, and the line length
//	and generates a single correctly justified line
std::string generateLine(std::vector<std::string> &wordsInLine, int alignType, int length){
	std::string line;
	//aligning flush to the left
	if(alignType==0){
		line=wordsInLine[0];
		length-=wordsInLine[0].size();
		for(int i=1;i<wordsInLine.size();i++){
			line+=" ";
			line+=wordsInLine[i];
			length--;
			length-=wordsInLine[i].size();
		}
		line+=std::string(length, ' ');
	}
	//aligning flush to the right
	else if(alignType==1){
		length-=wordsInLine[0].size();
		for(int i=1;i<wordsInLine.size();i++){
			length--;
			length-=wordsInLine[i].size();
		}
		line=std::string(length,' ');
		for(int i=0;i<wordsInLine.size()-1;i++){
			line+=wordsInLine[i];
			line+=" ";
		}
		line+=wordsInLine[wordsInLine.size()-1];
	}
	//aligning full justified
	else if(alignType==2){
		if(wordsInLine.size()==1){
			line=wordsInLine[0];
			line+=std::string(length-wordsInLine[0].size(),' ');
		}
		else{
			length-=wordsInLine[0].size();
			for(int i=1;i<wordsInLine.size();i++){
				length-=wordsInLine[i].size();
			}
			int baseNumSpaces=length/(wordsInLine.size()-1);
			int numLongSpaces=length%(wordsInLine.size()-1);
			line=wordsInLine[0];
			for(int i=1;i<wordsInLine.size();i++){
				line+=std::string(baseNumSpaces,' ');
				if(numLongSpaces>0){
					line+=" ";
					numLongSpaces--;
				}
				line+=wordsInLine[i];
			}
		}
	}
	else{
		std::cerr<<"Invalid alignment type given";
	}
	return line;
}


int main(int argc, char* argv[]){
	//acceptable strings to trigger the three justifications
	const std::string leftJustifyString="flush_left";
	const std::string rightJustifyString="flush_right";
	const std::string centerJustifyString="full_justify";

	//checks number of arguments
	if(argc!=5){
		std::cerr << "Incorrect number of arguments\n";
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

	//0 for left flush, 1 for right flush, 2 for full justified text
	int alignment;

	std::string alignString=std::string(argv[4]);
	if(alignString==leftJustifyString){
		alignment=0;
	}
	else if(alignString==rightJustifyString){
		alignment=1;
	}
	else if(alignString==centerJustifyString){
		alignment=2;
	}
	else{
		std::cerr<<"Invalid justification\n";
	}

	//the acceptable width of any given line
	int lineLength=std::stoi((std::string)argv[3]);

	std::vector<std::string> currentLine;
	std::string currentWord;
	outStr<<std::string(lineLength+4,'-')<<"\n";
	while(inStr >> currentWord){
		while(addToLine(currentWord,currentLine,lineLength)==false){
			outStr<<"| "<<(std::string)generateLine(currentLine,alignment,lineLength)<<" |\n";
			currentLine.clear();
		}
	}
	//prints the last line of full justified text as flush to the left
	if(alignment==2){
		alignment=0;
	}
	outStr<<"| "<<(std::string)generateLine(currentLine,alignment,lineLength)<<" |\n";
	outStr<<std::string(lineLength+4,'-');

	return 0;
}
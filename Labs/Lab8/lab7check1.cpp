#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>









int main(int argc, char* argv[]){
  	if (argc != 2) {
    	std::cerr << "Usage: " << argv[0] << " numbers-file\n";
    	return 1;
  	}
  	std::ifstream istr(argv[1]);
  	if (!istr) {
    	std::cerr << "Could not open " << argv[1]<<"\n";
    	return 1;
  	}

	std::map<int, int> frequencies;

	std::string inStr;
	while(istr>>inStr){
		++frequencies[stoi(inStr)];
	}


	std::vector<int> modes;
	int most=0;

	std::map<int, int>::iterator iter=frequencies.begin();
	while(iter!=frequencies.end()){
		if(iter->second>most){
			most=iter->second;
			modes.clear();
			modes.push_back(iter->first);
		}
		else if(iter->second==most){
			modes.push_back(iter->first);
		}
		iter++;
	}


	if(modes.size()==0){
		std::cout<<"There are no modes\n";
	}
	else if(modes.size()==1){
		std::cout<<"The mode is: "<<modes[0]<<"\n";
	}
	else{
		std::cout<<"The modes are: "<<modes[0];
		for(unsigned int i=1;i<modes.size();i++){
			std::cout<<", "<<modes[i];
		}
		std::cout<<"\n";
	}






	return 0;
}
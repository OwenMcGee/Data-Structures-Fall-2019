#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>



int main(int argc, char* argv[]){
	int product=1;
	for(int i=1;i<argc;i++){
		product=product*atoi(((std::string)argv[i]).c_str());
	}
	std::cout <<"product of integers: "<< product<<std::ends;
	return 0;
}
/*
int main(int argc, char* argv[]){
	std::vector<std::string> words;

	for(int i=1;i<argc;i++){
		words.push_back((std::string)argv[i]);
	}


	std::sort(words.begin(),words.end());
	std::cout <<"sorted strings: "<<std::ends;
	for(int i=0;i<argc;i++){
		std::cout<<words[i]<<std::ends;
	}
	return 0;
}








/*
int main(int argc, char* argv[]){
	bool nums=false;
	bool words=false;
	int product=1;
	std::vector<std::string> words;

	for(int i=1;i<argc;i++){
		if(IsNumeric(argv[i])){
			nums=true;
			product=product*atoi(((std::string)argv[i]).c_str());
		}
		else{
			words=true;
			words.push_back((std::string)argv[i]);
		}
	}
	if(words==true){
		std::cout<<"product of integers: "<<product<<std::ends;
	}
	if(nums==true){
		std::cout<<"sorted strings"<<std::ends;
		std::sort(words.begin(),words.end());
		for(int i=0;i<argc;i++){
			std::cout<<words[i]<<std::ends;
		}
	}

	return 0;
}
*/
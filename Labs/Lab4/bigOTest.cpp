#include <iostream>
#include <vector>
#include <string>


int bar(int x, int y){
	int answer=y-1;
	for(int a=1;a<x;a++){
		answer+=bar(x-a,y+x);
	}
	return answer;
}


void bar1(std::vector<std::string> &a, const std::string &b){
	for(int i=0;i<a.size();i++){
		a[i]=b;
	}
}

std::vector<int> bar2(const std::vector<std::string> &a){
	std::vector<int> answer;
	for(int i=0;i<a.size();i++){
		answer.push_back(a[i].size());
	}
	return answer;
}

std::vector<std::string> bar3(const std::vector<int> &a){
	std::vector<std::string> answer;
	for(int i=0;i<a.size();i++){
		answer.push_back(std::string(a[i],'+'));
	}
	return answer;
}




int main(){
	int val=bar(3,0);
	std::cout<<"\n"<<val<<"\n";

//	std::vector<std::string> a()
//	bar1()

	return 0;
}
#include <iostream>
#include <assert.h>


//big O of O((2^(x+y))
int recursiveFind(int x, int y){
	if((x<0)||(y<0)){
		return 0;
	}
	if((x==0)&&(y==0)){
		return 1;
	}

	return recursiveFind(x-1,y)+recursiveFind(x,y-1);

}




int main(){
int x;
int y;

std::cout<<"\nX coordinate: ";
std::cin>>x;
std::cout<<"\nY coordinate: ";
std::cin>>y;

std::cout<<"\n"<<recursiveFind(x,y)<<" possible paths\n";


	return 0;
}
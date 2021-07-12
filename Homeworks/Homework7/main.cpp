#include <iostream>
#include <map>
#include <cassert>
#include <string>
#include <map>
#include <list>

#include "bookInfo.h"

// two data structures store all of the information for efficiency
typedef std::map<std::string,BookInfo> LIBRARY_TYPE;
typedef std::map<std::string,std::list<std::string>> PEOPLE_TYPE;


// prototypes for the helper functions
void addItem(LIBRARY_TYPE& library);
void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people);
void lookup(LIBRARY_TYPE& library);
void printPeople(PEOPLE_TYPE& people);


int main() {
  LIBRARY_TYPE library;
  PEOPLE_TYPE people;
  char c;
  while (std::cin >> c) {
    if (c == 'a') {
      addItem(library);
    } else if (c == 'c') {
      checkoutItem(library,people);
    } else if (c == 'r') {
      returnItems(library,people);
    } else if (c == 'l') {
      lookup(library);
    } else if (c == 'p') {
      printPeople(people);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}

//adds a positive whole number of books that may or may not have already existed in the library
void addItem(LIBRARY_TYPE& library) {
  std::string title;
  int num;
  std::cin >> num >> title;

  //some fun error messages for undefined outputs
  if(num==0){
  	std::cout<<"Well that did... nothing\n";
  	return;
  }
  if(num<0){
  	std::cout<<"You can't take my books!\n";
  	return;
  }

  //increments either an existing or newly added book (newly added starting at 0)
  library[title].addNum(num);

  //handles plural vs singular cases of books
  std::cout<<"added "<<num<<" cop";
  if(num==1){
    std::cout<<"y";
  }
  else{
    std::cout<<"ies";
  }
  std::cout<<" of "<<title<<"\n";

}

//checks out a single book to a patron who did not already have the book checked out
void checkoutItem(LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  std::string title;
  std::cin >> name >> title;

  LIBRARY_TYPE::iterator bookIter=library.find(title);
  //error in case the book is not in the library
  if(bookIter==library.end()){
    std::cout<<"don't have "<<title<<" in library\n";
  }
  else{
  	std::list<std::string>::iterator iter=people[name].begin();
  	bool alreadyCheckedOut=false;
  	std::list<std::string>::iterator end=people[name].end();
  	//checks all books checked out by the patron to ensure they don't already have a copy
  	while(iter!=end){
  		if(*iter==title){
  			alreadyCheckedOut=true;
  			break;
  		}
  		iter++;
    }
    //error if the patron already has the book
    if(alreadyCheckedOut==true){
       std::cout<<name<<" already has "<<title<<"\n";
  	}
  	//error if the book exists but is out of stock (lower priority than above error)
    else{
  	  if(bookIter->second.getNum()<1){
    	  std::cout<<"no copies of "<<title<<" available\n";
      }
      //checks the book out to the patron, marking it down in the record of both the book and the patron
      else{
      	bookIter->second.addPatron(name);
      	bookIter->second.addNum(-1);
      	bookIter->second.addNumOut(1);
        people[name].push_back(title);
        std::cout<<name<<" checked out "<<title<<"\n";
      }
    }

  }




}

//returns all books a given patron has checked out
void returnItems(LIBRARY_TYPE& library, PEOPLE_TYPE& people) {
  std::string name;
  std::cin >> name;

  int numReturned=0;
  std::list<std::string> books=people[name];
  std::list<std::string>::iterator iter=books.begin();
  //runs through all books checked out by the patron
  //marks the numbers accordingly in the book's listing
  while(iter!=books.end()){
  	numReturned++;
  	LIBRARY_TYPE::iterator bookIter=library.find(*iter);
  	bookIter->second.addNum(1);
  	bookIter->second.addNumOut(-1);
  	bookIter->second.removePatron(name);

  	iter++;
  }
  //marks the patron's records as having no books checked out
  people.find(name)->second=std::list<std::string>();

  //outputs for patrons with 0, 1, or multiple books to return
  if(numReturned==0){
  	std::cout<<name<<" has no items checked out\n";
  }
  else if(numReturned==1){
  	std::cout<<name<<" returned 1 item\n";
  }
  else{
  	std::cout<<name<<" returned "<<numReturned<<" items\n";
  }


}

//looks up a given book and prints its information
void lookup(LIBRARY_TYPE& library) {
  std::string title;
  std::cin >> title;

  LIBRARY_TYPE::iterator iter=library.find(title);
  if(iter==library.end()){
  	return;
  }
  std::cout<<"library info for: "<<title<<"\n";
  int num=iter->second.getNum();
  //handles plural vs singular amounts of books in stock
  if(num>0){
  	std::cout<<"  "<<num<<" cop";
  	if(num==1){
  		std::cout<<"y";
  	}
  	else{
  		std::cout<<"ies";
  	}
  	std::cout<<" available\n";
	}
	int numOut=iter->second.getNumOut();
	//handles plural vs singular amounts of books checked out
	if(numOut>0){
		std::cout<<"  "<<numOut<<" cop";
		if(numOut==1){
			std::cout<<"y";
		}
		else{
			std::cout<<"ies";
		}
		std::cout<<" checked out by:\n";
  	std::list<std::string> patrons=iter->second.getList();
  	std::list<std::string>::iterator patronIter=patrons.begin();
  	//checks through all patrons who have checked the book out
  	while(patronIter!=patrons.end()){
  		std::cout<<"    "<<*patronIter<<"\n";
  		patronIter++;
  	}
	}

  //CHECK WHAT HAPPENS IF NO BOOK WITH THAT NAME IS FOUND


}

//prints all patron's and the books they have checked out
void printPeople(PEOPLE_TYPE& people) {
	PEOPLE_TYPE::iterator iter=people.begin();
	//runs through all patrons
	while(iter!=people.end()){
		std::list<std::string>::iterator personIter=iter->second.begin();
		if(personIter!=iter->second.end()){
			personIter++;
			if(personIter==iter->second.end()){
				//handles plural vs singular books
				std::cout<<iter->first<<" has this item checked out:\n";
				std::cout<<"  "<<iter->second.front()<<"\n";
			}
			else{
				personIter--;
				std::cout<<iter->first<<" has these items checked out:\n";
				//runs through each of their books
				while(personIter!=iter->second.end()){
					std::cout<<"  "<<*personIter<<"\n";
					personIter++;
				}
			}
		}
		iter++;

	}





}

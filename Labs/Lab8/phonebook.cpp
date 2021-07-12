// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>

// add a number, name pair to the phonebook
void add(std::map<int, std::string> & phonebook, int number, std::string const& name) {
  phonebook.erase(number);
  phonebook.insert(std::make_pair(number, name));
}

// given a phone number, determine who is calling
void identify(const std::map<int, std::string> & phonebook, int number) {
  if(phonebook.find(number)==phonebook.end())
    std::cout << "unknown caller!" << std::endl;
  else 
    std::cout << phonebook.find(number)->second << " is calling!" << std::endl;
}


int main() {

  std::map<int, std::string> phonebook;


  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
}


/*

Big O:

constructing: O(N)
adding: O(1)
identify: O(1)



constructing: O(1)
adding: O(logn)
identify O(logn)



*/
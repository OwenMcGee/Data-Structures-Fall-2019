#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ds_set.h"

int main() {

  ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy");  // should recognize that this is a duplicate!

  assert(set1.sanity_check());
  assert (set1.size() == 7);

  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));

  p = set1.find( "foo" );
  assert (p == set1.end());

  p = set1.find("puppy");
  assert (p != set1.end());
  assert (*p == "puppy");

  std::cout << "Here is the tree, printed sideways.\n"
  << "The indentation is proportional to the depth of the node\n"
  << "so that the value stored at the root is the only value printed\n"
  << "without indentation.  Also, for each node, the right subtree\n"
  << "can be found above where the node is printed and indented\n"
  << "relative to it\n";
  set1.print_as_sideways_tree( std::cout );
  std::cout << std::endl;


  // copy the set
  ds_set<std::string> set2( set1 );
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());
  

  //  Now add stuff to set2
  set2.insert( std::string("a") );
  set2.insert( std::string("b") );
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);


  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);


  // Test the iterators!



  ds_set<int> testSet;
  testSet.insert(8);
  testSet.insert(4);
  testSet.insert(12);
  testSet.insert(2);
  testSet.insert(6);
  testSet.insert(10);
  testSet.insert(14);
  testSet.insert(1);
  testSet.insert(3);
  testSet.insert(5);
  testSet.insert(7);
  testSet.insert(9);
  testSet.insert(11);
  testSet.insert(13);
  testSet.insert(15);
  testSet.print_as_sideways_tree(std::cout);


  ds_set<int>::iterator iter=testSet.end();
  while(iter!=testSet.begin()){
    iter--;
    std::cout<<*iter<<"\n";
  }



  testSet.insert(16);
  testSet.insert(17);
  testSet.insert(-1);
  testSet.print_as_sideways_tree(std::cout);
  iter=testSet.end();
  while(iter!=testSet.begin()){
    iter--;
    std::cout<<*iter<<"\n";
  }



  iter=testSet.begin();
  while(iter!=testSet.begin()){
    iter--;
    std::cout<<*iter<<"\n";
  }


  std::cout<<"check 3: "<<testSet.accumulate(0)<<"\n";

  ds_set<std::string> testSet2;
  testSet2.insert("hi");
  testSet2.insert("what");
  testSet2.insert("this");
  testSet2.insert("BAH");
  testSet2.print_as_sideways_tree(std::cout);
  std::cout<<"check 3: "<<testSet2.accumulate("for strings: ")<<"\n";






  return 0;
}
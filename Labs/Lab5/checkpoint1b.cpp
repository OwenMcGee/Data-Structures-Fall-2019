#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";
  typename std::list<T>::iterator iter;
  for(iter=data.begin();iter!=data.end();iter++){
    std::cout<<" "<<*iter;
  }  
  std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {

  typename std::list<T>::iterator frontIter=data.begin();
  typename std::list<T>::reverse_iterator backIter=data.rbegin();

  for(int i=0;i<data.size()/2;i++){
    T temp=*frontIter;
    *frontIter=*backIter;
    *backIter=temp;
    frontIter++;
    backIter++;
  }  


}


int main() {
  std::list<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");



  std::list<int> edgeTests;
  reverse(edgeTests);

  edgeTests.push_back(1);
  reverse(edgeTests);
  print(edgeTests,"after: ");

  edgeTests.push_back(2);
  reverse(edgeTests);
  print(edgeTests,"after: ");



  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");
}
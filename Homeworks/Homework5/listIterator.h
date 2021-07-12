#ifndef _listIterator_h_
#define _listIterator_h_

#include <string>

class ListIterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  ListIterator(Node* p=NULL, bool isBackup = false) : ptr(p), backup(isBackup) {}								//MAKE SURE I DO SOMETHING ABOUT ASSIGNING BACKUP RIGHT HERE
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  std::string& operator*()  { return ptr->value_;  }

  // increment & decrement operators
  ListIterator& operator++() { // pre-increment, e.g., ++iter
  	if(backup){
  		ptr = ptr->backup_next_;
  	}
  	else{
	    ptr = ptr->next_;
  	}
    return *this;
  }
  ListIterator operator++(int) { // post-increment, e.g., iter++
    ListIterator temp(*this);
  	if(backup){
  		ptr = ptr->backup_next_;
  	}
  	else{
	    ptr = ptr->next_;
  	}
    return temp;
  }
  ListIterator& operator--() { // pre-decrement, e.g., --iter
  	if(backup){
  		ptr = ptr->backup_prev_;
  	}
  	else{
	    ptr = ptr->prev_;
  	}
    return *this;
  }
  ListIterator operator--(int) { // post-decrement, e.g., iter--
    ListIterator temp(*this);
  	if(backup){
  		ptr = ptr->backup_prev_;
  	}
  	else{
	    ptr = ptr->prev_;
  	}
    return temp;
  }
  // the dslist class needs access to the private ptr_ member variable
  friend class Essay;

  // Comparisons operators are straightforward
  bool operator==(const ListIterator& r) const {
    return ptr == r.ptr; }
  bool operator!=(const ListIterator& r) const {
    return ptr != r.ptr; }

private:
  // REPRESENTATION
  Node* ptr;    // ptr to node in the list
  bool backup;
};





#endif
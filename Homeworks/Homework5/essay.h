#ifndef _essay_h_
#define _essay_h_

#include "node.h"
#include "listIterator.h"

//#include <iostream>

class Essay{
	private:
		Node* head_;
		Node* tail_;
		Node* backup_head_;
		Node* backup_tail_;
		unsigned int sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter;	//I wanted to call the method get size, I'll have you know
	public:
		// default constructor, copy constructor, assignment operator, and destructor
		Essay();
		Essay(const Essay & old) {copyEssay(old);};
		Essay& operator=(const Essay & old);
		~Essay() {destroyEssay();};

		typedef ListIterator iterator;

		//mutators
		void push_front(const std::string & str);
		void pop_front();
		void push_back(const std::string & str);
		void pop_back();

		//accessors
		unsigned int size() const{return sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter;};
		unsigned int num_added() const;
		unsigned int num_removed() const;


		void debug() const;


		void backup();
		void revert();
		bool splice(iterator startIter, iterator endIter, iterator destIter);

		iterator erase(iterator iter);
		iterator insert(iterator iter, const std::string & str);
		iterator begin() { return iterator(head_,false); };
		iterator end() {return iterator(tail_,false);};
		iterator backup_begin() {return iterator(backup_head_,true);};
		iterator backup_end() {return iterator(backup_tail_,true);};

	private:
		void copyEssay(const Essay & old);
		void destroyEssay();


};


#endif
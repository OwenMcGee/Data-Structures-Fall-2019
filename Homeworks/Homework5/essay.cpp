#include "essay.h"
#include "node.h"
#include <iostream>
#include <string>
#include <cassert>


Essay::Essay(){
	head_=NULL;
	tail_=NULL;
	backup_head_=NULL;
	backup_tail_=NULL;
	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter=0;
}

Essay& Essay::operator=(const Essay & old){
	if(&old!=this){
		destroyEssay();
		copyEssay(old);
	}
	return *this;
}

void Essay::push_front(const std::string & str){
	Node* temp=new Node(str);
	temp->added_=true;
	temp->backup_prev_=NULL;
	temp->backup_next_=NULL;
	if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter==0){
		head_=temp;
		tail_=new Node();
		tail_->prev_=head_;
	}
	else{
		temp->next_=head_;
		head_->prev_=temp;
		head_=temp;
	}
	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter++;
}

void Essay::pop_front(){
	if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter==0){
		std::cerr<<"There are no nodes to be popped from the front";
	}
	else if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter==1){
		if((head_!=backup_head_)&&(head_->backup_next_==NULL)){
			delete head_;
		}
		else{
			head_->removed_=true;
			head_->next_=NULL;
		}
		head_=NULL;
		tail_->prev_=NULL;
	}
	else{
		head_=head_->next_;
		head_->prev_->next_=NULL;
		if((head_->prev_!=backup_head_)&&(head_->prev_->backup_prev_==NULL)){
			delete head_->prev_;
		}
		else{
			head_->prev_->removed_=true;
		}
		head_->prev_=NULL;
	}
	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter--;													//MAKE SURE THIS DOESN'T EXECUTE IF THE SIZE==0 ERROR IS TRIGGERED (pretty sure it's ok)



}

void Essay::push_back(const std::string & str){
	Node* temp=new Node(str);
	temp->added_=true;
	temp->backup_prev_=NULL;
	temp->backup_next_=NULL;
	if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter==0){
		head_=temp;
		tail_=new Node();
		tail_->prev_=head_;
		head_->next_=tail_;
	}
	else{
		tail_->prev_->next_=temp;
		temp->prev_=tail_->prev_;
		tail_->prev_=temp;
		temp->next_=tail_;
		if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter==1){
			head_->next_=temp;
		}
	}
	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter++;
}

void Essay::pop_back(){
	if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter==0){
		std::cerr<<"There are no nodes to be popped from the back";
	}
	else if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter==1){
		if((head_!=backup_head_)&&(head_->backup_prev_==NULL)){
			delete head_;
		}
		else if(backup_head_!=NULL){
			head_->removed_=true;
		}
		head_=NULL;
		tail_->prev_=NULL;
	}
	else{
		tail_->prev_=tail_->prev_->prev_;
		if((tail_->prev_->next_->backup_next_!=backup_tail_)&&(tail_->prev_->next_->backup_next_==NULL)){
			delete tail_->prev_->next_;
		}
		else{
			tail_->prev_->next_->removed_=true;
			tail_->prev_->next_->next_=NULL;
		}
		tail_->prev_->next_=tail_;
	}
	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter--;

}

unsigned int Essay::num_added() const{
	Node* temp=head_;
	unsigned int totalAdded=0;
	while(temp!=NULL){
		if(temp->added_==true){
			totalAdded++;
		}
		temp=temp->next_;
	}
	return totalAdded;
}

unsigned int Essay::num_removed() const{
	Node* temp=backup_head_;
	unsigned int totalRemoved=0;
	while(temp!=NULL){
		if(temp->removed_==true){
			totalRemoved++;
		}
		temp=temp->backup_next_;
	}
	return totalRemoved;
}



void Essay::backup(){
	Node* temp=new Node();
	if(backup_head_!=NULL){
		temp=backup_head_;
		Node* nextTemp;

		while(temp!=NULL){
			nextTemp=temp->backup_next_;

			if((temp->prev_==NULL)&&(temp!=head_)){
				delete temp;
			}								//don't need to alter the existing backup pointers here because I overwrite them in the next loop anyway
			temp=nextTemp;
		}
	}

	temp=head_;
	backup_head_=head_;
	while(temp!=tail_){
		temp->backup_next_=temp->next_;
		temp->backup_prev_=temp->prev_;
		temp->added_=false;
		temp->removed_=false;
		temp=temp->next_;
	}
	delete backup_tail_;
	backup_tail_=new Node();
	backup_tail_->backup_prev_=tail_->prev_;
	backup_tail_->backup_prev_->backup_next_=backup_tail_;
//	tail_->prev_->backup_next_=backup_tail_;
//	backup_tail_->backup_prev_=temp->prev_;
}

void Essay::revert(){				//need to remember to alter the size!
	Node* temp;
	if(head_!=NULL){
		temp=head_;
		Node* nextTemp;

		while(temp!=NULL){
			nextTemp=temp->next_;
			if((temp->backup_prev_==NULL)&&(temp!=backup_head_)){
				delete temp;
			}
			temp=nextTemp;
		}
	}

	if(backup_head_==NULL){
		sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter=0;
		return;
	}

	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter=1;
	temp=backup_head_;
	head_=backup_head_;
	while(temp!=backup_tail_->backup_prev_){
		temp->next_=temp->backup_next_;
		temp->prev_=temp->backup_prev_;
		temp->added_=false;
		temp->removed_=false;
		temp=temp->backup_next_;
		sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter++;
	}
	temp->next_=tail_;
	temp->prev_=temp->backup_prev_;
	temp->removed_=false;
	tail_->prev_=temp;
}

bool Essay::splice(iterator startIter, iterator endIter, iterator destIter){
	return true;
}


Essay::iterator Essay::erase(iterator iter){
	assert (sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter>0);
	iterator result(iter.ptr->next_);
	if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter==1){
		if((head_!=backup_head_)&&(head_->backup_prev_==NULL)){
			delete head_;
		}
		else{
			head_->removed_=true;
		}
		head_=NULL;
		tail_->prev_=NULL;
	}
	else if(iter.ptr==head_){
		head_=head_->next_;
		if((head_->prev_!=backup_head_)&&(head_->prev_->backup_prev_==NULL)){
			delete head_;
		}
		else if(backup_head_!=NULL){
			head_->removed_=true;
		}
		head_->prev_=NULL;
	}
	else if(iter.ptr==tail_->prev_){
		tail_->prev_=tail_->prev_->prev_;
		if((tail_->prev_->next_->backup_next_!=backup_tail_)&&(tail_->prev_->next_->backup_next_==NULL)){
			delete tail_->prev_->next_;
		}
		else if(backup_head_!=NULL){
			tail_->prev_->next_->removed_=true;
		}
		tail_->prev_->next_->next_=tail_;
	}
	else{
		iter.ptr->prev_->next_=iter.ptr->next_;
		iter.ptr->next_->prev_=iter.ptr->prev_;
		if((iter.ptr->backup_prev_==NULL)&&(iter.ptr!=backup_head_)){
			delete iter.ptr;
		}
		else{
			iter.ptr->removed_=true;
			iter.ptr->prev_=NULL;
			iter.ptr->next_=NULL;
		}
	}
	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter--;
	return result;
}

Essay::iterator Essay::insert(iterator iter, const std::string & str){
	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter++;
	Node* newNode=new Node(str);
	newNode->added_=true;
	newNode->prev_=iter.ptr->prev_;
	newNode->next_=iter.ptr;
	iter.ptr->prev_=newNode;
	if(iter.ptr==head_)
		head_=newNode;
	else
		newNode->prev_->next_=newNode;
	return iterator(newNode);
}





void Essay::copyEssay(const Essay & old){
	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter=old.sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter;

	head_=old.head_;
	Node* newTemp=head_;
	Node* oldTemp=old.head_;
	if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter>1){
		oldTemp=oldTemp->next_;
	}
	if(sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter>0){
		if(old.head_->removed_==true){
			head_->removed_=true;
		}
		else if(old.head_->added_==true){
			head_->added_=true;
		}
	
		while(oldTemp!=NULL){
			newTemp->next_=oldTemp;
			newTemp->next_->prev_=newTemp;
			newTemp=oldTemp;

			if(oldTemp->removed_==true){
				newTemp->removed_=true;
			}
			else if(oldTemp->added_==true){
				newTemp->added_=true;
			}

			oldTemp=oldTemp->next_;
		}
		tail_->prev_=newTemp;
	}


	if(oldTemp!=NULL){
		backup_head_=old.backup_head_;
		newTemp=backup_head_;
		oldTemp=old.backup_head_;


		if(oldTemp->next_==NULL){
			backup_tail_->backup_prev_=backup_head_;
		}
		else{
			oldTemp=oldTemp->backup_next_;
			while(oldTemp!=NULL){
				newTemp->backup_next_=oldTemp;
				newTemp->backup_next_->backup_prev_=newTemp;
				newTemp=oldTemp;

				if(oldTemp->removed_==true){
					newTemp->removed_=true;
				}										//don't need to check added since these are in the backup

				oldTemp=oldTemp->backup_next_;
			}
			backup_tail_->backup_prev_=newTemp;
		}



	}




	backup_head_=old.backup_head_;
	newTemp=backup_head_;
	oldTemp=old.backup_head_;
	if((oldTemp!=NULL)&&(oldTemp->next_!=NULL)){
		oldTemp=oldTemp->next_;
	}



}

void Essay::destroyEssay(){
	Node* temp=head_;
	Node* nextTemp;
	while(temp!=NULL){
		nextTemp=temp->next_;
		if((temp->backup_prev_==NULL)&&(temp!=backup_head_)){
			delete temp;
		}
		temp=nextTemp;
	}


	temp=backup_head_;
	while(temp!=NULL){
		nextTemp=temp->next_;
		delete temp;
		temp=nextTemp;
	}

	sizeWithoutAnUnderscoreAtRheEndBecauseIHateYouAndCamelCaseIsBetter=0;

}




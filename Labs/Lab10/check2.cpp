#include <iostream>


class Node{
	public: int value;
	Node* left;
	Node* right;
};

bool shape_match(Node x, Node y){
	if(x==NULL&&y==NULL)
		return true;
	if(x==NULL||y==NULL)
		return false;
	return (shape_match(x->left,y->left)&&shape_match(x->right,y->right));
}

int largestShapeMatch(Node x, Node y){
	if(x==NULL&&y==NULL){
		return 0;
	}
	if(x==NULL||y==NULL){
		return -1;
	}
	if(shape_match)
}



Node find_subtree_match(Node x, Node y){

}

int main(){


	return 0;
}


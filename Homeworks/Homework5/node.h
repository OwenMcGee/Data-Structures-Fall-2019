#ifndef _node_h_
#define _node_h_

#include <string>

class Node {
public:
  Node() : next_(NULL), prev_(NULL), backup_next_(NULL), backup_prev_(NULL), added_(false), removed_(false) {}
  Node(const std::string & str) : value_(str), next_(NULL), prev_(NULL), backup_next_(NULL), backup_prev_(NULL), added_(false), removed_(false) {}

  void debug() const;

  //seriously though in what universe does putting an underscore at the end make sense? I despise this. It feels wrong
  //Like, when it's between two words as an alternative to camel case I can see the hint of logic there. But at the end?
  //Cruelty. (please don't dock points for this it's all in good fun (also the size variable name (sorry!)))
  std::string value_;
  Node* next_;
  Node* prev_;
  Node* backup_next_;
  Node* backup_prev_;
  bool added_;
  bool removed_;
};


#endif
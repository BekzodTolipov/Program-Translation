#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


struct Node{
  public:
  int data;
  Node*left;
  Node*right;
  Node(int d){
    data=d;
    left=NULL;
    right=NULL;
  }
};

Node* build_tree(std::string file_name);
void print(Node*root);
bool is_file_exist(std::string);

#endif

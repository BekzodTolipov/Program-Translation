#ifndef BUILD_TREE_H
#define BUILD_TREE_H
#include <bits/stdc++.h>
#include <string>
#include <cctype>
#include <cstring>
#include <sstream> 
#include <fstream>

using namespace std;

/* 
A binary tree node has data and pointer to next node,  
pointer to left child and a 
pointer to right child 
*/
struct Node { 
    string data;
	struct Node* next;
    struct Node* left;
	struct Node* right; 
};

Node* new_node(string data);
Node* insert(struct Node* root, string data);
void in_order(struct Node* root, int, std::ofstream&);
void pre_order(struct Node* root, int, std::ofstream&);
void post_order(struct Node* root, int, std::ofstream&);
void add_to_same_node(string item, struct Node** node);
void print_same_node(struct Node* root, std::ofstream&);
void print_spaces(int space, std::ofstream&);

#endif	//BUILD_TREE_H

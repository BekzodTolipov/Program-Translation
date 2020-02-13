#ifndef BUILD_TREE_H
#define BUILD_TREE_H
#include <bits/stdc++.h>
#include <string>
#include <cctype>
#include <cstring>
#include <sstream> 
#include <fstream>

using namespace std;

/* A binary tree node has data,  
pointer to left child and a 
pointer to right child */
struct Node { 
    string data;
	struct Node* next;
    struct Node* left;
	struct Node* right; 
};

Node* newNode(string data);
Node* insert(struct Node* root, string data);
void inOrder(struct Node* root, int, std::ofstream&);
void preOrder(struct Node* root, int, std::ofstream&);
void postOrder(struct Node* root, int, std::ofstream&);
void addToSameNode(string item, struct Node** node);
void print_same_node(struct Node* root, std::ofstream&);
void print_spaces(int space, std::ofstream&);
//bool is_number(const std::string& s);

#endif	//BUILD_TREE_H

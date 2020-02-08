#ifndef BUILD_TREE_H
#define BUILD_TREE_H
#include <bits/stdc++.h>
#include <string>
#include <cctype>
#include <cstring>
#include <sstream> 

using namespace std;

/* A binary tree node has data,  
pointer to left child and a 
pointer to right child */
struct Node { 
    char data[1024];
	//int dups;
    Node* left;
	Node* right; 
};

Node* newNode(string data);
Node* insertLevelOrder(char key[], Node* root);
void inOrder(Node* root);
void preOrder(Node* root, int lvl);
void postOrder(Node* root);
bool is_number(const std::string& s);

#endif	//BUILD_TREE_H

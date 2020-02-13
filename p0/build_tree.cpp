#include "build_tree.h"
#include<string>
#include<stdio.h> 
#include<stdlib.h>

struct Node *newNode(string item){ 
	struct Node *temp = new Node(); 
    temp->data = item;
	temp->next = NULL; 
    temp->left = temp->right = NULL;
	return temp; 
}

void addToSameNode(string item, struct Node** node){
	struct Node *last = *node;
	struct Node* new_node = newNode(item);
	
	while(last->next != NULL){
		last = last->next;
	}
	last->next = new_node;
} 
   
   
/* A utility function to insert a new node with given key in BST */
struct Node* insert(struct Node* node, string key){ 
	/* If the tree is empty, return a new node */
    if (node == NULL){
		return newNode(key); 
	}
  
    /* Otherwise, recur down the tree */
	if(key.substr(0, 2) == (node->data).substr(0,2)){
    	addToSameNode(key, &node);
	}
    else if (key < node->data){
        node->left  = insert(node->left, key); 
	}
    else if (key > node->data){
        node->right = insert(node->right, key);
	}
  
    /* return the (unchanged) node pointer */
    return node; 
} 

// Function to print tree nodes in 
// InOrder fashion 
void inOrder(Node* root, int space, std::ofstream &file){ 
    if (root == NULL){
		return;
	} 
    inOrder(root->left, space+2, file);
	//file.open(file_name_in);
	if(space > 2){
		print_spaces(space, file);
	}
	//cout<<space;
	//file.open(file_name_in);
	cout << root->data;
	file << root->data;
	//file.close();
	print_same_node(root->next, file);
	//file.close();
	//cout<<endl;
    inOrder(root->right, space+2, file);
	//file.close(); 
} 

void postOrder(Node* root, int space, std::ofstream &file){
	if(root == NULL){
		return;
	}
	postOrder(root->left, space+2, file);
    postOrder(root->right, space+2, file);
	if(space > 2){
		print_spaces(space, file);
	}
    cout << root->data;
	file << root->data;
	print_same_node(root->next, file);
	//cout<<endl;
}

void preOrder(Node* root, int space, std::ofstream &file){
	
	if(root == NULL){
		return;
	}
	if(space > 2){
		print_spaces(space, file);
	}
	//cout<<space;
    cout << root->data;
	file << root->data;
	print_same_node(root->next, file);
	//cout<<endl;
    preOrder(root->left, space+2, file);
    preOrder(root->right, space+2, file);
}

void print_same_node(struct Node* root, std::ofstream &file){
	//file.open(file_name);
	while(root != NULL){
		cout<<":"<<(root->data);
		file<<":"<<(root->data);
		root = root->next;
	}
	cout<<endl;
	file<<endl;
//	file.close();
}

void print_spaces(int space, std::ofstream &file){
	//file.open(file_name);
	for(int i = 0; i < space; i++){
		cout<<" ";
		file<<" ";
	}
//	file.close();
}

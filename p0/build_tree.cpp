#include "build_tree.h"
#include<string>
#include<stdio.h> 
#include<stdlib.h>

// Create a new node
struct Node *new_node(string item){ 
	struct Node *temp = new Node(); 
    temp->data = item;
	temp->next = NULL; 
    temp->left = temp->right = NULL;
	return temp; 
}

// Add to same node
void add_to_same_node(string item, struct Node** node){
	struct Node *last = *node;
	struct Node* new_node_created = new_node(item);
	
	while(last->next != NULL){
		last = last->next;
	}
	last->next = new_node_created;
} 
   
   
/* A utility function to insert a new node with given key in BST */
struct Node* insert(struct Node* node, string key){ 
	/* If the tree is empty, return a new node */
    if (node == NULL){
		return new_node(key); 
	}
  
    /* Otherwise, recur down the tree */
	if(key.substr(0, 2) == (node->data).substr(0,2)){
    	add_to_same_node(key, &node);
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
void in_order(Node* root, int space, std::ofstream &file){ 
    if (root == NULL){
		return;
	} 
    in_order(root->left, space+2, file);
	if(space > 2){
		print_spaces(space, file);
	}
	cout << root->data;
	file << root->data;
	print_same_node(root->next, file);
    in_order(root->right, space+2, file);
} 

// Print tree post order
void post_order(Node* root, int space, std::ofstream &file){
	if(root == NULL){
		return;
	}
	post_order(root->left, space+2, file);
    post_order(root->right, space+2, file);
	if(space > 2){
		print_spaces(space, file);
	}
    cout << root->data;
	file << root->data;
	print_same_node(root->next, file);
}

// Print tree pre order
void pre_order(Node* root, int space, std::ofstream &file){
	
	if(root == NULL){
		return;
	}
	if(space > 2){
		print_spaces(space, file);
	}
    cout << root->data;
	file << root->data;
	print_same_node(root->next, file);
    pre_order(root->left, space+2, file);
    pre_order(root->right, space+2, file);
}

// Print same node
void print_same_node(struct Node* root, std::ofstream &file){
	while(root != NULL){
		cout<<":"<<(root->data);
		file<<":"<<(root->data);
		root = root->next;
	}
	cout<<endl;
	file<<endl;
}

// Indentation with dashes
void print_spaces(int space, std::ofstream &file){
	for(int i = 0; i < space; i++){
		cout<<"-";
		file<<"-";
	}
}

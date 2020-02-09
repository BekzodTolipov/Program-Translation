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
//	else if(key.substr(0, 2) == (node->data).substr(0,2)){
//		cout>>"String 2 letters are same";
//	}
  
    /* return the (unchanged) node pointer */
    return node; 
} 

// Function to print tree nodes in 
// InOrder fashion 
void inOrder(Node* root){ 
    if (root == NULL){
		return;
	} 
       //cout << root->data <<" "; 
    inOrder(root->left); 
	cout << root->data; 
	print_same_node(root->next);
	cout<<" ";
    inOrder(root->right); 
} 

void postOrder(Node* root){
	if(root == NULL){
		return;
	}
	postOrder(root->left);
    //cout << root->data <<" ";
    postOrder(root->right);
    cout << root->data;
	print_same_node(root->next);
	cout<<" ";
}

void preOrder(Node* root){
	
	if(root == NULL){
		return;
	}
    cout << root->data;
	print_same_node(root->next);
	cout<<" ";
    preOrder(root->left);
    //cout << root->data <<" ";
    preOrder(root->right);
    //cout << root->data <<" ";
}

void print_same_node(struct Node* root){
	while(root != NULL){
		cout<<":"<<(root->data);
		root = root->next;
	}
	cout<<" ";
}

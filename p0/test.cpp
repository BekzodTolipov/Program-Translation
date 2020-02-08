// C program to demonstrate insert operation in binary search tree. 
#include<stdio.h> 
#include<stdlib.h> 
#include<string>
#include<vector>
#include <iostream>

using namespace std;

struct node 
{ 
    string key; 
    struct node *left, *right; 
}; 
   
// A utility function to create a new BST node 
struct node *newNode(string item) 
{ 
    struct node *temp = new node(); 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
   
// A utility function to do inorder traversal of BST 
void inorder(struct node *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        cout<<root->key; 
        inorder(root->right); 
    } 
} 
   
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, string key) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key);    
  
    /* return the (unchanged) node pointer */
    return node; 
} 
   
// Driver Program to test above functions 
int main() 
{ 
	vector<string> str{"50", "30", "40", "70", "60"};
    struct node *root = new node(); 
    root = insert(root, str[0]); 
    insert(root, str[1]); 
    insert(root, str[2]); 
    insert(root, str[3]); 
    insert(root, str[4]);  
   
    // print inoder traversal of the BST 
    inorder(root); 
   
    return 0;
} 

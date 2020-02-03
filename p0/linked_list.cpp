#include "linked_list.h"
#include <bits/stdc++.h> 
void push(Node** head_ref, int new_data)  
{  
    /* 1. allocate node */
    Node* new_node = new Node();  
  
    /* 2. put in the data */
    new_node->data = new_data;  
  
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);  
  
    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;  
} 

void printList(struct Node *node) 
{ 
    while (node != NULL) 
    { 
        printf(" %d ", node->data); 
        node = node->next; 
    } 
}

int getCount(struct Node* head) 
{ 
	if (head == NULL){
        	return 0; 
	}

	return 1 + getCount(head->next); 
} 

void deleteNode(struct Node **head_ref, int key) 
{
	struct Node* temp = *head_ref, *prev; 
	if (temp != NULL && temp->data == key) 
    	{ 
        	*head_ref = temp->next;
		free(temp);
		return;
	}
	
	while (temp != NULL && temp->data != key) 
    	{ 
        	prev = temp; 
        	temp = temp->next; 
    	} 

	if (temp == NULL) return; 

	prev->next = temp->next; 

	free(temp);
}

bool search(Node* head, int x)  
{  
  Node* current = head;
  while (current != NULL)  
  {  
    if (current->data == x){ 
            		return true;  
	}
    current = current->next;  
  }  
    return false;  
}  


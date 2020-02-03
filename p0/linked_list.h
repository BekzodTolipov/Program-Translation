#ifndef LINKED_LIST
#define LINKED_LIST

class Node { 
	public: 
        int data; 
        Node* next; 
};

void push(Node** head_ref, int new_data);
void printList(struct Node *node);
int getCount(struct Node* head);
void deleteNode(struct Node **head_ref, int key);
bool search(Node* head, int x);


#endif

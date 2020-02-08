#include "build_tree.h"

/* Helper function that allocates a new node */
Node* newNode(string data){
	//cout<<"\n\nNew node inserting: ";
//	cout<< data<<endl; 
	void *node_raw = malloc(sizeof(Node));
	Node* node = new(node_raw)Node;
	//node->data, data);
    node->data = data;
	 
//	cout<< "Data got: "; 
    node->left = node->right = NULL; 
 //   cout<<data<<endl;
	//int dummy;
	//cin>>dummy;
	return node; 
} 

// Function to insert nodes in level order 
struct Node* insertLevelOrder(string key, Node* root){

	//int pos = 0;
//	cout<<"Position: ";
//	cout<<i<<endl;
//	cout<<"Array Element: ";
	//cout<<arr[i]<<endl;
	//cin>>pos;
	//if(i < n){
		if(root == NULL){
		//	pos = i + 1;
		//	cout << "Root is empty so inserting" <<endl;
		//	cout<<"New position sending: ";
		//	cout<<pos<<endl;
			root = newNode(key);
			//cout << "Root is empty so inserting" <<endl;
			//insertLevelOrder(key,);
		}
	//	if(is_number(arr[i]) && is_number(root->data)){
			//cout<<"Hello\n";
			//stringstream geek(arr[i]);
			//int i;
			//std::istringstream(arr[i]) >> i;
			//cout<<i<<endl;
		//	int digitInArr = std::stoi(arr[i]);
			//geek >> digitInArr;

			//stringstream geeek(root->data);
			//string data = root->data;
		//	int digitInTree = std::stoi(root->data);
			//geeek >> digitInTree;
			
		//	cout<<"Digit in arr: ";
		//	cout<<digitInArr;
		//	cout<<" : ";
		//	cout<<digitInTree<<endl;
			//int dummy;
			//cin>>dummy;
			if(key < root->data){
			//	cout<<"Hello\n";
			//	pos = i + 1;
				root->left = insertLevelOrder(key, root->left);
			}
			else if(key > root->data){
			//	pos = i + 1;
			//	cout<< "Second else" << endl;
				root->right = insertLevelOrder(key, root->right);
			}
	//	}
//	}
//	cout<<"\n\nend of insert\n";
	
	// Base case for recursion 
//	if (i < n) 
//    { 
//        Node* temp = newNode(arr[i]); 
//        root = temp; 
		// insert left child
//		root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);
		// insert right child 
//		root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
//	} 
    return root; 
}

bool is_number(const std::string& s){
	std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
} 

// Function to print tree nodes in 
// InOrder fashion 
void inOrder(Node* root) 
{ 
    if (root == NULL){
		return;
	} 
       //cout << root->data <<" "; 
    inOrder(root->left); 
    cout << root->data <<" "; 
    inOrder(root->right); 
} 

void postOrder(Node* root){
	if(root == NULL){
		return;
	}
	postOrder(root->left);
    //cout << root->data <<" ";
    postOrder(root->right);
    cout << root->data <<" ";
}

void preOrder(Node* root, int lvl){
	
	if(root == NULL){
		return;
	}
    //cout << root->data <<" ";
	int count = 0;
	while(count < lvl){
		cout<<endl;
		count++;
	}
	count = 0;
	while(count < lvl){
		cout<<" ";
	}
    cout << root->data;
    preOrder(root->left, lvl+1);
    //cout << root->data <<" ";
    preOrder(root->right, lvl+1);
    //cout << root->data <<" ";
}


#include "tree.h"
Node* build_tree(std::string file_name){
  int d;
	if(file_name.empty()){
  		std::cin>>d;
	}
	else{
		std::cout << file_name << endl;
		is_file_exist(file_name);
		return NULL;
	}
  Node*root;
  if(d==-1){
    return NULL;
  }
  root=new Node(d);
  root->left=build_tree("");
  root->right=build_tree("");
  return root;
}
void print(Node*root){
  if(root==NULL){
    return;
  }
  std::cout<<root->data<<" ";
  print(root->left);
  print(root->right);
}

bool is_file_exist(std::string file_name){
	ifstream ifile;
	ifile.open(file_name.c_str());
	if(ifile){
		cout << "file exist\n";
		return true;
	}
	else{
		cout << "file does NOT exist\n";
		return false;
	}
}

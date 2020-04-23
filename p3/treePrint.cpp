#include <iostream>
#include "treePrint.h"

void printTree(Node *root, int level) {
	if (root == NULL) {
		return;
	} 

	string line;
	tokenInfo tkn;
	
	if(level > 0)
		line.append("|");
	for (int i = 0; i < level; i++) {
		line.append("_");
	}
	level++;
	line.append(root->label.c_str());
	if(root->label == ""){
		cout<<"LABEL is empty()\n\n";
	}
	if(root->tkn.size() > 0){
		line.append("\n");
		for(int i=0; i<level-1+(int)root->label.size(); i++){
			if(i == level)
				line.append("|");
			else if(i > level-1)
				line.append("_");
			else
				line.append(" ");
		}
		line += " ";
	}

	for(unsigned int j = 0; j < root->tkn.size(); j++){
		tkn = root->tkn[j];
		line.append(tkn.token);
		line.append(" | ");
	}
	if(root->tkn.size() > 0)
		line.erase(line.size() - 2);
	
	cout<<line<<endl;

	printTree(root->child_1, level+1);
	printTree(root->child_2, level+1);
	printTree(root->child_3, level+1);
	printTree(root->child_4, level+1);

}

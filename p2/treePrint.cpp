#include <iostream>
#include "treePrint.h"

void printTree(Node *root, int level) {
    if (root == NULL) {
        return;
    } 
	else { //process node

		string line;
		tokenInfo tkn;

        for (int i = 0; i < level; i++) {
            line.append("_");
        }
        level++;

        line.append(root->label.c_str());
        line.append(" ");
        
		for(int j = 0; j < root->tkn.size(); j++){
			tkn = root->tkn[j];
			line.append(tkn.token);
			line.append(" | ");
		}
		cout<<line<<endl;

        printTree(root->child_1, level+1);
        printTree(root->child_2, level+1);
        printTree(root->child_3, level+1);
        printTree(root->child_4, level+1);
        printTree(root->child_5, level+1);
    }
}

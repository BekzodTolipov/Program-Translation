#include "codeGenerator.h"
FILE *ofp = NULL;
vector<tokenInfo> local_st;
void startGenerator(Node *p, vector<tokenInfo> st, string fileName){
	return;
}

void printToTarget(tokenInfo tkn){
	cout<<tkn.token<<endl;
}

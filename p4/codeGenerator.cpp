#include "codeGenerator.h"
FILE *ofp = NULL;
vector<tokenInfo> local_st;
vector<string> temp_vars;

void startGenerator(Node *p, vector<tokenInfo> st, string fileName){
	local_st = st;
	//ofp = fopen(fileName.c_str(), "w");

	program(p);

	//Need to travers local_st and declare vars in assembly
	return;
}

void program(Node *p){
	if(p == NULL)
		return;
	vars(p->child_1);
	block(p->child_2);
}

void block(Node *p){
	if(p == NULL)
		return;
		vars(p->child_1);

		stats(p->child_2);
}

void vars(Node *p){
	if(p == NULL)
		return;
	if(p->tkn.size() != 0 && p->tkn[0].tokenType != "emptyToken" ){
		int pos = createNewTemp("VAR");
		printToTarget(temp_vars[pos], "STORE");
		printToTarget(p->tkn[1].token, "LOAD");
		printToTarget(p->tkn[0].token, "STORE");
		printToTarget(temp_vars[pos], "LOAD");

			vars(p->child_1);
	}
}

void stats(Node *p){
	if(p == NULL)
		return;
		stat(p->child_1);
		mStat(p->child_2);
}

void mStat(Node *p){
	if(p == NULL)
		return;
		stat(p->child_1);
		mStat(p->child_2);
}

void stat(Node *p){
	if(p == NULL)
		return;
	in(p->child_1);
	out(p->child_1);
}

void in(Node *p){
	if(p == NULL)
		return;
	if(p->label == "<in>")
		printToTarget(p->tkn[0].token, "WRITE");
}

void out(Node *p){
	if(p == NULL)
		return;
	if(p->label == "<out>")
		expr(p->child_1);
}

void expr(Node *p){
	if(p == NULL)
		return;
	
}

int createNewTemp(string what){
	static int var_cnt = 0;
	static int lab_cnt = 0;
	string tempName = "";


	if(what == "VAR"){ //create new temp var
		tempName = "VAR_" + to_string(++var_cnt);
		temp_vars.push_back(tempName);
		return (temp_vars.size()-1);
	}
	else if(what == "LABEL"){ // create new temp label
		tempName += "LABEL" + (++lab_cnt);
	}


	// need to return position of local_st
	return -1;
}

void printToTarget(string tkn, string command){
	cout<<command<<" "<<tkn<<endl;
}

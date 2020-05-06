#include "codeGenerator.h"
FILE *ofp = NULL;
vector<tokenInfo> local_st;
vector<string> temp_vars;
vector<string> temp_labs;
string VAR_TYPE = "VAR";
string LAB_TYPE = "LABEL";

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
		int pos = createNewTemp(VAR_TYPE);
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
	iffy(p->child_1);
	//loop(p->child_1);
	//label(p->child_1);
	//goTo(p->child_1);
}

void in(Node *p){
	if(p == NULL)
		return;

	//cout<<"in()\n";
	if(p->label == "<in>")
		printToTarget(p->tkn[0].token, "READ");
}

void out(Node *p){
	if(p == NULL)
		return;

	//cout<<"out()\n";
	if(p->label == "<out>")
		expr(p->child_1);
}

void expr(Node *p){
	if(p == NULL)
		return;

	//cout<<"expr() "<<"\n";
	N(p->child_1);
	if(p->child_2 != NULL){
		int pos = createNewTemp(VAR_TYPE);
		printToTarget(temp_vars[pos], "STORE");
		expr(p->child_2);
		printToTarget(temp_vars[pos], "SUB");
	}
}

void N(Node *p){
	if(p == NULL)
		return;

	//cout<<"N()\n";

	if(p->tkn.size() == 0){
		A(p->child_2);
		return;
	}
	N(p->child_2);
	if(p->child_1 != NULL){
		if(p->child_2->tkn[0].tokenType == "divideToken"){
			int pos = createNewTemp(VAR_TYPE);
			printToTarget(temp_vars[pos], "STORE");
			A(p->child_1);
			printToTarget(temp_vars[pos], "DIV");
		}
		else if(p->tkn[0].tokenType == "multiplyToken"){
			int pos = createNewTemp(VAR_TYPE);
			printToTarget(temp_vars[pos], "STORE");
			A(p->child_1);
			printToTarget(temp_vars[pos], "MULT");
		}
	}
}

void A(Node *p){
	if(p == NULL)
		return;

	//cout<<"A()\n";

	if(p->tkn.size() == 0){
		M(p->child_1);
	}
	A(p->child_2);
	if(p->child_1 != NULL){
		int pos = createNewTemp(VAR_TYPE);
		printToTarget(temp_vars[pos], "STORE");
		M(p->child_1);
		printToTarget(temp_vars[pos], "ADD");
	}
}

void M(Node *p){
	if(p == NULL)
		return;

	//cout<<"M()";
	if(p->label == "<M>"){
		M(p->child_1);
		printToTarget("-1", "MULT");
	}
	else if(p->label == "<R>"){
		R(p->child_1);
	}
}

void R(Node *p){
	if(p == NULL)
		return;

	//cout<<"R()\n";
	if(p->tkn.size() != 0){
		if(p->tkn[0].tokenType == "idToken" || p->tkn[0].tokenType == "intToken"){
			printToTarget(p->tkn[0].token, "LOAD");
		}
	}
	else{
		expr(p->child_1);
	}
}

void iffy(Node *p){
	if(p == NULL || p->label != "<iffy>")
		return;

	//cout<<"iffy()\n";
	expr(p->child_1);
	int v_pos = createNewTemp("VAR");
	printToTarget(temp_vars[v_pos], "STORE");
	expr(p->child_3);
	printToTarget(temp_vars[v_pos], "SUB");
	int l_pos = createNewTemp("LABEL");
	if(p->child_2->tkn[0].tokenType == "eqEqToken"){
		printToTarget(temp_labs[l_pos], "BRNEG");
		printToTarget(temp_labs[l_pos], "BRPOS");
	}
	else if(p->child_2->tkn[0].token == "lessThanToken"){
		if(p->child_2->tkn.size() == 2){
			if(p->child_2->tkn[1].token == "greaterThanToken"){
				printToTarget(temp_labs[l_pos], "BRZERO");
			}
			else{
				printToTarget(temp_labs[l_pos], "BRPOS");
			}
		}
		else{
			printToTarget(temp_labs[l_pos], "BRPOS");
		}
	}
	else{
		printToTarget(temp_labs[l_pos], "BRNEG");
	}
	stat(p->child_4);
	printToTarget(": NOOP", temp_labs[l_pos]);
	return;
}

void loop(Node *p){
	if(p == NULL || p->label != "<loop>")
		return;

	expr(p->child_1);
	int v_pos = createNewTemp("VAR");
	printToTarget(temp_vars[v_pos], "STORE");
	expr(p->child_3);
	printToTarget(temp_vars[v_pos], "SUB");
	int l_pos = createNewTemp("LABEL");

	if(p->child_2->tkn[0].tokenType == "eqEqToken"){
		printToTarget(temp_labs[l_pos], "BRNEG");
		printToTarget(temp_labs[l_pos], "BRPOS");
	}
	stat(p->child_4);
	printToTarget(": NOOP", temp_labs[l_pos]);
}

void assign(Node *p){
	if(p == NULL || p->label != "<assign>")
		return;

	expr(p->child_1);
}

void label(Node *p){
	if(p == NULL || p->label != "<label>")
		return;

	// Dont know yet
}

void goTo(Node *p){
	if(p == NULL || p->label != "<goto>")
		return;
	printToTarget(p->tkn[0].token, "BR");
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
		tempName = "LABEL_" + to_string(++lab_cnt);
		temp_labs.push_back(tempName);
		return (temp_labs.size()-1);
	}


	// need to return position of local_st
	return -1;
}

void printToTarget(string tkn, string command){
	cout<<command<<" "<<tkn<<endl;
}

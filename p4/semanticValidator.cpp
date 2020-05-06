#include <iostream>
#include <algorithm>
//#include <map>
#include "semanticValidator.h"

tokenInfo foundToken;
static string originTag = "";

map<string, int> error_map = {
	{"VARS_ERR_CODE", 1},
	{"IN_ERR_CODE", 2},
	{"ASS_ERR_CODE", 3},
	{"R_ERR_CODE", 4},
	{"LABEL_ERR_CODE", 5},
	{"GOTO_ERR_CODE", 6}
};

// Generate ERRORS
void errorMessage(tokenInfo token, int option){
	switch(option){
		case 1: cout<<"[SEMANTIC-ERROR]: Error caught during <declare> statement:\n-->Variable already has been declared "<<token.token<<" in line "<<token.line+1<<endl;
			break;
		case 2: cout<<"[SEMANTIC-ERROR]: Error coaught during <in> statement:\n-->Variable has not been declared "<<token.token<<" in line "<<token.line+1<<endl;
			break;
		case 3: cout<<"[SEMANTIC-ERROR]: Error coaught during <assign> statement:\n-->Variable has not been declared "<<token.token<<" in line "<<token.line+1<<endl;
			break;
		case 4: cout<<"[SEMANTIC-ERROR]: Error coaught during "<<originTag<<" statement:\n-->Variable has not been declared "<<token.token<<" in line "<<token.line+1<<endl;
			break;
		case 5: cout<<"[SEMANTIC-ERROR]: Error coaught during <label> statement:\n-->Variable has not been declared "<<token.token<<" in line "<<token.line+1<<endl;
			break;
		case 6: cout<<"[SEMANTIC-ERROR]: Error coaught during <goto> statement:\n-->Variable has not been declared "<<token.token<<" in line "<<token.line+1<<endl;
			break;
	}

	cout<<"\n";
	exit(EXIT_FAILURE);
}

// Check if variable used in <out>, <iffy>, <assing>, <in>, <goto>, <loop>, <label> is declared
void checkIfDeclared(tokenInfo tkn, bool isFound, string errCode){
	if(tkn.tokenType == "idToken"){
		if(!isFound){
			if(tkn.token == "Empty") return;
			errorMessage(tkn, error_map[errCode]);
		}
	}
}

// Check if identifier in a node exists in declared variable pool
bool checkIfInPool(tokenInfo fromNode, vector<tokenInfo> pool){
	for(unsigned int j = 0; j < pool.size(); j++){
		if(fromNode.tokenType == "idToken" && pool[j].token == fromNode.token){
			foundToken = pool[j];
			return true;
		}
	}
	return false;
}

// Driver
vector<tokenInfo> validateSemantic(Node *p){
	static vector<tokenInfo> stt = {};
	if(p == NULL){
		return stt;
	}

	if(p->label == "<vars>"){
		//cout<<"Found vars, label: "<<p->label<<endl;
		for(unsigned int i = 0; i < p->tkn.size(); i++){
			bool isFound = checkIfInPool(p->tkn[i], stt);

			if(p->tkn[i].tokenType == "idToken"){
				if(!isFound){
					if(p->tkn[i].token == "Empty") continue;
					stt.push_back(p->tkn[i]);
				}
				else{
					errorMessage(foundToken, error_map["VARS_ERR_CODE"]);
				}
			}
		}
	}
	else if(p->label == "<in>"){
		//cout<<"Found <in>, token: "<<p->tkn[0].token<<endl;
		for(unsigned int i = 0; i < p->tkn.size(); i++){
			bool isFound = checkIfInPool(p->tkn[i], stt);

			checkIfDeclared(p->tkn[i], isFound, "IN_ERR_CODE");
		}
	}
	else if(p->label == "<assign>"){
		for(unsigned int i = 0; i < p-> tkn.size(); i++){
			bool isFound = checkIfInPool(p->tkn[i], stt);
			
			checkIfDeclared(p->tkn[i], isFound, "ASS_ERR_CODE");
		}
	}
	else if(p->label == "<R>"){
		for(unsigned int i = 0; i < p-> tkn.size(); i++){
			bool isFound = checkIfInPool(p->tkn[i], stt);
			checkIfDeclared(p->tkn[i], isFound, "R_ERR_CODE");
		}
	}
	else if(p->label == "<out>"){
		originTag = "<out>";
    }
	else if(p->label == "<label>"){
        for(unsigned int i = 0; i < p-> tkn.size(); i++){
            bool isFound = checkIfInPool(p->tkn[i], stt);
            checkIfDeclared(p->tkn[i], isFound, "LABEL_ERR_CODE");
        }
	}
	else if(p->label == "<goto>"){
        for(unsigned int i = 0; i < p-> tkn.size(); i++){
            bool isFound = checkIfInPool(p->tkn[i], stt);
            checkIfDeclared(p->tkn[i], isFound, "GOTO_ERR_CODE");
        }
    }
	else if(p->label == "<iffy>"){
		originTag = "<iffy>";
	}
	else if(p->label == "<loop>"){
		originTag = "<loop>";
	}

	validateSemantic(p->child_1);
	validateSemantic(p->child_2);
	validateSemantic(p->child_3);
	validateSemantic(p->child_4);

	return stt;
}

#include <iostream>
#include <algorithm>
#include "semanticValidator.h"

bool isNumber(string s){
	for (unsigned int i = 0; i < s.length(); i++) 
		if (isdigit(s[i]) == false) 
			return false; 

	return true;
}

void validateSemantic(Node *p){
	static vector<tokenInfo> stt = {};
	if(p == NULL){
		return;
	}

	if(p->label == "<vars>"){
		//cout<<"Found vars, label: "<<p->label<<endl;
		for(unsigned int i = 0; i < p->tkn.size(); i++){
			bool isFound = false;
			tokenInfo foundToken;
			for(unsigned int j = 0; j < stt.size(); j++){
				//cout<<"Checking token: "<< stt[j].token<<"  and  "<<p->tkn[i].token<<endl;
				if(!isNumber(p->tkn[i].token) && stt[j].token == p->tkn[i].token){
					isFound = true;
					//cout<<"FAILED CHECKING: "<< stt[j].token<<"  and  "<<p->tkn[i].token<<endl;
					foundToken = stt[j];
					break;
				}
				else {
					//cout<<"PASSED CHECKING: "<< stt[j].token<<"  and  "<<p->tkn[i].token<<endl;
				}
			}
			if(!isNumber(p->tkn[i].token)){
				if(!isFound){
					if(p->tkn[i].token == "Empty") continue;
					//cout<<"Adding: "<<p->tkn[i].token<<"\n\n";
					stt.push_back(p->tkn[i]);
				}
				else{
					cout<<"[SEMANTIC-ERROR]: Variable already has been declared "<<foundToken.token<<" in line "<<foundToken.line+1<<endl;
					exit(EXIT_FAILURE);
				}
			}
		}
	}

	validateSemantic(p->child_1);
	validateSemantic(p->child_2);
	validateSemantic(p->child_3);
	validateSemantic(p->child_4);
}

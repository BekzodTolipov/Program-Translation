#include "scanner.h"

using namespace std;

int asciiMax = 128;
const int FINAL = 1000;
const int ERROR = 0;

Scanner::Scanner() {
	setupFSAtable();
}

void Scanner::printTheWord() {
	cout<<wordToCheck<<endl;
}

void Scanner::setNewWord(string newWord, int line, int word) {
	wordToCheck = newWord;
	lineCount = line;
	wordCount = word;
	driverFA();
}

char Scanner::getLetter(unsigned int pos){
	if(pos >= wordToCheck.size()){
		//	int val = '\0';
		//	cout<<val<<" null value\n";
		return '\0';
	}
	//cout<<"\n\n letter we checking: "<< wordToCheck[pos]<<"\n\n";
	return wordToCheck[pos];
	//	int value = (int) val;
	//	return value;
}

void Scanner::addToStruct(int pos){
	temp.tokenType = tokenType[pos];
	temp.token = acceptingToken;
	temp.line = lineCount;
	temp.charToWord = wordCount;
}

void Scanner::printTokens(){
	cout<<"<"<<temp.tokenType<<", "<<temp.token<<", "<<temp.line<<", "<<temp.charToWord<<">\n";
}

void Scanner::findTokenType(int state){
	int check = state-1001;
	//struct tokenInfo temp = NULL;
	//	switch(check){
	//		case 0:	// For identifiers and reserved words
	if(find(reservedWords.begin(), reservedWords.end(), acceptingToken) != reservedWords.end()){
		//printTokens("resToken");
		addToStruct(22);// resWord	
		printTokens();
		tokens.push_back(temp);
	}
	else{
		//cout<<"<idToken, "<<wordToCheck<<">\n";
		//printTokens("idToken");
		addToStruct(check);
		printTokens();
		tokens.push_back(temp);
	}
	//			break;
	//		case 1:	// For integers
	//cout<<"<intToken, "<<wordToCheck<<">\n";
	//printTokens("intToken");
	//			addToStruct(check);
	//			printTokens();
	//			tokens.push_back(temp);
	//			break;
	//		case 2:
	//			addToStruct();
	//			printTokens()
	//		case 21:	// End of file token
	//printTokens("EOFToken");
	//			addToStruct(check);
	//			printTokens
	//			tokens.push_back(temp);
	//			break;
	//	}

}

void Scanner::findError(int state){
	int val = (state * -1) - 1;
	vector<string> errors = {"Unknown symbol was found", "Unknown symbol was found in identifier", "can NOT be used by itself (valid symbols{:= or ==})"};

	cout<<"SCANNER ERROR: "<<"'"<<wordToCheck<<"' "<<errors[val]<<" on line: "<<lineCount<<", "<<wordCount<<endl;
}

void Scanner::driverFA(){
	if(wordToCheck == "EOF"){
		acceptingToken = "EOF";
		findTokenType(1022);
		return;
	}
	int state = 1;
	int nextState;
	char nextChar;
	unsigned int position = 0;
	string potenToken = "";
	//	for(char letter : wordToCheck){
	while(state < FINAL){
		nextChar = getLetter(position);
		//cout<<state<<" state its in\n";
		nextState = fsaTable[state][nextChar];
		//cout<<nextState<<" Checking next state\n";
		if(nextState < ERROR){
			wordCount += position;
			findError(nextState);
			return;
		}
		if(nextState > FINAL){
			if((state != 8) and ((potenToken == ":" and nextChar == '=') or (potenToken == "=" and nextChar == '='))){
				state = 8;
				continue;
			}
			else if((state == 8) and ((potenToken == ":" and nextChar == '=') or (potenToken == "=" and nextChar == '='))){
				position++;
			}

			if(position < wordToCheck.size()){
				acceptingToken = wordToCheck.substr(0, position);
				findTokenType(nextState);
				wordToCheck = wordToCheck.substr(position, (wordToCheck.size()-position));
				//cout<<"\n\n"<<wordToCheck<<" new substring we have\n\n";
				state = 1;
				wordCount += position;
				position = -1;
				potenToken = "";
			}
			else{
				//cout<<"\n\nposition not less anymore\n\n";
				acceptingToken = wordToCheck;
				findTokenType(nextState);
				return;
			}	
		}
		else{
			state = nextState;
			potenToken += nextChar;
		}
		position++;
		//	if(getLetter(position) == '\0')
		//		break;
	}
	//	}
}

void Scanner::setupFSAtable() {
	/*
State_1: will send each matching letter to next state
State_2: if letters will keep accepting until non letter or non digit given
State_2: if letter or digit keep accepting for others finish the token

Errors:
-1: Unknown symbol to language is given
-2: 
-3: = is not accepted by itself
-4:
-5:

Accepting:
1001: Identifiers
1002: Integers
1003: Colon Operator
1004: Colon Equal Operator
1005: Less Than Operator
1006: Greater Than Operator
1007: == Operator
1008: + Operator
1009: - Operator
1010: * Operator
1011: / Operator
1012: % Operator
1013: . Operator
1014: ( Operator
1015: ) Operator
1016: , Operator
1017: { Operator
1018: } Operator
1019: ; Operator
1020: [ Operator
1021: ] Operator

1022: EOFToken
1023: resWordToken
*/
	int i;
	int j;
	vector<int> header;
	vector<int> state_1;	// For White Space

	for(i=0; i < asciiMax; i++){
		header.push_back(i);
		state_1.push_back(-1);
	}
	fsaTable.push_back(header);

	int accept = 999;

	for(j=0; j < 22; j++){
		// Set up header of the matrix
		for(i=0; i < asciiMax; i++){
			//header.push_back(i);
			if(i == 32){	// WS
				if(j==0)
					state_1[i] = 1;
				else if(j==7)
					state_1[i] = -3;
				else
					state_1[i] = accept+j;
			}
			else if(i == 37){	// Percent
				if(j==0){
					state_1[i] = 13;
				}
				else if(j == 2){
					state_1[i] = -2;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 40){	// Left Paren
				if(j==0){
					state_1[i] = 15;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 41){	// Right Parenthesis
				if(j==0){
					state_1[i] = 16;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 43){	// Plus
				if(j==0){
					state_1[i] = 9;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 44){	// Comma
				if(j==0){
					state_1[i] = 17;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 45){ // Minus
				if(j==0){
					state_1[i] = 10;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 46){	// Period
				if(j==0){
					state_1[i] = 14;
				}
				else if(j==2){
					state_1[i] = -2;
				} 
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 47){	// Slash 
				if(j==0){
					state_1[i] = 12;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i >= 48 and i <= 57){	//Digits
				if(j==0){
					state_1[i] = 3;
				}
				else if(j==1){
					state_1[i] = 2;
				}
				else if(j==2){
					state_1[i] = 3;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 58){	// Colon
				if(j==0){
					state_1[i] = 4;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 59){	// Semicolon
				if(j==0){
					state_1[i] = 20;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 60){	// Less than
				if(j==0){
					state_1[i] = 6;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 61){	// Equal
				if(j==0){
					state_1[i] = 8;
				}
				else if(j==3){
					state_1[i] = 5;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 62){	// Greater than
				if(j==0){
					state_1[i] = 7;
				}
				else if(j==7){
					state_1[i] = 8;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 91){	// Left square bracket
				if(j==0){
					state_1[i] = 21;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 93){	// Right square bracket
				if(j==0){
					state_1[i] = 22;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 42){	// Asterisk
				if(j==0){
					state_1[i] = 11;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 123){	// Left curly
				if(j==0){
					state_1[i] = 18;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 125){	// Right curly
				if(j==0){
					state_1[i] = 19;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i>=65 and i<91) {	// Uppercase
				if(j==0 || j==1){
					state_1[i] = 2;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i>=97 and i<123){	// Lowercase
				if(j==0 || j==1){
					state_1[i] = 2;
				}
				else if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 0){	// Null
				if(j==7){
					state_1[i] = -3;
				}
				else{
					state_1[i] = accept+j+1;
				}
			}

		}
		//fsaTable.push_back(header);
		fsaTable.push_back(state_1);// ]
	}

}

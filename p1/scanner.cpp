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
	
	return wordToCheck[pos];
//	int value = (int) val;
//	return value;
}

void Scanner::addToStruct(){
	temp.token = wordToCheck;
	temp.line = lineCount;
	temp.charToWord = wordCount;
}

void Scanner::printTokens(string tokenType){
	cout<<"<"<<tokenType<<", "<<wordToCheck<<", "<<lineCount<<", "<<wordCount<<">\n";
}

void Scanner::findTokenType(int state){

	//struct tokenInfo temp = NULL;
	switch(state-1001){
		case 0:	// For identifiers and reserved words
			if(find(reservedWords.begin(), reservedWords.end(), wordToCheck) != reservedWords.end()){
				printTokens("resToken");
				addToStruct();	
                resToken.push_back(temp);
            }
            else{
				//cout<<"<idToken, "<<wordToCheck<<">\n";
				printTokens("idToken");
				addToStruct();
                idToken.push_back(temp);
            }
			break;
		case 1:	// For integers
			//cout<<"<intToken, "<<wordToCheck<<">\n";
			printTokens("intToken");
			addToStruct();
			intToken.push_back(temp);
			break;
	}

}

void Scanner::findError(int state){
	int val = (state * -1) - 1;
	vector<string> errors = {"Unknown symbol was found", "Unknown symbol was found in identifier", "Unknown symbol was found in Integer"};

	cout<<"SCANNER ERROR: "<<errors[val]<<endl;
}

void Scanner::driverFA(){
	int state = 1;
	int nextState;
	char nextChar;
	int position = 0;
	string potenToken = "";
//	for(char letter : wordToCheck){
		while(state < FINAL){
			nextChar = getLetter(position);
			//cout<<state<<" state its in\n";
			nextState = fsaTable[state][nextChar];
			//cout<<nextState<<" Checking next state\n";
			if(nextState < ERROR){
				findError(nextState);
				return;
			}
			if(nextState > FINAL){
				findTokenType(nextState);
				return;	
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

		Accepting:
		1001: Identifiers
		1002: Integers
	*/
	int i;
	vector<int> header;
	vector<int> state_1;	// For White Space
	vector<int> state_2;	// For Identifiers
	vector<int> state_3;	// For Integers
	// Set up header of the matrix
	for(i=0; i < asciiMax; i++){
		header.push_back(i);
		if(i == 32){	// WS
			state_1.push_back(1);
			state_2.push_back(1001);
			state_3.push_back(1002);
		}
		else if(i == 37){	// Percent
			state_1.push_back(-1);
			state_2.push_back(1001);
			state_3.push_back(-2);
		}
		else if(i >= 40 and i <= 41){	// Parenthesis
			state_1.push_back(-1);
			state_2.push_back(1001);
			state_3.push_back(1002);
		}
		else if(i == 43){	// Plus
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 44){	// Comma
			state_1.push_back(-1);
			state_2.push_back(1001);
			state_3.push_back(1002);
		}
		else if(i == 45){ // Minus
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 46){	// Period
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(-2);
		}
		else if(i == 47){	// Slash 
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i >= 48 and i <= 57){	//Digits
			state_1.push_back(3);
			state_2.push_back(2);
			state_3.push_back(3);
		}
		else if(i == 58){	// Colon
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 59){	// Semicolon
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 60){	// Less than
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 61){	// Equal
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 62){	// Greater than
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 91){	// Left square bracket
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 93){	// Right square bracket
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 42){	// Asterisk
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
		}
		else if(i == 123){	// Left curly
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
			
		}
		else if(i == 125){	// Right curly
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);

		}
		else if(i>=65 and i<91) {	// Uppercase
			state_1.push_back(2);
			state_2.push_back(2);
			state_3.push_back(1002);
		}
		else if(i>=97 and i<123){	// Lowercase
			state_1.push_back(2);
			state_2.push_back(2);
			state_3.push_back(1002);
		}
		else if(i == 0){
			state_1.push_back(-1);
			state_2.push_back(1001);
			state_3.push_back(1002);
		}
		else{
			state_1.push_back(-1);	//Unknown symbol identified
			state_2.push_back(-2);	//Unknown symbol used in identifier
			state_3.push_back(-3);	//Unknown symbol used for integer
		}
		
	}
	fsaTable.push_back(header);
	fsaTable.push_back(state_1);
	fsaTable.push_back(state_2);//Identifiers
	fsaTable.push_back(state_3);//Digits
}

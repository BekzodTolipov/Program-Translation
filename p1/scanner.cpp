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
		case 1000:	// End of file token
			printTokens("EOFToken");
			addToStruct();
			EOFToken.push_back(temp);
			break;
	}

}

void Scanner::findError(int state){
	int val = (state * -1) - 1;
	vector<string> errors = {"Unknown symbol was found", "Unknown symbol was found in identifier", "Unknown symbol was found in Integer"};

	cout<<"SCANNER ERROR: "<<"'"<<wordToCheck<<"' "<<errors[val]<<" on line: "<<lineCount<<", "<<wordCount<<endl;
}

void Scanner::driverFA(){
	if(wordToCheck == "EOF"){
		findTokenType(2001);
		return;
	}
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
				wordCount += position;
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
	*/
	int i;
	vector<int> header;
	vector<int> state_1;	// For White Space
	vector<int> state_2;	// For Identifiers
	vector<int> state_3;	// For Integers
	vector<int> state_4;	// For Colon
	vector<int> state_5;	// For Colon Equal
	vector<int> state_6;	// For Less Than
	vector<int> state_7;	// For Greater Than
	vector<int> state_8;	// For ==
	vector<int> state_9;	// For +
	vector<int> state_10;	// For -
	vector<int> state_11;	// For *
	vector<int> state_12;	// For /
	vector<int> state_13;	// For %
	vector<int> state_14;	// For .
	vector<int> state_15;	// For (
	vector<int> state_16;	// For )
	vector<int> state_17;	// For ,
	vector<int> state_18;	// For {
	vector<int> state_19;	// For }
	vector<int> state_20;	// For ;
	vector<int> state_21;	// For [
	vector<int> state_22;	// For ]

	// Set up header of the matrix
	for(i=0; i < asciiMax; i++){
		header.push_back(i);
		if(i == 32){	// WS
			state_1.push_back(1);
			state_2.push_back(1001);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 37){	// Percent
			state_1.push_back(13);
			state_2.push_back(1001);
			state_3.push_back(-2);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 40){	// Left Paren
			state_1.push_back(15);
            state_2.push_back(1001);
            state_3.push_back(1002);
            state_4.push_back(1003);
            state_5.push_back(1004);
            state_6.push_back(1005);
            state_7.push_back(1006);
            state_8.push_back(-3);
            state_9.push_back(1008);
            state_10.push_back(1009);
            state_11.push_back(1010);
            state_12.push_back(1011);
            state_13.push_back(1012);
            state_14.push_back(1013);
            state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);

		}
		else if(i == 41){	// Right Parenthesis
			state_1.push_back(16);
			state_2.push_back(1001);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 43){	// Plus
			state_2.push_back(1001);
			state_1.push_back(9);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 44){	// Comma
			state_1.push_back(17);
			state_2.push_back(1001);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 45){ // Minus
			state_2.push_back(1001);
			state_1.push_back(10);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 46){	// Period
			state_2.push_back(1001);
			state_1.push_back(14);
			state_3.push_back(-2);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 47){	// Slash 
			state_2.push_back(1001);
			state_1.push_back(12);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i >= 48 and i <= 57){	//Digits
			state_1.push_back(3);
			state_2.push_back(2);
			state_3.push_back(3);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 58){	// Colon
			state_2.push_back(1001);
			state_1.push_back(4);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 59){	// Semicolon
			state_2.push_back(1001);
			state_1.push_back(20);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 60){	// Less than
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 61){	// Equal
			state_2.push_back(1001);
			state_1.push_back(8);
			state_3.push_back(1002);
			state_4.push_back(5);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(1007);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 62){	// Greater than
			state_2.push_back(1001);
			state_1.push_back(-1);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 91){	// Left square bracket
			state_2.push_back(1001);
			state_1.push_back(21);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 93){	// Right square bracket
			state_2.push_back(1001);
			state_1.push_back(22);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 42){	// Asterisk
			state_2.push_back(1001);
			state_1.push_back(11);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 123){	// Left curly
			state_2.push_back(1001);
			state_1.push_back(18);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
			
		}
		else if(i == 125){	// Right curly
			state_2.push_back(1001);
			state_1.push_back(19);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);

		}
		else if(i>=65 and i<91) {	// Uppercase
			state_1.push_back(2);
			state_2.push_back(2);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i>=97 and i<123){	// Lowercase
			state_1.push_back(2);
			state_2.push_back(2);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else if(i == 0){	// Null
			state_1.push_back(-1);
			state_2.push_back(1001);
			state_3.push_back(1002);
			state_4.push_back(1003);
			state_5.push_back(1004);
			state_6.push_back(1005);
			state_7.push_back(1006);
			state_8.push_back(-3);
			state_9.push_back(1008);
			state_10.push_back(1009);
			state_11.push_back(1010);
			state_12.push_back(1011);
			state_13.push_back(1012);
			state_14.push_back(1013);
			state_15.push_back(1014);
			state_16.push_back(1015);
			state_17.push_back(1016);
			state_18.push_back(1017);
			state_19.push_back(1018);
			state_20.push_back(1019);
			state_21.push_back(1020);
			state_22.push_back(1021);
		}
		else{
			state_1.push_back(-1);	//Unknown symbol identified
			state_2.push_back(-1);	//Unknown symbol used in identifier
			state_3.push_back(-1);	//Unknown symbol used for integer
			state_4.push_back(-1);	// : error
			state_5.push_back(-1);	// := Error
			state_6.push_back(-1);	// < Error
			state_7.push_back(-1);
			state_8.push_back(-1);
			state_9.push_back(-1);
			state_10.push_back(-1);
			state_11.push_back(-1);
			state_12.push_back(-1);
			state_13.push_back(-1);
			state_14.push_back(-1);
			state_15.push_back(-1);
			state_16.push_back(-1);
			state_17.push_back(-1);
			state_18.push_back(-1);
			state_19.push_back(-1);
			state_20.push_back(-1);
			state_21.push_back(-1);
			state_22.push_back(-1);
		}
		
	}
	fsaTable.push_back(header);
	fsaTable.push_back(state_1);
	fsaTable.push_back(state_2);// Identifiers
	fsaTable.push_back(state_3);// Digits
	fsaTable.push_back(state_4);// Colon
	fsaTable.push_back(state_5);// Colon Equal
	fsaTable.push_back(state_6);// Less Than
	fsaTable.push_back(state_7);// Greater Than
	fsaTable.push_back(state_8);// ==
	fsaTable.push_back(state_9);// +
	fsaTable.push_back(state_10);// -
	fsaTable.push_back(state_11);// *
	fsaTable.push_back(state_12);// /
	fsaTable.push_back(state_13);// %
	fsaTable.push_back(state_14);// .
	fsaTable.push_back(state_15);// (
	fsaTable.push_back(state_16);// )
	fsaTable.push_back(state_17);// ,
	fsaTable.push_back(state_18);// {
	fsaTable.push_back(state_19);// }
	fsaTable.push_back(state_20);// ;
	fsaTable.push_back(state_21);// [
	fsaTable.push_back(state_22);// ]

}

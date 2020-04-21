#include "scanner.h"

using namespace std;

int asciiMax = 128;
const int FINAL = 1000;
const int ERROR = 0;

// Constructor to start building table
Scanner::Scanner() {
	setupFSAtable();
}
// Debug
void Scanner::printTheWord() {
	cout<<wordToCheck<<endl;
}
// Start the scanner by adding the values into its struct and run 
// driverFA() and return its result
void Scanner::setNewWord(string newWord, int line, int word) {
	wordToCheck = newWord;
	lineCount = line;
	wordCount = word;
	//	return driverFA();
}
// Extract letter from word
char Scanner::getLetter(unsigned int pos){
	if(pos >= wordToCheck.size()){
		return '\0';
	}
	return wordToCheck[pos];
}

tokenInfo Scanner::getEmptyToken(){
	tokenInfo dummy;
	dummy.tokenType = "emptyToken";
	dummy.token = "Empty";
	dummy.line = temp.line;
	return dummy;
}

// Keeping it inside struct native to Scanner
void Scanner::addToStruct(int pos){
	temp.tokenType = tokenType[pos];
	temp.token = wordToCheck;
	temp.line = lineCount;
	temp.charToWord = wordCount;
}
// Success tokens to print
string Scanner::printTokens(){
	ostringstream msg_oss;
	msg_oss << "<" << temp.tokenType << ", " << temp.token << ", " << temp.line << ", " << temp.charToWord << ">";
	string msg = msg_oss.str();
	cout<<msg<<endl;
	return msg;
}
// Identify token type, such as identifier, reserved or operator
tokenInfo Scanner::findTokenType(int state){
	int check = state-1001;
	string result = "";
	//	cout<<"TOKEN WORD CURRENTLY: "<<temp.token<<"RRR\n\n"<<endl;
	//	temp.token += '\0';
	if(find(reservedWords.begin(), reservedWords.end(), temp.token) != reservedWords.end()){
		//	addToStruct(22);// resWord	
		//		cout<<"\n\nFOUND RESERVED WORD\n\n";
		temp.tokenType = tokenType[22];
		result = printTokens();
		tokens.push_back(temp);
		return temp;
	}
	else{
		//addToStruct(check);
		temp.tokenType = tokenType[check];
		//		cout<<"\n\nFOUND IDENTIFIER WORD\n\n";
		result = printTokens();
		tokens.push_back(temp);
		return temp;
	}
}
// Fail token error to print
string Scanner::findError(int state){
	int val = (state * -1) - 1;
	vector<string> errors = {"Unknown symbol was found", "Unknown symbol was found in identifier", "can NOT be used by itself (valid symbols{:= or ==})"};
	ostringstream msg_oss;
	msg_oss << "SCANNER ERROR: '" << wordToCheck << "' " << errors[val] << " on line: " << lineCount << ", " << wordCount;
	string msg = msg_oss.str();
	cout<<msg<<endl;
	return msg;
}

// Diver to check if given word is acceptable
tokenInfo Scanner::driverFA(FILE *fp){
	//	if(wordToCheck == "EOF"){
	//		acceptingToken = "EOF";
	//		findTokenType(1022);
	//		return temp;
	//	}
	int state = 1;
	int nextState;
	char nextChar;
	static int line = 0;
	unsigned int position = 0;
	string potenToken = "";
	string WHITESPACE = "\n\r\t\f\v";

		cout<<"driverFA: potenToken: "<<potenToken<<endl;

	while(state < FINAL){
		nextChar = fgetc(fp);
		if(nextChar == -1){
			if(potenToken == ""){
				//ungetc(nextChar, fp);
				temp.tokenType = "EOFToken";
				temp.line = line;
				temp.token = "EOF";
				return temp;
			}
			//else{
			//	ungetc(nextChar, fp);
				
			//}
		}
		cout<<"Next char: "<<nextChar<<endl;
	//	if(nextChar == '\n' && potenToken == ""){
	//		line++;
	//		continue;
	//	}

		if(nextChar == '#'){
			cout<<"[SCANNER]: Found comments!\n";
			nextChar = fgetc(fp);
			while(nextChar != '#' && nextChar != EOF){
				//cout<<nextChar<<endl;
				if(nextChar == '\n')
					line++;
				nextChar = fgetc(fp);
			}
			if(nextChar == EOF){
				temp.tokenType = "EOFToken";
				temp.line = line;
				temp.token = "EOF";
				return temp;
			}
			//else if(nextChar == '#'){
			//	continue;
			//}
			cout<<"[SCANNER]: Comments finished! with nextChar: "<<nextChar<<"\n\n";
			continue;
		}

		nextState = fsaTable[state][nextChar];
		cout<<"Next state: "<<nextState<<endl;
		//cin>>position;
		if(nextState >= 1000 || nextState == -99){
			if(nextChar == '\n'){
				line++;
			}
			if(nextState == -99){
				ungetc(nextChar, fp);
				temp.tokenType = "EOFToken";
				temp.line = line;
				temp.token = "EOF";
				return temp;
			}
			// If FAIL
			if(nextState < ERROR){
				wordCount += position;
				temp.line = line;
				findError(nextState);
				exit(-1);
			}
			// If SUCCSESS
			if(nextState >= FINAL){
			//	if(potenToken == ""){
			//		ungetc(nextChar, fp);
			//		return getEmptyToken();
			//	}
				cout<<"SCANNER: TOKEN: "<<potenToken<<endl;
			//	size_t start = potenToken.find_first_not_of(WHITESPACE);	// Trim left
		//		size_t end = potenToken.find_last_not_of(WHITESPACE);	// Trim right
		//		potenToken = potenToken.substr(start, end+1);

				string trimmed = "";
				for(int i=0; i < potenToken.length(); i++){
					if(!isspace(potenToken[i])){
						trimmed += potenToken[i];
					}
				}
				//cout<<"SCANNER: TOKEN: "<<trimmed<<endl;

				acceptingToken = temp.token = trimmed;
				//potenToken += '\n';
				//setNewWord(potenToken, line, 0);
				findTokenType(nextState);
				//acceptingToken = temp.token = potenToken;
				temp.line = line;
				temp.charToWord = 0;
			//	ungetc(nextChar, fp);
				return temp;
				//}	
		}
		// If still checking
		//	else{
		//cout<<FINAL<<endl;	
		//		state = nextState;
		//		potenToken += nextChar;
		//	}
	}
	else{
		cout<<"Check next char and add to potenToken: "<<nextChar<<endl;
		if(!isspace(nextChar)){
			potenToken += nextChar;
		}
		state = nextState;
	}
}

//temp.tokenType = "EOFToken";
//temp.line = line;
//temp.token = "EOF";
return temp;
//cout<<potenToken<<endl;
//return null;
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
-99: EOF

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
	// Build table by setting everything to reject state
	for(i=0; i < asciiMax; i++){
		header.push_back(i);
		state_1.push_back(-1);
	}
	// Add header for later print the table
	fsaTable.push_back(header);

	int accept = 999;

	for(j=0; j < 22; j++){
		// Set up header of the matrix
		for(i=0; i < asciiMax; i++){
			if(i == 10) {	// NEW-LINE
				if(j==0)
					state_1[i] = 1;
				else if(j==7)
					state_1[i] = -3;
				else
					state_1[i] = accept+j+1;
			}
			else if(i == 26){	// EOF
				if(j==0)
					state_1[i] = 1;
				else{
					state_1[i] = accept+j+1;
				}
			}
			else if(i == 32){	// WS
				if(j==0)
					state_1[i] = 1;
				else if(j==7)
					state_1[i] = -3;
				else
					state_1[i] = accept+j+1;
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
		fsaTable.push_back(state_1);// ]
	}
}

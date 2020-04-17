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
tokenInfo Scanner::setNewWord(string newWord, int line, int word) {
	wordToCheck = newWord;
	lineCount = line;
	wordCount = word;
	return driverFA();
}
// Extract letter from word
char Scanner::getLetter(unsigned int pos){
	if(pos >= wordToCheck.size()){
		return '\0';
	}
	return wordToCheck[pos];
}
// Keeping it inside struct native to Scanner
void Scanner::addToStruct(int pos){
	temp.tokenType = tokenType[pos];
	temp.token = acceptingToken;
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
	if(find(reservedWords.begin(), reservedWords.end(), acceptingToken) != reservedWords.end()){
		addToStruct(22);// resWord	
		result = printTokens();
		tokens.push_back(temp);
		return temp;
	}
	else{
		addToStruct(check);
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

tokenInfo Scanner::scanner(FILE *fp){

	if(!fp) {	// File does not exist
		cout << "[ERROR] Unable to open file\n";
		exit(1); // terminate with error
	}

	string line;
	string word;
	tokenInfo result;
	string WHITESPACE = "\n\r\t\f\v";
	static int line_count = 0;
	string filtered_word = "";
	const int MAX_SIZE = 1024;
	char buff[MAX_SIZE];
	while(!fgets(buff, MAX_SIZE, fp)){
		line = buff;
		int space_to_word = 0;
		line = filterElement(line);
		stringstream iss(line);
		while(iss >> word) {
			if(word == "#"){
				continue;
			}
			size_t start = word.find_first_not_of(WHITESPACE);	// Trim left
			size_t end = word.find_last_not_of(WHITESPACE);	// Trim right
			string trimmed_word = word.substr(start, end+1);
		//	file_vals.push_back(trimmed_word);
			result = setNewWord(trimmed_word, line_count+1, space_to_word);
		//	if(result.find("SCANNER ERROR:") != std::string::npos){
		//		exit(-1);
		//	}
			space_to_word += word.size();
		}
		line_count++;
	}
	setNewWord("EOF", line_count+1, 0);
}

// Will receive a line from file 
// and check if it contains comment
// and filters them out
string Scanner::filterElement(string line){
	int pos = 0;
	int prev_pos = 0;
	string new_line = "";
	stringstream iss(line);
	string word = "";
	static bool found = false;
	if(line == "#"){
		found = found ? false : true;
		return "#";
	}
	while(iss >> word){
		if(word == "#"){
			found = found ? false : true;
			prev_pos = pos = 0;
			continue;
		}
		for(char letter : word){
			if(letter == '#'){
				if(!found){
					new_line +=  word.substr(prev_pos, (pos-prev_pos)) + " ";
					prev_pos = pos+1;
					found = true;
				}
				else{
					prev_pos = pos+1;
					found = false;
				}	
			}
			pos++;
		}
		if(!found && prev_pos < pos){
			new_line += word.substr(prev_pos, pos) + " ";
			prev_pos = pos = 0;
		}
		prev_pos = pos = 0;
	}
	return new_line;
}

// Diver to check if given word is acceptable
tokenInfo Scanner::driverFA(){
	if(wordToCheck == "EOF"){
		acceptingToken = "EOF";
		findTokenType(1022);
		return temp;
	}
	int state = 1;
	int nextState;
	char nextChar;
	unsigned int position = 0;
	string potenToken = "";
	while(state < FINAL){
		nextChar = getLetter(position);
		nextState = fsaTable[state][nextChar];
		// If FAIL
		if(nextState < ERROR){
			wordCount += position;
			findError(nextState);
			exit(-1);
		}
		// If SUCCSESS
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
				state = 1;
				wordCount += position;
				position = -1;
				potenToken = "";
			}
			else{
				acceptingToken = wordToCheck;
				return findTokenType(nextState);
			}	
		}
		// If still checking
		else{	
			state = nextState;
			potenToken += nextChar;
		}
		position++;
	}
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
		fsaTable.push_back(state_1);// ]
	}
}

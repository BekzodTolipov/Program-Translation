#include <bits/stdc++.h> 
#include <string>
#include <vector>
#include <iostream>
//#include "parser.h"

using namespace std;
#ifndef SCANNER_H
#define SCANNER_H

struct tokenInfo {
	string tokenType;
	int line;
	int charToWord;
	string token;
};

class Scanner {
	// Structure to keep track internally
//	struct tokenInfo{
//		string tokenType;
//		int line;
///		int charToWord;
//		string token;
//	};
	private:
	string wordToCheck;	// Checking in progress word
	string acceptingToken;	// Finished checking now will accept that word
	int lineCount;	// Which line word was read
	int wordCount;	// Which column it was found
	struct tokenInfo temp;	// Temp storage for token
	vector< vector<int> > fsaTable;

	vector<tokenInfo> tokens;	// All tokens which was read during execution
	// All accepting token types
	vector<string> tokenType = {"idToken",
		"intToken",
		"colonToken",
		"colonEqToken",
		"lessThanToken",
		"greaterThanToken",
		"eqEqToken",
		"plusToken",
		"minusToken",
		"multiplyToken",
		"divideToken",
		"precentTokent",
		"dotToken",
		"leftParenToken",
		"rightParenToken",
		"commaToken",
		"leftCurlyToken",
		"rightCurlyToken",
		"semicolonToken",
		"leftBrackToken",
		"rightBreacketToken",
		"EOFToken",
		"resWordToken"
	};
	// All accepting reserved words
	vector<string> reservedWords = {"label", 
		"goto", 
		"loop", 
		"void", 
		"declare", 
		"return", 
		"in", 
		"out", 
		"program", 
		"iffy", 
		"then", 
		"assign", 
		"data"
	};
	public:
	// Prototypes
	Scanner();
	tokenInfo scanner(FILE *fp);
	void printTheWord();
	tokenInfo setNewWord(string newWord, int lineCount, int wordCount);
	void setupFSAtable();
	tokenInfo driverFA();
	char getLetter(unsigned int);
	tokenInfo findTokenType(int);
	string findError(int);
	void addToStruct(int);
	string printTokens();
	string filterElement(string line);
};

#endif

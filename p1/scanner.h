#include <bits/stdc++.h> 
#include <string>
#include <vector>

using namespace std;
#ifndef SCANNER_H
#define SCANNER_H

class Scanner {
	struct tokenInfo{
		string tokenType;
		int line;
		int charToWord;
		string token;
	};
	private:
	string wordToCheck;
	string acceptingToken;
	int lineCount;
	int wordCount;
	struct tokenInfo temp;
	vector<vector<int>> fsaTable;

	vector<tokenInfo> tokens;

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
	Scanner();
	void printTheWord();
	void setNewWord(string newWord, int lineCount, int wordCount);
	void setupFSAtable();
	void driverFA();
	char getLetter(unsigned int);
	void findTokenType(int);
	void findError(int);
	void addToStruct(int);
	void printTokens();
};

#endif

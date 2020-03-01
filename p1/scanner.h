#include <bits/stdc++.h> 
#include <string>
#include <vector>

using namespace std;
#ifndef SCANNER_H
#define SCANNER_H

class Scanner {
	struct tokenInfo{
		int line;
		int charToWord;
		string token;
	};
	private:
		string wordToCheck;
		int lineCount;
		int wordCount;
		struct tokenInfo temp;
		vector<vector<int>> fsaTable;

		vector<tokenInfo> idToken;
		vector<tokenInfo> intToken;
		vector<tokenInfo> resToken;

		vector<string> reservedWords = {"label", "goto", "loop", "void", "declare", "return", "in", "out", "program", "iffy", "then", "assign", "data"};
	public:
		Scanner();
		void printTheWord();
		void setNewWord(string newWord, int lineCount, int wordCount);
		void setupFSAtable();
		void driverFA();
		char getLetter(unsigned int);
		void findTokenType(int);
		void findError(int);
		void addToStruct();
		void printTokens(string);
};

#endif

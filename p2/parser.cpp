#include "parser.h"

tokenInfo tkn;
FILE *fp = NULL;
Scanner scan;

Node *parser(string filename) {
	fp = fopen(filename.c_str(), "r");
	tkn = scan.scanner(fp);
	
	// Create root node
	Node *root = NULL;
	root = program();
	
	if(tkn.tokenType == "EOFToken") {
		root->tkn.push_back(tkn);
		
		return root;
	} else {
		printf("Error on line %i: Could not find EOF token\n", tkn.line);
		exit(EXIT_FAILURE);
	}

	fclose(fp);
}

// <program> -> program <vars> <block>
Node *program() {
	//printf("Entered program\n");
	// Create new node
	Node *newNode = createNode("<program>");
	
	if(tkn.token == "program") {
		newNode->tkn.push_back(tkn);
		tkn = scan.scanner(fp);
		
	//	newNode->child_1 = vars();
		newNode->child_2 = block();
		
		return newNode;
		
	} else {
		printf("Error on line %d: Expected \"program\"\n", tkn.line);
		exit(EXIT_FAILURE);
	}
}

// <block> -> start <vars> <stats> stop
Node *block() {
	//printf("Entered block\n");
	// Create new node
	Node *newNode = createNode("<block>");
	
	if(tkn.token == "start") {
		newNode->tkn.push_back(tkn);
		tkn = scan.scanner(fp);
		
	//	newNode->child_1 = vars();
	//	newNode->child_2 = stats();
		
		if(tkn.token == "stop") {
			newNode->tkn.push_back(tkn);
			tkn = scan.scanner(fp);
			
			return newNode;
			
		} else {
			printf("Error on line %d: Expected \"stop\"\n", tkn.line);
			exit(EXIT_FAILURE);
		}
		
	} else {
		printf("Error on line %d: Expected \"start\" tkn\n", tkn.line);
		exit(EXIT_FAILURE);
	}
}

Node *createNode(string name) {
	Node* newNode = new Node();
	newNode->child_1 = NULL;
	newNode->child_2 = NULL;
	newNode->child_3 = NULL;
	newNode->child_4 = NULL;
	newNode->child_5 = NULL;
	newNode->label = name;
	
	return newNode;
}

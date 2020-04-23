#include "parser.h"

tokenInfo tkn;
tokenInfo empty_tkn;
FILE *fp = NULL;
Scanner scan;

Node *parser(string filename) {
	fp = fopen(filename.c_str(), "r");
	tkn = scan.driverFA(fp);

	// Create root node
	Node *root = NULL;
	root = program();

	if(tkn.tokenType == "EOFToken") {
		fclose(fp);
		return root;
	} 
	else {
		printf("Error on line %i: Could not find EOF token\n", tkn.line);
		exit(EXIT_FAILURE);
	}
}

// <program> -> program <vars> <block>
Node *program() {
	cout<<"Entered program();\n";
	Node *newNode = createNode("<program>");

	newNode->child_1 = vars();
	newNode->child_2 = block();

	return newNode;
}

// <block> -> { <vars> <stats> }
Node *block() {
	cout<<"Entered block(); tokenType: "<<tkn.tokenType<<endl;

	Node *newNode = createNode("<block>");

	if(tkn.tokenType == "leftCurlyToken") {
		tkn = scan.driverFA(fp);

		newNode->child_1 = vars();
		newNode->child_2 = stats();

		if(tkn.tokenType == "rightCurlyToken") {
			tkn = scan.driverFA(fp);
			return newNode;
		} 
		else {
			printf("Error on line %d: Expected \"}\"\n", tkn.line);
			exit(EXIT_FAILURE);
		}
	} 
	else {
		printf("Error on line %d: Expected \"{\" tkn\n", tkn.line);
		exit(EXIT_FAILURE);
	}
}

//<vars> -> empty | declare Identifier := Integer ; <vars>
Node *vars(){
	cout<<"Entered vars(); tokenType: "<<tkn.tokenType<<endl;
	Node* newNode = createNode("<vars>");

	if(tkn.tokenType == "resWordToken" && tkn.token == "declare"){
		tkn = scan.driverFA(fp);

		if(tkn.tokenType == "idToken"){
			newNode->tkn.push_back(tkn);
			tkn = scan.driverFA(fp);

			if(tkn.tokenType == "colonEqToken"){
				tkn = scan.driverFA(fp);

				if(tkn.tokenType == "intToken"){
					newNode->tkn.push_back(tkn);
					tkn = scan.driverFA(fp);

					if(tkn.tokenType == "semicolonToken"){
						tkn = scan.driverFA(fp);

						newNode->child_1 = vars();
						return newNode;
					}
					else{
						printf("[PARSER ERROR]: Error in line %d: Expected \";\" token\n", tkn.line);
						exit(EXIT_FAILURE);
					}
				}
				else{
					printf("[PARSER ERROR]: Error in line %d: Expected \"Integer\" token\n", tkn.line);
					exit(EXIT_FAILURE);
				}
			}
			else{
				printf("[PARSER ERROR]: Error in line %d: Expected \":=\" token\n", tkn.line);
				exit(EXIT_FAILURE);		
			}
		}
		else{
			printf("[PARSER ERROR]: Error on line %d: Expected Identifier\n", tkn.line);
			exit(EXIT_FAILURE);
		}
	}
	else{
		newNode->tkn.push_back(scan.getEmptyToken());
		return newNode;
	}

	exit(EXIT_FAILURE);
}

// <expr> -> <N> - <expr> | <N>
Node *expr(){
	cout<<"Entered expr()\n";
	Node* newNode = createNode("<expr>");

	newNode->child_1 = N();

	if(tkn.tokenType == "minusToken"){
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);

		newNode->child_2 = expr();
	}

	return newNode;
}

// <N> -> <A> / <N> | <A> * <N> | <A>
Node *N(){
	cout<<"Entered N()\n";
	Node *newNode = createNode("<N>");

	newNode->child_1 = A();

	if(tkn.tokenType == "divideToken" || tkn.tokenType == "multiplyToken"){
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);

		newNode->child_2 = N();
	}

	return newNode;
}

// <A> -> <M> + <A> | <M>
Node *A(){
	cout<<"Entered A()\n";
	Node* newNode = createNode("<A>");

	newNode->child_1 = M();

	if(tkn.tokenType == "plusToken"){
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);

		newNode->child_2 = A();
	}

	return newNode;
}

// <M> -> * <M> | <R>
Node *M(){
	cout<<"Entered M()\n";
	Node* newNode = createNode("<M>");

	if(tkn.tokenType == "multiplyToken"){
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);

		newNode->child_1 = M();
		return newNode;
	}

	newNode->child_1 = R();
	return newNode;
}

// <R> -> ( <expr> ) | Identifier | Integer
Node *R(){
	cout<<"Entered R()\n";
	Node* newNode = createNode("<R>");

	if(tkn.tokenType == "leftParenToken"){
		tkn = scan.driverFA(fp);

		newNode->child_1 = expr();

		if(tkn.tokenType == "rightParenToken"){
			tkn = scan.driverFA(fp);
			return newNode;
		}
		else{
			printf("[PARSER ERROR]: Error on line %d: Expected \")\"\n", tkn.line);
			exit(EXIT_FAILURE);
		}
	}
	else if(tkn.tokenType == "idToken" || tkn.tokenType == "intToken"){
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);
		return newNode;
	}
	else{
		printf("[PARSER ERROR]: Error on line %d: Expected (Identifier or Integer)\n", tkn.line);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_FAILURE);
}

// <stats> -> <stat> <mStat>
Node * stats(){
	cout<<"Entered stats()\n";
	Node *newNode = createNode("<stats>");

	newNode->child_1 = stat();
	newNode->child_2 = mStat();

	return newNode;
}

// <mStat> -> empty | <stat> <mStat>
Node *mStat(){
	cout<<"Entered mStat(), received token: "<<tkn.tokenType<<endl;
	Node *newNode = createNode("<mStat>");

	if((tkn.tokenType == "resWordToken" && (tkn.token == "in" || tkn.token == "out" || tkn.token == "iffy" || tkn.token == "loop" || tkn.token == "label" || tkn.token == "goto")) 
			|| 
			(tkn.tokenType == "leftCurlyToken")
			|| 
			(tkn.tokenType == "idToken")
	  ){
		newNode->child_1 = stat();
		newNode->child_2 = mStat();
		return newNode;
	}
	else{
		newNode->tkn.push_back(scan.getEmptyToken());
		return newNode;
	}
}

// <stat> -> <in> ; | <out> ; | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ; | <block>
Node *stat(){
	cout<<"Entered stat(); tokenType: "<<tkn.tokenType<<endl;
	Node *newNode = createNode("<stat>");

	if(tkn.tokenType == "resWordToken"){
		if(tkn.token == "in"){
			tkn = scan.driverFA(fp);

			newNode->child_1 = in();

			if(tkn.tokenType == "semicolonToken"){
				tkn = scan.driverFA(fp);
				return newNode;
			}
			else{
				printf("[PARSER ERROR]: Error on line %d: Expected \";\"\n", tkn.line);
				exit(EXIT_FAILURE);
			}
		}
		else if(tkn.token == "out"){
			cout<<"Matched out, now expecting integer\n";
			tkn = scan.driverFA(fp);
			newNode->child_1 = out();

			if(tkn.tokenType == "semicolonToken"){
				tkn = scan.driverFA(fp);
				return newNode;
			}
			else{
				printf("[PARSER ERROR]: Error on line %d: Expected \";\"\n", tkn.line);
				exit(EXIT_FAILURE);
			}
		}
		else if(tkn.token == "iffy"){
			tkn = scan.driverFA(fp);
			newNode->child_1 = iffy();

			if(tkn.tokenType == "semicolonToken"){
				tkn = scan.driverFA(fp);
				return newNode;
			}
			else{
				printf("[PARSER ERROR]: Error on line %d: Expected \";\"\n", tkn.line);
				exit(EXIT_FAILURE);
			}

		}
		else if(tkn.token == "loop"){
			tkn = scan.driverFA(fp);
			newNode->child_1 = loop();

			if(tkn.tokenType == "semicolonToken"){
				tkn = scan.driverFA(fp);
				return newNode;
			}
			else{
				printf("[PARSER ERROR]: Error on line %d: Expected \";\"\n", tkn.line);
				exit(EXIT_FAILURE);
			}

		}
		else if(tkn.token == "label"){
			tkn = scan.driverFA(fp);
			newNode->child_1 = label();

			if(tkn.tokenType == "semicolonToken"){
				tkn = scan.driverFA(fp);
				return newNode;
			}
			else{
				printf("[PARSER ERROR]: Error on line %d: Expected \";\"\n", tkn.line);
				exit(EXIT_FAILURE);
			}

		}
		else if(tkn.token == "goto"){
			tkn = scan.driverFA(fp);
			newNode->child_1 = goTo();

			if(tkn.tokenType == "semicolonToken"){
				tkn = scan.driverFA(fp);
				return newNode;
			}
			else{
				printf("[PARSER ERROR]: Error on line %d: Expected \";\"\n", tkn.line);
				exit(EXIT_FAILURE);
			}

		}
		else{
			printf("[PARSER ERROR]: Error on line %d: Expected \"in, out, iffy, loop, label, goto or Identifier\"\n", tkn.line);
			exit(EXIT_FAILURE);
		}
	}
	else if(tkn.tokenType == "idToken"){
		tokenInfo temp = tkn;// Save before lose
		tkn = scan.driverFA(fp);

		newNode->child_1 = assign();
		newNode->child_1->tkn.push_back(temp);

		if(tkn.tokenType == "semicolonToken"){
			tkn = scan.driverFA(fp);
			return newNode;
		}
		else{
			printf("[PARSER ERROR]: Error on line %d: Expected \";\"\n", tkn.line);
			exit(EXIT_FAILURE);
		}
	}
	else{
		newNode->child_1 = block();
		return newNode;
	}

	exit(EXIT_FAILURE);
}

// <in> -> in Identifier
Node *in(){
	cout<<"Entered in()\n";
	Node *newNode = createNode("<in>");

	if(tkn.tokenType == "idToken"){
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);
		return newNode;
	}
	else{
		printf("[PARSER ERROR]: Error on line %d: Expected \"Identifier\"\n", tkn.line);
		exit(EXIT_FAILURE);	
	}

	exit(EXIT_FAILURE);
}

// <out> -> out <expr>
Node *out(){
	cout<<"Entered out()\n";
	Node *newNode = createNode("<out>");

	newNode->child_1 = expr();
	return newNode;
}

// <iffy> -> iffy [ <expr> <RO> <expr> ] then <stat>
Node *iffy(){
	cout<<"Entered iffy()\n";
	Node *newNode = createNode("<iffy>");

	if(tkn.tokenType == "leftBrackToken"){
		tkn = scan.driverFA(fp);

		newNode->child_1 = expr();
		newNode->child_2 = RO();
		newNode->child_3 = expr();

		if(tkn.tokenType == "rightBracketToken"){
			tkn = scan.driverFA(fp);

			if(tkn.token == "then"){
				tkn = scan.driverFA(fp);

				newNode->child_4 = stat();
				return newNode;
			}
			else{
				printf("[PARSER ERROR]: Error on line %d: Expected \"then\" token\n", tkn.line);
				exit(EXIT_FAILURE);
			}
		}
		else{
			printf("[PARSER ERROR]: Error on line %d: Expected \"]\" token\n", tkn.line);
			exit(EXIT_FAILURE);
		}
	}
	else{
		printf("[PARSER ERROR]: Error on line %d: Expected \"[\" token\n", tkn.line);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_FAILURE);
}

// <loop> -> loop [ <expr> <RO> <expr> ] <stat>
Node *loop(){
	cout<<"Entered loop();\n";
	Node *newNode = createNode("<loop>");

	if(tkn.tokenType == "leftBrackToken"){
		tkn = scan.driverFA(fp);

		newNode->child_1 = expr();
		newNode->child_2 = RO();
		newNode->child_3 = expr();

		if(tkn.tokenType == "rightBracketToken"){
			tkn = scan.driverFA(fp);

			newNode->child_4 = stat();
			return newNode;
		}
		else{
			printf("[PARSER ERROR]: Error on line %d: Expected \"]\" token\n", tkn.line);
			exit(EXIT_FAILURE);
		}
	}
	else{
		printf("[PARSER ERROR]: Error on line %d: Expected \"[\" token\n", tkn.line);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_FAILURE);
}

// <assign> -> Identifier := <expr>
Node *assign(){
	cout<<"Entered assign();";
	Node *newNode = createNode("<assign>");

	if(tkn.tokenType == "colonEqToken"){
		tkn = scan.driverFA(fp);

		newNode->child_1 = expr();
		return newNode;
	}
	else{
		printf("[PARSER ERROR]: Error on line %d: Expected \":=\" token\n", tkn.line);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

// <label> -> label Identifier
Node *label(){
	cout<<"Entered label();";
	Node *newNode = createNode("<label>");

	if(tkn.tokenType == "idToken"){
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);
		return newNode;
	}
	else{
		printf("[PARSER ERROR]: Error on line %d: Expected \"Identifier\" token\n", tkn.line);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_FAILURE);
}

// <goto> -> goto Identifier
Node *goTo(){
	cout<<"Entered goto();";
	Node *newNode = createNode("<goto>");

	if(tkn.tokenType == "idToken"){
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);
		return newNode;
	}
	else{
		printf("[PARSER ERROR]: Error on line %d: Expected \"Identifier\" token\n", tkn.line);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_FAILURE);
}

// <RO> -> < | << (two tokens) | > | >> (two tokens) | == (one token ==) | <> (two tokens) 
Node *RO(){
	cout<<"Entered RO();";
	Node *newNode = createNode("<RO>");

	if(tkn.tokenType == "lessThanToken") {
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);		

		if(tkn.tokenType == "lessThanToken") {
			newNode->tkn.push_back(tkn);
			tkn = scan.driverFA(fp);
			return newNode;
		}
		else if(tkn.tokenType == "greaterThanToken") {
			newNode->tkn.push_back(tkn);
			tkn = scan.driverFA(fp);
			return newNode;
		}
		else {
			return newNode;
		}
	}
	else if(tkn.tokenType == "greaterThanToken") {
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);		

		if(tkn.tokenType == "greaterThanToken") {
			newNode->tkn.push_back(tkn);
			tkn = scan.driverFA(fp);
			return newNode;
		}
		else {
			return newNode;
		}
	}
	else if(tkn.tokenType == "eqEqToken") {
		newNode->tkn.push_back(tkn);
		tkn = scan.driverFA(fp);;	
		return newNode;
	}
	else {
		printf("[PARSER ERROR]: Error on line %d: Expected \"<, <<, >, >>, ==, <>\" token\n", tkn.line);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_FAILURE);
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

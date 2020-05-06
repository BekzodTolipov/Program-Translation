#include <bits/stdc++.h> 
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include "parser.h"
#include "semanticValidator.h"
#include "treePrint.h"
#include "codeGenerator.h"

using namespace std; 

// Prototypes
string convert_to_string(char* a, int size);
void my_get_opt(int argc, char* argv[]);
int validate_cmd_line(int argc, char* argv[]);
vector<string> read_user_input();
void is_file_empty(vector<string> file_content);

//Global varaibles
string file_name;
bool is_file_given = false;
const int MAXCHAR = 1024;

int main(int argc, char*argv[]){ 
	cout<<"\nWelcome to simple program to demonstrate on how scanner and parser works together and check static semantics.\n";

	if(validate_cmd_line(argc, argv) == -1){	// Check commend line for arguments
	//	temp = read_user_input();
	}
	else{
		my_get_opt(argc, argv);
		if(!is_file_given){
			int size = strlen(argv[1]);
			file_name = convert_to_string(argv[1], size);	// If file is given without option than convert it
			file_name.append(".sp2020");
		}
	}

	Node *parseTree = parser(file_name);
	printTree(parseTree, 0);

	cout<<"\n\n{MASTER}: Entering semantic validation section!\n\n";
	vector<tokenInfo> st = validateSemantic(parseTree);
	cout<<"\n{MASTER}: Passed Static Semantic Test\n";
	startGenerator(parseTree, st, file_name);
	cout<<endl;

	return 0;
}

// Check if file is empty
void is_file_empty(vector<string> file_content){
	if(file_content.size() == 0){
		cout<<"[ERROR] Content is empty, exiting program\n";
		exit(1);
	}
}

// If no file is given then read from command line
vector<string> read_user_input(){
	vector<string> user_input;
	cout<<"Please input data in a single line(x:=z go245)\n";
	string line;
	if(!getline(cin, line)){
		cout<<"[ERROR] can not read input\n";
		exit(1);
	}
	line+=" ";
	string build_word = "";
	for(auto word : line){
		if(word == ' '){
			if(build_word != ""){
				user_input.push_back(build_word);
			}
			build_word = "";
		}
		else{
			build_word += word;
		}
	}
	is_file_empty(user_input);
	return user_input;
}

// Check if any option is given
void my_get_opt(int argc, char* argv[]){
	int c;
	int size;	// Char array length
	char dummy[MAXCHAR];	// Store argument line to char array
	while ((c = getopt (argc, argv, "hf:")) != -1){
		switch (c)
		{
			case 'h':
				cout<<"To run the program you have following options:\n\n[ -h for help]\nTo execute the file follow the code:\n"<<argv[0]<<" [ -h | -f ]\n\n";
				exit(0);
				break;
			case 'f':
				strncpy(dummy, optarg, 255);
				size = strlen(dummy);
				file_name = convert_to_string(optarg, size);
				file_name.append(".sp2020");
				is_file_given = true;
				break;
		}
	}
}

// Convert char array to string
string convert_to_string(char* a, int size){ 
	int i;
	string s = ""; 
	for (i = 0; i < size; i++) { 
		s = s + a[i]; 
	} 
	return s; 
} 

// Validate command line
int validate_cmd_line(int argc, char* argv[]){
	if(argc > 1){
		return 0;	// file is given
	}
	else{
		cout<<"[REDIRECT] No input file is given launching user input!\n";
		return -1;	// no file is given
	}
}

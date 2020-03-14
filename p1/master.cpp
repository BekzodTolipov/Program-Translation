#include <bits/stdc++.h> 
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include "scanner.h"
using namespace std; 

// Prototypes
string convert_to_string(char* a, int size);
void my_get_opt(int argc, char*argv[]);
int validate_cmd_line(int argc, char* argv[]);
vector<string> read_file(string file_name);
vector<string> read_user_input();
void is_file_empty(vector<string> file_content);
string filterElement(string);

//Global varaibles
string file_name;
bool is_file_given = false;
const int MAXCHAR = 1024;

// Scanner
Scanner newScanner;

int main(int argc, char*argv[]){ 
	vector<string> temp;
	cout<<"\nWelcome to simple Scanner to tokenize the given file\n";

	if(validate_cmd_line(argc, argv) == -1){	// Check commend line for arguments
		temp = read_user_input();
	}
	else{
		my_get_opt(argc, argv);
		if(is_file_given){
			temp = read_file(file_name);	// Read the file
		}
		else{
			int size = strlen(argv[1]);
			file_name = convert_to_string(argv[1], size);	// If file is given without option than convert it
			file_name.append(".sp2020");
			temp = read_file(file_name);
		}
	}

	// Open a stream to output to a file

	//ofstream file;
	//file.open("output.inorder");
	//file.close();

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
				printf("To run the program you have following options:\n\n[ -h for help]\nTo execute the file follow the code:\n./%s [ -h | -f ]", argv[0]);
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

// Read the file given
vector<string> read_file(string file_name){
	//Scanner newScanner;
	vector<string> file_vals;
	ifstream file;
	file.open(file_name);	// Open given file

	if(!file) {	// File does not exist
		cout << "[ERROR] Unable to open file\n";
		exit(1); // terminate with error
	}
	string line;
	string word;
	string result;
	string WHITESPACE = "\n\r\t\f\v";
	int line_count = 0;
	string filtered_word = "";
	while(getline(file, line)){
		int space_to_word = 0;
		line = filterElement(line);
		stringstream iss(line);
		while(iss >> word) {
			size_t start = word.find_first_not_of(WHITESPACE);	// Trim left
			size_t end = word.find_last_not_of(WHITESPACE);	// Trim right
			string trimmed_word = word.substr(start, end+1);
			file_vals.push_back(trimmed_word);
			result = newScanner.setNewWord(trimmed_word, line_count+1, space_to_word);
			if(result.find("SCANNER ERROR:") != std::string::npos){
				exit(-1);
			}
			space_to_word += word.size();
		}
		line_count++;
	}
	newScanner.setNewWord("EOF", line_count+1, 0);

	is_file_empty(file_vals);	// Check if file is empty

	file.close();
	return file_vals;
}
// Will receive a line from file 
// and check if it contains comment
// and filters them out
string filterElement(string line){
	int pos = 0;
	int prev_pos = 0;
	string new_line = "";
	stringstream iss(line);
	string word = "";
	static bool found = false;
	while(iss >> word){
		for(char letter : word){
			if(letter == '#'){
				if(!found){
					new_line +=  word.substr(prev_pos, pos-prev_pos) + " ";
					prev_pos = pos;
					found = true;
				}
				else{
					prev_pos = pos+1;
					found = false;
				}	
			}
			pos++;
		}
		if(!found && prev_pos < pos)
			new_line += " " + word.substr(prev_pos, pos);
	}
	//cout<<new_line<<endl;
	return new_line;
}

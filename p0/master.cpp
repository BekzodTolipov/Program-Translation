//#include "linked_list.h"
#include <bits/stdc++.h> 
#include <string>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include "build_tree.h" 
//#include "tree.h" 
using namespace std; 

string convert_to_string(char* a, int size);
void my_get_opt(int argc, char*argv[]);
int validate_cmd_line(int argc, char* argv[]);
vector<string> read_file(string file_name);
vector<string> read_user_input();
//Global varaibles
string file_name;
Node* head;
bool is_file_given = false;

const int MAXCHAR = 1024;

int main(int argc, char*argv[]){ 
	struct Node* root = new Node();
	vector<string> temp;
	int i;
	cout<<"\nWelcome to simple binary search tree implementation\n";
    if(validate_cmd_line(argc, argv) == -1){
    	temp = read_user_input();
        for (i = 0; (unsigned)i < temp.size(); ++i){
            insert(root, temp[i]);
        }

    }
    else{
        my_get_opt(argc, argv);
		if(is_file_given){
	        vector<string> temp = read_file(file_name);
        	root = insert(root, temp[0]);
        	for (i = 1; (unsigned)i < temp.size(); ++i){
            	insert(root, temp[i]);
        	}
    	}

    }

	if(is_file_given){
		temp = read_file(file_name);
		root = insert(root, temp[0]);
		int i;
		for (i = 1; (unsigned)i < temp.size(); ++i){
			insert(root, temp[i]);
		}
	}

	cout<<"\nIn-Order Traversal:";
	inOrder(root);
	cout<<"\nPost-Order Traversal: ";
	postOrder(root);
	cout<<"\nPre-Order Traversal:";
	preOrder(root);
	cout<<endl;

    return 0;
}

vector<string> read_user_input(){
	vector<string> user_input;
	cout<<"Please input data in a single line seperated by space(George, geo, hello)\n";
	string line;
	if(!getline(cin, line)){
		cout<<"Erro accured while reading\n";
		exit(1);
	}
	string build_word = "";
	for(auto word : line){
		if(word == ' '){
			user_input.push_back(build_word);
			build_word = "";
		}
		else{
			build_word += word;
		}
	}
	return user_input;
}

void my_get_opt(int argc, char* argv[]){
	int c;
	int size;
	char dummy[MAXCHAR];
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
                //cout << file_name << endl;
                read_file(file_name);
				is_file_given = true;
                break;
			default:
				cout<<"Uknown option is given, termination started!\n";
				break;
        }
    }
}

string convert_to_string(char* a, int size){ 
    int i;
//	cout << size << " size of string\n"; 
    string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

int validate_cmd_line(int argc, char* argv[]){
	if(argc > 1){
		return 0;
	}
	else{
		cout<<"No input file is given launching user input!\n";
		return -1;
	}
}

vector<string> read_file(string file_name){
	vector<string> file_vals;
	ifstream file;
	file.open(file_name);

	if(!file) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string val;
    while(file >> val) {
		file_vals.push_back(val);
    }
    
    file.close();
	return file_vals;
}

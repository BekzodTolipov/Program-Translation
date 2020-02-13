#include <bits/stdc++.h> 
#include <string>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include "build_tree.h" 
using namespace std; 

string convert_to_string(char* a, int size);
void my_get_opt(int argc, char*argv[]);
int validate_cmd_line(int argc, char* argv[]);
vector<string> read_file(string file_name);
vector<string> read_user_input();
void is_file_empty(vector<string> file_content);
//Global varaibles
string file_name;
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
	        temp = read_file(file_name);
        	root = insert(root, temp[0]);
        	for (i = 1; (unsigned)i < temp.size(); ++i){
            	insert(root, temp[i]);
        	}
    	}
		else{
			int size = strlen(argv[1]);
			file_name = convert_to_string(argv[1], size);
            file_name.append(".sp2020");
	        temp = read_file(file_name);
        	root = insert(root, temp[0]);
        	for (i = 1; (unsigned)i < temp.size(); ++i){
            	insert(root, temp[i]);
			}
		}
    }


	ofstream file;
	file.open("output.inorder");
	cout<<"\nIn-Order Traversal:\n";
	file<<"\nIn-Order Traversal:\n";
	inOrder(root, 0, file);
	file.close();
		
	file.open("output.postorder");
	cout<<"\nPost-Order Traversal:\n";
	file<<"\nPost-Order Traversal:\n";
	postOrder(root, 0, file);
	file.close();

	file.open("output.preorder");
	cout<<"\nPre-Order Traversal:\n";
	file<<"\nPre-Order Traversal:\n";
	preOrder(root, 0, file);
	file.close();

	cout<<endl;
	file.close();

    return 0;
}

void is_file_empty(vector<string> file_content){
	if(file_content.size() == 0){
		cout<<"[ERROR] Content is empty, exiting program\n";
		exit(1);
	}
}

vector<string> read_user_input(){
	vector<string> user_input;
	cout<<"Please input data in a single line seperated by space(George, geo, hello)\n";
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
				is_file_given = true;
                break;
        }
    }
}

string convert_to_string(char* a, int size){ 
    int i;
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
		cout<<"[REDIRECT] No input file is given launching user input!\n";
		return -1;
	}
}

vector<string> read_file(string file_name){
	vector<string> file_vals;
	ifstream file;
	file.open(file_name);

	if(!file) {
        cout << "[ERROR] Unable to open file\n";
        exit(1); // terminate with error
    }
    string val;
	string WHITESPACE = "\n\r\t\f\v";
    while(file >> val) {
		size_t start = val.find_first_not_of(WHITESPACE);
		size_t end = val.find_last_not_of(WHITESPACE);
		string trimmed_val = val.substr(start, end+1);
		file_vals.push_back(trimmed_val);
    }

	is_file_empty(file_vals);

    file.close();
	return file_vals;
}

//#include "linked_list.h"
#include <bits/stdc++.h> 
#include <string>
#include <iostream>
#include <unistd.h>
#include "build_tree.h" 
//#include "tree.h" 
using namespace std; 

string convert_to_string(char* a, int size);
void my_get_opt(int argc, char*argv[]);
int validate_cmd_line(int argc, char* argv[]);
vector<string>* read_file(string file_name);
//Global varaibles
string file_name;
Node* head;

const int MAXCHAR = 1024;

int main(int argc, char*argv[]){ 
	Node* root = NULL;
	vector<string> arr;
	arr.push_back("7");
	arr.push_back("1");
	arr.push_back("4");
	arr.push_back("5");
	arr.push_back("9");
	arr.push_back("11");
 
    
	//int n = arr.size()-1;
	root = insertLevelOrder(arr[0], root); 
	root = insertLevelOrder(arr[1], root); 
	root = insertLevelOrder(arr[2], root); 
	root = insertLevelOrder(arr[3], root); 
    inOrder(root);
	cout<<endl;
	preOrder(root, 0);
	cout<<endl;
	postOrder(root);
	cout<<endl;
	string str = "14";
	if(str.compare("13") < 0)
		cout<<"12 is less than 13\n";
	else
		cout<<"12 is bigger than 13\n";
    //if(validate_cmd_line(argc, argv) == -1){
    //	return -1;
   // }
   // else{
   //     my_get_opt(argc, argv);
    //}

    return 0;
}

void my_get_opt(int argc, char* argv[]){
	int c;
    while ((c = getopt (argc, argv, "hf:")) != -1){
        switch (c)
        {
            case 'h':
                printf("To run the program you have following options:\n\n[ -h for help]\nTo execute the file follow the code:\n./%s [ -h ] or any other options", argv[0]);
                break;
            case 'f':
				char dummy[MAXCHAR];
				strncpy(dummy, optarg, 255);
				int size = strlen(dummy);
				file_name = convert_to_string(optarg, size);
                file_name.append(".sp2020");
                //cout << file_name << endl;
                read_file(file_name);
                break;
        }
    }
}

string convert_to_string(char* a, int size) 
{ 
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
		cout << "Argument not received\n";
		return -1;
	}
}

vector<string>* read_file(string file_name){

	return NULL;
}

//#include "linked_list.h"
#include <bits/stdc++.h> 
#include <string>
#include <iostream>
#include <unistd.h> 
#include "tree.h" 
using namespace std; 

string convert_to_string(char* a, int size);
void my_get_opt(int argc, char*argv[]);
int validate_cmd_line(int argc, char* argv[]);
//Global varaibles
string file_name;
Node* head;

const int MAXCHAR = 1024;

int main(int argc, char*argv[]){ 
    //Node* head;
	//print(head); 
    if(validate_cmd_line(argc, argv) == -1){
    	return -1;
    }
    else{
        my_get_opt(argc, argv);
    }

    

  //  head = new Node(); 
   // push(&head, 10);  
   // push(&head, 30);  
   // push(&head, 11);  
   // push(&head, 21);  
   // push(&head, 14); 

    //printList(head); 

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
                build_tree(file_name);
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
		//int pos;
		//for(pos = 1; pos < argc; pos++){
		//	cout << argv[pos] << endl;
		//}
		return 0;
	}
	else{
		cout << "Argument not received\n";
		return -1;
	}
}

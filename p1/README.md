# Scanner

This project is build to demonstrate how SCANNER tokenize words it received.
It has 4 main categories:
* Launcher
	* Will start the program by reading given argument by user, which can be a file or commend line input
* FSA table generator
	* Scanner will have this function to generate FSA table with acceptance and rejection codes set up
* Filter
	* Will filter out all comments before its passed to scanner
* Driver
	* Will receive filtered word and check if its allowed token based on FSA table
* Termination
	* Scanner will be terminated in case it finds unsupported symbol within FSA table

## Getting Started
To run the program in commend line type the following:
* To build the project
	* make
* To run the program to request help text
	* ./scanner -h
* To run the program with file
	* ./scanner -f file_name 
		or
	  ./scanner file_name

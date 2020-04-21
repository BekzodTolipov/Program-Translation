# Parser

This project is build to demonstrate how SCANNER tokenize words and passes it to PARSER to check if given program follows given BNF grammar. There are also 2 different test files to check if program works.
It has 5 main categories:
* Launcher
	* Will start the program by reading given argument by user, which can be a file or commend line input
* Parser
	* After master file finds file that it needs to open, it will need to pass the filename to parser(filename) which later start calling lookaheads from Scanner for tokens and check if it folows grammar sequence. 
* FSA table generator
	* Scanner will have this function to generate FSA table with acceptance and rejection codes set up
* Filter
	* Will filter out all comments before its passed to scanner
* Driver
	* Will receive filtered word and check if its allowed token based on FSA table
* Termination
	* Scanner will be terminated in case it finds unsupported symbol within FSA table
	* Parser will be terminated in case it finds unsupoorted sequence of token found thru Scanner.

## Getting Started
To run the program in commend line type the following:
* To build the project
	* make
* To run the program to request help text
	* ./parser -h
* To run the program with file
	* ./scanner -f file_name 
		or
	  ./parser file_name

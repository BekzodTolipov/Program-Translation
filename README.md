# Program-Translation

    To run the program type one of the following in command line:
        1) For help message: ./p0 -h
        2) For input file: ./p0 filename or ./p0 -f filename
        3) For manually type data: ./p0
   
## Program Description
This is simple project to practice on how tree is build and see 
### In-order:
    process left child
    process root
    process right child
### Pre-order:
    process root
    process children left to right
### Post-order traversals:
      process left and right child
      process root
    
Program will accept filename in command line by reading simple command line argument or by using getopt. There will also be help option to show User on how to execute the program. Another option for user to avoid putting filename but using commandline to write their input after program execution.

## Output
After data is received, program will start building a tree and apply first 2 letters rule where if it matches first 2 letters while building a tree it will be stored in a same node. After building the tree, it will produce three different files where it will have default filename inorder.ouput, preorder.output, and postorder.output.

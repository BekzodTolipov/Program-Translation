#ifndef PARSER_H
#define PARSER_H

//#include "scanner.h"
#include "node.h"

extern FILE* fp;
extern int lineNum;
extern Scanner scan;

Node *parser(string filename);
Node *program();
Node *block();
Node *vars();
Node *mvars();
Node *expr();
Node *M();
Node *T();
Node *F();
Node *R();
Node *stats();
Node *mStat();
Node *stat();
Node *in();
Node *out();
Node *_if();
Node *loop();
Node *assign();
Node *RO();

Node *createNode(string);

#endif

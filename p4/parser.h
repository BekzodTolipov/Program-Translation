#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include <fstream>

extern FILE* fp;
extern Scanner scan;

Node *parser(string filename);
Node *program();
Node *block();
Node *vars();
Node *expr();
Node *M();
Node *A();
Node *N();
Node *R();
Node *stats();
Node *mStat();
Node *stat();
Node *in();
Node *out();
Node *iffy();
Node *loop();
Node *assign();
Node *label();
Node *goTo();
Node *RO();

Node *createNode(string);

#endif

#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <vector>
#include <string>
#include <fstream>
#include "node.h"
#include "scanner.h"

extern FILE* ofp;

void startGenerator(Node *p, vector<tokenInfo> st, string fileName);
void program(Node *p);
void block(Node *p);
void vars(Node *p);
void expr(Node *p);
void M(Node *p);
void A(Node *p);
void N(Node *p);
void R(Node *p);
void stats(Node *p);
void mStat(Node *p);
void stat(Node *p);
void in(Node *p);
void out(Node *p);
void iffy(Node *p);
void loop(Node *p);
void assign(Node *p);
void label(Node *p);
void goTo(Node *p);
void RO(Node *p);

int createNewTemp(string what);
void printToTarget(string tkn, string command);

#endif

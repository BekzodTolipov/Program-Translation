#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <vector>
#include <string>
#include "node.h"
#include "scanner.h"

void startGenerator(Node *p, vector<tokenInfo> st);
void printToTarget(tokenInfo tkn);

#endif

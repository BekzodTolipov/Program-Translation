#ifndef SEMANTIC_VALIDATOR_H
#define SEMANTIC_VALIDATOR_H

#include "node.h"
#include "scanner.h"
#include <vector>
#include <string>

void validateSemantic(Node *p);
void errorMessage(tokenInfo token, int option);
void checkIfDeclared(tokenInfo tkn, bool isFound, string errCode);
bool checkIfInPool(tokenInfo fromNode, vector<tokenInfo> pool);

#endif

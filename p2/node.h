#ifndef NODE_H
#define NODE_H

#include <string>
#include "scanner.h"

using namespace std;

struct Node {
	string label;
	Node *child_1, *child_2, *child_3, *child_4, *child_5;
	vector<tokenInfo> tkn;
	int level;
};

#endif

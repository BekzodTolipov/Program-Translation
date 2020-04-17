#ifndef NODE_H
#define NODE_H

#include <string>
#include "scanner.h"

using namespace std;

struct node_t {
    string label;
    node_t *child_1, *child_2, *child_3, *child_4, *child_5;
    tokenInfo token_t;
};

#endif

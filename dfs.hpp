#ifndef _NODE
#include "Node.hpp"
#endif
#include <set>
#include <stack>

Node dfs(Node root, int columns, int rows, std::set<int> usedStates, long long targetHash, int* searchCost, long long p, long long x);
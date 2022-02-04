#ifndef _NODE
#include "Node.hpp"
#endif
#include <set>

Node dfs(Node root, int columns, int rows, std::set<std::string> usedStates, std::string targetState, int* searchCost);
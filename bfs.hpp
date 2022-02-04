#ifndef _NODE
#include "Node.hpp"
#endif
#include <queue>
#include <set>

Node bfs(Node root, int columns, int rows, std::set<std::string> usedStates, std::string targetState, int* searchCost);
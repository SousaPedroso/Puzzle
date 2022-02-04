#include "dfs.hpp"

Node dfs(Node root, int columns, int rows, std::set<std::string> usedStates, std::string targetState, int* searchCost){
    if (usedStates.find(root.state) != usedStates.end()){
        return root;
    }

    for (Node expandedNode: root.expandNode(columns, rows)){
        expandedNode.cost ++;
        if (expandedNode.state == targetState){
            return expandedNode;
        }
        expandedNode = dfs(expandedNode, columns, rows, usedStates, targetState, searchCost++);
    }
    // Return a node with the searchCost, but initial state and emptyPath
    // Return a node with the searchCost, but initial state and emptyPath
    std::vector<std::string> emptyPath;
    Node notFound = Node(root.state, *searchCost, emptyPath);

    return notFound;
}
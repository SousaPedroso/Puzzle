#include "dfs.hpp"

Node dfs(Node root, int columns, int rows, std::set<std::string> usedStates, std::string targetState, int* searchCost){
    usedStates.insert(root.state);
    for (Node expandedNode: root.expandNode(columns, rows)){
        expandedNode.cost ++;
        // std::cout<< "Search cost: "<< expandedNode.cost<< std::endl;
        // std::cout<< "State: "<< expandedNode.state<< std::endl;
        if (usedStates.find(expandedNode.state) == usedStates.end()){
            dfs(expandedNode, columns, rows, usedStates, targetState, searchCost);
        }
        if (expandedNode.state == targetState){
            return expandedNode;
        }
    }
    // Return a node with the searchCost, but initial state and emptyPath
    std::vector<std::string> emptyPath;
    Node notFound = Node(root.state, root.cost, emptyPath);

    return notFound;
}
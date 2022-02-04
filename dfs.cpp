#include "dfs.hpp"

Node dfs(Node root, int columns, int rows, std::set<std::string> usedStates, std::string targetState, int* searchCost){
    std::stack<Node> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()){
        // Get last Node
        Node nextNode = nodeStack.top();
        // Push his state
        usedStates.insert(nextNode.state);
        nodeStack.pop();
        for (Node expandedNode: nextNode.expandNode(columns, rows)){
            (*searchCost)++;
            if (expandedNode.state == targetState){
                return expandedNode;
            }
            if (usedStates.find(expandedNode.state) == usedStates.end()){
                nodeStack.push(expandedNode);
                usedStates.insert(expandedNode.state);
            }
        }
    }

    // Return a node with the searchCost, but initial state and emptyPath
    std::vector<std::string> emptyPath;
    Node notFound = Node(root.state, *searchCost, emptyPath);

    return notFound;
}
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
            if (expandedNode.state == targetState){
                return expandedNode;
            }
            if (usedStates.find(expandedNode.state) == usedStates.end()){
                (*searchCost)++;
                nodeStack.push(expandedNode);
                usedStates.insert(expandedNode.state);
            }
            // All possible states were seen (https://stackoverflow.com/questions/32983617/improve-8-puzzle-using-bfs)
            if (usedStates.size() >= 181440){
                // Return a node with the searchCost, but initial state and emptyPath
                std::vector<std::string> emptyPath;
                std::vector<int> indices(rows*columns, 0);
                Node notFound = Node(root.state, *searchCost, emptyPath, indices);
                return notFound;
            }
        }
    }

    // Return a node with the searchCost, but initial state and emptyPath
    std::vector<std::string> emptyPath;
    std::vector<int> indices(rows*columns, 0);
    Node notFound = Node(root.state, *searchCost, emptyPath, indices);

    return notFound;
}
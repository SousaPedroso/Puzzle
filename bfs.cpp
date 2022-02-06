#include "bfs.hpp"

Node bfs(Node root, int columns, int rows, std::set<std::string> usedStates, std::string targetState, int* searchCost){
    std::queue<Node> nodeQueue;

    nodeQueue.push(root);
    while (!nodeQueue.empty()){
        Node nextNode = nodeQueue.front();
        // Push his state
        usedStates.insert(nextNode.state);
        nodeQueue.pop();
        for (Node expandedNode: nextNode.expandNode(columns, rows)){
            if (expandedNode.state == targetState){
                return expandedNode;
            }
            if (usedStates.find(expandedNode.state) == usedStates.end()){
                (*searchCost) ++;
                nodeQueue.push(expandedNode);
                usedStates.insert(expandedNode.state);
            }
        }
    }
    // Return a node with the searchCost, but initial state and emptyPath
    std::vector<std::string> emptyPath;
    std::vector<int> indices(rows*columns, 0);
    Node notFound = Node(root.state, *searchCost, emptyPath, indices);

    return notFound;
}
#include "Node.hpp"
#include <queue>
#include <set>

Node dfs(Node root, int columns, int rows, std::set<std::string> usedStates, std::string targetState){
    std::queue<Node> nodeQueue;

    nodeQueue.push(root);
    int searchCost = 0;
    while (!nodeQueue.empty()){
        Node nextNode = nodeQueue.front();
        nodeQueue.pop();
        for (Node expandedNode: nextNode.expandNode(columns, rows)){
            searchCost ++;
            if (usedStates.find(expandedNode.state) != usedStates.end()){
                nodeQueue.push(expandedNode);
                usedStates.insert(expandedNode.state);
            }
            if (expandedNode.state == targetState){
                return expandedNode;
            }
        }
    }
    // Return a node with the searchCost, but initial state and emptyPath
    std::vector<std::string> emptyPath;
    Node notFound = Node(root.state, searchCost, emptyPath);

    return notFound;
}
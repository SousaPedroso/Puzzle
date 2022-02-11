#include "bfs.hpp"

Node bfs(Node root, int columns, int rows, std::set<int> usedStates, long long targetHash, int* searchCost, long long p, long long x){
    std::queue<Node> nodeQueue;

    nodeQueue.push(root);
    while (!nodeQueue.empty()){
        Node nextNode = nodeQueue.front();
        // Push his state
        usedStates.insert(nextNode.hash);
        nodeQueue.pop();
        // std::cout<< "Root: "<< nextNode.state<< ", hash: "<< nextNode.hash<< endLine;
        for (Node expandedNode: nextNode.expandNode(columns, rows)){
            expandedNode.hash = expandedNode.computeHash(p, x, rows, columns);
            // std::cout<< "State: "<< expandedNode.state<< ", hash: "<< expandedNode.hash<< endLine;
            if (expandedNode.hash == targetHash){
                return expandedNode;
            }
            if (usedStates.find(expandedNode.hash) == usedStates.end()){
                (*searchCost) ++;
                nodeQueue.push(expandedNode);
                usedStates.insert(expandedNode.hash);
            }
        }
    }
    // Return a node with the searchCost, but initial state and emptyPath
    std::vector<std::string> emptyPath;
    std::array<int, 9> indices;
    Node notFound = Node(root.state, *searchCost, emptyPath, indices);

    return notFound;
}
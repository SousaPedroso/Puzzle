#include "dfs.hpp"

Node dfs(Node root, int columns, int rows, std::set<int> usedStates, long long targetHash, int* searchCost, long long p, long long x){
    std::stack<Node> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()){
        // Get last Node
        Node nextNode = nodeStack.top();
        // Push his state
        usedStates.insert(nextNode.hash);
        nodeStack.pop();
        for (Node expandedNode: nextNode.expandNode(columns, rows)){
            expandedNode.hash = expandedNode.computeHash(p, x, rows, columns);
            if (expandedNode.hash == targetHash){
                return expandedNode;
            }
            if (usedStates.find(expandedNode.hash) == usedStates.end()){
                (*searchCost)++;
                nodeStack.push(expandedNode);
                usedStates.insert(expandedNode.hash);
            }
            // All possible states were seen (https://stackoverflow.com/questions/32983617/improve-8-puzzle-using-bfs)
            if (usedStates.size() >= 181440){
                // Return a node with the searchCost, but initial state and emptyPath
                std::vector<std::string> emptyPath;
                std::array<int, 9> indices;
                Node notFound = Node(root.state, *searchCost, emptyPath, indices);
                return notFound;
            }
        }
        // std::cout << nodeStack.size()<< endLine;
    }

    // Return a node with the searchCost, but initial state and emptyPath
    std::vector<std::string> emptyPath;
    std::array<int, 9> indices;
    Node notFound = Node(root.state, *searchCost, emptyPath, indices);

    return notFound;
}
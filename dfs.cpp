#include "dfs.hpp"

Node dfs(Node root, int columns, int rows, std::set<std::string> usedStates, std::string targetState, int* searchCost){
    std::stack<Node> nodeStack;
    nodeStack.push(root);

    int depth = -1;
    int lastDepth;
    int indexBlankPiece;
    std::string newState;
    std::list<std::string> solutionPath;

    while (!nodeStack.empty()){
        // Get last Node
        Node nextNode = nodeStack.top();

        lastDepth = depth;
        depth = nextNode.cost;

        // Check if came for a parent
        if (depth < lastDepth){
            solutionPath.pop_back();
        }

        nodeStack.pop();
        indexBlankPiece = nextNode.index;

        // Ignore moves for this state
        if (usedStates.find(nextNode.state) != usedStates.end()){
            continue;
        }

        // 
        (*searchCost)++;
        usedStates.insert(nextNode.state);
        solutionPath.push_back(nextNode.state);

        if (nextNode.state == targetState){
            nextNode.path = solutionPath;
            return nextNode;
        }

        // Move leftside
        if (nextNode.index % columns != 0){
            newState = nextNode.changeState(indexBlankPiece, indexBlankPiece-1);
            Node node = Node(newState, nextNode.cost+1, nextNode.path, indexBlankPiece-1);
            nodeStack.push(node);
        }

        // Move downside
        if (indexBlankPiece < (rows-1)*columns){
            newState = nextNode.changeState(indexBlankPiece, indexBlankPiece+columns);
            Node node = Node(newState, nextNode.cost+1, nextNode.path, indexBlankPiece+columns);
            nodeStack.push(node);
        }

        // Move rightside
        if (indexBlankPiece % columns != columns-1){
            newState = nextNode.changeState(indexBlankPiece, indexBlankPiece+1);
            Node node = Node(newState, nextNode.cost+1, nextNode.path, indexBlankPiece+1);
            nodeStack.push(node);
        }

        // Move upside
        if (indexBlankPiece >= columns){
            newState = nextNode.changeState(indexBlankPiece, indexBlankPiece-columns);
            Node node = Node(newState, nextNode.cost, nextNode.path, indexBlankPiece-columns);
            nodeStack.push(node);
        }
    }

    Node notFound = Node(root.state, *searchCost, solutionPath, -1);

    return notFound;
}
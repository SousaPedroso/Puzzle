#include "Node.hpp"

Node::Node(std::string state, int cost, std::vector<std::string> path){
    this->state = state;
    this->cost = cost;
    this->path = path;
    // Update the path with the current node
    this->path.push_back(this->state);
};

std::string Node::changeState(int originPiece, int destinyPiece){
    std::string newState;
    // Find first piece
    newState = this->state;
    char firstPiece = newState[originPiece*2];
    newState[originPiece*2] = newState[destinyPiece*2];
    newState[destinyPiece*2] = firstPiece;

    return newState;
}

std::vector<Node> Node::expandNode(int columns, int rows){
    
    // Check the first space and iterate over
    // Get the index for each element
    std::string delimiter=" ";

    // 
    std::size_t start = 0U;
    std::size_t end = this->state.find(delimiter);
    std::vector<int> indices(rows*columns, 0);
    std::vector<Node> expandedNodes;
    int position = 0;

    // TO-DO: Generalize for two or more digits number
    while (end != this->state.npos){
        // Converts the string to the number
        // Check the position and assign this position to him
        // Unless is the blank space
        if (this->state.substr(start, end-start) != "X"){
            indices[std::stoi(this->state.substr(start, end-start))-1] = position;
        }
        else {
            indices[rows*columns-1] = position;
        }
        start = end + delimiter.length();
        // Next number
        end = this->state.find(delimiter, start);
        position ++;
    }
    // Check the possible moves (Check if it is on the corner)
    int indexBlankPiece = indices[rows*columns-1];
    // New state
    std::string newState;
    // First/Last row
    if (indexBlankPiece < columns || indexBlankPiece >= (rows-1)*columns){

        // First column -> right
        if (indexBlankPiece % columns == 0){
            newState = changeState(indexBlankPiece, indexBlankPiece+1);
            Node node = Node(newState, this->cost, this->path);
            expandedNodes.push_back(node);

        }
        else {
            // Last column <- left
            if (indexBlankPiece % columns == columns-1){
                newState = changeState(indexBlankPiece, indexBlankPiece-1);
                Node node = Node(newState, this->cost, this->path);
                expandedNodes.push_back(node);
            }
            else {
                // Three moves
                // right and left
                newState = changeState(indexBlankPiece, indexBlankPiece+1);
                Node node = Node(newState, this->cost, this->path);
                expandedNodes.push_back(node);

                newState = changeState(indexBlankPiece, indexBlankPiece-1);
                node = Node(newState, this->cost, this->path);
                expandedNodes.push_back(node);

            }
        }
        // First row, down
        if (indexBlankPiece < columns){
            newState = changeState(indexBlankPiece, indexBlankPiece+columns);
            Node node = Node(newState, this->cost, this->path);
            expandedNodes.push_back(node);
        }
        // Last row, up
        else{
            newState = changeState(indexBlankPiece, indexBlankPiece-columns);
            Node node = Node(newState, this->cost, this->path);
            expandedNodes.push_back(node);
        }
    }
    else{
        // Check three or four possible moves
        // Down and up always happen
        newState = changeState(indexBlankPiece, indexBlankPiece+columns);
        Node node = Node(newState, this->cost, this->path);
        expandedNodes.push_back(node);

        newState = changeState(indexBlankPiece, indexBlankPiece-columns);
        node = Node(newState, this->cost, this->path);
        expandedNodes.push_back(node);

        // Three moves are on laterals

        // First column, -> right
        if (indexBlankPiece % columns == 0){
            newState = changeState(indexBlankPiece, indexBlankPiece+1);
            Node node = Node(newState, this->cost, this->path);
            expandedNodes.push_back(node);

        }
        else{
            // Left
            if(indexBlankPiece % columns == columns-1){
                newState = changeState(indexBlankPiece, indexBlankPiece-1);
                Node node = Node(newState, this->cost, this->path);
                expandedNodes.push_back(node);
            }
            else{
                // Right and left
                newState = changeState(indexBlankPiece, indexBlankPiece+1);
                node = Node(newState, this->cost, this->path);
                expandedNodes.push_back(node);

                newState = changeState(indexBlankPiece, indexBlankPiece-1);
                Node node = Node(newState, this->cost, this->path);
                expandedNodes.push_back(node);
            }
        }
    }
    // TO-DO: Optimize verifications
    return expandedNodes;
}
#include "Node.hpp"

Node::Node(std::string state, int cost, std::vector<std::string> path, std::vector<int> indices){
    this->state = state;
    this->cost = cost;
    this->path = path;
    // Update the index of the pieces
    this->indices = indices;
    // Update the path with the current node
    this->path.push_back(this->state);
};

Node::~Node() = default;

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
    
    std::vector<Node> expandedNodes;
    int position = 0;

    // Check the possible moves (Check if it is on the corner)
    int indexBlankPiece = this->indices[rows*columns-1];

    // for (int i=0; i<rows*columns; i++){
    //     std::cout<< "Index of piece "<< i+1<< ": "<< this->indices[i]<< endLine;
    // }
    
    // std::cout<< indexBlankPiece<< endLine;
    // std::cout<< this->state[indexBlankPiece*2]<< endLine;
    // New state
    std::string newState;
    // First/Last row
    if (indexBlankPiece < columns || indexBlankPiece >= (rows-1)*columns){

        // First column -> right
        if (indexBlankPiece % columns == 0){
            newState = changeState(indexBlankPiece, indexBlankPiece+1);
            Node node = Node(newState, this->cost, this->path, this->indices);
            // Update the index of the pieces
            int indexBlankPieceCopy = indices[rows*columns-1];
            char pieceToChange = this->state[(indexBlankPiece+1)*2];
            // New position
            node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
            node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
            expandedNodes.push_back(node);

        }
        else {
            // Last column <- left
            if (indexBlankPiece % columns == columns-1){
                newState = changeState(indexBlankPiece, indexBlankPiece-1);
                Node node = Node(newState, this->cost, this->path, this->indices);
                // Update the index of the pieces
                // Save the indexBlankPiece
                int indexBlankPieceCopy = indices[rows*columns-1];
                char pieceToChange = this->state[(indexBlankPiece-1)*2];
                node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
                node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
                expandedNodes.push_back(node);
            }
            else {
                // Three moves
                // right and left
                newState = changeState(indexBlankPiece, indexBlankPiece+1);
                Node node = Node(newState, this->cost, this->path, this->indices);
                // Update the index of the pieces
                int indexBlankPieceCopy = indices[rows*columns-1];
                char pieceToChange = this->state[(indexBlankPiece+1)*2];
                node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
                node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
                expandedNodes.push_back(node);

                newState = changeState(indexBlankPiece, indexBlankPiece-1);
                node = Node(newState, this->cost, this->path, this->indices);
                // Update the index of the pieces
                indexBlankPieceCopy = indices[rows*columns-1];
                pieceToChange = this->state[(indexBlankPiece-1)*2];
                node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
                node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
                expandedNodes.push_back(node);

            }
        }
        // First row, down
        if (indexBlankPiece < columns){
            newState = changeState(indexBlankPiece, indexBlankPiece+columns);
            Node node = Node(newState, this->cost, this->path, this->indices);
            // Update the index of the pieces
            int indexBlankPieceCopy = indices[rows*columns-1];
            char pieceToChange = this->state[(indexBlankPiece+columns)*2];
            node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
            node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
            expandedNodes.push_back(node);
        }
        // Last row, up
        else{
            newState = changeState(indexBlankPiece, indexBlankPiece-columns);
            Node node = Node(newState, this->cost, this->path, this->indices);
            // Update the index of the pieces
            int indexBlankPieceCopy = indices[rows*columns-1];
            char pieceToChange = this->state[(indexBlankPiece-columns)*2];
            node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
            node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
            expandedNodes.push_back(node);
        }
    }
    else{
        // Check three or four possible moves
        // Down and up always happen
        newState = changeState(indexBlankPiece, indexBlankPiece+columns);
        Node node = Node(newState, this->cost, this->path, this->indices);
        // Update the index of the pieces
        int indexBlankPieceCopy = indices[rows*columns-1];
        char pieceToChange = this->state[(indexBlankPiece+columns)*2];
        node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
        node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
        expandedNodes.push_back(node);

        newState = changeState(indexBlankPiece, indexBlankPiece-columns);
        node = Node(newState, this->cost, this->path, this->indices);
        // Update the index of the pieces
        indexBlankPieceCopy = indices[rows*columns-1];
        pieceToChange = this->state[(indexBlankPiece-columns)*2];
        node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
        node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
        expandedNodes.push_back(node);

        // Three moves are on laterals

        // First column, -> right
        if (indexBlankPiece % columns == 0){
            newState = changeState(indexBlankPiece, indexBlankPiece+1);
            Node node = Node(newState, this->cost, this->path, this->indices);
            // Update the index of the pieces
            int indexBlankPieceCopy = indices[rows*columns-1];
            char pieceToChange = this->state[(indexBlankPiece+1)*2];
            node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
            node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
            expandedNodes.push_back(node);

        }
        else{
            // Left
            if(indexBlankPiece % columns == columns-1){
                newState = changeState(indexBlankPiece, indexBlankPiece-1);
                Node node = Node(newState, this->cost, this->path, this->indices);
                // Update the index of the pieces
                int indexBlankPieceCopy = indices[rows*columns-1];
                char pieceToChange = this->state[(indexBlankPiece-1)*2];
                node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
                node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
                expandedNodes.push_back(node);
            }
            else{
                // Right and left
                newState = changeState(indexBlankPiece, indexBlankPiece+1);
                node = Node(newState, this->cost, this->path, this->indices);
                // Update the index of the pieces
                int indexBlankPieceCopy = indices[rows*columns-1];
                char pieceToChange = this->state[(indexBlankPiece+1)*2];
                node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
                node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
                expandedNodes.push_back(node);

                newState = changeState(indexBlankPiece, indexBlankPiece-1);
                Node node = Node(newState, this->cost, this->path, this->indices);
                // Update the index of the pieces
                indexBlankPieceCopy = indices[rows*columns-1];
                pieceToChange = this->state[(indexBlankPiece-1)*2];
                node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
                node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
                expandedNodes.push_back(node);
            }
        }
    }
    // TO-DO: Optimize verifications
    return expandedNodes;
}

void Node::printState(int columns, int rows){
    int position = 0;
    for (int i=0; i<rows; i++){
        // First row
        if (i == 0){
            std::cout<< "\t-------------"<< endLine;
        }
        for (int j=0; j<columns; j++){
            // First column
            if (j == 0){
                std::cout<< "\t| "<<this->state[position]<< " ";
            }
            else{
                if (j < columns-1){
                    std::cout<< "| "<<this->state[position]<< " |";
                }
                // Last row
                else{
                    std::cout<< " "<< state[position]<< " |";
                }
            }
            position += 2;
        }
        std::cout<< endLine;
    }
    // Close the puzzle
    std::cout<< "\t-------------"<< endLine;
}
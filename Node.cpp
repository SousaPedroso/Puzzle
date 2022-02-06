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

    // Move upside
    if (indexBlankPiece >= columns){
        newState = changeState(indexBlankPiece, indexBlankPiece-columns);
        Node node = Node(newState, this->cost, this->path, this->indices);
        // Update the index of the pieces
        int indexBlankPieceCopy = indices[rows*columns-1];
        char pieceToChange = this->state[(indexBlankPiece-columns)*2];
        // New position
        node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
        node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
        expandedNodes.push_back(node);
    }
    // Move downside
    if (indexBlankPiece < (rows-1)*columns){
        newState = changeState(indexBlankPiece, indexBlankPiece+columns);
        Node node = Node(newState, this->cost, this->path, this->indices);
       // Update the index of the pieces
        int indexBlankPieceCopy = indices[rows*columns-1];
        char pieceToChange = this->state[(indexBlankPiece+columns)*2];
        // New position
        node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
        node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
        expandedNodes.push_back(node);
    }
    // Move rightside
    if (indexBlankPiece % columns != columns-1){
        newState = changeState(indexBlankPiece, indexBlankPiece+1);
        Node node = Node(newState, this->cost, this->path, this->indices);
        // Update the index of the pieces
        int indexBlankPieceCopy = indices[rows*columns-1];
        char pieceToChange = this->state[(indexBlankPiece+1)*2];
        node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
        node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
        expandedNodes.push_back(node);
    }
    // Move leftside
    if (indexBlankPiece % columns != 0){
        newState = changeState(indexBlankPiece, indexBlankPiece-1);
        Node node = Node(newState, this->cost, this->path, this->indices);
        // Update the index of the pieces
        int indexBlankPieceCopy = indices[rows*columns-1];
        char pieceToChange = this->state[(indexBlankPiece-1)*2];
        node.indices[rows*columns-1] = node.indices[(pieceToChange-'0')-1];
        node.indices[(pieceToChange-'0')-1] = indexBlankPieceCopy;
        expandedNodes.push_back(node);
    }

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
                // Last column
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
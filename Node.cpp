#include "Node.hpp"

Node::Node(std::string state, int cost, std::vector<std::string> path, std::array<int, 9> indices){
    this->state = state;
    this->cost = cost;
    this->path = path;
    // Update the index of the pieces
    this->indices = indices;
    // Initial value
    this->hash = 0;
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

    // Check the possible moves
    int indexBlankPiece = this->indices[rows*columns-1];

    // for (int i=0; i<rows*columns; i++){
    //     std::cout<< "Index of piece "<< i+1<< ": "<< this->indices[i]<< endLine;
    // }
    
    // std::cout<< indexBlankPiece<< endLine;
    // std::cout<< this->state[indexBlankPiece*2]<< endLine;
    // New state
    std::string newState;

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

long long Node::computeHash(int prime, int x, int rows, int columns){
    long long storeHash[rows*columns];
    storeHash[0] = this->state[0];
    for (int i=1; i<this->state.size()/2; i++){
        storeHash[i] = ((storeHash[i-1]*x)+state[i*2])%prime;
    }
    return storeHash[rows*columns-1];
}
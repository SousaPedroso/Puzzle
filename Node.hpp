#include <stdlib.h>
#include <iostream>
#include <utility>
#include <vector>


// Each Node is represented by a state (Combination of pieces in specific positions)
struct Node{
    // State of the puzzle
    std::string state;
    // Cost of the search
    int cost;
    // Composed by a sequence of states
    std::vector<std::string> path;
    
    Node(std::string state, int cost, std::vector<std::string> path){
        this->state = state;
        this->cost = cost;
        this->path = path;
        // Update the path with the current node
        this->path.push_back(this->state);
    };

    // Find two pieces by index and change their position
    std::string changeState(int originPiece, int destinyPiece);
    // Considering 2, 3 or 4 movements
    std::vector<Node> expandNode(int columns, int rows);
};

#include <iostream>
#include <vector>
#include <list>

#define _NODE

#ifndef endline
#define endLine '\n';
#endif
// Each Node is represented by a state (Combination of pieces in specific positions)
struct Node{
    // State of the puzzle
    std::string state;
    // Cost of the search
    int cost;
    // Composed by a sequence of states
    std::list<std::string> path;
    // Stores the index of the blank piece
    int index;

    Node(std::string state, int cost, std::list<std::string> path, int index);
    ~Node();
    // Find two pieces by index and change their position
    std::string changeState(int originPiece, int destinyPiece);
    // Considering 2, 3 or 4 movements
    std::vector<Node> expandNode(int columns, int rows);
    // Format output
    void printState(int columns, int rows);
};
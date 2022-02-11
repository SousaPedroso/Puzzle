#include <stdlib.h>
#include <iostream>
#include <array>
#include <random>
#include <utility>
#include <vector>

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
    std::vector<std::string> path;
    // Stores the indices for O(1) change of states
    std::array<int, 9> indices;
    // Check states are by hash (need polynomes and each hash)
    long long hash;

    Node(std::string state, int cost, std::vector<std::string> path, std::array<int, 9> indices);
    ~Node();
    // Find two pieces by index and change their position
    std::string changeState(int originPiece, int destinyPiece);
    // Compute the hash
    long long computeHash(int prime, int x, int rows, int columns);
    // Considering 2, 3 or 4 movements
    std::vector<Node> expandNode(int columns, int rows);
    // Format output
    void printState(int columns, int rows);
};
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>


struct Node{
    int piece;
    // Each adjacent piece is represented as a pair of the address the node and the piece value
    // for comparison agility
    // Considerar a peça em branco como a peça de valor mais alto+1
    // No quebra-cabeça da atividade, por exemplo, seria a peça 9
    std::map<int, Node> adjacents;
    Node(){};
};

void addAdjacent(Node& n, int p, Node& n1);
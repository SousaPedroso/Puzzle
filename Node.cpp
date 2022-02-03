#include "Node.hpp"

void addAdjacent(Node& n, int p, Node& n1){
    n.adjacents[p] = n1;
}
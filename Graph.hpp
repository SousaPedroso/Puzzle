#include "Node.hpp"
#include <set>
#include <queue>
#include <string>

struct Graph{
    std::vector<Node> nodes;
    Node root;
    std::string state; // Current state
    std::vector<int> indices; // indices for each node
    Graph(){};
};

void swap(Graph& g, Node& n1, Node& n2);
void dfs(Graph& g, Node& r, std::set<std::string> states, std::string targetState, int& searchCost);
void bfs(Graph& g, Node& r, std::set<std::string> states, int& searchCost);
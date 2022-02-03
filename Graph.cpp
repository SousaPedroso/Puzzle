#include "Graph.hpp"

// Change two adjacents nodes and fix the adjacencies
void swap(Graph& g, Node& n1, Node& n2){
    std::cout << "\nAdjacents of piece "<< n1.piece<< ": "<< n1.adjacents.size() << '\n';
    std::cout << "Adjacents of piece "<< n2.piece<< ": "<< n2.adjacents.size() << '\n';

    std::cout << "\nBefore adjust adjacents"<< '\n';
    // Adjacentes
    for (int i =0; i<g.indices.size(); i++){
        std::cout << "Adjacents of piece "<< g.nodes[i].piece<< ": "<< g.nodes[i].adjacents.size() << '\n';
    }
    // Remove him self of each piece, they are adjacents
    n2.adjacents.erase(n1.piece);
    n1.adjacents.erase(n2.piece);

    // Swap adjacencies
    n1.adjacents.swap(n2.adjacents);
    
    // Now push again each adjacencie
    addAdjacent(n1, n2.piece, n2);
    addAdjacent(n2, n2.piece, n1);

    // Fix adjacencies of node n1
    for (std::map<int, Node>::iterator adjacent = n2.adjacents.begin(); adjacent != n2.adjacents.end(); adjacent++){
        // Remove the piece n1 and add the n2 piece for the adjacency of the piece
        g.nodes[g.indices[adjacent->first]].adjacents.erase(n1.piece);
        addAdjacent(g.nodes[g.indices[adjacent->first]], g.nodes[g.indices[adjacent->first]].piece, n2);
    }

    // Fix adjacencies of node n2
    for (std::map<int, Node>::iterator adjacent = n1.adjacents.begin(); adjacent != n1.adjacents.end(); adjacent++){
        // Remove the piece n2 and add the n1 piece for the adjacency of the piece
        g.nodes[g.indices[adjacent->first]].adjacents.erase(n2.piece);
        addAdjacent(g.nodes[g.indices[adjacent->first]], g.nodes[g.indices[adjacent->first]].piece, n1);
    }


    std::cout << "\nAfter adjust adjacents"<< '\n';
    // Adjacentes
    for (int i =0; i<g.indices.size(); i++){
        std::cout << "Adjacents of piece "<< g.nodes[i].piece<< ": "<< g.nodes[i].adjacents.size() << '\n';
    }

}

void dfs(Graph& g, Node& r, std::set<std::string> states, std::string targetState, int& searchCost){
    if (r.piece == 0){
        return ;
    }

    std::cout<< "Number of adjacents: "<< r.adjacents.size() << '\n';
    for (std::map<int, Node>::iterator adjacent = r.adjacents.begin(); adjacent != r.adjacents.end(); adjacent++){
        std::cout<< "Adjacent: "<< adjacent->first << '\n';
        searchCost ++;
        dfs(g, g.nodes[g.indices[adjacent->first]], states, targetState, searchCost);
        // Check if it will be necessary change the pieces
        int nodeTarget;
        int node0;
        nodeTarget = g.indices[adjacent->first];
        node0 = g.indices[0];
        // Change the indices to update the state
        std::iter_swap(g.state.begin()+nodeTarget, g.state.begin()+node0);
        std::cout << "State "<< g.state<< '\n'; // Linha certa
        // Avoid repeating states
        if (states.find(g.state) == states.end()){
            std::iter_swap(g.state.begin()+nodeTarget, g.state.begin()+node0);
            // If 0-piece is adjacency, change the nodes
            std::map<int, Node> adjacencies = g.nodes[g.indices[adjacent->first]].adjacents;
            if (adjacencies.find(0) != adjacencies.end()){
                // Move pieces
                swap(g, g.nodes[nodeTarget], g.nodes[node0]);
                // Change the position of the nodes and indices
                std::iter_swap(g.nodes.begin()+node0, g.nodes.begin()+nodeTarget);
                std::iter_swap(g.indices.begin(), g.indices.begin()+g.indices[adjacent->first]);
                // New state inserted
                std::cout << "Move piece "<< adjacent->first<< " to blank space"<< '\n';
                states.insert(g.state);
            }
        }
        else {
            // Return to the anterior state and exit the ramification
            std::iter_swap(g.state.begin()+nodeTarget, g.state.begin()+node0);
        }
    }
    return ;
}

void bfs(Graph& g, Node& r, std::set<std::string> states, int& searchCost){
    
    if (r.piece == 0){
        return ;
    }

    std::queue<Node> queueBFS;
    for (std::map<int, Node>::iterator adjacent = r.adjacents.begin(); adjacent != r.adjacents.end(); adjacent++){
        // Avoid repeating pieces
        // Move pieces
        // Avoid repeating states
        // Check if it will be necessary change the pieces
        int nodeTarget;
        int node0;
        nodeTarget = g.indices[adjacent->first];
        node0 = g.indices[0];
        // Convert the indices to update the state
        g.state[nodeTarget] = node0+'0';
        g.state[node0] = nodeTarget+'0';
        if (states.find(g.state) == states.end()){
            swap(g, adjacent->second, g.nodes[g.indices[0]]);
            // New state inserted
            states.insert(g.state);
            searchCost ++;
            // Update the indices
            g.indices[adjacent->first] = node0;
            g.indices[0] = g.indices[nodeTarget];
            std::cout << "Move piece "<< adjacent->first<< " to blank space"<< '\n';
            queueBFS.push(adjacent->second);
        }
        else {
            // Comeback to the anterior state
            g.state[nodeTarget] = nodeTarget+'0';
            g.state[node0] = node0+'0';
        }
    }
    // bfs for each piece
    while (!queueBFS.empty()){
        Node& nodePiece = queueBFS.back();
        queueBFS.pop();
        bfs(g, nodePiece, states, searchCost);
    }
}
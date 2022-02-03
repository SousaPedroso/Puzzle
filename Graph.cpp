#include "Graph.hpp"

// Change two adjacents nodes and fix the adjacencies
void swap(Graph& g, Node& n1, Node& n2){
    // n1 = 2, n2 = 9
    // std::cout << "\nBefore adjust adjacents"<< '\n';
    // Adjacencies
    // for (int i =0; i<g.indices.size(); i++){
    //     std::cout << "Adjacents of piece "<< g.nodes[i].piece<< ": "<< g.nodes[i].adjacents.size() << '\n';
    // }
    // for (int i =0; i<g.indices.size(); i++){
    //     std::cout << "Adjacents of piece "<< g.nodes[i].piece<< ": "<< g.nodes[i].adjacents.size() << '\n';
    //     for (std::map<int, Node>::iterator adjacent=g.nodes[i].adjacents.begin(); adjacent != g.nodes[i].adjacents.end(); adjacent++){
    //         std::cout << adjacent->first << '\n';
    //     }
    //     std::cout<< '\n';
    // }
    // Remove him self of each piece, they are adjacents
    n2.adjacents.erase(n1.piece);
    n1.adjacents.erase(n2.piece);

    // Swap adjacencies
    n1.adjacents.swap(n2.adjacents);
    // Adjacencias do 9 são do 2

    // Fix adjacencies of node n1
    for (std::map<int, Node>::iterator adjacent = n2.adjacents.begin(); adjacent != n2.adjacents.end(); adjacent++){
        // Remove the piece n1 and add the n2 piece for the adjacency of the piece
        g.nodes[g.indices[adjacent->first-1]].adjacents.erase(n1.piece);
        addAdjacent(g.nodes[g.indices[adjacent->first-1]], n2.piece, n2);
    }

    // Fix adjacencies of node n2
    for (std::map<int, Node>::iterator adjacent = n1.adjacents.begin(); adjacent != n1.adjacents.end(); adjacent++){
        // Remove the piece n2 and add the n1 piece for the adjacency of the piece
        g.nodes[g.indices[adjacent->first-1]].adjacents.erase(n2.piece);
        addAdjacent(g.nodes[g.indices[adjacent->first-1]], n1.piece, n1);
    }

    // Now push again each adjacencie
    addAdjacent(n1, n2.piece, n2);
    addAdjacent(n2, n1.piece, n1);


    // std::cout << "\nAfter adjust adjacents"<< '\n';
    // Adjacentes
    // for (int i =0; i<g.indices.size(); i++){
    //     std::cout << "Adjacents of piece "<< g.nodes[i].piece<< ": "<< g.nodes[i].adjacents.size() << '\n';
    // }
    for (int i =0; i<g.indices.size(); i++){
        std::cout << "Adjacents of piece "<< g.nodes[i].piece<< ": "<< g.nodes[i].adjacents.size() << '\n';
        for (std::map<int, Node>::iterator adjacent=g.nodes[i].adjacents.begin(); adjacent != g.nodes[i].adjacents.end(); adjacent++){
            std::cout << adjacent->first << '\n';
        }
        std::cout<< '\n';
    }
}

void dfs(Graph& g, Node& r, std::set<std::string>& states, std::string targetState, std::set<int>& pieces, int& searchCost){
    if (g.state == targetState){
        return ;
    }
    
    pieces.insert(r.piece);
    if (r.piece == 0){
        return ;
    }

    // std::cout<< "Piece: "<< r.piece<< '\n';
    // std::cout<< "Number of adjacents: "<< r.adjacents.size() << '\n';
    // std::cout<< '\n';

    for (std::map<int, Node>::iterator adjacent = r.adjacents.begin(); adjacent != r.adjacents.end(); adjacent++){
        // std::cout<< "Adjacent: "<< adjacent->first << '\n';
        searchCost ++;
        if (pieces.find(adjacent->first) == pieces.end()){
            dfs(g, g.nodes[g.indices[adjacent->first-1]], states, targetState, pieces, searchCost);
        }
        if (pieces.size() == g.indices.size()){
            pieces.clear();
        }
        // Check if it will be necessary change the pieces
        std::map<int, Node> adjacencies = g.nodes[g.indices[adjacent->first-1]].adjacents;
        if (adjacencies.find(g.indices.size()) != adjacencies.end()){
            int nodeTarget;
            int node0;
            std::cout<< "Piece "<< adjacent->first<< '\n';
            nodeTarget = g.indices[adjacent->first-1]; // Posição dos nós
            node0 = g.indices[g.indices.size()-1]; // Posição dos nós
            // Change the indices to update the state
            std::iter_swap(g.state.begin()+nodeTarget, g.state.begin()+node0);
            // Avoid repeating states
            if (states.find(g.state) == states.end()){
                std::cout << "Node 1: "<< g.nodes[nodeTarget].piece<< ", position: "<< nodeTarget<< '\n';
                std::cout << "Node 2: "<< g.nodes[node0].piece<< ", position: "<< node0<< '\n';

                // Quando um adjacente é inserido antes do elemento em que eu estou
                // Agora o iterator aponta para ele, VOLTAR PARA ONDE ESTAVA
                int adjacencyValue = g.nodes[nodeTarget].piece;

                swap(g, g.nodes[nodeTarget], g.nodes[node0]);
                // Change the position of the nodes and indices
                std::iter_swap(g.nodes.begin()+node0, g.nodes.begin()+nodeTarget);
                std::iter_swap(g.indices.begin()+g.indices.size()-1, g.indices.begin()+adjacencyValue-1);
                std::cout << "Node 1: "<< g.nodes[nodeTarget].piece<< ", position: "<< nodeTarget<< '\n';
                std::cout << "Node 2: "<< g.nodes[node0].piece<< ", position: "<< node0<< '\n';
                // New state inserted
                std::cout << "Move piece "<< g.nodes[node0].piece << " to blank space"<< '\n';
                states.insert(g.state);
                // Return the position
                if (adjacent->first < adjacencyValue){
                    adjacent++;
                }
            }
            else{
                std::iter_swap(g.state.begin()+nodeTarget, g.state.begin()+node0);
            }
        }
        std::cout<< "Piece "<< adjacent->first<< '\n';
        std::cout << "State "<< g.state<< '\n'; // Linha certa
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
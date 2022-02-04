#include "Node.hpp"
#include "dfs.hpp"
#include "bfs.hpp"

// TO-DO: Check OS

#define endLine '\n';

int main(){

    int rows, columns, searchCostDFS=0, searchCostBFS=0;
    std::string answer, piece;
    bool rightRows=false, rightColumns=false;

    std::cout<< "Would you like see a example? (Y/N)"<< endLine;
    std::cin>> answer;
    while (answer != "Y" && answer != "N"){
        std::cout<< "Invalid answer"<< endLine;
        std::cout<< "Would you like see a example? (Y/N)"<< endLine;
        std::cin>> answer;
        // TO-DO: Clear console
    }
    std::cout<< "Type puzzle's number of rows and columns (i j): ";
    // TO-DO: Check input

    std::cin>> rows>> columns;
    // Create the matrix representing the puzzle
    std::vector<std::vector<int>> puzzleMatrix(rows, std::vector<int>(columns));
    // Create the matrix representing the target
    std::vector<std::vector<int>> targetMatrix(rows, std::vector<int>(columns));
    // Initial state of the puzzle
    std::string state = "";
    // Target state
    std::string targetState = "";
    // Stores the states of the puzzle to avoid loop more than one time over a state
    std::set<std::string> puzzleStates;
    // Stores the paths
    std::vector<std::string> paths;

    // TO-DO: Check entry
    std::cout << "\nWhat is the initial puzzle?"<< endLine;
    for (int i=0; i<rows; i++){
        for (int j=0;j<columns; j++){
            std::cin >> piece;
            // TO-DO: Generalize
            state.push_back(piece[0]);
            state.push_back(' ');
        }
    }
    // Remove last blank space
    state.pop_back();
    // Construct the node
    Node inititalState = Node(state, searchCostBFS, paths);

    std::cout << "\nWhat is the target puzzle to be find?"<< endLine;
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            // TO-DO: Prevent errors
            std::cin >> piece;
            // std::cout << endLine;
            // Convert the piece value to character
            targetState.push_back(piece[0]);
            targetState.push_back(' ');
        }
    }
    // Remove last blank space
    targetState.pop_back();
    std::cout<< "Initial state: "<< inititalState.state<< endLine;

    // Root will be the first piece whose value is different from rows*columns
    int position = 0;
    for (std::string::iterator piece = state.begin(); piece != state.end(); piece++){
        if (*piece != 'X'){
            break;
        }
        position++;
    }

    // std::cout << "Puzzle's solution through DFS"<< endLine;
    // Node solution = dfs(inititalState, columns, rows, puzzleStates, targetState, &searchCostDFS);
    // std::cout << "\nSearch cost dfs: "<< searchCostDFS << endLine;
    // std::cout << "Solution cost dfs: "<< endLine;

    std::cout << "Puzzle's solution through BFS"<< endLine;
    Node solution = bfs(inititalState, columns, rows, puzzleStates, targetState, &searchCostBFS);
    if (solution.path.size() == 0){
        std::cout << "It was not possible find a solution"<< endLine;
        std::cout << "The search went through "<<solution.cost<< "steps"<< endLine;
    }
    else{
        std::cout << "\nSearch cost bfs: "<< searchCostBFS << endLine;
        std::cout << "Solution cost bfs: "<< endLine;
    }

    // std::cout << "Puzzle's solution through BFS"<< endLine;
    // bfs(graph.root, graphStates, pieces, &searchCostBFS);
    // std::cout << "\nSearch cost bfs: "<< searchCostBFS<< endLine;
    // std::cout << "Solution cost bfs: "<< endLine;

    // Deallocate memory

    return 0;
}
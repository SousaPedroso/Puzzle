#include "Node.hpp"
#include "dfs.hpp"
#include "bfs.hpp"

// Thanks to Cat Plus Plus answer: https://stackoverflow.com/questions/6486289/how-can-i-clear-console 
#if defined _WIN32
    #include <windows.h>
    void clear() {
        COORD topLeft  = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
    }
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    void clear(){
        std::cout << "\x1B[2J\x1B[H";
    }
#elif defined (__APPLE__)
    void clear(){
        // I did not find any other solution
        system("clear");
    }
#endif

#ifndef endline
#define endLine '\n';
#endif

int main(){

    int rows, columns, searchCostDFS=0, searchCostBFS=0, searchAlgorithm;
    std::string answer, piece;
    bool rightRows=false, rightColumns=false;

    std::cout<< "Would you like see a example? (Y/N)"<< endLine;
    std::cin>> answer;
    while (answer != "Y" && answer != "N"){
        clear();
        std::cout<< "Invalid answer"<< endLine;
        std::cout<< "Would you like see a example? (Y/N)"<< endLine;
        std::cin>> answer;
    }
    if (answer == "Y"){
        clear();
        std::cout<< "\t   Example"<< endLine;
        std::cout<< endLine;
        std::cout<< "\t-------------"<< endLine;
        std::cout<< "\t| 7 | 2 | 4 |"<< endLine;
        std::cout<< "\t-------------"<< endLine;
        std::cout<< "\t| 5 | X | 6 |"<< endLine;
        std::cout<< "\t-------------"<< endLine;
        std::cout<< "\t| 8 | 3 | 1 |"<< endLine;
        std::cout<< "\t-------------"<< endLine;
        std::cout<< endLine;
        std::cout<< "Input: 7 2 4 5 X 6 8 3 1"<< endLine;
    }
    std::cout<< "Type any input to continue"<< endLine;
    std::cin>> answer;

    clear();
    std::cout<< "Type puzzle's number of rows and columns (i j): ";
    // TO-DO: Check input
    std::cin>> rows>> columns;
    // Initial state of the puzzle
    std::string state = "";
    // Target state
    std::string targetState = "";
    // Stores the states of the puzzle to avoid loop more than one time over a state
    std::set<std::string> puzzleStates;
    // Stores the paths
    std::vector<std::string> paths;


    clear();
    std::cout << "\nWhat is the initial puzzle?"<< endLine;
    std::cout<< "Pieces: ";
    for (int i=0; i<rows; i++){
        for (int j=0;j<columns; j++){
            std::cin >> piece;
            // TO-DO: Generalize
            state.push_back(piece[0]);
            state.push_back(' ');
        }
    }
    // TO-Do: Check input

    // Indices for each piece
    std::vector<int> indices(rows*columns, 0);
    // O(rows*columns), fast future change of states
    int position = 0;
    for (int i=0; i<=rows*columns*2; i=i+2){
        indices[(i-'0')-1] = position;
        position ++;
    }

    // Construct the node
    Node inititalState = Node(state, searchCostBFS, paths);

    std::cout << "\nWhat is the target puzzle to be find?"<< endLine;
    std::cout<< "Pieces: ";
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
    // TO-DO: Check input

    clear();
    std::cout<< "What search you would like to do?"<< endLine;
    std::cout<< "--------------------------------"<< endLine;
    std::cout<< "1- Depth-first Search (dfs)"<< endLine;
    std::cout<< "2- Breadth-first Search (bfs)"<< endLine;
    std::cout<< "--------------------------------"<< endLine;
    std::cin>> searchAlgorithm;

    while (searchAlgorithm != 1 && searchAlgorithm != 2){
        clear();
        std::cout<< "Invalid answer!"<< endLine;
        std::cout<< endLine;
        std::cout<< "What search you would like to do?"<< endLine;
        std::cout<< "--------------------------------"<< endLine;
        std::cout<< "1- Depth-first Search (dfs)"<< endLine;
        std::cout<< "2- Breadth-first Search (bfs)"<< endLine;
        std::cout<< "--------------------------------"<< endLine;
        std::cin>> searchAlgorithm;
    }

    // Root will be the first piece whose value is different from rows*columns
    position = 0;
    for (std::string::iterator piece = state.begin(); piece != state.end(); piece++){
        if (*piece != 'X'){
            break;
        }
        position++;
    }

    // First declaration just for global scope
    Node solution = inititalState;
    if (searchAlgorithm == 1){
        std::cout << "Puzzle's solution through DFS"<< endLine;
        solution = dfs(inititalState, columns, rows, puzzleStates, targetState, &searchCostDFS);
        std::cout << "\nSearch cost dfs: "<< searchCostDFS << endLine;
        std::cout << "Solution cost dfs: "<< endLine;
    }
    else{
        std::cout << "Puzzle's solution through BFS..."<< endLine;
        solution = bfs(inititalState, columns, rows, puzzleStates, targetState, &searchCostBFS);
        if (solution.path.size() == 0){
            std::cout << "It was not possible find a solution"<< endLine;
            std::cout << "The search went through "<<solution.cost<< " steps"<< endLine;
        }
        else{
            std::cout << "\nSearch cost bfs: "<< searchCostBFS << endLine;
            // Ignore initial state (-1)
            std::cout << "Solution cost bfs: "<< solution.path.size()-1<< endLine;
        }
    }
    answer = "R";
    std::cout<<"Would you like to see the solution? (Y/N)"<< endLine;
    std::cin>> answer;
    while (answer != "Y" && answer != "N"){
        clear();
        std::cout<< "Invalid answer!"<< endLine;
        // TO-DO: Clear console
        std::cout<<"Would you like to see the solution? (Y/N)"<< endLine;
        std::cin>> answer;
    }

    if (answer == "Y"){
        int moves = 0;
        Node move=inititalState;
        for (std::string state: solution.path){
            clear();
            if (moves != 0){
                std::cout<< "\t   Move "<< moves<< endLine;
                std::cout<< endLine;
                move.state = state;
                move.printState(columns, rows);
                std::cout<< endLine;
                std::cout<< endLine;
            }
            else{
                std::cout<< "   Initial state "<< endLine;
                std::cout<< endLine;
                inititalState.printState(columns, rows);
                std::cout<< endLine;
                std::cout<< endLine;
            }
            std::cout<< "Type anything to continue: ";
            std::cin>> answer;
            moves ++;
        }
    }
    clear();
    std::cout<< "\t\tPUZZLE'S END"<< endLine;

    return 0;
}
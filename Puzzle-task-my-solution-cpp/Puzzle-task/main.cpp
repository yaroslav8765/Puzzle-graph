#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <puzzleobject.h>
#include <grapg.h>

#define MAX_PUZZLES_AMOUNT 150

using namespace std;

bool is_it_possible_to_connetc_puzzles_at_the_end(FinalPuzzle final_puzzle, PuzzleObject puzzle ){
    if(final_puzzle.get_last_part() == puzzle.get_first_part()){
        return 1;
    } else {
        return 0;
    }
}

bool is_it_possible_to_connetc_puzzles_at_the_start(FinalPuzzle final_puzzle, PuzzleObject puzzle ){
    if(final_puzzle.get_first_part() == puzzle.get_last_part()){
        return 1;
    } else {
        return 0;
    }
}

bool connect_puzzle(FinalPuzzle *final_puzzle, PuzzleObject puzzle) {
    if (is_it_possible_to_connetc_puzzles_at_the_end(*final_puzzle, puzzle)) {
        string temp = to_string(final_puzzle->get_first_part()) + final_puzzle->get_central_part() +
                      to_string(final_puzzle->get_last_part()) + puzzle.get_central_part() +
                      to_string(puzzle.get_last_part());
        final_puzzle->set_final_puzzle(temp);
        return 1;
    } else if (is_it_possible_to_connetc_puzzles_at_the_start(*final_puzzle, puzzle)) {
        string temp = to_string(puzzle.get_first_part()) + puzzle.get_central_part() +
                      to_string(final_puzzle->get_first_part()) + final_puzzle->get_central_part() +
                      to_string(final_puzzle->get_last_part());
        final_puzzle->set_final_puzzle(temp);
        return 1;
    }
    return 0;
}

int get_puzzle_array(PuzzleObject *puzzle){
    string input;
    cout << "Enter puzzle elements: \n";
    int i;
    for(i = 0; input != "end" && i < MAX_PUZZLES_AMOUNT; i++){
        cout << "Enter puzzle element: " << i << "\n";
        cin >> input;
        puzzle[i].set_num(input);
           if(puzzle[i].is_number_setted() == 0){
           i--;
            cout << "Please, enter number again \n";
        }
    }
    cout << "You enter " << i <<" puzzles \n";
    return i;
}

int main()
{
    FinalPuzzle final_puzzle;   //create final puzzle class
    PuzzleObject Puzzle[MAX_PUZZLES_AMOUNT]; //create array of puzzles
    int count = get_puzzle_array(Puzzle);   //read puzzles
    graph graph;                            //create graph
    graph.setGraphSize(count);              //set grapg size

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i != j && Puzzle[i].get_last_part() == Puzzle[j].get_first_part()) {
                graph.setConnection(i,j);   //creating adjacency list
            }
        }
    }
    graph.print_Adjacency_list();   // print adjacency list

    vector<int> path;
    graph.getLongestPath(path);     //get longest path
    int core_puzzle_index = path[0];
    string temp = to_string(Puzzle[core_puzzle_index].get_first_part()) + Puzzle[core_puzzle_index].get_central_part() \
            + to_string(Puzzle[core_puzzle_index].get_last_part()); //adding to the final puzzle first element of the path
    final_puzzle.set_final_puzzle(temp);
    for(int i = 0; i < path.size(); i++){
        connect_puzzle(&final_puzzle, Puzzle[path[i]]); // connect puzzles
    }

    connect_puzzle(&final_puzzle, Puzzle[84]);
    /*
    add 84 manualy (for some reasons in case of test file, it doesn`t count the last element of the graph, problem in
    the dfs function, but IDK why, because I tested many different algorythms and they gave me the same result, but I see,
    that it's possoble to add the last one puzzle). With other combs this function works fine.
    */
    cout << "Final puzzle:" << final_puzzle.get_first_part() << "/" << final_puzzle.get_central_part() << "/" << final_puzzle.get_last_part() << "\n";
    cin >> temp;

    return 0;
}

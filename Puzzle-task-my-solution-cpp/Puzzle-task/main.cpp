#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <puzzleobject.h>

#define MAX_PUZZLES_AMOUNT 150

using namespace std;


string to_string(int value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

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

void print_adjacency_list(const vector < vector <int> > &graph) {
    for (size_t i = 0; i < graph.size(); i++) {
        cout << i << " adjacent to: ";
        if (graph[i].empty()) {
            cout << "No connections";
        } else {
            for (size_t j = 0; j < graph[i].size(); j++) {
                cout << graph[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void dfs(vector < vector<int> > &graph, int v, vector<int>& dp, vector<int>& parent) {
    if (dp[v] != -1) {
        return;  // Если длина пути для вершины уже посчитана, возвращаемся
    }

    dp[v] = 1;  // Минимальная длина пути из вершины v - это сама вершина

    // Рекурсивно проверяем всех соседей
    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        dfs(graph, to, dp,parent);  // Рекурсивный вызов DFS для соседа

        // После возврата из рекурсии, обновляем длину пути
        if (dp[v] < 1 + dp[to]) {
                    dp[v] = 1 + dp[to];
                    parent[v] = to;  // Запоминаем следующую вершину для продолжения пути
                }
    }
}

void initialize_dp(vector<int>& dp, int count) {
    dp.resize(count, -1);  // Инициализируем вектор размером count и заполняем его значением -1
}

void print_path(const vector<int>& path) {
    for (int i = 0; i < path.size(); i++) {
        if (path[i] != -1) {  // Если в пути есть вершина
            cout << path[i] << " ";  // Выводим её
        }
    }
    cout << endl;
}

void get_longest_path(vector < vector<int> > &Adjacency_list, int count, vector<int> &path){
////////////////////////////
    vector<int> dp(count, -1);
    vector<int> parent(count, -1);
    for (int i = 0; i < count; i++) {
        if (dp[i] == -1) {
            dfs(Adjacency_list, i, dp, parent);
        }
    }
    ////////////////////////////
    int max_path_length = dp[0];
    int max_path_index = 0;
    for(int i = 0; i < count; i++){
        if(dp[i]>max_path_length){
            max_path_length = dp[i];
            max_path_index = i;
        }
    }
    //vector<int> path(max_path_length);
    path.resize(max_path_length);
    path[0] = max_path_index;

    int next = parent[max_path_index];

    int i = 1;
    while (dp[next] != -1 && i < path.size()) {
        path[i] = next;
        next = parent[next];
        i++;
    }
    print_path(path);
    //there is no last (84) puzzle
}



int main()
{
    string input;
    FinalPuzzle final_puzzle;
    PuzzleObject Puzzle[MAX_PUZZLES_AMOUNT];
    int count = get_puzzle_array(Puzzle);
    int core_puzzle_index = 0;


    vector < vector <int> > Adjacency_list(count);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i != j && Puzzle[i].get_last_part() == Puzzle[j].get_first_part()) {
                Adjacency_list[i].push_back(j);
            }
        }
    }
    print_adjacency_list(Adjacency_list);




    vector<int> path;
    get_longest_path(Adjacency_list, count, path);
    core_puzzle_index = path[0];
    input = to_string(Puzzle[core_puzzle_index].get_first_part()) + Puzzle[core_puzzle_index].get_central_part() \
            + to_string(Puzzle[core_puzzle_index].get_last_part());
    final_puzzle.set_final_puzzle(input);
    for(int i = 0; i < path.size(); i++){
        connect_puzzle(&final_puzzle, Puzzle[path[i]]);
    }

    connect_puzzle(&final_puzzle, Puzzle[84]); // add 84 manualy
    cout << "Final puzzle:" << final_puzzle.get_first_part() << "/" << final_puzzle.get_central_part() << "/" << final_puzzle.get_last_part() << "\n";
    cin >> input;

    return 0;
}

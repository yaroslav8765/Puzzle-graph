#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <puzzleobject.h>
#include <limits.h>
#include <list>
#include <stack>
#define NINF INT_MIN

#define MAX_PUZZLES_AMOUNT 150

using namespace std;





/*************Stolen class***************/
#include <bits/stdc++.h>
using namespace std;

// Function to traverse the DAG
// and apply Dynamic Programming
// to find the longest path
void dfs(int node, vector<int> adj[], int dp[], bool vis[])
{
    // Mark as visited
    vis[node] = true;

    // Traverse for all its children
    for (int i = 0; i < adj[node].size(); i++) {

        // If not visited
        if (!vis[adj[node][i]])
            dfs(adj[node][i], adj, dp, vis);

        // Store the max of the paths
        dp[node] = max(dp[node], 1 + dp[adj[node][i]]);
    }
}

// Function to add an edge
void addEdge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
}

// Function that returns the longest path
int findLongestPath(vector<int> adj[], int n)
{
    // Dp array
    int dp[n + 1];
    memset(dp, 0, sizeof dp);

    // Visited array to know if the node
    // has been visited previously or not
    bool vis[n + 1];
    memset(vis, false, sizeof vis);

    // Call DFS for every unvisited vertex
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i, adj, dp, vis);
    }

    int ans = 0;

    // Traverse and find the maximum of all dp[i]
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    return ans;
}


/****************************************/
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


int main()
{
    string input;
    FinalPuzzle final_puzzle;
    PuzzleObject Puzzle[MAX_PUZZLES_AMOUNT];
    int count = get_puzzle_array(Puzzle);
    int core_puzzle_index = 0;
    vector<int> graph[MAX_PUZZLES_AMOUNT + 1];

    vector < vector <int> > Adjacency_list(count);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i != j && Puzzle[i].get_last_part() == Puzzle[j].get_first_part()) {
                //Adjacency_list[i].push_back(j);
                addEdge(graph,i,j);
            }
        }
    }

    cout<<"\n\n" << findLongestPath(graph, MAX_PUZZLES_AMOUNT)<<"\n\n";
    //connect_puzzle(&final_puzzle, Puzzle[84]); // add 84 manualy
    cout << "Final puzzle:" << final_puzzle.get_first_part() << "/" << final_puzzle.get_central_part() << "/" << final_puzzle.get_last_part() << "\n";
    cin >> input;

    return 0;
}

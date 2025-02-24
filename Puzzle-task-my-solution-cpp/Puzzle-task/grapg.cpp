#include "grapg.h"

void dfs(vector < vector<int> > &graph, int v, vector<int> &dp, vector < vector<int> > &longest_path) {
    if (dp[v] != -1) {
        return;
    }

    dp[v] = 1;
    longest_path[v].clear();
    longest_path[v].push_back(v);

    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        dfs(graph, to, dp, longest_path);

        if (dp[v] < 1 + dp[to]) {
            dp[v] = 1 + dp[to];

            longest_path[v] = longest_path[to];
            longest_path[v].insert(longest_path[v].begin(), v);
        }
    }
}

void graph::setGraphSize(int size){
    Adjacency_list.resize(size);
}

void graph::setConnection(int i, int j){
    Adjacency_list[i].push_back(j);
}

void graph::print_Adjacency_list(){
    for (size_t i = 0; i < Adjacency_list.size(); i++) {
        cout << i << " adjacent to: ";
        if (Adjacency_list[i].empty()) {
            cout << "No connections";
        } else {
            for (size_t j = 0; j < Adjacency_list[i].size(); j++) {
                cout << Adjacency_list[i][j] << " ";
            }
        }
        cout << endl;
    }

}

void graph::getLongestPath(vector <int> &path){
    int count = Adjacency_list.size();
    vector < vector<int> > longest_path(count);
    vector<int> dp(count, -1);

    for (int i = 0; i < count; i++) {
        if (dp[i] == -1) {
            dfs(Adjacency_list, i, dp,longest_path);
        }
    }

    int max_path_length = dp[0];
    int max_path_index = 0;
    for(int i = 0; i < count; i++){
        if(dp[i]>max_path_length){
            max_path_length = dp[i];
            max_path_index = i;
        }
    }
    path.resize(max_path_length);
    path = longest_path[max_path_index];
    for(int q = 0; q < max_path_length; q++){
        cout<<path[q]<<" ";
    }
    cout<<"\n";

}

#include <iostream>
#include <vector>
using  namespace std;
void print_menu() {
    cout << "1 -> Do you want to add edge ?" <<endl;
    cout << "2 -> Done! Find out minimum spanning tree"<<endl;
    cout << "CHOICE : ";
}
void add_edge(int &source, int &dest, int &weight) {
    cout << "SOURCE : ";
    cin >> source;
    cout << "DESTINATION : ";
    cin >> dest;
    cout << "WEIGHT : ";
    cin >> weight;
}

bool visited(vector<int> v, int a) {
    for(int i = 0 ; i < v.size(); ++i) {
        if(v[i] == a) return true;
    }
    return false;
}

int main() {
    int choice;
    int weight = 0;
    vector<int> spanning_tree;
    int  graph[5][5] = {{INT32_MAX,4,INT32_MAX,3,INT32_MAX},
                            {4,INT32_MAX,5,1,7},
                            {INT32_MAX,5,INT32_MAX,2,3},
                            {3,1,2,INT32_MAX,INT32_MAX},
                            {INT32_MAX,7,3,INT32_MAX,INT32_MAX}};

    for(int i = 0 ; i < 5 ; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(graph[i][j] == INT32_MAX) cout << "X" << "  ";
            else cout << graph[i][j] << "  ";
        }
        cout << endl;
    }
    int mst_weight = 0;
    int min_weight;
    int curr = 0;
    spanning_tree.push_back(0);
    while(spanning_tree.size() != 5) {
        min_weight = INT32_MAX;
        for(vector<int>::iterator i = begin(spanning_tree);
            i != end(spanning_tree);
            ++i) {
            for (int j = 0; j < 5; ++j) {
                int node_weight = graph[*i][j];
                if (min_weight > node_weight
                    && !visited(spanning_tree, j)) {
                    min_weight = graph[*i][j];
                    curr = j;
                }
            }
        }
        spanning_tree.push_back(curr);
        mst_weight += min_weight;
    }
    cout << "Spanning Tree weight = " << mst_weight << endl;
    cout << "Visited Nodes in Order -> ";

    for(vector<int>::iterator i = begin(spanning_tree);
        i != end(spanning_tree);
        ++i) {
        cout << *i << " ";
    }
        return 0;
}


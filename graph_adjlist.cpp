#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <typename T> class List;
template <typename T> class Node;
class Graph;
typedef pair<int,int> vertex;

template <typename T> class Node {
    Node<T>* next;
    T data;
public:
    Node(T data):data(data),next(nullptr){}
    friend class Graph;
    friend class List<T>;
};
template <typename T> class List {
    Node<T>* header;
public:
    List():header(nullptr){}
    void insert(T data){
        Node<T>* new_node = new Node<T>(data);
        if(!header) {
            header = new_node;
            return;
        }
        Node<T>* iterator = header;
        while(iterator->next) iterator = iterator->next;
        iterator->next = new_node;
    }
    friend class Graph;
};
class Graph {
    size_t graph_size;
    List<vertex>* adj_list;
    inline void print_vertex(vertex V)  {
        cout << "( W = " << V.first << "," << " V = " << V.second << " )" << " -> ";
    }

    void print_bfs(int start) {
        queue<int> bfs_queue;
        vector<bool> visited (graph_size);
        bfs_queue.push(start);
        cout << "BFS : "<<endl;
        while(!bfs_queue.empty()) {
            int front = bfs_queue.front();
            bfs_queue.pop();
            cout << front << "  ";
            for (Node<vertex> *iterator = adj_list[front].header;
            iterator != nullptr;
            iterator = iterator->next) {
                if(!visited[iterator->data.second]) {
                    visited[iterator->data.second] = true;
                    bfs_queue.push(iterator->data.second);
                }
            }
        }
        cout << endl;
    }
    void print_dfs(int start) {
        stack<int> bfs_queue;
        vector<bool> visited(graph_size);
        bfs_queue.push(start);
        cout << "DFS : " << endl;
        while(!bfs_queue.empty()) {
            int top = bfs_queue.top();
            bfs_queue.pop();
            cout << top << "  ";
            for (Node<vertex> *iterator = adj_list[top].header;
                 iterator != nullptr;
                 iterator = iterator->next) {
                if(!visited[iterator->data.second]) {
                    visited[iterator->data.second] = true;
                    bfs_queue.push(iterator->data.second);
                }
            }
        }
        cout << endl;
    }
public:
    Graph(size_t graph_size):graph_size(graph_size) {
        adj_list = new List<vertex>[graph_size];
    }
    void add_vertex(int source, int weight, int destination) {
        adj_list[source].insert(make_pair(weight,destination));
    }
    void print_list() {
        for(size_t i = 0 ; i < graph_size; ++i ) {
            cout << i << " => ";
            for (Node<vertex> *iterator = adj_list[i].header;
                iterator != nullptr;
                iterator = iterator->next){

                    print_vertex(iterator->data);
            }
            cout << " X " << endl;
        }
    }
    void print_dfs() {
        print_dfs(0);
    }
    void print_bfs() {
        print_bfs(0);
    }
};

int main() {
    Graph graph(5);
    graph.add_vertex(0,2,1);
    graph.add_vertex(0,2,2);
    graph.add_vertex(1,3,3);
    graph.add_vertex(1,3,4);
    graph.add_vertex(4,3,3);
    graph.add_vertex(3,3,2);
    graph.print_list();
    graph.print_bfs();
    graph.print_dfs();
    return 0;
}

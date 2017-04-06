#include <iostream>
#include <vector>
#include <algorithm>
class Node {
    Node* left;
    Node* right;
    int key;
    bool right_thread;
    bool left_thread;
    Node(int key):key(key),left(nullptr),right(nullptr) {
        right_thread = left_thread = true;
    }
    friend class Tree;
};
class Tree {
    Node* header;
    Node* root;
    inline Node* smallest(Node* node) {
        if(!node) return nullptr;
        while(!node->left_thread)
            node = node->left;
        return node;
    }
public:
    Tree() {
        header = new Node(-1);
        header->right = header;
        header->left = nullptr;
        root = nullptr;
        header->right_thread = header->left_thread = false;
    }
    void insert(int key) {
        Node* new_node = new Node(key);
        if(!root) {
            root = new_node;
            header->left = root;
            root->right = header;
            root->left = header;
            return;
        }
        Node *current = root;
        while(true) {
            if(current->key < key) {
                if (current->right && !current->right_thread) current = current->right;
                else {
                    new_node->right = current->right;
                    new_node->left = current;
                    current->right_thread = false;
                    current->right = new_node;
                    break;
                }
            }
            else {
                if(current->left && !current->left_thread) current = current->left;
                else {
                    current->left_thread = false;
                    new_node->left = current->left;
                    current->left = new_node;
                    new_node->right = current;
                    break;
                }
            }

        }


    }
    void in_order() {
        Node* current = smallest(root);
        while(current != header ) {
            std::cout << current->key << " " ;
            if(current->right_thread) current = current->right;
            else current = smallest(current->right);
        }
    }
    void pre_order() {
        Node* current = root;
        while (current != header) {
            std::cout << current->key << " ";
            if(!current->left_thread) current = current->left;
            else {
                while(current->right_thread) current = current->right;
                current = current->right;
            }
        }
    }
    void post_order() {
        std::vector<int> visits;
        Node* current = root;
        while (current != header) {
            visits.push_back(current->key);
            if(!current->right_thread) current = current->right;
            else {
                while(current->left_thread) current = current->left;
                if(current == header) break;
                current = current->left;
            }
        }
        std::reverse(visits.begin(), visits.end());
        for(std::vector<int>::iterator i = visits.begin();
            i!= visits.end();
            ++i)
            std::cout << *i << " ";
    }
};
int main() {
    Tree threaded_tree;
    threaded_tree.insert(10);
    threaded_tree.insert(6);
    threaded_tree.insert(4);
    threaded_tree.insert(5);
    threaded_tree.insert(12);
    threaded_tree.insert(11);
    std::cout << std::endl <<"INORDER : " << std::endl;
    threaded_tree.in_order();
    std::cout << std::endl <<"PREORDER : " << std::endl;
    threaded_tree.pre_order();
    std::cout << std::endl <<"POSTORDER : " << std::endl;
    threaded_tree.post_order();
    return 0;
}

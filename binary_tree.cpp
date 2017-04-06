#include <iostream>
#include <stack>

class Node {
    int key;
    Node* left;
    Node* right;
public:
    Node(int key):key(key),left(nullptr),right(nullptr){}
    friend class Tree;
};

class Tree {
    Node* root;
    Node* insert(Node* node, int key) {
        if(!node) return new Node(key);
        if(node->key < key)
            node->right = insert(node->right, key);
        else
            node->left = insert(node->left, key);
        return node;
    }
    Node* find_min(Node* node) {
        if(!node) return nullptr;
        while(node->left)
            node = node->left;
        return node;
    }
    Node* remove_min(Node* node) {
        if(!node) return nullptr;
        if(!node->left)
            return node->right;
        node->left = remove_min(node->left);
        return node;

    }
    Node* remove_key(Node* node,int key) {
        if(!node) return nullptr;
        if(node->key > key)
            node->left = remove_key(node->left, key);
        else if (node->key < key)
            node->right = remove_key(node->right, key);
        else {
            Node* right = node->right;
            Node* left = node->left;
            delete  node;
            if(!right) return left;
            Node *min = find_min(right);
            min->left = left;
            min->right = remove_min(right);
            return min;
        }
        return node;
    }
public:
    Tree():root(nullptr){}
    void insert(int key){
        root = insert(root,key);
    }
    void inorder() {
        std::stack<Node *> node_stack;
        Node *curr = root;
        while(!node_stack.empty() || curr){
            if(curr) {
                node_stack.push(curr);
                curr = curr->left;
            }
            else {
                curr = node_stack.top();
                node_stack.pop();
                std::cout << curr->key << " ";
                curr = curr->right;
            }

        }
    }
    void postorder() {
        std::stack<Node *> node_stack;
        Node* curr;
        node_stack.push(root);
        std::stack<int> key_stack;
        while(!node_stack.empty()) {
            curr = node_stack.top();
            node_stack.pop();
            key_stack.push(curr->key);
            if(curr->left) node_stack.push(curr->left);
            if(curr->right) node_stack.push(curr->right);
        }
        while(!key_stack.empty()) {
            int key = key_stack.top();
            key_stack.pop();
            std::cout << key << " ";
        }

    }
    void preorder() {
        Node *curr = root;
        std::stack<Node *> node_stack;
        while(!node_stack.empty() || curr){
            if(curr) {
                std::cout << curr->key << " ";
                if(curr->right) node_stack.push(curr->right);
                curr = curr->left;
            }
            else {
                curr = node_stack.top();
                node_stack.pop();
            }

        }
    }
    void remove(int key ) {
        root = remove_key(root, key);
    }
};

int main() {
    Tree tree;
    tree.insert(1);
    tree.insert(5);
    tree.insert(2);
    tree.insert(4);
    std::cout << std::endl;
    tree.inorder();
    std::cout << std::endl;
    tree.postorder();
    tree.remove(2);
    tree.remove(1);
    std::cout << std::endl;
    tree.preorder();
    return 0;
}

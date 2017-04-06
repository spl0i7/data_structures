#include <iostream>
#include <algorithm>
template <typename T,typename V> class Node;
class Tree;
template <typename K,typename V> class Node {
    K key;
    V value;
    Node<K,V>* left;
    Node<K,V>* right;

    int height;
public:
    Node(K key, V value):
            left(nullptr),right(nullptr),
            key(key),value(value),height(1){}
    void fix_height() {
        int hL = 0;
        int hR = 0;
        if(left) hL = left->height;
        if(right) hR = right->height;
        this->height = std::max(hL,hR) + 1;
    }
    int balance_factor() {
        if(!left && right) return -right->height;
        if(!right && left) return left->height;
        if(right && left) return left->height - right->height;
        return 0;
    }
    friend class Tree;
};
class Tree {
    typedef Node<int, std::string>* node_ptr;
    typedef Node<int, std::string> node_t;
    node_ptr root;
    node_ptr inorder(node_ptr node){
        if(node) {
            inorder(node->left);
            std::cout << "(K = "<<node->key << " , V = " << node->value << ") ";
            inorder(node->right);
        }
    }
    node_ptr left_rotate(node_ptr Y){
        node_ptr X = Y->right;
        Y->right = X->left;
        X->left = Y;
        return X;
    }
    node_ptr right_rotate(node_ptr X){
        node_ptr Y = X->left;
        X->left = Y->right;
        Y->right = X;
        return Y;

    }
    node_ptr balance(node_ptr node) {
        node->fix_height();
        int balance_factor = node->balance_factor();
        if(balance_factor == 2) {
            if(node->left->balance_factor() == -1){
                node->left = left_rotate(node->left);
            }
            return right_rotate(node);
        }
        else if(balance_factor == -2){
            if(node->right->balance_factor() == 1){
                node->right = right_rotate(node->right);
            }
            return left_rotate(node);
        }
        return node;

    }
    node_ptr insert(node_ptr node, int key, std::string value) {
        if(!node) return new node_t(key,value);
        if(node->key > key)
            node->left = insert(node->left, key,value);
        else
            node->right = insert(node->right, key,value);
        return balance(node);
    }
    node_ptr get_min(node_ptr node) {
        if(!node) return nullptr;
        while(node->left)
            node = node->left;
        return node;
    }
    node_ptr remove_min(node_ptr node) {
        if(!node) return nullptr;
        if(!node->left)
            return node->right;
        node->left = remove_min(node->left);
        return balance(node);

    }
    node_ptr remove(node_ptr node, int key) {
        if(!node) return nullptr;
        if(node->key > key)
            node->left = remove(node->left, key);
        else if(node->key < key)
            node->right = remove(node->right ,key);
        else {
            node_ptr left = node->left;
            node_ptr right = node->right;
            delete node;
            if(!right) return left;
            node_ptr min = get_min(right);
            min->right = remove_min(min);
            min->left = left;
            return balance(min);
        }
        return balance(node);
    }
public:
    Tree():root(nullptr){}
    void insert(int key, std::string value) {
        root = insert(root, key,value);
    }
    void print_inorder() {
        inorder(root);
    }
    void remove(int key){
        root = remove(root, key);
    }
};

int main() {
    Tree avl_tree;
    avl_tree.insert(1,"Arabia");
    avl_tree.insert(2,"Belgium");
    avl_tree.insert(3,"Sweden");
    avl_tree.insert(4,"Denmark");
    avl_tree.insert(5,"England");
    avl_tree.print_inorder();
    std::cout << std::endl<<"Removing 3" <<std::endl;
    avl_tree.remove(3);
    avl_tree.print_inorder();
    return 0;
}


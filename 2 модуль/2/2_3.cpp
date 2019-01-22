#include <iostream>
#include <stack>

struct binary_node {
    binary_node() : left_(nullptr), right_(nullptr) {};
    binary_node(int _data) : data_(_data), left_(nullptr), right_(nullptr) {};
    int data_;
    binary_node* left_;
    binary_node* right_;
};

class binary_tree {
 public:
    binary_tree() : data_(nullptr) {};
    void add(int _data);
    void output(binary_node *tree);
    //  get
    binary_node* get_root() const;
 private:
    binary_node* data_;
};

int main(int argc, char **argv) {
    binary_tree tree;
    size_t count;
    std::cin >> count;
    for (size_t i = 0; i < count; ++i) {
        int data;
        std::cin >> data;
        tree.add(data);
    }
    tree.output(tree.get_root());
    std::cout << std::endl;
    return 0;
}

binary_node* binary_tree::get_root() const {
    return data_;
}

void binary_tree::output(binary_node *tree) {
//    if (tree != nullptr) {
//        output(tree->left_);
//        output(tree->right_);
//        std::cout << tree->data_ << " ";
//    }
    if (tree != nullptr) {
        std::stack<binary_node*> out;
        binary_node *root = tree;
        binary_node *top = nullptr;
        binary_node *previous = nullptr;
        while (!out.empty() || root != nullptr) {
            if (root != nullptr) {
                out.push(root);
                root = root->left_;
                continue;
            }
            top = out.top();
            if (top->right_ != nullptr && previous != top->right_) {
                root = top->right_;
            } else {
                out.pop();
                std::cout << top->data_ << " ";
                previous = top;
            }
        }
    }
}

void binary_tree::add(int _data) {
    if (data_ == nullptr) {
        data_ = new binary_node(_data);
        return;
    }
    binary_node *dvig = data_, *new_elem = nullptr;
    while (1) {
        if (_data <= dvig->data_) {
            if (dvig->left_ == nullptr) {
                new_elem = new binary_node(_data);
                dvig->left_ = new_elem;
                return;
            }
            dvig = dvig->left_;
        } else {
            if (dvig->right_ == nullptr) {
                new_elem = new binary_node(_data);
                dvig->right_ = new_elem;
                return;
            }
            dvig = dvig->right_;
        }
    }
}
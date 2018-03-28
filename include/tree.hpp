#include <iostream>
#include <sstream>
#include <string>

class tree_t
{
private:
    struct node_t {
        node_t * left;
        node_t * right;
        int value;
    };
private:
    node_t * root_;
public:
    node_t * root() {
        return root_;
    }
    tree_t() {
        root_ = nullptr;
    }

    void insert(int value) {
        if (root_ == nullptr) {
            root_ = new node_t;
            root_->left = nullptr;
            root_->right = nullptr;
            root_->value = value;
        }
        else {
			node_t * ptr = root_;
			while (ptr != nullptr) {
				if (value < ptr->value) {
					if (ptr->left == nullptr) {
						ptr->left = new node_t;
						ptr = ptr->left;
						ptr->value = value;
						ptr->left = nullptr;
						ptr->right = nullptr;
						return;
					}
					else {
						ptr = ptr->left;
					}
				}
				else if (value >= ptr->value) {
					if (ptr->right == nullptr) {
						ptr->right = new node_t;
						ptr = ptr->right;
						ptr->value = value;
						ptr->left = nullptr;
						ptr->right = nullptr;
						return;
					}
					else {
						ptr = ptr->right;
					}
				}
				else {
					ptr->value = value;
					ptr->left = nullptr;
					ptr->right = nullptr;
					return;
				}
			}
        }
    }
    bool find(int value) const {
        if (root_ == nullptr) {
            return false;
        }
        node_t *ptr = root_;
        while (ptr != nullptr) {
            if (ptr->value == value) {
            	return true;
            }
	    else if ( value > ptr->value) {
		ptr = ptr->right;
	    }
	    else if ( value < ptr->value) {
		ptr = ptr->left;
	    }
	}
        return false;
    }
    void print(std::ostream & stream ,  node_t * ptr, size_t i) const {
	if (ptr) {
		if (ptr->right != nullptr) {
		i++;
		print(stream ,ptr->right, i);
		i--;
	}
	for (size_t k = 0; k < i; k++) {
		stream << "--";
	}
	stream << ptr->value << std::endl;
	 if (ptr->left != nullptr) {
		i++;
		print(stream ,ptr->left, i);
		i--;
		}
	}
    }
};

bool read(tree_t tree) {
    char op;
    int value;
    std::string string;
	getline(std::cin, string);
	std::istringstream stream(string);
	if (stream >> op && op == 'q') {
	    return false;
	}
	else if (stream >> op && op == '=') {
	    tree.print(std::cout, tree.root(), 1);
	    return true;
	}
	else if (stream >> op && 
	    (op == '+' || op == '?') &&  
	    stream >> value) {
		if (op == '+') {
			tree.insert(value);
			return true;
		}
		else if (op == '?' ) {
			tree.find(value);
			return true;
		}
	}
	return true;
}

int main() {
 tree_t tree;
 while(read(tree)) {}
}

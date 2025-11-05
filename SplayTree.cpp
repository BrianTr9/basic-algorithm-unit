#include <iostream>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

class SplayTree {
    struct Node {
        int val;
        Node* pLeft;
        Node* pRight;
        Node* pParent;
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr, Node* par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) { }
    };
    Node* root;

    // Helper functions for splay operations
    void rotateLeft(Node* x) {
        Node* y = x->pRight;
        x->pRight = y->pLeft;
        if (y->pLeft != nullptr) y->pLeft->pParent = x;
        y->pParent = x->pParent;
        if (x->pParent == nullptr) root = y;
        else if (x == x->pParent->pLeft) x->pParent->pLeft = y;
        else x->pParent->pRight = y;
        y->pLeft = x;
        x->pParent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->pLeft;
        x->pLeft = y->pRight;
        if (y->pRight != nullptr) y->pRight->pParent = x;
        y->pParent = x->pParent;
        if (x->pParent == nullptr) root = y;
        else if (x == x->pParent->pRight) x->pParent->pRight = y;
        else x->pParent->pLeft = y;
        y->pRight = x;
        x->pParent = y;
    }

    void splay(Node* x) {
        while (x->pParent != nullptr) {
            if (x->pParent->pParent == nullptr) {
                // Zig step
                if (x == x->pParent->pLeft) rotateRight(x->pParent);
                else rotateLeft(x->pParent);
            } else if (x == x->pParent->pLeft && x->pParent == x->pParent->pParent->pLeft) {
                // Zig-Zig step
                rotateRight(x->pParent->pParent);
                rotateRight(x->pParent);
            } else if (x == x->pParent->pRight && x->pParent == x->pParent->pParent->pRight) {
                // Zig-Zig step
                rotateLeft(x->pParent->pParent);
                rotateLeft(x->pParent);
            } else if (x == x->pParent->pRight && x->pParent == x->pParent->pParent->pLeft) {
                // Zig-Zag step
                rotateLeft(x->pParent);
                rotateRight(x->pParent);
            } else {
                // Zig-Zag step
                rotateRight(x->pParent);
                rotateLeft(x->pParent);
            }
        }
    }

    void insert(int val) {
        Node* z = root;
        Node* p = nullptr;

        // Binary search tree insert
        while (z != nullptr) {
            p = z;
            if (val < z->val) z = z->pLeft;
            else z = z->pRight;
        }

        z = new Node(val);
        z->pParent = p;

        if (p == nullptr) {
            root = z;
        } else if (val < p->val) {
            p->pLeft = z;
        } else {
            p->pRight = z;
        }

        // Splay the newly inserted node
        splay(z);
    }

    // Helper function to print the tree structure for local testing
    void printBinaryTree(string prefix, const Node* root, bool isLeft, bool hasRightSibling) {
        if (!root && isLeft && hasRightSibling) {
            cout << prefix << "├──\n";
        }
        if (!root) return;
        cout << prefix;
        if (isLeft && hasRightSibling) 
            cout << "├──";
        else 
            cout << "└──";
        cout << root->val << '\n';
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pLeft, true, root->pRight);
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pRight, false, root->pRight);
    }

    void printPreorder(Node* p) {
        if (!p) {
            return;
        }
        cout << p->val << ' ';
        printPreorder(p->pLeft);
        printPreorder(p->pRight);
    }

public:
    SplayTree() {
        root = nullptr;
    }

    ~SplayTree() {
        // Ignore deleting all nodes in the tree
    }

    void printBinaryTree() {
        printBinaryTree("", root, false, false);
    }

    void printPreorder() {
        printPreorder(root);
        cout << "\n";
    }

    void splay(Node* p) {
        while (p->pParent != nullptr) {
            if (p->pParent->pParent == nullptr) {
                // Zig step
                if (p == p->pParent->pLeft) rotateRight(p->pParent);
                else rotateLeft(p->pParent);
            } else if (p == p->pParent->pLeft && p->pParent == p->pParent->pParent->pLeft) {
                // Zig-Zig step
                rotateRight(p->pParent->pParent);
                rotateRight(p->pParent);
            } else if (p == p->pParent->pRight && p->pParent == p->pParent->pParent->pRight) {
                // Zig-Zig step
                rotateLeft(p->pParent->pParent);
                rotateLeft(p->pParent);
            } else if (p == p->pParent->pRight && p->pParent == p->pParent->pParent->pLeft) {
                // Zig-Zag step
                rotateLeft(p->pParent);
                rotateRight(p->pParent);
            } else {
                // Zig-Zag step
                rotateRight(p->pParent);
                rotateLeft(p->pParent);
            }
        }
    }

    void insert(int val) {
        Node* z = root;
        Node* p = nullptr;

        // Binary search tree insert
        while (z != nullptr) {
            p = z;
            if (val < z->val) z = z->pLeft;
            else z = z->pRight;
        }

        z = new Node(val);
        z->pParent = p;

        if (p == nullptr) {
            root = z;
        } else if (val < p->val) {
            p->pLeft = z;
        } else {
            p->pRight = z;
        }

        // Splay the newly inserted node
        splay(z);
    }

    bool search(int val) {
        Node* z = root;
        Node* last = nullptr;

        while (z != nullptr) {
            last = z;
            if (val == z->val) {
                splay(z);
                return true;
            } else if (val < z->val) {
                z = z->pLeft;
            } else {
                z = z->pRight;
            }
        }

        if (last != nullptr) {
            splay(last);
        }

        return false;
    }

    Node* remove(int val) {
        if (root == nullptr) return nullptr;

        // Search for the node to splay
        if (!search(val)) return nullptr;

        // Root should now be the node to remove
        Node* nodeToRemove = root;

        if (nodeToRemove->val != val) return nullptr;

        Node* leftSubtree = root->pLeft;
        Node* rightSubtree = root->pRight;

        if (leftSubtree != nullptr) leftSubtree->pParent = nullptr;
        if (rightSubtree != nullptr) rightSubtree->pParent = nullptr;

        delete root; // Remove the root

        if (leftSubtree == nullptr) {
            root = rightSubtree;
        } else {
            root = leftSubtree;
            Node* maxLeft = leftSubtree;
            while (maxLeft->pRight != nullptr) {
                maxLeft = maxLeft->pRight;
            }
            splay(maxLeft);
            maxLeft->pRight = rightSubtree;
            if (rightSubtree != nullptr) rightSubtree->pParent = maxLeft;
        }

        return nodeToRemove;
    }
};

int main() {
    SplayTree tree;
    int query;
    cin >> query;
    for (int i = 0; i < query; i++) {
        string op;
        int val;
        cin >> op >> val;
        if (op == "insert")
            tree.insert(val);
        else if (op == "remove")
            cout << (tree.remove(val) != nullptr ? "removed" : "not found") << '\n';
        else if (op == "search")
            cout << (tree.search(val) ? "found" : "not found") << '\n';
        else if (op == "print")
            tree.printPreorder();
    }
    tree.printBinaryTree();
    return 0;
}
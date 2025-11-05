#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
    int *keys;      // An array of keys
    int t;          // Minimum degree (defines the range for number of keys)
    BTreeNode **C;  // An array of child pointers
    int n;          // Current number of keys
    bool leaf;      // Is true when node is leaf. Otherwise false

public:
    BTreeNode(int t, bool leaf);

    // Function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // Function to search a key in the subtree rooted with this node
    BTreeNode *search(int k);

    // A utility function to insert a new key in the subtree rooted with this node
    void insertNonFull(int k);

    // A utility function to split the child y of this node
    void splitChild(int i, BTreeNode *y);

    // A utility function to remove a key from the subtree rooted with this node
    void remove(int k);

    // A function to remove the key present in idx-th position in this node which is a leaf
    void removeFromLeaf(int idx);

    // A function to remove the key present in idx-th position in this node which is a non-leaf
    void removeFromNonLeaf(int idx);

    // A utility function to get the predecessor of the key- where the key is present in the idx-th position in the node
    int getPred(int idx);

    // A utility function to get the successor of the key- where the key is present in the idx-th position in the node
    int getSucc(int idx);

    // A utility function to fill up the child node present in the idx-th position in the C[] array if that child has less than t-1 keys
    void fill(int idx);

    // A utility function to borrow a key from the C[idx-1]-th node and place it in C[idx]th node
    void borrowFromPrev(int idx);

    // A utility function to borrow a key from the C[idx+1]-th node and place it in C[idx]th node
    void borrowFromNext(int idx);

    // A utility function to merge idx-th child of the node with (idx+1)th child of the node
    void merge(int idx);

    // Make BTree a friend so that we can access private members of this class in BTree functions
    friend class BTree;
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    // Allocate memory for maximum number of possible keys and child pointers
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];

    // Initialize the number of keys as 0
    n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse() {
    // There are n keys and n+1 children, traverse through n keys and first n children
    int i;
    for (i = 0; i < n; i++) {
        // If this is not a leaf, then before printing keys[i], traverse the subtree rooted with child C[i]
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}

// Function to search a key in the subtree rooted with this node
BTreeNode *BTreeNode::search(int k) {
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;

    // If the key is not found here and this is a leaf node
    if (leaf == true)
        return nullptr;

    // Go to the appropriate child
    return C[i]->search(k);
}

// A utility function to insert a new key in the subtree rooted with this node
void BTreeNode::insertNonFull(int k) {
    // Initialize index as index of rightmost element
    int i = n - 1;

    // If this is a leaf node
    if (leaf == true) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    } else {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;

        // See if the found child is full
        if (C[i + 1]->n == 2 * t - 1) {
            // If the child is full, then split it
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i+1] goes up and C[i+1] is split into two
            // See which of the two is going to have the new key
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// A utility function to split the child y of this node
void BTreeNode::splitChild(int i, BTreeNode *y) {
    // Create a new node which is going to store (t-1) keys of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children of y to z
    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child, create space of new child
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    // Link the new child to this node
    C[i + 1] = z;

    // A key of y will move to this node. Find the location of new key and move all greater keys one space ahead
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // Copy the middle key of y to this node
    keys[i] = y->keys[t - 1];

    // Increment count of keys in this node
    n = n + 1;
}

// A utility function to remove a key from the subtree rooted with this node
void BTreeNode::remove(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;

    // The key to be removed is present in this node
    if (idx < n && keys[idx] == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        // If this node is a leaf node, then the key is not present in the tree
        if (leaf) {
            cout << "The key " << k << " is not in the tree\n";
            return;
        }

        // The key to be removed is present in the subtree rooted with this node
        // The flag indicates whether the key is present in the subtree rooted with the last child of this node
        bool flag = (idx == n);

        // If the child where the key is supposed to exist has less than t keys, we fill that child
        if (C[idx]->n < t)
            fill(idx);

        // If the last child has been merged, it must have been merged with the previous child and so we recurse on the (idx-1)th child.
        // Else, we recurse on the (idx)th child which now has at least t keys
        if (flag && idx > n)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
}

// A function to remove the key present in idx-th position in this node which is a leaf
void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    n--;
}

// A function to remove the key present in idx-th position in this node which is a non-leaf
void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];

    if (C[idx]->n >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    } else if (C[idx + 1]->n >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    } else {
        merge(idx);
        C[idx]->remove(k);
    }
}

// A utility function to get the predecessor of the key- where the key is present in the idx-th position in the node
int BTreeNode::getPred(int idx) {
    BTreeNode *cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

// A utility function to get the successor of the key- where the key is present in the idx-th position in the node
int BTreeNode::getSucc(int idx) {
    BTreeNode *cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

// A utility function to fill up the child node present in the idx-th position in the C[] array if that child has less than t-1 keys
void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);
    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

// A utility function to borrow a key from the C[idx-1]-th node and place it in C[idx]th node
void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

// A utility function to borrow a key from the C[idx+1]-th node and place it in C[idx]th node
void BTreeNode::borrowFromNext(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[child->n] = keys[idx];

    if (!(child->leaf))
        child->C[child->n + 1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

// A utility function to merge idx-th child of the node with (idx+1)th child of the node
void BTreeNode::merge(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
}

class BTree {
    BTreeNode *root; // Pointer to root node
    int t;           // Minimum degree

public:
    // Constructor (Initializes tree as empty)
    BTree(int t) {
        root = nullptr;
        this->t = t;
    }

    // Function to traverse the tree
    void traverse() {
        if (root != nullptr)
            root->traverse();
    }

    // Function to search a key in this tree
    BTreeNode *search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    // Function to insert a new key in this tree
    void insert(int k);

    // Function to remove a key in this tree
    void remove(int k);
};

// Function to insert a new key in this tree
void BTree::insert(int k) {
    // If tree is empty
    if (root == nullptr) {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k; // Insert key
        root->n = 1; // Update number of keys in root
    } else {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1) {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move a key to the new root
            s->splitChild(0, root);

            // New root has two children now. Decide which of the two children is going to have the new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        } else
            root->insertNonFull(k);
    }
}

// Function to remove a key in this tree
void BTree::remove(int k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(k);

    if (root->n == 0) {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->C[0];

        delete tmp;
    }
}

int main() {
    BTree t(3); // A B-Tree with minimum degree 3 (order 3)

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed tree is ";
    t.traverse();
    cout << endl;

    t.remove(6);
    cout << "Traversal of the tree after removing 6 ";
    t.traverse();
    cout << endl;

    t.remove(13);
    cout << "Traversal of the tree after removing 13 ";
    t.traverse();
    cout << endl;

    t.remove(7);
    cout << "Traversal of the tree after removing 7 ";
    t.traverse();
    cout << endl;

    t.remove(4);
    cout << "Traversal of the tree after removing 4 ";
    t.traverse();
    cout << endl;

    t.remove(2);
    cout << "Traversal of the tree after removing 2 ";
    t.traverse();
    cout << endl;

    t.remove(16);
    cout << "Traversal of the tree after removing 16 ";
    t.traverse();
    cout << endl;

    return 0;
}
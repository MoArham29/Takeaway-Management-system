// TreeNode.h
// One node of the binary search tree (used by Tree.h).
#pragma once                                   // Stops this header being included twice in one file

// ---------------------------------------------------------------------------
// TreeNode: one node in the tree. Holds a key, the stored item and two children.
// ---------------------------------------------------------------------------
template <typename T>                          // T is the type of item stored (e.g. Supplier*)
struct TreeNode {
    int key;                                   // The value the tree is ordered by (supplier ID)
    T data;                                    // The item stored in this node
    TreeNode* left;                            // Pointer to the child with a smaller key
    TreeNode* right;                           // Pointer to the child with a larger key

    TreeNode(int k, T d)                       // Constructor: builds a node with no children
        : key(k), data(d), left(nullptr), right(nullptr) {}  // Initialiser list sets every member
};

// Tree.h
// Binary search tree template, adapted from the practical sessions.
// In this system it stores Supplier* objects, ordered by supplier ID (the key).
// The tree does NOT own the objects it stores: Takeaway creates and deletes them.
#pragma once                                   // Stops this header being included twice in one file

#include "TreeNode.h"                          // The node type the tree is built from

// ---------------------------------------------------------------------------
// Tree: the binary search tree itself.
// ---------------------------------------------------------------------------
template <typename T>                          // The same T as the nodes it holds
class Tree {
private:
    TreeNode<T>* root;                         // Pointer to the top node; nullptr when empty
    int count;                                 // Number of items currently in the tree

    // Recursive helper: inserts a new node below 'node' and returns the subtree's root
    TreeNode<T>* insert(TreeNode<T>* node, int key, T data) {
        if (node == nullptr) {                 // Reached an empty spot, so the new node goes here
            count++;                           // One more item in the tree
            return new TreeNode<T>(key, data); // Allocate the node on the heap and return it
        }
        if (key < node->key) {                 // Smaller keys belong in the left subtree
            node->left = insert(node->left, key, data);    // Insert on the left, relink the child
        } else if (key > node->key) {          // Larger keys belong in the right subtree
            node->right = insert(node->right, key, data);  // Insert on the right, relink the child
        }                                      // Equal key: duplicate, so nothing is inserted
        return node;                           // This subtree's root is unchanged
    }

    // Recursive helper: finds the node with this key, or returns nullptr
    TreeNode<T>* search(TreeNode<T>* node, int key) const {
        if (node == nullptr) return nullptr;   // Fell off the tree: the key is not present
        if (key == node->key) return node;     // Found the matching node
        if (key < node->key)                   // Key is smaller, so it can only be on the left
            return search(node->left, key);    // Continue searching the left subtree
        return search(node->right, key);       // Otherwise continue searching the right subtree
    }

    // Helper: returns the node with the smallest key in a subtree (its leftmost node)
    TreeNode<T>* findMin(TreeNode<T>* node) const {
        while (node->left != nullptr)          // Keep going left while there is a left child
            node = node->left;                 // Move one step left
        return node;                           // The leftmost node has the smallest key
    }

    // Recursive helper: removes the node with this key and returns the new subtree root
    TreeNode<T>* remove(TreeNode<T>* node, int key, bool& removed) {
        if (node == nullptr) return nullptr;   // Key not found in this subtree
        if (key < node->key) {                 // Target is in the left subtree
            node->left = remove(node->left, key, removed);   // Remove there and relink
        } else if (key > node->key) {          // Target is in the right subtree
            node->right = remove(node->right, key, removed); // Remove there and relink
        } else {                               // This is the node to remove
            removed = true;                    // Record that a node was found and removed
            if (node->left == nullptr) {       // Case 1/2: no left child
                TreeNode<T>* child = node->right;  // Keep the right child (may be nullptr)
                delete node;                   // Free the removed node's memory
                count--;                       // One fewer item in the tree
                return child;                  // The right child takes this node's place
            }
            if (node->right == nullptr) {      // Case 2: only a left child
                TreeNode<T>* child = node->left;   // Keep the left child
                delete node;                   // Free the removed node's memory
                count--;                       // One fewer item in the tree
                return child;                  // The left child takes this node's place
            }
            TreeNode<T>* successor = findMin(node->right);  // Case 3: two children, so find the next-largest key
            node->key = successor->key;        // Copy the successor's key into this node
            node->data = successor->data;      // Copy the successor's item into this node
            node->right = remove(node->right, successor->key, removed);  // Delete the successor from the right subtree
        }
        return node;                           // Return this subtree's (possibly unchanged) root
    }

    // Recursive helper: visits nodes in key order (left, node, right)
    void inOrder(TreeNode<T>* node, void (*visit)(T)) const {
        if (node == nullptr) return;           // Empty subtree: nothing to visit
        inOrder(node->left, visit);            // Visit all smaller keys first
        visit(node->data);                     // Call the function pointer on this node's item
        inOrder(node->right, visit);           // Then visit all larger keys
    }

    // Recursive helper: deletes every node in a subtree (children before parent)
    void destroy(TreeNode<T>* node) {
        if (node == nullptr) return;           // Nothing to delete
        destroy(node->left);                   // Delete the left subtree first
        destroy(node->right);                  // Then the right subtree
        delete node;                           // Finally free this node
    }

public:
    Tree() : root(nullptr), count(0) {}        // Constructor: starts as an empty tree

    ~Tree() {                                  // Destructor: frees every node when the tree is destroyed
        destroy(root);                         // Delete all nodes (not the items they point to)
    }

    Tree(const Tree&) = delete;                // Copying disabled: two trees must not share nodes
    Tree& operator=(const Tree&) = delete;     // Assignment disabled for the same reason

    void insert(int key, T data) {             // Public insert: adds an item under the given key
        root = insert(root, key, data);        // Start at the root; root may change if tree was empty
    }

    T search(int key) const {                  // Public search: returns the item, or nullptr if missing
        TreeNode<T>* node = search(root, key); // Look for the node from the root down
        return node ? node->data : nullptr;    // Return its item if found, otherwise nullptr
    }

    bool remove(int key) {                     // Public remove: returns true if a node was removed
        bool removed = false;                  // Assume nothing removed until the helper says so
        root = remove(root, key, removed);     // Remove from the root down; root may change
        return removed;                        // Tell the caller whether the key was found
    }

    void inOrder(void (*visit)(T)) const {     // Public traversal: calls 'visit' on every item in key order
        inOrder(root, visit);                  // Start the recursive walk at the root
    }

    int size() const { return count; }         // Returns how many items are stored
    bool isEmpty() const { return root == nullptr; }  // True when the tree has no nodes
};
// BinaryTree.h
// A binary search tree, adapted from the Session 15 practical.
// Items are kept sorted by their number, so they can be found quickly.
// Used to store Suppliers and StockItems. The tree deletes its items when it is destroyed.
#pragma once                                   // Only include this file once

#include "Node.h"                              // The tree is made of Nodes

template <class T>                             // T is the type of item stored (must be a pointer)
class BinaryTree {
private:
    Node<T>* root;                             // The top node of the tree (empty if the tree is empty)
    int count;                                 // How many items are in the tree

    void DisplayInOrder(Node<T>* localRoot) const {     // Shows every item below this node, smallest number first
        if (localRoot != nullptr) {                     // Stop when there is no node here
            DisplayInOrder(localRoot->leftChild);       // First show everything with a smaller number
            localRoot->data->Display();                 // Then show this item
            DisplayInOrder(localRoot->rightChild);      // Then show everything with a bigger number
        }
    }

    void InOrder(Node<T>* localRoot, void (*visit)(T)) const {  // Same walk, but runs the given function on each item
        if (localRoot != nullptr) {                     // Stop when there is no node here
            InOrder(localRoot->leftChild, visit);       // First the smaller numbers
            visit(localRoot->data);                     // Run the function on this item
            InOrder(localRoot->rightChild, visit);      // Then the bigger numbers
        }
    }

    void DeleteAll(Node<T>* localRoot) {                // Deletes every node and item below this node
        if (localRoot != nullptr) {                     // Stop when there is no node here
            DeleteAll(localRoot->leftChild);            // Delete everything on the left
            DeleteAll(localRoot->rightChild);           // Delete everything on the right
            delete localRoot->data;                     // Delete the item in this node
            delete localRoot;                           // Delete the node itself
        }
    }

public:
    BinaryTree() : root(nullptr), count(0) {}  // A new tree starts empty

    ~BinaryTree() {                            // When the tree is destroyed...
        DeleteAll(root);                       // ...delete every node and item, starting from the top
    }

    BinaryTree(const BinaryTree&) = delete;    // Stop the tree being copied (two copies would delete the same items)
    BinaryTree& operator=(const BinaryTree&) = delete;  // Stop the tree being assigned for the same reason

    bool IsEmpty() const {                     // Is the tree empty?
        return (root == nullptr);              // It is empty if there is no top node
    }

    int Count() const {                        // How many items are in the tree?
        return count;                          // Give back the running total
    }

    bool Insert(int id, T newData) {           // Adds an item. Gives back false if the number is already used
        Node<T>* newNode = new Node<T>(id, newData);    // Make a new node for the item
        if (root == nullptr) {                 // If the tree is empty...
            root = newNode;                    // ...the new node becomes the top node
            count++;                           // One more item
            return true;                       // Added
        }
        Node<T>* current = root;               // Otherwise start at the top
        while (true) {                         // Keep going down until a free space is found
            if (id < current->id) {            // Smaller number: go left
                if (current->leftChild == nullptr) {    // Is the left space free?
                    current->leftChild = newNode;       // Put the new node there
                    count++;                   // One more item
                    return true;               // Added
                }
                current = current->leftChild;  // Not free, so move down to the left
            } else if (id > current->id) {     // Bigger number: go right
                if (current->rightChild == nullptr) {   // Is the right space free?
                    current->rightChild = newNode;      // Put the new node there
                    count++;                   // One more item
                    return true;               // Added
                }
                current = current->rightChild; // Not free, so move down to the right
            } else {                           // Same number already in the tree
                delete newNode;                // Throw away the unused node
                return false;                  // Not added
            }
        }
    }

    T Find(int id) const {                     // Finds the item with this number (empty if not found)
        Node<T>* current = root;               // Start at the top
        while (current != nullptr) {           // Keep going until we run out of nodes
            if (id == current->id)             // Is this the one?
                return current->data;          // Yes: give back the item
            else if (id < current->id)         // Looking for a smaller number?
                current = current->leftChild;  // Go left
            else                               // Looking for a bigger number?
                current = current->rightChild; // Go right
        }
        return nullptr;                        // Not found
    }

    bool Delete(int id) {                      // Removes the item with this number. Gives back false if not found
        Node<T>* current = root;               // The node we are checking
        Node<T>* parent = nullptr;             // The node above it
        while (current != nullptr && current->id != id) {   // Search for the node, remembering the one above
            parent = current;                  // Move the "above" marker down
            if (id < current->id)              // Smaller number: go left
                current = current->leftChild;
            else                               // Bigger number: go right
                current = current->rightChild;
        }
        if (current == nullptr)                // Not found
            return false;                      // Nothing removed

        delete current->data;                  // Delete the item stored in this node

        if (current->leftChild != nullptr && current->rightChild != nullptr) {  // Case 3: the node has two children
            Node<T>* successorParent = current;         // Find the next biggest number (the successor)...
            Node<T>* successor = current->rightChild;   // ...it is one step right...
            while (successor->leftChild != nullptr) {   // ...then as far left as possible
                successorParent = successor;            // Move the "above" marker down
                successor = successor->leftChild;       // Move left
            }
            current->id = successor->id;       // Copy the successor's number into this node
            current->data = successor->data;   // Copy the successor's item into this node
            if (successorParent == current)    // If the successor was directly to the right...
                successorParent->rightChild = successor->rightChild;    // ...skip over it on the right
            else                               // Otherwise it was further down on the left...
                successorParent->leftChild = successor->rightChild;     // ...so skip over it on the left
            delete successor;                  // Delete the successor's old node (its item has moved)
            count--;                           // One less item
            return true;                       // Removed
        }

        Node<T>* child = (current->leftChild != nullptr) ? current->leftChild : current->rightChild;  // Cases 1 and 2: keep the only child (or nothing)
        if (parent == nullptr)                 // If we are removing the top node...
            root = child;                      // ...its child becomes the new top
        else if (parent->leftChild == current) // If it was on the left of the node above...
            parent->leftChild = child;         // ...link the child there instead
        else                                   // If it was on the right...
            parent->rightChild = child;        // ...link the child there instead
        delete current;                        // Delete the removed node
        count--;                               // One less item
        return true;                           // Removed
    }

    void DisplayInOrder() const {              // Shows every item, smallest number first
        DisplayInOrder(root);                  // Start the walk at the top
    }

    void InOrder(void (*visit)(T)) const {     // Runs the given function on every item, smallest number first
        InOrder(root, visit);                  // Start the walk at the top
    }
};
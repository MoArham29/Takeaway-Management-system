// Node.h
// One box (node) in the tree. It holds an item and links to two smaller trees below it.
#pragma once                                   // Only include this file once

template <class T>                             // T is the type of item stored (for example Supplier*)
class Node {
public:
    int id;                                    // The item's number, used to decide where it goes in the tree
    T data;                                    // The item itself
    Node* leftChild;                           // Link to the node with a smaller number (empty if none)
    Node* rightChild;                          // Link to the node with a bigger number (empty if none)

    Node(int id, T data)                       // Builds a new node with no children yet
        : id(id), data(data), leftChild(nullptr), rightChild(nullptr) {}  // Store the number and item, children start empty
};
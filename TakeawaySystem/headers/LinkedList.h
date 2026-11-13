// LinkedList.h
// Singly linked list template, adapted from the practical sessions.
// In this system it stores Delivery* and DailyReport* objects in the order they happen.
// The list does NOT own the objects it stores: Takeaway creates and deletes them.
#pragma once                                   // Stops this header being included twice in one file

#include "ListNode.h"                          // The node type the list is built from

// ---------------------------------------------------------------------------
// LinkedList: the list itself, with head and tail pointers.
// ---------------------------------------------------------------------------
template <typename T>                          // The same T as the nodes it holds
class LinkedList {
private:
    ListNode<T>* head;                         // Pointer to the first node; nullptr when empty
    ListNode<T>* tail;                         // Pointer to the last node, so append is O(1)
    int count;                                 // Number of items currently in the list

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}  // Constructor: starts empty

    ~LinkedList() {                            // Destructor: frees every node
        ListNode<T>* current = head;           // Start at the first node
        while (current != nullptr) {           // Loop until the end of the list
            ListNode<T>* nextNode = current->next;  // Remember the next node before deleting
            delete current;                    // Free this node (not the item it points to)
            current = nextNode;                // Move on to the remembered next node
        }
    }

    LinkedList(const LinkedList&) = delete;    // Copying disabled: two lists must not share nodes
    LinkedList& operator=(const LinkedList&) = delete;  // Assignment disabled for the same reason

    void append(T data) {                      // Adds an item to the end of the list
        ListNode<T>* node = new ListNode<T>(data);  // Allocate a new node on the heap
        if (head == nullptr) {                 // List is empty
            head = node;                       // The new node is the first node
            tail = node;                       // ...and also the last node
        } else {                               // List already has nodes
            tail->next = node;                 // Link the old last node to the new node
            tail = node;                       // The new node is now the last node
        }
        count++;                               // One more item in the list
    }

    bool contains(T data) const {              // Returns true if this exact item is in the list
        ListNode<T>* current = head;           // Start at the first node
        while (current != nullptr) {           // Check every node in turn
            if (current->data == data)         // Compare the stored item with the one wanted
                return true;                   // Found it
            current = current->next;           // Move to the next node
        }
        return false;                          // Reached the end without finding it
    }

    T find(bool (*match)(T, int), int value) const {  // Returns the first item where match(item, value) is true
        ListNode<T>* current = head;           // Start at the first node
        while (current != nullptr) {           // Check every node in turn
            if (match(current->data, value))   // Call the function pointer to test this item
                return current->data;          // Return the first matching item
            current = current->next;           // Move to the next node
        }
        return nullptr;                        // No item matched
    }

    bool remove(T data) {                      // Removes the node holding this item; true if removed
        ListNode<T>* current = head;           // Node being checked
        ListNode<T>* previous = nullptr;       // Node before 'current' (none at the start)
        while (current != nullptr) {           // Walk the list
            if (current->data == data) {       // Found the node to remove
                if (previous == nullptr)       // It is the first node
                    head = current->next;      // The second node becomes the head
                else                           // It is further along the list
                    previous->next = current->next;  // Bypass it by linking previous to next
                if (current == tail)           // It was the last node
                    tail = previous;           // The previous node becomes the tail
                delete current;                // Free the removed node
                count--;                       // One fewer item in the list
                return true;                   // Report success
            }
            previous = current;                // Step 'previous' forward
            current = current->next;           // Step 'current' forward
        }
        return false;                          // Item was not in the list
    }

    T get(int index) const {                   // Returns the item at a position (0 = first), or nullptr
        if (index < 0 || index >= count)       // Position outside the list
            return nullptr;                    // Nothing to return
        ListNode<T>* current = head;           // Start at the first node
        for (int i = 0; i < index; i++)        // Step forward 'index' times
            current = current->next;           // Move to the next node
        return current->data;                  // Return the item at that position
    }

    void traverse(void (*visit)(T)) const {    // Calls 'visit' on every item, first to last
        ListNode<T>* current = head;           // Start at the first node
        while (current != nullptr) {           // Until the end of the list
            visit(current->data);              // Call the function pointer on this item
            current = current->next;           // Move to the next node
        }
    }

    int size() const { return count; }         // Returns how many items are stored
    bool isEmpty() const { return head == nullptr; }  // True when the list has no nodes
};
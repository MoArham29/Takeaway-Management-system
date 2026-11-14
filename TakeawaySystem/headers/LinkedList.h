// LinkedList.h
// A linked list, adapted from the Session 13 and 17 practicals.
// New items go on the front, so the newest is always first (like a bank statement).
// Used to store every Transaction. The list deletes its items when it is destroyed.
#pragma once                                   // Only include this file once

#include "Link.h"                              // The list is made of Links

template <class T>                             // T is the type of item stored (must be a pointer)
class LinkedList {
private:
    Link<T>* first;                            // The first link (empty if the list is empty)

public:
    LinkedList() : first(nullptr) {}           // A new list starts empty

    ~LinkedList() {                            // When the list is destroyed...
        while (!IsEmpty()) {                   // ...keep going until it is empty
            Link<T>* link = Delete();          // Take the first link off the list
            delete link->data;                 // Delete the item it held
            delete link;                       // Delete the link itself
        }
    }

    LinkedList(const LinkedList&) = delete;    // Stop the list being copied (two copies would delete the same items)
    LinkedList& operator=(const LinkedList&) = delete;  // Stop the list being assigned for the same reason

    bool IsEmpty() const {                     // Is the list empty?
        return (first == nullptr);             // It is empty if there is no first link
    }

    void Insert(Link<T>* newLink) {            // Adds a link to the front of the list
        newLink->next = first;                 // The new link points to the old first link
        first = newLink;                       // The new link is now first
    }

    Link<T>* Find(int key) const {             // Finds the link with this number (empty if not found)
        Link<T>* current = first;              // Start at the first link
        while (current != nullptr) {           // Check every link in turn
            if (current->key == key)           // Is this the one?
                return current;                // Yes: give it back
            current = current->next;           // No: move to the next link
        }
        return nullptr;                        // Not found
    }

    Link<T>* Delete() {                        // Takes the first link off the list and gives it back
        Link<T>* temp = first;                 // Remember the first link
        first = first->next;                   // The second link becomes first
        return temp;                           // Give back the removed link
    }

    Link<T>* Delete(int key) {                 // Takes the link with this number off the list (empty if not found)
        Link<T>* current = first;              // The link we are checking
        Link<T>* previous = nullptr;           // The link before it
        while (current != nullptr && current->key != key) {  // Search, remembering the link before
            previous = current;                // Move "previous" along
            current = current->next;           // Move "current" along
        }
        if (current == nullptr)                // Not found
            return nullptr;                    // Nothing removed
        if (previous == nullptr)               // If it was the first link...
            first = current->next;             // ...the next one becomes first
        else                                   // Otherwise...
            previous->next = current->next;    // ...link around it
        return current;                        // Give back the removed link
    }

    int Count() const {                        // How many links are in the list?
        int total = 0;                         // Start counting at zero
        Link<T>* current = first;              // Start at the first link
        while (current != nullptr) {           // Until the end of the list
            total++;                           // Count this link
            current = current->next;           // Move to the next link
        }
        return total;                          // Give back the total
    }

    void Display() const {                     // Shows every item, newest first
        Link<T>* current = first;              // Start at the first link
        while (current != nullptr) {           // Until the end of the list
            current->Display();                // Show this item
            current = current->next;           // Move to the next link
        }
    }
};
// Link.h
// One link in the linked list. It holds an item and points to the next link.
#pragma once                                   // Only include this file once

template <class T>                             // T is the type of item stored (for example Transaction*)
class Link {
public:
    int key;                                   // The item's number, used to find it later
    T data;                                    // The item itself
    Link* next;                                // The next link in the list (empty at the end)

    Link(int key, T data)                      // Builds a new link that does not point anywhere yet
        : key(key), data(data), next(nullptr) {}  // Store the number and item, no next link yet

    T GetData() const {                        // Gives back the item
        return data;                           // Return the stored item
    }

    void Display() const {                     // Shows the item
        data->Display();                       // Ask the item to show itself
    }
};
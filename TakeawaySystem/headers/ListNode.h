// ListNode.h
// One node of the singly linked list (used by LinkedList.h).
#pragma once                                   // Stops this header being included twice in one file

// ---------------------------------------------------------------------------
// ListNode: one node in the list. Holds an item and a pointer to the next node.
// ---------------------------------------------------------------------------
template <typename T>                          // T is the type of item stored (e.g. Delivery*)
struct ListNode {
    T data;                                    // The item stored in this node
    ListNode* next;                            // Pointer to the following node; nullptr at the end

    ListNode(T d) : data(d), next(nullptr) {}  // Constructor: stores the item, no next node yet
};
// main.cpp
// Step 2 test: checks the tree and the list work before the real classes are written.
#include <iostream>
#include <string>
#include "BinaryTree.h"
#include "LinkedList.h"

// A simple test item. The real program will store suppliers, stock and transactions instead.
class TestItem {
public:
    int number;
    std::string name;
    TestItem(int number, std::string name) : number(number), name(name) {}
    ~TestItem() { std::cout << "  [deleted] " << name << std::endl; }
    void Display() const { std::cout << "  " << number << ": " << name << std::endl; }
};

// Used to test the tree's InOrder function, which takes a function pointer
void shout(TestItem* item) {
    std::cout << "  Visiting " << item->name << "!" << std::endl;
}

int main() {
    std::cout << "=== Tree ===" << std::endl;
    BinaryTree<TestItem*>* tree = new BinaryTree<TestItem*>();
    tree->Insert(3, new TestItem(3, "Chicken"));
    tree->Insert(1, new TestItem(1, "Beef"));
    tree->Insert(5, new TestItem(5, "Chips"));
    tree->Insert(2, new TestItem(2, "Buns"));
    tree->Insert(4, new TestItem(4, "Lettuce"));
    std::cout << "Items: " << tree->Count() << " (added as 3,1,5,2,4 but shown in order)" << std::endl;
    tree->DisplayInOrder();
    std::cout << "Find 5: " << tree->Find(5)->name << std::endl;
    std::cout << "Find 9: " << (tree->Find(9) == nullptr ? "not found" : "found") << std::endl;
    std::cout << "Delete 3 (has two children):" << std::endl;
    tree->Delete(3);
    tree->DisplayInOrder();
    std::cout << "InOrder with a function pointer:" << std::endl;
    tree->InOrder(shout);

    std::cout << "\n=== Linked list ===" << std::endl;
    LinkedList<TestItem*>* list = new LinkedList<TestItem*>();
    list->Insert(new Link<TestItem*>(1, new TestItem(1, "Monday sales")));
    list->Insert(new Link<TestItem*>(2, new TestItem(2, "Tuesday sales")));
    list->Insert(new Link<TestItem*>(3, new TestItem(3, "Chicken purchase")));
    std::cout << "Links: " << list->Count() << " (newest first)" << std::endl;
    list->Display();
    std::cout << "Find 2: ";
    list->Find(2)->Display();
    Link<TestItem*>* removed = list->Delete(2);
    std::cout << "Removed link 2:" << std::endl;
    delete removed->GetData();
    delete removed;
    list->Display();

    std::cout << "\n=== Cleaning up (the tree and list delete their own items) ===" << std::endl;
    delete list;
    delete tree;
    return 0;
}
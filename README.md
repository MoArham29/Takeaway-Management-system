# Takeaway Management System
COM6023 Advanced Programming - CW1.

A back-office system for a takeaway: suppliers, stock control with nightly counts and
order lists, daily cash/card sales, purchases, expenses, a running balance and weekly reports.

## Run on macOS (VS Code)
1. Install the compiler once: `xcode-select --install`
2. Open this folder in VS Code and install the **C/C++** extension (Microsoft).
3. Press **Cmd+Shift+B**, then click in the terminal to type menu choices.

Or in Terminal from this folder:
`mkdir -p build && clang++ -std=c++17 -Wall -I TakeawaySystem/headers TakeawaySystem/src/*.cpp TakeawaySystem/main.cpp -o build/takeaway && ./build/takeaway`

Menu option 17 runs a full two-week demo of every feature.

## Layout
- `TakeawaySystem/headers` - all .h files
- `TakeawaySystem/src` - all .cpp files
- `TakeawaySystem/main.cpp` - the interactive menu
- `Node.h`, `BinaryTree.h`, `Link.h`, `LinkedList.h` are templates, so they are header-only.

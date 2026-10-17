// Lab 6, Part 2: Doubly linked list and Floyd cycle detection. C++17.
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

struct Node {
    int data;
    Node* prev = nullptr;
    Node* next = nullptr;
    explicit Node(int value) : data(value) {}
};

bool isCircularTwoPointer(const Node* head) {
    // TODO: detect any cycle reachable through next pointers using Floyd's
    // slow/fast pointers. Empty/linear chains: false; any cycle: true.
    // Do not modify nodes. O(n) time and O(1) auxiliary space.
    (void)head;
    throw std::logic_error("TODO: isCircularTwoPointer");
}

enum class DeleteResult { removed, invalid_or_empty, out_of_bounds };

class DoublyLinkedList {
    Node* head_ = nullptr;
    Node* tail_ = nullptr;

public:
    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    ~DoublyLinkedList() {
        while (head_) {
            Node* old = head_;
            head_ = head_->next;
            delete old;
        }
    }

    void addFirst(int data) {
        // TODO: prepend; maintain head_, tail_, prev and next. O(1).
        (void)data;
        throw std::logic_error("TODO: addFirst");
    }
    void append(int data) {
        // TODO: append using tail_, including an empty list. O(1).
        (void)data;
        throw std::logic_error("TODO: append");
    }
    void insert(int data, int pos) {
        // TODO: pos <= 0 prepends; pos >= length appends. O(n).
        (void)data; (void)pos;
        throw std::logic_error("TODO: insert");
    }
    DeleteResult deleteAtIndex(int index) {
        // TODO: negative index OR empty list -> invalid_or_empty;
        // nonnegative index >= length in nonempty list -> out_of_bounds;
        // otherwise unlink/delete that node and return removed. O(n).
        (void)index;
        throw std::logic_error("TODO: deleteAtIndex");
    }
    const Node* search(int data) const {
        // TODO: first matching node or nullptr. O(n).
        (void)data;
        throw std::logic_error("TODO: search");
    }
    bool isCircularTwoPointer() const {
        return ::isCircularTwoPointer(head_);
    }
    void display() const {
        std::cout << "Doubly Linked List: ";
        for (const Node* p = head_; p; p = p->next)
            std::cout << p->data << " <-> ";
        std::cout << "NULL\n";
    }
    void displayReverse() const {
        std::cout << "Reverse Doubly Linked List: ";
        for (const Node* p = tail_; p; p = p->prev)
            std::cout << p->data << " <-> ";
        std::cout << "NULL\n";
    }
};

// Supplied isolated test fixture. It does not change the student's DLL.
// Ownership is independent of next/prev, so even a cyclic fixture is freed.
bool runCycleTest(int n, int entry) {
    std::vector<std::unique_ptr<Node>> nodes;
    nodes.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        int value = 0;
        if (!(std::cin >> value)) throw std::runtime_error("Invalid input");
        nodes.push_back(std::make_unique<Node>(value));
    }
    for (int i = 1; i < n; ++i) {
        nodes[i - 1]->next = nodes[i].get();
        nodes[i]->prev = nodes[i - 1].get();
    }
    if (n > 0 && entry >= 0) nodes.back()->next = nodes[entry].get();
    // An internal-entry cycle is a next-pointer graph, not a valid circular DLL.
    return isCircularTwoPointer(n == 0 ? nullptr : nodes.front().get());
}

int main() {
    int q = 0;
    if (!(std::cin >> q) || q < 0) return 1;
    DoublyLinkedList list;
    try {
        for (int i = 0; i < q; ++i) {
            std::string command;
            if (!(std::cin >> command)) return 1;
            if (command == "addFirst" || command == "append") {
                int x = 0;
                if (!(std::cin >> x)) return 1;
                if (command == "addFirst") list.addFirst(x);
                else list.append(x);
            } else if (command == "insert") {
                int x = 0, pos = 0;
                if (!(std::cin >> x >> pos)) return 1;
                list.insert(x, pos);
            } else if (command == "deleteAtIndex") {
                int index = 0;
                if (!(std::cin >> index)) return 1;
                const auto result = list.deleteAtIndex(index);
                if (result == DeleteResult::invalid_or_empty)
                    std::cout << "Invalid index or empty list.\n";
                else if (result == DeleteResult::out_of_bounds)
                    std::cout << "Index out of bounds.\n";
            } else if (command == "search") {
                int x = 0;
                if (!(std::cin >> x)) return 1;
                std::cout << (list.search(x) ? "Found\n" : "Not Found\n");
            } else if (command == "display") list.display();
            else if (command == "displayReverse") list.displayReverse();
            else if (command == "isCircular") {
                const bool cyclic = list.isCircularTwoPointer();
                std::cout << "Is the list circular (two-pointer check)? "
                          << (cyclic ? "Yes\n" : "No\n");
            } else if (command == "testCycle") {
                int n = 0, entry = -1;
                if (!(std::cin >> n >> entry) || n < 0 || n > 10000 ||
                    entry < -1 || entry >= n) return 1;
                const bool cyclic = runCycleTest(n, entry);
                std::cout << "Cycle detected: " << (cyclic ? "Yes\n" : "No\n");
            } else return 1;
        }
    } catch (const std::logic_error&) { return 2; }
      catch (const std::runtime_error&) { return 1; }
}

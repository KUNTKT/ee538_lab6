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
    // Detect any cycle reachable through next pointers using Floyd's
    // slow/fast pointers. Empty/linear chains: false; any cycle: true.
    // Do not modify nodes. O(n) time and O(1) auxiliary space.
    const Node* slow = head;
    const Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
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
        // Prepend; maintain head_, tail_, prev and next. O(1).
        Node* node = new Node(data);
        node->next = head_;
        if (head_) head_->prev = node;
        else tail_ = node;
        head_ = node;
    }
    void append(int data) {
        // Append using tail_, including an empty list. O(1).
        Node* node = new Node(data);
        node->prev = tail_;
        if (tail_) tail_->next = node;
        else head_ = node;
        tail_ = node;
    }
    void insert(int data, int pos) {
        // pos <= 0 prepends; pos >= length appends. O(n).
        if (pos <= 0 || !head_) {
            addFirst(data);
            return;
        }
        Node* cur = head_;
        int index = 0;
        while (cur && index < pos) {
            cur = cur->next;
            ++index;
        }
        if (!cur) {
            append(data);
            return;
        }
        Node* node = new Node(data);
        node->next = cur;
        node->prev = cur->prev;
        cur->prev->next = node;
        cur->prev = node;
    }
    DeleteResult deleteAtIndex(int index) {
        // Negative index OR empty list -> invalid_or_empty;
        // nonnegative index >= length in nonempty list -> out_of_bounds;
        // otherwise unlink/delete that node and return removed. O(n).
        if (index < 0 || !head_) return DeleteResult::invalid_or_empty;
        Node* cur = head_;
        int i = 0;
        while (cur && i < index) {
            cur = cur->next;
            ++i;
        }
        if (!cur) return DeleteResult::out_of_bounds;
        if (cur->prev) cur->prev->next = cur->next;
        else head_ = cur->next;
        if (cur->next) cur->next->prev = cur->prev;
        else tail_ = cur->prev;
        delete cur;
        return DeleteResult::removed;
    }
    const Node* search(int data) const {
        // First matching node or nullptr. O(n).
        for (const Node* node = head_; node; node = node->next) {
            if (node->data == data) return node;
        }
        return nullptr;
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

// Lab 6, Part 1: Singly linked list. C++17.
// Complete the six TODO functions. Keep the supplied driver and formatting.
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

struct Node {
    int data;
    Node* next = nullptr;
    explicit Node(int value) : data(value) {}
};

class LinkedList {
    Node* head_ = nullptr;

public:
    LinkedList() = default;
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
    ~LinkedList() {
        while (head_) {
            Node* old = head_;
            head_ = head_->next;
            delete old;
        }
    }

    bool isEmpty() const { return head_ == nullptr; }

    void addFirst(int data) {
        // TODO: insert one new node at the head. O(1).
        (void)data;
        throw std::logic_error("TODO: addFirst");
    }

    void append(int data) {
        // TODO: append one new node, including when the list is empty. O(n).
        (void)data;
        throw std::logic_error("TODO: append");
    }

    void insert(int data, int pos) {
        // TODO: pos <= 0 means prepend; pos >= length means append. O(n).
        (void)data; (void)pos;
        throw std::logic_error("TODO: insert");
    }

    bool deleteNode(int data) {
        // TODO: remove/delete only the first matching node. Return success.
        // Return false if no match, including an empty list. O(n).
        (void)data;
        throw std::logic_error("TODO: deleteNode");
    }

    const Node* search(int data) const {
        // TODO: return the first matching node or nullptr. O(n).
        (void)data;
        throw std::logic_error("TODO: search");
    }

    std::optional<int> pop() {
        // TODO: return/remove/delete the first node; nullopt if empty. O(1).
        // All int values, including -1, are valid data.
        throw std::logic_error("TODO: pop");
    }

    void display() const {
        std::cout << "Linked List: ";
        for (const Node* p = head_; p; p = p->next)
            std::cout << p->data << " -> ";
        std::cout << "NULL\n";
    }
};

int main() {
    int q = 0;
    if (!(std::cin >> q) || q < 0) return 1;
    LinkedList list;
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
            } else if (command == "delete") {
                int x = 0;
                if (!(std::cin >> x)) return 1;
                if (list.isEmpty()) std::cout << "List is empty.\n";
                else if (!list.deleteNode(x))
                    std::cout << "Value " << x << " not found in the list.\n";
            } else if (command == "search") {
                int x = 0;
                if (!(std::cin >> x)) return 1;
                std::cout << (list.search(x) ? "Found\n" : "Not Found\n");
            } else if (command == "pop") {
                const auto value = list.pop();
                if (value) std::cout << "Popped: " << *value << '\n';
                else std::cout << "List is empty. Cannot pop.\n";
            } else if (command == "display") {
                list.display();
            } else return 1;
        }
    } catch (const std::logic_error&) {
        return 2; // An unfinished TODO was called. No diagnostic on stdout.
    }
}

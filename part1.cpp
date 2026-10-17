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
        // Insert one new node at the head. O(1).
        Node* node = new Node(data);
        node->next = head_;
        head_ = node;
    }

    void append(int data) {
        // Append one new node, including when the list is empty. O(n).
        if (!head_) {
            addFirst(data);
            return;
        }
        Node* tail = head_;
        while (tail->next) tail = tail->next;
        tail->next = new Node(data);
    }

    void insert(int data, int pos) {
        // pos <= 0 means prepend; pos >= length means append. O(n).
        if (pos <= 0 || !head_) {
            addFirst(data);
            return;
        }
        Node* prev = head_;
        int index = 0;
        while (prev->next && index < pos - 1) {
            prev = prev->next;
            ++index;
        }
        if (!prev->next) {
            prev->next = new Node(data);
            return;
        }
        Node* node = new Node(data);
        node->next = prev->next;
        prev->next = node;
    }

    bool deleteNode(int data) {
        // Remove/delete only the first matching node. Return success.
        // Return false if no match, including an empty list. O(n).
        if (!head_) return false;
        if (head_->data == data) {
            Node* old = head_;
            head_ = head_->next;
            delete old;
            return true;
        }
        Node* prev = head_;
        while (prev->next && prev->next->data != data) prev = prev->next;
        if (!prev->next) return false;
        Node* old = prev->next;
        prev->next = old->next;
        delete old;
        return true;
    }

    const Node* search(int data) const {
        // Return the first matching node or nullptr. O(n).
        for (const Node* node = head_; node; node = node->next) {
            if (node->data == data) return node;
        }
        return nullptr;
    }

    std::optional<int> pop() {
        // Return/remove/delete the first node; nullopt if empty. O(1).
        // All int values, including -1, are valid data.
        if (!head_) return std::nullopt;
        Node* old = head_;
        const int value = old->data;
        head_ = head_->next;
        delete old;
        return value;
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

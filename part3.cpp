// Lab 6, Part 3: Circular linked FIFO queue, capacity 8. C++17.
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

struct Node {
    int data;
    Node* next = nullptr;
    explicit Node(int value) : data(value) {}
};

class CircularQueue {
    Node* tail_ = nullptr;
    int count_ = 0;

public:
    static constexpr int capacity = 8;
    CircularQueue() = default;
    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;
    ~CircularQueue() {
        if (!tail_) return;
        Node* current = tail_->next;
        tail_->next = nullptr; // Break the ring before linear cleanup.
        while (current) {
            Node* old = current;
            current = current->next;
            delete old;
        }
    }
    bool isEmpty() const { return count_ == 0; }
    bool isFull() const { return count_ == capacity; }
    int size() const { return count_; }

    bool enqueue(int data) {
        // TODO: if full, return false without changing the queue.
        // Otherwise allocate/link one node, update tail_ and count_, return true.
        // Empty queue: the new node points to itself. O(1).
        (void)data;
        throw std::logic_error("TODO: enqueue");
    }
    std::optional<int> dequeue() {
        // TODO: nullopt if empty; otherwise remove/delete tail_->next,
        // update tail_/count_, return the removed value. O(1).
        throw std::logic_error("TODO: dequeue");
    }
    std::optional<int> peek() const {
        // TODO: front value without modifying the queue; nullopt if empty.
        // -1 is valid data, not an empty-queue marker. O(1).
        throw std::logic_error("TODO: peek");
    }
    void display() const {
        if (!tail_) { std::cout << "Queue is empty.\n"; return; }
        std::cout << "Circular Queue: ";
        const Node* current = tail_->next;
        for (int i = 0; i < count_; ++i) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "(back to head)\n";
    }
};

int main() {
    int q = 0;
    if (!(std::cin >> q) || q < 0) return 1;
    CircularQueue queue;
    try {
        for (int i = 0; i < q; ++i) {
            std::string command;
            if (!(std::cin >> command)) return 1;
            if (command == "enqueue") {
                int x = 0;
                if (!(std::cin >> x)) return 1;
                if (queue.enqueue(x))
                    std::cout << "Enqueued: " << x << " (size: " << queue.size() << ")\n";
                else std::cout << "Queue is full. Cannot enqueue " << x << ".\n";
            } else if (command == "dequeue") {
                const auto value = queue.dequeue();
                if (value)
                    std::cout << "Dequeued: " << *value << " (size: " << queue.size() << ")\n";
                else std::cout << "Queue is empty. Cannot dequeue.\n";
            } else if (command == "peek") {
                const auto value = queue.peek();
                if (value) std::cout << "Front element: " << *value << '\n';
                else std::cout << "Queue is empty.\n";
            } else if (command == "display") queue.display();
            else return 1;
        }
    } catch (const std::logic_error&) { return 2; }
}


#ifndef OWNED_FORWARD_LIST_H
#define OWNED_FORWARD_LIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class OwnedForwardList {
   private:
    struct Node {
        T* data;
        Node* next;
        Node(T* ptr) : data(ptr), next(nullptr) {}
    };

    Node* head;
    std::size_t count;

    void copy_from(const OwnedForwardList& other) {
        head = nullptr;
        count = 0;
        Node** curr = &head;
        for (Node* it = other.head; it; it = it->next) {
            T* clone_ptr = it->data->clone();
            *curr = new Node(clone_ptr);
            curr = &((*curr)->next);
            ++count;
        }
    }

   public:
    OwnedForwardList() : head(nullptr), count(0) {}

    OwnedForwardList(const OwnedForwardList& other) { copy_from(other); }

    OwnedForwardList(OwnedForwardList&& other) noexcept : head(other.head), count(other.count) {
        other.head = nullptr;
        other.count = 0;
    }

    OwnedForwardList& operator=(const OwnedForwardList& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    OwnedForwardList& operator=(OwnedForwardList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            count = other.count;
            other.head = nullptr;
            other.count = 0;
        }
        return *this;
    }

    ~OwnedForwardList() { clear(); }

    void push_back(const T& obj) {
        T* ptr = obj.clone();
        Node* node = new Node(ptr);
        if (!head)
            head = node;
        else {
            Node* it = head;
            while (it->next) it = it->next;
            it->next = node;
        }
        ++count;
    }

    void remove_at(std::size_t index) {
        if (index >= count) throw std::out_of_range("Index out of range");
        Node* prev = nullptr;
        Node* it = head;
        for (std::size_t i = 0; i < index; ++i) {
            prev = it;
            it = it->next;
        }
        if (prev)
            prev->next = it->next;
        else
            head = it->next;
        delete it->data;
        delete it;
        --count;
    }

    void print_all(std::ostream& os) const {
        Node* it = head;
        std::size_t idx = 0;
        while (it) {
            os << "[" << idx++ << "] " << *it->data;
            it = it->next;
        }
    }

    void clear() {
        Node* it = head;
        while (it) {
            Node* next = it->next;
            delete it->data;
            delete it;
            it = next;
        }
        head = nullptr;
        count = 0;
    }

    std::size_t size() const { return count; }
};

#endif
#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template<typename T, class Compare = std::less<T>>
class priority_queue {
  private:
    struct node {
        T data;
        node *l, *r;
        node(const T &e) : data(e), l(nullptr), r(nullptr) {}
    };
    using node_ptr = node*;

    node_ptr _root; // the root of the heap
    size_t   _size; // the number of the elements

    // create a new node
    node_ptr _new_node(const T &e) {
        node_ptr p = new node(e);
        return p;
    }

    // delete a node
    void _delete_node(node_ptr p) {
        delete p;
    }

    // copy heap q to p
    void _copy_heap(node_ptr &p, const node_ptr &q) {
        if (q != nullptr) {
            p = _new_node(q->data);
            _copy_heap(p->l, q->l);
            _copy_heap(p->r, q->r);
        }
    }

    // delete heap
    void _delete_heap(const node_ptr &p) {
        if (p != nullptr) {
            _delete_heap(p->l);
            _delete_heap(p->r);
            _delete_node(p);
        }
    }

    // merge two heap
    node_ptr _merge_heap(node_ptr p, node_ptr q) {
        if (p == nullptr) return q;
        if (q == nullptr) return p;
        if (Compare()(p->data, q->data)) std::swap(p, q);
        p->r = _merge_heap(p->r, q);
        std::swap(p->l, p->r);
        return p;
    }

  public:
    /**
     * constructors
     */
    priority_queue() {
        _root = nullptr;
        _size = 0;
    }
    priority_queue(const priority_queue &other) {
        _copy_heap(_root, other._root);
        _size = other._size;
    }
    /**
     * deconstructor
     */
    ~priority_queue() {
        _delete_heap(_root);
    }
    /**
     * Assignment operator
     */
    priority_queue &operator=(const priority_queue &other) {
        if (this == &other) return *this;
        _delete_heap(_root);
        _copy_heap(_root, other._root);
        _size = other._size;
        return *this;
    }
    /**
     * get the top of the queue.
     * @return a reference of the top element.
     * throw container_is_empty if empty() returns true;
     */
    const T &top() const {
        if (empty()) throw container_is_empty();
        return _root->data;
    }
    /**
     * push new element to the priority queue.
     */
    void push(const T &e) {
        node_ptr tmp = _new_node(e);
        try {
            _root = _merge_heap(_root, tmp);
        } catch (...) {
            _delete_node(tmp);
            throw;
        }
        ++_size;
    }
    /**
     * delete the top element.
     * throw container_is_empty if empty() returns true;
     */
    void pop() {
        if (empty()) throw container_is_empty();
        node_ptr tmp = _root;
        _root = _merge_heap(_root->l, _root->r);
        _delete_node(tmp);
        --_size;
    }
    /**
     * return the number of the elements.
     */
    size_t size() const {
        return _size;
    }
    /**
     * check if the container has at least an element.
     * @return true if it is empty, false if it has at least an element.
     */
    bool empty() const {
        return _size == 0;
    }
    /**
     * merge two priority_queues with at most O(logn) complexity.
     * clear the other priority_queue.
     */
    void merge(priority_queue &other) {
        _root = _merge_heap(_root, other._root);
        _size += other._size;
        other._root = nullptr;
        other._size = 0;
    }
};

}

#endif

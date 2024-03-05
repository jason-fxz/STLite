#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <memory>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
T max(const T &x, const T &y) {
    return x > y ? x : y;
}

template<typename T>
class vector {
  private:
    static constexpr double MULTIPLIER = 2;
    T *_m_data;
    size_t _m_size;
    size_t _m_cap;
    std::allocator<T> _alloc;

  public:
    /**
     * TODO
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
    /**
     * you can see RandomAccessIterator at CppReference for help.
     */
    class const_iterator;
    class iterator {
        // The following code is written for the C++ type_traits library.
        // Type traits is a C++ feature for describing certain properties of a type.
        // For instance, for an iterator, iterator::value_type is the type that the
        // iterator points to.
        // STL algorithms and containers may use these type_traits (e.g. the following
        // typedef) to work properly. In particular, without the following code,
        // @code{std::sort(iter, iter1);} would not compile.
        // See these websites for more information:
        // https://en.cppreference.com/w/cpp/header/type_traits
        // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
        // About iterator_category: https://en.cppreference.com/w/cpp/iterator
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::output_iterator_tag;
        friend class vector;

      private:
        T *_m_ptr;
        const vector *const _vec;
        iterator(T *_ptr, const vector *__vec) : _m_ptr(_ptr), _vec(__vec) {}

      public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator operator+(const int &n) const {
            return iterator(_m_ptr + n, _vec);
        }
        iterator operator-(const int &n) const {
            return iterator(_m_ptr - n, _vec);
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            if (_vec != rhs._vec) throw invalid_iterator();
            return _m_ptr - rhs._m_ptr;
        }
        iterator &operator+=(const int &n) {
            _m_ptr += n;
            return *this;
        }
        iterator &operator-=(const int &n) {
            _m_ptr -= n;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ++_m_ptr;
            return tmp;
        }

        iterator &operator++() {
            ++_m_ptr;
            return *this;
        }

        iterator operator--(int) {
            auto tmp = *this;
            --_m_ptr;
            return tmp;
        }

        iterator &operator--() {
            --_m_ptr;
            return *this;
        }

        T &operator*() const {
            return *_m_ptr;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return _m_ptr == rhs._m_ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return _m_ptr == rhs._m_cptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return _m_ptr != rhs._m_ptr;
        }
        bool operator!=(const const_iterator &rhs) const {
            return _m_ptr != rhs._m_cptr;
        }
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     */
    class const_iterator {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::output_iterator_tag;

      private:
        /*TODO*/
        const T *_m_cptr;
        const vector *const _vec;
        const_iterator(const T *_ptr, const vector *__vec) : _m_cptr(_ptr), _vec(__vec) {}
        const_iterator(const iterator &other) : _m_cptr(other._m_ptr), _vec(other._vec) {}
        friend class vector;

      public:
        const_iterator operator+(const int &n) const {
            return const_iterator(_m_cptr + n, _vec);
        }
        const_iterator operator-(const int &n) const {
            return const_iterator(_m_cptr - n, _vec);
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const {
            if (_vec != rhs._vec) throw invalid_iterator();
            return _m_cptr - rhs._m_cptr;
        }
        const_iterator &operator+=(const int &n) {
            _m_cptr += n;
            return *this;
        }
        const_iterator &operator-=(const int &n) {
            _m_cptr -= n;
            return *this;
        }

        const_iterator operator++(int) {
            auto tmp = *this;
            ++_m_cptr;
            return tmp;
        }

        const_iterator &operator++() {
            ++_m_cptr;
            return *this;
        }

        const_iterator operator--(int) {
            auto tmp = *this;
            --_m_cptr;
            return tmp;
        }

        const_iterator &operator--() {
            --_m_cptr;
            return *this;
        }

        const T &operator*() const {
            return *_m_cptr;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return _m_cptr == rhs._m_ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return _m_cptr == rhs._m_cptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return _m_cptr != rhs._m_ptr;
        }
        bool operator!=(const const_iterator &rhs) const {
            return _m_cptr != rhs._m_cptr;
        }

    };
    /**
     * TODO Constructs
     * At least two: default constructor, copy constructor
     */
    vector() : _m_data(nullptr), _m_cap(0), _m_size(0) {}
    vector(const vector &other) {
        _m_data = _alloc.allocate(other._m_cap);
        _m_size = other._m_size;
        _m_cap = other._m_cap;
        for (int i = 0; i < _m_size; ++i) {
            std::construct_at(_m_data + i, std::as_const(other._m_data[i]));
        }
    }
    /**
     * TODO Destructor
     */
    ~vector() {
        clear();
    }
    /**
     * TODO Assignment operator
     */
    vector &operator=(const vector &other) {
        if (this == &other) return *this;
        clear();
        _m_data = _alloc.allocate(other._m_cap);
        _m_size = other._m_size;
        _m_cap = other._m_cap;
        for (int i = 0; i < _m_size; ++i) {
            std::construct_at(_m_data + i, std::as_const(other._m_data[i]));
        }
        return *this;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T &at(const size_t &pos) {
        if (pos < 0 || pos >= _m_size) throw index_out_of_bound();
        return _m_data[pos];
    }
    const T &at(const size_t &pos) const {
        if (pos < 0 || pos >= _m_size) throw index_out_of_bound();
        return _m_data[pos];
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    T &operator[](const size_t &pos) {
        return at(pos);
    }
    const T &operator[](const size_t &pos) const {
        return at(pos);
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T &front() const {
        if (_m_size == 0) throw container_is_empty();
        return _m_data[0];
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T &back() const {
        if (_m_size == 0) throw container_is_empty();
        return _m_data[_m_size - 1];
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return iterator(_m_data, this);
    }
    const_iterator cbegin() const {
        return const_iterator(_m_data, this);
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(_m_data + _m_size, this);
    }
    const_iterator cend() const {
        return const_iterator(_m_data + _m_size, this);
    }
    /**
     * checks whether the container is empty
     */
    bool empty() const {
        return _m_size == 0;
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return _m_size;
    }
    /**
     * returns the number of elements that can be held in currently allocated storage.
     */
    size_t capacity() const {
        return _m_cap;
    }
    /**
     * clears the contents
     */
    void clear() {
        if (_m_data == nullptr) return;
        for (int i = 0; i < _m_size; ++i) {
            std::destroy_at(_m_data + i);
        }
        _alloc.deallocate(_m_data, _m_cap);
        _m_data = nullptr;
        _m_size = 0;
        _m_cap = 0;
    }
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    iterator insert(iterator pos, const T &value) {
        return insert(pos - begin(), value);
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
    iterator insert(const size_t &ind, const T &value) {
        if (ind > _m_size) throw index_out_of_bound();
        _grow_capacity_until(_m_size + 1);
        for (size_t i = _m_size; i > ind; --i) {
            if (i == _m_size) {
                std::construct_at(_m_data + i, std::move_if_noexcept(_m_data[i - 1]));
            } else {
                _m_data[i] = std::move_if_noexcept(_m_data[i - 1]);
            }
        }
        if (ind == _m_size) {
            std::construct_at(_m_data + ind, value);
        } else {
            _m_data[ind] = value;
        }
        ++_m_size;
        return iterator(_m_data + ind, this);
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        return erase(pos - begin());
    }
    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind) {
        if (ind >= _m_size) throw index_out_of_bound();
        --_m_size;
        for (size_t i = ind; i < _m_size; ++i) {
            _m_data[i] = std::move_if_noexcept(_m_data[i + 1]);
        }
        std::destroy_at(_m_data + _m_size);
        _shrink_capacity();
        return iterator(_m_data + ind, this);
    }
    /**
     * adds an element to the end.
     */
    void push_back(const T &value) {
        _grow_capacity_until(_m_size + 1);
        std::construct_at(_m_data + _m_size, value);
        ++_m_size;
    }
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        if (_m_size == 0) throw container_is_empty();
        std::destroy_at(_m_data + _m_size - 1);
        --_m_size;
        _shrink_capacity();
    }

  private:
    void _grow_capacity_until(size_t n) {
        if (n <= _m_cap) return;
        n = max(n, size_t(_m_cap * MULTIPLIER));
        auto old_data = _m_data;
        _m_data = _alloc.allocate(n);
        if (old_data) {
            for (size_t i = 0; i < _m_size; ++i) {
                std::construct_at(_m_data + i, std::move_if_noexcept(old_data[i]));
            }
            for (size_t i = 0; i < _m_size; ++i) {
                std::destroy_at(old_data + i);
            }
            _alloc.deallocate(old_data, _m_cap);
        }
        _m_cap = n;
    }
    void _shrink_capacity() {
        if (_m_size * MULTIPLIER >= _m_cap) return ;
        int n = _m_cap / MULTIPLIER;
        auto old_data = _m_data;
        _m_data = _alloc.allocate(n);
        if (old_data) {
            for (size_t i = 0; i < _m_size; ++i) {
                std::construct_at(_m_data + i, std::move_if_noexcept(old_data[i]));
            }
            for (size_t i = 0; i < _m_size; ++i) {
                std::destroy_at(old_data + i);
            }
            _alloc.deallocate(old_data, _m_cap);
        }
        _m_cap = n;
    }

};


}

#endif

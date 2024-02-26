#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <deque>
#include <memory>
#include <utility>

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
    static constexpr double alpha = 2;
    T *m_data;
    size_t m_size;
    size_t m_cap;
    std::allocator<T> alloc;

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
        T *m_ptr;
        const vector *const _vec;
        iterator(T *_ptr, const vector *__vec) : m_ptr(_ptr), _vec(__vec) {}

      public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator operator+(const int &n) const {
            return iterator(m_ptr + n, _vec);
        }
        iterator operator-(const int &n) const {
            return iterator(m_ptr - n, _vec);
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            if (_vec != rhs._vec) throw invalid_iterator();
            return m_ptr - rhs.m_ptr;
        }
        iterator &operator+=(const int &n) {
            m_ptr += n;
            return *this;
        }
        iterator &operator-=(const int &n) {
            m_ptr -= n;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ++m_ptr;
            return tmp;
        }

        iterator &operator++() {
            ++m_ptr;
            return *this;
        }

        iterator operator--(int) {
            auto tmp = *this;
            --m_ptr;
            return tmp;
        }

        iterator &operator--() {
            --m_ptr;
            return *this;
        }

        T &operator*() const {
            return *m_ptr;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return m_ptr != rhs.m_ptr;
        }
        bool operator!=(const const_iterator &rhs) const {
            return m_ptr != rhs.m_ptr;
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
        const T *m_ptr;
        const vector *const _vec;
        const_iterator(const T *_ptr, const vector *__vec) : m_ptr(_ptr), _vec(__vec) {}
        const_iterator(const iterator &other) : m_ptr(other.m_ptr), _vec(other._vec) {}
        friend class vector;

      public:
        const_iterator operator+(const int &n) const {
            return const_iterator(m_ptr + n, _vec);
        }
        const_iterator operator-(const int &n) const {
            return const_iterator(m_ptr - n, _vec);
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const {
            if (_vec != rhs._vec) throw invalid_iterator();
            return m_ptr - rhs.m_ptr;
        }
        const_iterator &operator+=(const int &n) {
            m_ptr += n;
            return *this;
        }
        const_iterator &operator-=(const int &n) {
            m_ptr -= n;
            return *this;
        }

        const_iterator operator++(int) {
            auto tmp = *this;
            ++m_ptr;
            return tmp;
        }

        const_iterator &operator++() {
            ++m_ptr;
            return *this;
        }

        const_iterator operator--(int) {
            auto tmp = *this;
            --m_ptr;
            return tmp;
        }

        const_iterator &operator--() {
            --m_ptr;
            return *this;
        }

        const T &operator*() const {
            return *m_ptr;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator==(const const_iterator &rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {
            return m_ptr != rhs.m_ptr;
        }
        bool operator!=(const const_iterator &rhs) const {
            return m_ptr != rhs.m_ptr;
        }

    };
    /**
     * TODO Constructs
     * At least two: default constructor, copy constructor
     */
    vector() : m_data(nullptr), m_cap(0), m_size(0) {}
    vector(const vector &other) {
        m_data = alloc.allocate(other.m_cap);
        m_size = other.m_size;
        m_cap = other.m_cap;
        for (int i = 0; i < m_size; ++i) {
            std::construct_at(m_data + i, std::as_const(other.m_data[i]));
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
        m_data = alloc.allocate(other.m_cap);
        m_size = other.m_size;
        m_cap = other.m_cap;
        for (int i = 0; i < m_size; ++i) {
            std::construct_at(m_data + i, std::as_const(other.m_data[i]));
        }
        return *this;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T &at(const size_t &pos) {
        if (pos < 0 || pos >= m_size) throw index_out_of_bound();
        return m_data[pos];
    }
    const T &at(const size_t &pos) const {
        if (pos < 0 || pos >= m_size) throw index_out_of_bound();
        return m_data[pos];
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
        if (m_size == 0) throw container_is_empty();
        return m_data[0];
    }
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T &back() const {
        if (m_size == 0) throw container_is_empty();
        return m_data[m_size - 1];
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        return iterator(m_data, this);
    }
    const_iterator cbegin() const {
        return const_iterator(m_data, this);
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        return iterator(m_data + m_size, this);
    }
    const_iterator cend() const {
        return const_iterator(m_data + m_size, this);
    }
    /**
     * checks whether the container is empty
     */
    bool empty() const {
        return m_size == 0;
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return m_size;
    }
    /**
     * returns the number of elements that can be held in currently allocated storage.
     */
    size_t capacity() const {
        return m_cap;
    }
    /**
     * clears the contents
     */
    void clear() {
        if (m_data == nullptr) return;
        for (int i = 0; i < m_size; ++i) {
            std::destroy_at(m_data + i);
        }
        alloc.deallocate(m_data, m_cap);
        m_data = nullptr;
        m_size = 0;
        m_cap = 0;
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
		if (ind > m_size) throw index_out_of_bound();
		_grow_capacity_until(m_size + 1);
		for (size_t i = m_size; i > ind; --i) {
            if (i == m_size) {
                std::construct_at(m_data + i, std::move_if_noexcept(m_data[i - 1]));
            } else {
                m_data[i] = std::move_if_noexcept(m_data[i - 1]);
            } 
		}
        if (ind == m_size) {
            std::construct_at(m_data + ind, value);
        } else {
            m_data[ind] = value;
        }
		++m_size;
		return iterator(m_data + ind, this);
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
		if (ind >= m_size) throw index_out_of_bound();
		--m_size;
		for (size_t i = ind; i < m_size; ++i) {
            m_data[i] = std::move_if_noexcept(m_data[i + 1]);
		}
        std::destroy_at(m_data + m_size);
		_shrink_capacity();
		return iterator(m_data + ind, this);
	}
    /**
     * adds an element to the end.
     */
    void push_back(const T &value) {
		_grow_capacity_until(m_size + 1);
		std::construct_at(m_data + m_size, value);
		++m_size;
	}
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
		if (m_size == 0) throw container_is_empty();
		std::destroy_at(m_data + m_size - 1);
		--m_size;
		_shrink_capacity();
	}

  private:
    void _grow_capacity_until(size_t n) {
		if (n <= m_cap) return;
		n = max(n, size_t(m_cap * alpha));
		auto old_data = m_data;
		m_data = alloc.allocate(n);
		if (old_data) {
			for (size_t i = 0; i < m_size; ++i) {
                std::construct_at(m_data + i, std::move_if_noexcept(old_data[i]));
			}
            for (size_t i = 0; i < m_size; ++i) {
                std::destroy_at(old_data + i);
            }
			alloc.deallocate(old_data, m_cap);
		}
		m_cap = n;
	}
	void _shrink_capacity() {
		if (m_size * alpha >= m_cap) return ;
		int n = m_cap / alpha;
		auto old_data = m_data;
		m_data = alloc.allocate(n);
		if (old_data) {
			for (size_t i = 0; i < m_size; ++i) {
                std::construct_at(m_data + i, std::move_if_noexcept(old_data[i]));
			}
            for (size_t i = 0; i < m_size; ++i) {
                std::destroy_at(old_data + i);
            }
			alloc.deallocate(old_data, m_cap);
		}
		m_cap = n;
	}

};


}

#endif

#include <iterator>
#include <algorithm>
#include <type_traits>

#include "map.hpp"
#include <list>

namespace sjtu {

template <typename Tp>
concept iterator_type = requires {
    typename std::iterator_traits<Tp>::iterator_category;
    typename std::iterator_traits<Tp>::value_type;
    typename std::iterator_traits<Tp>::pointer;
    typename std::iterator_traits<Tp>::reference;
    typename std::iterator_traits<Tp>::difference_type;
};

template <typename _Iter>
void my_sort(_Iter __first, _Iter __last) {
    // For random access iterator, use std::sort.
    // For sjtu::map iterator, return directly.
    // For others, static_assert(false, "Not a random access iterator.");
    // You may use std::iterator_traits to get the iterator category.
    if constexpr(!iterator_type<_Iter>) {
        static_assert(iterator_type<_Iter>, "Not an iterator.");
    } else {
        using category = typename std::iterator_traits<_Iter>::iterator_category;
        if constexpr(std::is_base_of_v<std::random_access_iterator_tag, category>) {
            std::cerr << "use std::sort" << std::endl;
            std::sort(__first, __last);
        } else if constexpr(std::is_same_v<category, sjtu::map_iterator_tag>) {
            std::cerr << "do not sort" << std::endl;
            return;
        } else {
            static_assert(std::is_base_of_v<std::random_access_iterator_tag, category>,
                          "Not a random access iterator.");
        }
    }
}

} // namespace sjtu

int a[10];
std::list<int> b;
sjtu::map<int, int> c;
std::vector<int> d;
int main() {
    sjtu::my_sort(a, a + 10);
    // sjtu::my_sort(b.begin(), b.end());
    // std::sort(b.begin(), b.end());
    sjtu::my_sort(c.begin(), c.end());
    // sjtu::my_sort(d.begin(), d.end());
    int x = 0;
    // sjtu::my_sort(x, x);
    return 0;
}
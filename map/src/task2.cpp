#include <iterator>
#include <algorithm>
#include <type_traits>
#include <iterator>
#include <vector>
#include <iostream>
#include <iomanip>
#include <map>

#include "map.hpp"

namespace sjtu {

template <typename _Tp>
static constexpr bool is_container_v = requires(const _Tp &x) {
    std::begin(x);
    std::end(x);
};

template <typename _Tp>
static constexpr bool is_containers_container_v = requires(const _Tp &x) {
    std::begin(*std::begin(x));
    std::end(x);
};

template <typename _Tp>
static constexpr bool is_pair_v = requires(const _Tp &x) {
    x.first;
    x.second;
};



template <typename _Tp>
void print(const _Tp &__val, size_t __indent = 0) {
    if constexpr(is_containers_container_v<_Tp>) {
        std::cout << std::setw(__indent) << "" << "{\n";
        for (const auto &elem : __val) {
            print(elem, __indent + 2);
        }
        // std::cout << "]\n";
        std::cout << std::setw(__indent) << "" << "}\n";
    } else if constexpr(is_container_v<_Tp>) {
        std::cout << std::setw(__indent) << "" << '{';
        for (auto it = begin(__val); it != __val.end(); ++it) {
            if (it != __val.begin()) std::cout << ' ';
            print(*it);
        }
        std::cout << "}\n";
    } else if constexpr (is_pair_v<_Tp>){
        std::cout << "(" << __val.first << ", " << __val.second << ")";
    } else {
        std::cout << __val;
    }

}

} // namespace sjtu


int main() {
    std::vector<int> a[5];
    std::map<int, int> mp;
    mp[1] = 2, mp[3] = 4;
    sjtu::print(mp);
    std::vector<std::vector<int>> b[5];
    for (int i = 0 ; i < 5 ; ++i)
        b[i].push_back({1, 2, 3}), b[i].push_back({4, 5, 6});
    
    for (int i = 0 ; i < 5 ; ++i)
        a[i].push_back(i), a[i].push_back(i); 
    sjtu::print(a);
    sjtu::print(b);

    return 0;
}

/*
应当输出类似如下(总之好看即可):
[
  [0 0]
  [1 1]
  [2 2]
  [3 3]
  [4 4]
]
*/

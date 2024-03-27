#include "map.hpp"
#include <iostream>
#include <random>
#include <map>
#include <vector>

void testRBT() {
    std::cerr << "testRBT" << std::endl;
    int seed = 1711442050;
    std::cerr << seed << std::endl;
    std::mt19937 gen(seed);
    sjtu::RBTree<int, int> T;
    std::map<int, int> M;
    for (int i = 1; i <= 1000; ++i) {
        int x = gen() % 1000;
        printf("insert{ %d, %d }\n", x, i);
        T.insert({x, i});
        M.insert({x, i});
    }
    T.print();
    for (int i = 1; i <= 1000; ++i) {
        int x = gen() % 1000;
        printf("erase{ %d }\n", x);
        auto t = T.find(x);
        if (t) {
            printf("find { %d, %d }\n", t->data.first, t->data.second);
            T.remove(x);
        } else {
            printf("not found\n");
        }
        M.erase(x);
        T.print();
    }
    // T.print();
    for (auto it = M.begin(); it != M.end(); ++it) {
        auto t = T.find(it->first);
        if (t) {
            assert(t->data.second == it->second);
        } else throw;
    }
    std::cerr << "END" << std::endl;
}
void testmap() {
    std::cerr << "testmap" << std::endl;
    int seed = 1711442050;
    std::cerr << seed << std::endl;
    std::mt19937 gen(seed);
    sjtu::map<int, int> T;
    std::map<int, int> M;
    std::cerr << T.size() << " " << T.empty() << std::endl;
    for (int i = 1; i <= 1000; ++i) {
        int x = gen() % 1000;
        printf("insert{ %d, %d }\n", x, i);
        // T.insert({x, i});
        // M.insert({x, i});
        T[x] = i;
        M[x] = i;
    }
    assert(T.size() == M.size());
    for (auto it = M.begin(); it != M.end(); ++it) {
        auto t = T.find(it->first);
        if (t != T.end()) {
            assert(t->second == it->second);
        } else throw;
    }
    std::cerr << "END" << std::endl;
}
int main() {
    // testRBT();
    testmap();
    return 0;
}
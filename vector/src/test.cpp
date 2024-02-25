#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> v2 = {1, 2, 3, 4, 5};
    vector<int>::iterator it = v.begin();
    vector<int>::iterator it2 = v2.begin();
    cout << it - it2 << endl;
    std::allocator<int> alloc;
    return 0;
}
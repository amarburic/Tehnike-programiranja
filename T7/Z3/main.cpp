#include <iostream>
#include <list>

using namespace std;

template <typename T>
list<T> SortirajListu(list<T> l) {
    for(auto it = l.begin(); it != l.end(); it++)
        for(auto it2 = it; it2 != l.end();) {
            if(++it2 == l.end()) break;
            if(*it > *it2) swap(*it, *it2);
        }
    return l;
}

int main() {
    int n;
    cin >> n;
    list<int> l(n);
    for(auto &i : l)
        cin >> i;
    for(auto i : SortirajListu(l))
        cout << i << " ";
    return 0;
}


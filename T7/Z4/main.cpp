#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

template <typename T>
set<T> Presjek (const set<T> &s1, const set<T> &s2) {
    set<T> s3;
    for(auto element : s1)
        if(s2.find(element) != s2.end())
            s3.insert(element);
    return s3;
}

template <typename T>
set<T> Unija (const set<T> &s1, const set<T> &s2) {
    set<T> s3(s1);
    s3.insert(s2.begin(), s2.end());
    return s3;
}

int main() {
    set<string> s1{"a", "b", "c", "d"}, s2{"c", "d", "e"};
    cout << "Unija: ";
    for(auto s : Unija(s1, s2))
        cout << s << " ";
    cout << "\nPresjek: ";
    for(auto s : Presjek(s1, s2))
        cout << s << " ";
    return 0;
}


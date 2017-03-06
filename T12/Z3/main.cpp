#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

template <typename T>
set<T> operator + (const set<T>& s1, const set<T>& s2) {
    set<T> s3(s1);
    s3.insert(s2.begin(), s2.end());
    return s3;
}

template <typename T>
set<T> operator * (const set<T>& s1, const set<T>& s2) {
    set<T> s3(s1);
    for(auto it = s3.begin(); it != s3.end(); it++) {
        if(s2.count(*it) == 0) 
            s3.erase(it);
    }
    //remove_if(it, it2, [&s2](T el){ return s2.count(el) == 0; });
    return s3;
}

template <typename T>
ostream& operator << (ostream& tok, const set<T>& s) {
    tok << "{"; 
    for(auto it = s.begin(); it != s.end();) {
        tok << *it;
        if(++it != s.end()) tok << ",";
    }
    tok << "}";
    return tok;
}

int main() {
        std::set<int> s1{3,5,1,2,8}, s2{7, 2, 8, 4};
    std::cout << s1*s2;
    return 0;
}


#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string funkcija (string s) {
    string s1;
    remove_copy(s.rbegin(), s.rend(), back_inserter(s1),  ' ');
    return s1;
}

int main() {
    string s;
    getline(cin, s);
    cout << funkcija(s);
    return 0;
}


#include <iostream>
#include <string>

using namespace std;

template <typename IterTip>
IterTip RazmijeniBlokove(IterTip p1, IterTip k1, IterTip p2) {
    while(p1 != k1) {
        auto temp(*p1);
        *p1++ = *p2;
        *p2++ = temp;
    }
    return p2;
}

int main() {
    int i1[]{1, 2, 3, 4, 5}, i2[]{6, 7, 8, 9, 10};
    cout << "Prije razmjene: ";
    cout << "Prvi niz: ";
    for(int i: i1)
        cout << i << " ";
    cout << endl;
    cout << "Drugi niz: ";
    for(int i: i2)
        cout << i << " ";
    cout << endl;
    RazmijeniBlokove(i1, i1 + 5, i2);
    cout << "Nakon razmjene: ";
    cout << "Prvi niz: ";
    for(int i: i1)
        cout << i << " ";
    cout << endl;
    cout << "Drugi niz: ";
    for(int i: i2)
        cout << i << " ";
    cout << endl;
    
    string s1[]{"ab", "bc", "de", "fg", "ij"}, s2[]{"abc", "sdfc", "ddgdf", "dfgs", "sdf"};
    cout << "Prije razmjene: ";
    cout << "Prvi niz: ";
    for(string s: s1)
        cout << s << " ";
    cout << endl;
    cout << "Drugi niz: ";
    for(string s: s2)
        cout << s << " ";
    cout << endl;
    RazmijeniBlokove(s1, s1 + 5, s2);
    cout << "Nakon razmjene: ";
    cout << "Prvi niz: ";
    for(string s: s1)
        cout << s << " ";
    cout << endl;
    cout << "Drugi niz: ";
    for(string s: s2)
        cout << s << " ";
    cout << endl;
    return 0;
}


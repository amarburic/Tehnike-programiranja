#include <iostream>
#include <deque>

using namespace std;

template <typename IterTip>
auto SumaBloka(IterTip pocetak, IterTip iza_kraja) -> decltype(*pocetak + *pocetak) {
    decltype(*pocetak + *pocetak) suma(*pocetak);
    while(++pocetak != iza_kraja) 
        suma += *pocetak;
    return suma;
}

int main() {
    deque<int> unos;
    int n;
    cout << "Unesite broj elemenata: ";
    cin >> n;
    unos.resize(n);
    for(int i = 0; i < n; i++) {
        cout << "Unesite " << i + 1 << ". element deka: ";
        cin >> unos[i];
    }
    cout << "Suma bloka: " << SumaBloka(unos.begin(), unos.end());
    return 0;
}


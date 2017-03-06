#include <iostream>
#include <stdexcept>

#define SIZE 50

using namespace std;

int BinarySearch(int* p, int* k, int n) {
    int a(0), b(k - p - 1);
    while(p[a] != n) {
        if(n < p[a] || n > p[b])
        throw range_error("Element se ne nalazi u nizu!");
        if(p[(a + b)/2] > n)
            b = (a + b)/2;
        else 
            a = (a + b)/2;
    }
    return a;
}

int main() {
    int niz[SIZE];
    cout << "Unesite sortiran niz: " << endl;
    for(int i = 0; i < SIZE; i++) {
        cout << "Unesite " << i + 1 << ". element niza: ";
        cin >> niz[i];
    }
    int n;
    cout << "Unesi trazeni element: ";
    cin >> n;
    try {
        cout << "Indeks trazenog elementa je: " << BinarySearch(niz, niz + SIZE, n);
    }
    catch(range_error e) {
        cout << "Doslo je do sljedece greske: " << e.what();
    }
    return 0;
}


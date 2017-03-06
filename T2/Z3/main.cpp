#include <iostream>
#include <complex>

using namespace std;

int main() {
        complex<double> imp(0,0), unos;
        int n;
        cout << "Unesite broj elemenata: ";
        cin >> n;
        for(int i = 1; i <= n; i++){
                cout << "Z_" << i << " = ";
                cin >> unos;
                imp += complex<double>(1,0)/unos;
        }
        imp = complex<double>(1,0)/imp;
        cout << "Paralelna veza ovih elemenata ima impedansu Z_ = " << imp << endl;
        return 0;
}


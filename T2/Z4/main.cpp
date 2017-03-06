#include <iostream>
#include <complex>

using namespace std;

int main() {
        complex<double> imp(0,0);
        double r, x;
        int n;
        cout << "Unesite broj elemenata: ";
        cin >> n;
        for(int i = 1; i <= n; i++){
                cout << "R" << i << " = ";
                cin >> r;
                cout << "X" << i << " = ";
                cin >> x;
                imp += complex<double>(1,0)/complex<double>(r, x);
        }
        imp = complex<double>(1,0)/imp;
        cout << "Paralelna veza ovih elemenata ima R = " << real(imp) << " i X = " << imag(imp) << "." << endl; 

        return 0;
}


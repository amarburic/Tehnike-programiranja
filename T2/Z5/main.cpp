#include <iostream>
#include <complex>
#define PI 3.141

using namespace std;

int main() {
        complex<double> imp(0,0);
        double z, fi;
        int n;
        cout << "Unesite broj elemenata: ";
        cin >> n;
        for(int i = 1; i <= n; i++){
                cout << "z" << i << " = ";
                cin >> z;
                cout << "fi" << i << " = ";
                cin >> fi;
                fi = PI*fi/180;
                imp += complex<double>(1,0)/polar(z, fi);
        }
        imp = complex<double>(1,0)/imp;
        cout << "Paralelna veza ovih elemenata ima z = " << abs(imp) << " i fi = " << 180*arg(imp)/PI << "." << endl; 
        return 0;
}


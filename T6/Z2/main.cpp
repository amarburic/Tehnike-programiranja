#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename T>
T* DinamickaAlokacija(vector<T> v) {
    if(v.size() == 0)
        throw domain_error("Prazan vektor");
    try {
        T* p(new T[v.size()]);
        reverse_copy(v.begin(), v.end(), p);
        return p;
    }
    catch(...) {
        throw "Greska sa memorijom";
    }
}

int main() {
    int n;
    cout << "Unesite broj elemenata: ";
    cin >> n;
    vector<double> v(n);
    cout << "Unesite elemente vektora: ";
    for (double &i: v) 
        cin >> i;
    try {
        double* p(DinamickaAlokacija(v));
        for(int i = 0; i < n; i++)
            cout << p[i] << " ";
        delete[] p;
    }
    catch(domain_error e) {
        cout << e.what();
    }
    catch(const char* s) {
        cout << s;
    }
    
    return 0;
}


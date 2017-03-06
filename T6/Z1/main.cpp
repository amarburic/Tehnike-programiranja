#include <iostream>

using namespace std;

int *DinamickaAlokacija(int n) {
    if(n <= 0)
        throw "Broj elemenata mora biti pozitivan";
    try {
        int* p(new int[n]), stepen(1);
        for(int i = 0; i < n; i++) {
            p[i] = stepen;
            stepen *= 2;
        }
        return p;
    }
    catch(...) {
        throw "Alokacija nije uspjela";
    }
    
}

int main() {
    int n;
    cin >> n;
    try {
        int* p(DinamickaAlokacija(n));
        for(int i = 0; i < n; i++)
            cout << p[i] << " ";
        delete[] p;
    } 
    catch(const char* poruka) {
        cout << poruka;
    }
    return 0;
}


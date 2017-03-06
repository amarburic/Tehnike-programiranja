#include <iostream>
#include <stdexcept>
#include <new>

using namespace std;

int **DinamickaAlokacija(int n) {
    if(n <= 0)
        throw domain_error("Velicina mora biti pozitivna");
    try {
        int **m(new int*[n]);
        for(int i = 0; i < n; i++) m[i] = nullptr;
        try {
            for(int i = 0; i < n; i++) {
                m[i] = new int[2*i + 1];
                for(int j = 0; j < 2*i + 1; j++)
                    m[i][j] = (j <= i)?(j + 1):(2*i + 1 - j);
            }
            return m;
        }
        catch(...) {
            for(int i = 0; i < n; i++) delete[] m[i];
            delete[] m;
            throw;
        }
    } 
    catch(...) {
        throw;
    }
}

int main() {
    int n;
    cin >> n;
    try {
        int **m(DinamickaAlokacija(n));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 2*i + 1; j++)
                cout << m[i][j] << " ";
            cout << endl;
        }
        for(int i = 0; i < n; i++) delete[] m[i];
        delete[] m;
    } catch(bad_alloc e) {
        cout << "Greska sa memorijom";
    } catch(domain_error e) {
        cout << e.what();
    }
    return 0;
}


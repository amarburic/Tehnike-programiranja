#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <new>

using namespace std;

template <typename T> 
T** DinamickaAlokacija(vector<vector<T>> vvt) {
    if(vvt.size() <= 0)
        throw domain_error("Vektor ne smije biti prazan");
    T** m(new T*[vvt.size()]);
    for(int i = 0; i < vvt.size(); i ++) m[i] = nullptr;
    try {
        for(int i = 0; i < vvt.size(); i++) {
            m[i] = new T[vvt[i].size()];
            copy(vvt[i].begin(), vvt[i].end(), m[i]);
        }
        return m;
    } catch(...) {
        for(int i = 0; i < vvt.size(); i ++) delete[] m[i];
        delete[] m;
        throw;
    }
} 

int main() {
    vector<vector<int>> vvi(3, vector<int>(3));
    for(auto &vi: vvi)
        for(auto &i: vi)
            cin >> i;
    try {
        int **m(DinamickaAlokacija(vvi));
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++)
                cout << m[i][j] << " ";
            cout << endl;
        }
        for(int i = 0; i < 3; i++) delete[] m[i];
        delete[] m;
    } catch(bad_alloc) {
        cout << "Problem sa memorijom";
    } catch(domain_error e) {
        cout << e.what();
    }
    return 0;
}


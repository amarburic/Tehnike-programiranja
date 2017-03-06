#include <iostream>
#include <complex>
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std;

complex<double> VrhMatrice(vector<vector<int>>mat, int p, int q){
        for(int i = 1; i < mat.size(); i++)
                if(mat[i].size() != mat[0].size())
                        throw domain_error("Nekorektna matrica");
        if(p < 0 || q < 0 || p >= mat.size() || q >= mat[0].size())
                throw range_error("Nekorektna pocetna pozicija");
        vector<complex<double>> rel{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
        complex<double> trenutna(q,p);
        while(true) {
                complex<double> sljedeca;
                int max(mat[imag(trenutna)][real(trenutna)]);
                for(complex<double> i: rel) {
                        complex<double> c(trenutna + i);
                        if(real(c) >= 0 && real(c) < mat[0].size()
                        && imag(c) >= 0 && imag(c) < mat.size())
                                if(mat[imag(c)][real(c)] > max) {
                                        max = mat[imag(c)][real(c)];
                                        sljedeca = c;
                                }
                }
                if(max == mat[imag(trenutna)][real(trenutna)])
                        return complex<double>(imag(trenutna), real(trenutna));
                else trenutna = sljedeca;
        }
}

int main() {
        int m, n, p, q;
        cout << "Unesite brojeve m i n: ";
        cin >> m >> n;
        vector<vector<int>> matrica(m, vector<int>(n));
        for(int i = 0; i < matrica.size(); i++)
                for(int j = 0; j < matrica[0].size(); j++){
                        cout << "\nUnesite element " << i << " x " << j << ": ";
                        cin >> matrica[i][j];
                }
        cout << "\nUnesite brojeve p i q: ";
        cin >> p >> q;
        try{
                complex<int> koord(VrhMatrice(matrica, p, q));
                cout << "\nVrh matrice je na poziciji: "  << koord << ".";
                cout << "\nVrijednost elementa je: " << matrica[real(koord)][imag(koord)] << ".";
                
        }catch(domain_error e) {
                cout << "\nIzuzetak: " << e.what();
        }catch(range_error e) {
                cout << "\nIzuzetak: " << e.what();
        }
        
        return 0;
}


#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std;

typedef vector<vector<double>> Matrica;

void IspisiMatricu(Matrica mat)
{
        for(int i = 0; i < mat.size(); i++) {
                for(int j = 0; j < mat[0].size(); j++)
                        cout << setw(4) << mat[i][j];
                if(i != mat.size() - 1)
                        cout << endl;
        }
}

Matrica EkspanzijaMatrice(Matrica pocetna, int p, int q)
{

        if(p <= 0 || q <= 0)
                throw domain_error("Nelegalni parametri");
        for(int i = 1; i < pocetna.size(); i++)
                if(pocetna[i].size() != pocetna[0].size())
                        throw domain_error("Nekorektna matrica");
        if(pocetna.size() == 0 || pocetna[0].size() == 0)
                return pocetna;
        int m(pocetna.size()), n(pocetna[0].size());

        Matrica prosirena(p*m, vector<double>(q*n));

        for(int i = 0; i < m; i++) {
                for(int j = 0; j < n; j++)
                        for(int k = i*p; k < p*m; k++)
                                for(int l = j*q; l < q*n; l++)
                                        prosirena[k][l] = pocetna[i][j];
        }

        return prosirena;
}

int main()
{
        int m, n, p, q;
        cout << "Unesite brojeve m i n: ";
        cin >> m >> n;
        Matrica matrica(m, vector<double>(n));
        for(int i = 0; i < matrica.size(); i++)
                for(int j = 0; j < matrica[0].size(); j++) {
                        cout << "\nUnesite element " << i << " x " << j << ": ";
                        cin >> matrica[i][j];
                }
        cout << "\nUnesite brojeve p i q: ";
        cin >> p >> q;
        try {
                IspisiMatricu(EkspanzijaMatrice(matrica, p, q));
        } catch(domain_error de) {
                cout << "\n" << de.what();
        }
        cout << ".";
        return 0;
}

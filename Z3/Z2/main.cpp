#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <map>
#include <functional>

using namespace std;

template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr;
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> mat) {
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
 }

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona) {
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova; mat.br_kolona = br_kolona;
    mat.elementi = new TipElemenata*[br_redova];
    for(int i = 0; i < br_redova; i++) mat.elementi[i] = nullptr;
    try {
        for(int i = 0; i < br_redova; i++)
        mat.elementi[i] = new TipElemenata[br_kolona];
    }
    catch(...) {
       UnistiMatricu(mat);
       throw;
    }
    return mat;
}

template <typename TipElemenata>
void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat) {
    for(int i = 0; i < mat.br_redova; i++)
       for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << ime_matrice
            << "(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}

template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat,
int sirina_ispisa, int preciznost = 4, bool treba_brisati = false) {
    for(int i = 0; i < mat.br_redova; i++) {
       for(int j = 0; j < mat.br_kolona; j++)
            std::cout << std::setw(sirina_ispisa)
            << setprecision(preciznost) << mat.elementi[i][j];
       std::cout << std::endl;
    }
    if(treba_brisati) UnistiMatricu(mat);
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
const Matrica<TipElemenata> &m2) {
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona));
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}

Matrica<int> ProsiriPoFunkcijama(Matrica<int> mat, map<string, function<int(int)>> mapa, int n) {
    if(n <= 0) throw logic_error("Besmislen parametar n!");
    for(auto it = mapa.begin(); it != mapa.end(); ++it) {
        bool ispravan_kljuc(false);
        for(auto s : {"dolje", "desno", "dijagonalno"})
            if(it->first == s) {
                ispravan_kljuc = true; break;
            }
        if(!ispravan_kljuc) throw logic_error("Neispravna mapa!");
    }
    bool dolje(mapa.count("dolje")), desno(mapa.count("desno")),
    dijagonalno(mapa.count("dijagonalno"));
    for(int i = 1; i < n; i++) {
        Matrica<int> ret;
        try {
            ret = StvoriMatricu<int>(mat.br_redova * (1 + (dolje || dijagonalno)),
            mat.br_kolona * (1 + (desno || dijagonalno)));
        } catch(...) {
            UnistiMatricu(mat);
            throw;
        }
        for(int i = 0; i < ret.br_redova; i++)
            for(int j = 0; j < ret.br_kolona; j++)
                ret.elementi[i][j] = mat.elementi[i % mat.br_redova][j % mat.br_kolona];
        if(desno)
            for(int i = 0; i < mat.br_redova; i++)
                for(int j = mat.br_kolona; j < 2 * mat.br_kolona; j++)
                    ret.elementi[i][j] = mapa["desno"](mat.elementi[i][j - mat.br_kolona]);
        if(dolje)
            for(int i = mat.br_redova; i < 2 * mat.br_redova; i++)
                for(int j = 0; j < mat.br_kolona; j++)
                    ret.elementi[i][j] = mapa["dolje"](mat.elementi[i - mat.br_redova][j]);
        if(dijagonalno)
            for(int i = mat.br_redova; i < 2 * mat.br_redova; i++)
                for(int j = mat.br_kolona; j < 2 * mat.br_kolona; j++)
                    ret.elementi[i][j] = mapa["dijagonalno"](mat.elementi[i - mat.br_redova][j - mat.br_kolona]);

        UnistiMatricu(mat);
        mat = ret;
    }
    return mat;
}

int main()
{
    int dim1, dim2;
    std::cout<<"Unesi broj redova i kolona za matricu: ";
    std::cin>>dim1>>dim2;
    Matrica<int> m;
    int n;
    std::map<std::string, std::function<int(int)>> mapa{
    {"desno", [] (int x) { return x + 1; }},
    {"dolje", [] (int x) { return x + 2; }},
    {"dijagonalno", [] (int x) { return x + 3; }}
    };
    std::cout<<std::endl;
    try {
        m = StvoriMatricu<int>(dim1, dim2);
        std::cout<<"Unesi matricu A: "<<std::endl;
        UnesiMatricu<int>('A', m);
        std::cout<<"Unesite n: ";
        std::cin>>n;
        IspisiMatricu(ProsiriPoFunkcijama(m, mapa, n), 5, true);
        UnistiMatricu(m);
    }
    catch (std::bad_alloc) {
        std::cout<<"Nema dovoljno memorije! ";
    }
    catch (std::domain_error e) {
        std::cout<<e.what();
    }
    catch (std::logic_error e) {
        std::cout<<e.what();
    }
    return 0;
}
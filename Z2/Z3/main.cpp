#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <limits>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int PascalovTrougao(int m, int n) {
    if(m <= 0 || n <= 0)
        throw domain_error("Neispravni parametri!");
    if(n == 1 || m == n)
        return 1;
    return PascalovTrougao(m - 1, n - 1) + PascalovTrougao(m - 1, n);
}

int NewtonovBinomniKoeficijent(int m, int n) {
    if(m <= 0 || n < 0 || m < n)
        throw domain_error("Neispravni parametri!");
    int binomni_koeficijent(1);
    for(int i = m; i > max(n, m - n); i--)
        binomni_koeficijent *= i;
    for(int i = 1; i <= min(n, m - n); i++)
        binomni_koeficijent /= i;
    return binomni_koeficijent;
}

template <typename Kontejner>
auto Izmijeni3DKontejner(Kontejner &k3d, typename remove_reference<decltype(*(begin(*begin(*begin(k3d)))))>::type fun(int, int),
                         int p = 0, int q = 0) -> typename remove_reference<decltype(*(begin(*begin(*begin(k3d)))))>::type {
    if(begin(k3d) == end(k3d)) throw domain_error("Neispravni parametri!");
    for(auto it3d = begin(k3d); it3d != end(k3d); it3d++) {
        if(begin(*it3d) == end(*it3d)) throw domain_error("Neispravni parametri!");
        for(auto it2d = begin(*it3d); it2d != end(*it3d); it2d++)
            if(begin(*it2d) == end(*it2d)) throw domain_error("Neispravni parametri!");
    }
    auto trazeni_element = fun(p, q);
    bool pronadjeno(false), moze_stati(trazeni_element <= sqrt(numeric_limits<decltype(trazeni_element)>::max()));
    for(auto it3d = begin(k3d); it3d != end(k3d); it3d++)
        for(auto it2d = begin(*it3d); it2d != end(*it3d); it2d++)
            for(auto it = begin(*it2d); it != end(*it2d); it++) {
                if(*it == trazeni_element) {
                    pronadjeno = true;
                    if(moze_stati) *it = trazeni_element * trazeni_element;
                }
            }
    if(!pronadjeno) throw range_error("Nije pronadjen broj!");
    return trazeni_element;
}

int main() {
    int a, b, c, p, q;
    cout << "Unesite dimenzije 3D kontejnera: ";
    cin >> a >> b >> c;
    vector<vector<vector<int>>> vvvi(a, vector<vector<int>>(b, vector<int>(c)));
    cout << "Unesite elemente: ";
    for(auto &vvi: vvvi)
        for(auto &vi: vvi)
            for(auto &i: vi)
                cin >> i;
    cout << "Unesite brojeve p i q: ";
    cin >> p >> q;
    try {
        int trazeni_element(Izmijeni3DKontejner(vvvi, PascalovTrougao, p, q));
        cout << "Kontejner nakon zamjene broja " << trazeni_element << " brojem "
        << trazeni_element * trazeni_element << " glasi:" << endl;
        for(auto &vvi: vvvi) {
            for(auto &vi: vvi) {
                for(auto &i: vi)
                    cout << left << setw(5) << i;
                cout << endl;
            }
            cout << endl;
        }
    } catch(domain_error e) {
        cout << e.what();
    } catch(range_error e) {
        cout << e.what();
    }
    return 0;
}

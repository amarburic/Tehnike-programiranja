#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

using namespace std;

template <typename Tip>
auto Izdvajanje(Tip p1, Tip& p2, int& broj_nadjenih) -> typename remove_reference<decltype(*p1)>::type* {
    auto savrsen = [](typename remove_reference<decltype(*p1)>::type a) {
        int suma(0);
        for(decltype(a) i = 1; i < a; i++)
            if(a % i == 0)
                suma += i;
        return a == suma;
        };
    broj_nadjenih = 0;
    for(auto i = p1; i != p2; i++) {
        if(savrsen(*i)) {
            bool duplikat(false);
            for(auto j = i;;) {
                if(j-- == p1) break;
                if(*i == *j) {
                    duplikat = true;
                    break;
                }
            }
            if(!duplikat) broj_nadjenih++;
        }
    }
    typename remove_reference<decltype(*p1)>::type* niz(nullptr);
    if(broj_nadjenih != 0) {
        try {
            niz = new typename remove_reference<decltype(*p1)>::type[broj_nadjenih];
            int sljedeca_pozicija(0);
            for(auto i = p1; i != p2; i++) {
                if(savrsen(*i)) {
                    bool duplikat(false);
                    for(auto j = i;;) {
                        if(j-- == p1) break;
                        if(*i == *j) {
                            duplikat = true;
                            break;
                        }
                    }
                    if(!duplikat) niz[sljedeca_pozicija++] = *i;
                }
            }
        } catch(...) {
            throw domain_error("Nedovoljno memorije!");
        }
    }
    auto isto_djelioca = [](typename remove_reference<decltype(*p1)>::type x, typename remove_reference<decltype(*p1)>::type y) {
        int broj_djelioca_x(0), broj_djelioca_y(0);
        for(decltype(x) i = 1; i <= x; i++)
            if(x % i == 0) broj_djelioca_x++;
        for(decltype(y) i = 1; i <= y; i++)
            if(y % i == 0) broj_djelioca_y++;
        return  broj_djelioca_x == broj_djelioca_y;
    };
    for(auto i = p1; i != p2; i++) {
        bool pronadjen(false);
        int obrisano(0);
        for(auto j = i;;){
            if(++j == p2) break;
            if(isto_djelioca(*i, *j)) {
                for(auto k = j, l = j;; l++) {
                if(++k == p2) break;
                *l = *k;
                }
                p2--; obrisano++; j--;
                pronadjen = true;
            }
        }
        if(pronadjen) {
            for(auto k = i, l = i;; l++) {
                if(++k == p2) break;
                *l = *k;
            }
            p2--; i--;
        }
        if(i == p2) break;
    }
    sort(p1, p2, [](typename remove_reference<decltype(*p1)>::type a,
                    typename remove_reference<decltype(*p1)>::type b) -> bool {
         int suma_djelioca_a(0), suma_djelioca_b(0);
         for(decltype(a) i = 1; i <= a; i++)
            if(a % i == 0) suma_djelioca_a += i;
        for(decltype(b) i = 1; i <= b; i++)
            if(b % i == 0) suma_djelioca_b += i;
        if(suma_djelioca_a < suma_djelioca_b)
            return true;
        if(suma_djelioca_a == suma_djelioca_b)
            return a > b;
        return false;
         });
    return niz;
}

int main() {
    vector<int> v;
    int unos, broj_nadjenih;
    cout << "Unesite brojeve: ";
    while(cin >> unos, unos != -1) v.push_back(unos);
    int* p(nullptr);
    try {
        auto p1(v.begin()), p2(v.end());
        p = (Izdvajanje(p1, p2, broj_nadjenih));
        cout << "Modificirani kontejner: ";
        for(auto it = p1; it != p2; it++) {
            if(it != p1) cout << ", ";
            cout << *it;
        }
        cout << endl;
        cout << "Savrseni brojevi: ";
        for(auto itp = p; itp != p + broj_nadjenih; itp++) {
            if(itp != p) cout << ", ";
            cout << *itp;
        }
    } catch(domain_error e) {
        cout << e.what();
    }
    delete[] p;
    return 0;
}

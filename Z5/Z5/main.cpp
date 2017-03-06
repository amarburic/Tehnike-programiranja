#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iterator>

using namespace std;

class Berza {
    static constexpr double FENINGA_U_MARKI = 100;
    int min_cijena, max_cijena;
    vector<int> registrovane;
public:
    Berza(int min_cijena, int max_cijena) : min_cijena(min_cijena), max_cijena(max_cijena) {
        if(min_cijena < 0 || max_cijena < 0) throw range_error("Ilegalne granicne cijene");
    }
    explicit Berza(int max_cijena) : min_cijena(0), max_cijena(max_cijena) {
        if(max_cijena < 0) throw range_error("Ilegalne granicne cijene");
    }
    void RegistrirajCijenu(int cijena) {
        if(cijena < min_cijena || cijena > max_cijena) throw range_error("Ilegalna cijena");
        registrovane.push_back(cijena);
    }
    int DajBrojRegistriranihCijena() const { return registrovane.size(); }
    void BrisiSve() { registrovane.clear(); }
    int DajMinimalnuCijenu() const {
        if(registrovane.empty()) throw range_error("Nema registriranih cijena");
        return *min_element(registrovane.begin(), registrovane.end());
    }
    int DajMaksimalnuCijenu() const {
        if(registrovane.empty()) throw range_error("Nema registriranih cijena");
        return *max_element(registrovane.begin(), registrovane.end());
    }
    bool operator ! () const { return registrovane.empty(); }
    int DajBrojCijenaVecihOd(int cijena) const {
        if(registrovane.empty()) throw range_error("Nema registriranih cijena");
        return count_if(registrovane.begin(), registrovane.end(), bind(greater<int>(), placeholders::_1, cijena));
    }
    void Ispisi() const {
        vector<double> temp(registrovane.begin(), registrovane.end());
        sort(temp.begin(), temp.end(), greater<int>());
        transform(temp.begin(), temp.end(),
            ostream_iterator<double>(cout << setprecision(2) << fixed, "\n"),
            bind(divides<double>(), placeholders::_1, 100.));
    }
    int operator [] (int indeks) const {
        if(indeks < 1 || indeks > registrovane.size())
            throw range_error("Neispravan indeks");
        return registrovane[indeks - 1];
    }
    Berza& operator++() {
        if(find_if(registrovane.begin(), registrovane.end(),
            bind(greater<int>(), placeholders::_1, max_cijena - 100)) != registrovane.end())
            throw range_error("Prekoracen dozvoljeni opseg cijena");
        transform(registrovane.begin(), registrovane.end(),
            registrovane.begin(), bind(plus<int>(), placeholders::_1, 100));
        return *this;
    }
    Berza operator++(int) {
        auto temp(*this);
        if(find_if(registrovane.begin(), registrovane.end(),
            bind(greater<int>(), placeholders::_1, max_cijena - 100)) != registrovane.end())
            throw range_error("Prekoracen dozvoljeni opseg cijena");
        transform(registrovane.begin(), registrovane.end(),
            registrovane.begin(), bind(plus<int>(), placeholders::_1, 100));
        return temp;
    }
    Berza& operator--() {
        if(find_if(registrovane.begin(), registrovane.end(),
            bind(less<int>(), placeholders::_1, min_cijena + 100)) != registrovane.end())
            throw range_error("Prekoracen dozvoljeni opseg cijena");
        transform(registrovane.begin(), registrovane.end(),
            registrovane.begin(), bind(minus<int>(), placeholders::_1, 100));
        return *this;
    }
    Berza operator--(int) {
        auto temp(*this);
        if(find_if(registrovane.begin(), registrovane.end(),
            bind(less<int>(), placeholders::_1, min_cijena + 100)) != registrovane.end())
            throw range_error("Prekoracen dozvoljeni opseg cijena");
        transform(registrovane.begin(), registrovane.end(),
            registrovane.begin(), bind(minus<int>(), placeholders::_1, 100));
        return temp;
    }
    Berza operator - () const {
        Berza ret(*this);
        transform(ret.registrovane.begin(), ret.registrovane.end(),
                  ret.registrovane.begin(),
                  bind(minus<int>(), ret.max_cijena + ret.min_cijena, placeholders::_1));
        return ret;
    }
    Berza& operator += (int x) {
       return *this = *this + x;
    }
    Berza& operator -= (int x) {
       return *this = *this - x;
    }
    Berza& operator -= (const Berza& x) {
       return *this = *this - x;
    }
    friend Berza operator + (Berza, int);
    friend Berza operator + (int, const Berza&);
    friend Berza operator - (Berza, int);
    friend Berza operator - (int, Berza);
    friend Berza operator - (Berza, const Berza&);
    friend bool operator == (const Berza&, const Berza&);
    friend bool operator != (const Berza&, const Berza&);
};

Berza operator + (Berza x, int y) {
    if(find_if(x.registrovane.begin(), x.registrovane.end(),
        bind(greater<int>(), placeholders::_1, x.max_cijena + y)) != x.registrovane.end())
        throw domain_error("“Prekoracen dozvoljeni opseg cijena");
    transform(x.registrovane.begin(), x.registrovane.end(),
        x.registrovane.begin(), bind(plus<int>(), placeholders::_1, y));
    return x;

}

Berza operator + (int y, const Berza& x) {
    return x + y;
}

Berza operator - (Berza x, int y) {
    if(find_if(x.registrovane.begin(), x.registrovane.end(),
        bind(less<int>(), placeholders::_1, x.min_cijena - y)) != x.registrovane.end())
        throw domain_error("“Prekoracen dozvoljeni opseg cijena");
    transform(x.registrovane.begin(), x.registrovane.end(),
        x.registrovane.begin(), bind(minus<int>(), placeholders::_1, y));
    return x;
}

Berza operator - (int y, Berza x) {
    if(find_if(x.registrovane.begin(), x.registrovane.end(),
        bind(less<int>(), y - x.min_cijena, placeholders::_1)) != x.registrovane.end())
        throw domain_error("“Prekoracen dozvoljeni opseg cijena");
    if(find_if(x.registrovane.begin(), x.registrovane.end(),
        bind(greater<int>(), y - x.max_cijena, placeholders::_1)) != x.registrovane.end())
        throw domain_error("“Prekoracen dozvoljeni opseg cijena");
    transform(x.registrovane.begin(), x.registrovane.end(),
        x.registrovane.begin(), bind(minus<int>(), y, placeholders::_1));
    return x;
}
 Berza operator - (Berza x, const Berza& y) {
    if(x.registrovane.size() != y.registrovane.size()
       || x.max_cijena != y.max_cijena
       || x.min_cijena != y.min_cijena)
        throw domain_error("Nesaglasni operandi");
    transform(x.registrovane.begin(), x.registrovane.end(),
              y.registrovane.begin(), x.registrovane.begin(),
              minus<int>());
    if(find_if(x.registrovane.begin(), x.registrovane.end(),
        bind(less<int>(), placeholders::_1, x.min_cijena)) != x.registrovane.end())
        throw domain_error("“Prekoracen dozvoljeni opseg cijena");
    return x;
 }

bool operator == (const Berza& x, const Berza& y) {
    return x.max_cijena == y.max_cijena && x.min_cijena == y.min_cijena
    && x.registrovane.size() == y.registrovane.size()
    && equal(x.registrovane.begin(), x.registrovane.end(),
             y.registrovane.begin());
}

bool operator != (const Berza& x, const Berza& y) {
    return !(x == y);
}

int main() {
}

#include <bits/stdc++.h>
#define SUMA

using namespace std;

template <class T>
class PomocniTip {
    int red;
    vector<vector<T>>& matrica;
public:
    PomocniTip(int red, vector<vector<T>>& matrica) : red(red), matrica(matrica) {}
    T& operator [](int kolona);
};

template <class T>
T& PomocniTip<T>::operator [](int kolona) {
    if(kolona < matrica[red].size())
        return matrica[red][kolona];
    else
        return matrica[kolona][red];
}

template <class T>
class ConstPomocniTip {
    int red;
    const vector<vector<T>>& matrica;
public:
    ConstPomocniTip(int red, const vector<vector<T>>& matrica) : red(red), matrica(matrica) {}
    T operator [](int kolona) const;
};

template <class T>
T ConstPomocniTip<T>::operator [](int kolona) const {
    if(kolona < matrica[red].size())
        return matrica[red][kolona];
    else
        return matrica[kolona][red];
}

template <class T>
class SimetricnaMatrica {
    vector<vector<T>> matrica;
    template <class T1, class T2>
    friend void TestDimenzija(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r);
    template <class T1, class T2>
    friend void TestSimetricnostiProizvoda(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r);
public:
    SimetricnaMatrica() = default;
    template<class T2>
    SimetricnaMatrica(const SimetricnaMatrica<T2>& sm);
    SimetricnaMatrica(const vector<vector<T>>& sm);
    SimetricnaMatrica(const initializer_list<initializer_list<T>>& l);
    explicit SimetricnaMatrica(int n);
    int DajDimenziju() const { return matrica.size(); }
    bool operator !() const;
    ConstPomocniTip<T> operator [](int red) const {
        return ConstPomocniTip<T>(red, matrica);
    }
    PomocniTip<T> operator [](int red) {
        return PomocniTip<T>(red, matrica);
    }
    T& operator()(int red, int kolona) {
        if(red < 1 || kolona < 1 || red > DajDimenziju() || kolona > DajDimenziju())
            throw range_error("Indeks van opsega");
        return (*this)[red - 1][kolona - 1];
    }
    T operator()(int red, int kolona) const {
        if(red < 1 || kolona < 1 || red > DajDimenziju() || kolona > DajDimenziju())
            throw range_error("Indeks van opsega");
        return (*this)[red - 1][kolona - 1];
    }
    template <class T2>
    bool operator ==(const SimetricnaMatrica<T2>& sm);
    template <class T2>
    bool operator !=(const SimetricnaMatrica<T2>& sm) {
        return !(*this == sm);
    }
    template <class T2>
    SimetricnaMatrica<T>& operator +=(const SimetricnaMatrica<T2>& r);
    template <class T2>
    SimetricnaMatrica<T>& operator -=(const SimetricnaMatrica<T2>& r);
    template <class T2>
    SimetricnaMatrica<T>& operator *=(const SimetricnaMatrica<T2>& r);
    template <class T2>
    SimetricnaMatrica<T>& operator *=(const T2& skalar);

    template <class T1, class T2>
    friend auto operator +(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) ->
        SimetricnaMatrica<decltype(l[0][0] + r[0][0])>;
    template <class T1, class T2>
    friend auto operator -(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) ->
        SimetricnaMatrica<decltype(l[0][0] - r[0][0])>;
    template <class T1, class T2>
    friend auto operator *(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) ->
        SimetricnaMatrica<decltype(l[0][0] * r[0][0])>;
    template <class T1, class T2>
    friend auto operator *(const SimetricnaMatrica<T1>& l, const T2& skalar) ->
        SimetricnaMatrica<decltype(l[0][0] * skalar)>;
    template <class T1, class T2>
    friend auto operator *(const T2& skalar, const SimetricnaMatrica<T1>& r) ->
        SimetricnaMatrica<decltype(skalar * r[0][0])>;
    template <class T1>
    friend ostream& operator << (ostream& out, const SimetricnaMatrica<T1>& sm);
    template <class T1>
    friend istream& operator >> (istream& out, SimetricnaMatrica<T1>& sm);
};

template <class T1, class T2>
void TestDimenzija(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) {
    if(l.DajDimenziju() != r.DajDimenziju())
        throw domain_error("Matrice nisu saglasne za trazenu operaciju");
}

template <class T1, class T2>
void TestSimetricnostiProizvoda(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) {
    vector<vector<decltype(l[0][0] * r[0][0])>> matrica(l.DajDimenziju(),
        vector<decltype(l[0][0] * r[0][0])>(l.DajDimenziju()));
     for(int i = 0; i < l.DajDimenziju(); i++)
       for(int j = 0; j < r.DajDimenziju(); j ++) {
           decltype(l[0][0] * r[0][0]) suma = decltype(l[0][0] * r[0][0])();
           for(int k = 0; k < r.DajDimenziju(); k++)
               suma += l[i][k] * r[k][j];
           matrica[i][j] = suma;
       }
    for(int i = 0; i < matrica.size(); i++)
        for(int j = 0; j < matrica[0].size(); j++)
            if(matrica[i][j] != matrica[j][i])
                throw logic_error("Rezultantna matrica nije simetricna");
}


template <class T>
template <class T2>
SimetricnaMatrica<T>::SimetricnaMatrica(const SimetricnaMatrica<T2>& sm)
    : matrica(sm.DajDimenziju()) {
    for(int i = 0; i < sm.DajDimenziju(); i++) {
        matrica[i].resize(i + 1);
        for(int j = 0; j < i + 1; j++)
            matrica[i][j] = sm[i][j];
    }
}

template <class T>
SimetricnaMatrica<T>::SimetricnaMatrica(const vector<vector<T>>& sm)
    : matrica(sm) {
    for(int i = 0; i < sm.size(); i++)
        if(sm[i].size() != i + 1)
            throw logic_error("Nekorektna forma simetricne matrice");
}

template <class T>
SimetricnaMatrica<T>::SimetricnaMatrica(const initializer_list<initializer_list<T>>& l)
    : matrica(l.begin(), l.end()) {
    for(int i = 0; i < l.size(); i++)
        if((l.begin() + i)->size() != i + 1)
            throw logic_error("Nekorektna forma simetricne matrice");
}

template <class T>
SimetricnaMatrica<T>::SimetricnaMatrica(int n) {
    if(n < 0) throw domain_error("Neispravna dimenzija");
    matrica.resize(n);
    for(int i = 1; i <= n; i++)
        matrica[i - 1].resize(i);
}

template <class T>
bool SimetricnaMatrica<T>::operator !() const {
    for(auto& vi : matrica)
        for(auto i : vi)
            if(i != 0)
                return false;
    return true;
}

template <class T>
template <class T2>
bool SimetricnaMatrica<T>::operator ==(const SimetricnaMatrica<T2>& sm) {
    if(DajDimenziju() != sm.DajDimenziju())
        return false;
    for(int i = 0; i < DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j++)
            if(matrica[i][j] != sm[i][j])
                return false;
    return true;
}

template <class T>
template <class T2>
SimetricnaMatrica<T>& SimetricnaMatrica<T>::operator +=(const SimetricnaMatrica<T2>& r) {
    TestDimenzija(*this, r);
    for(int i = 0; i < DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j++)
            matrica[i][j] += r[i][j];
    return *this;
}

template <class T>
template <class T2>
SimetricnaMatrica<T>& SimetricnaMatrica<T>::operator -=(const SimetricnaMatrica<T2>& r) {
    TestDimenzija(*this, r);
    for(int i = 0; i < DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j++)
            matrica[i][j] -= r[i][j];
    return *this;
}

template <class T>
template <class T2>
SimetricnaMatrica<T>& SimetricnaMatrica<T>::operator *=(const SimetricnaMatrica<T2>& r) {
    TestDimenzija(*this, r);
    TestSimetricnostiProizvoda(*this, r);
    auto temp(*this);
    for(int i = 0; i < temp.DajDimenziju(); i++)
        for(int j = 0; j < r.DajDimenziju(); j ++) {
            decltype(temp[0][0] * r[0][0]) suma =  decltype(temp[0][0] * r[0][0])();
            for(int k = 0; k < r.DajDimenziju(); k++)
                suma += temp[i][k] * r[k][j];
            matrica[i][j] = suma;
        }
    return *this;
}

template <class T>
template <class T2>
SimetricnaMatrica<T>& SimetricnaMatrica<T>::operator *=(const T2& skalar) {
    for(int i = 0; i < DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j ++)
            matrica[i][j] *= skalar;
    return *this;
}

template <class T1, class T2>
auto operator +(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) ->
    SimetricnaMatrica<decltype(l[0][0] + r[0][0])> {
    TestDimenzija(l, r);
    SimetricnaMatrica<decltype(l[0][0] + r[0][0])> ret(l.DajDimenziju());
    for(int i = 0; i < ret.DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j ++)
            ret[i][j] = l[i][j] + r[i][j];
    return ret;
}

template <class T1, class T2>
auto operator -(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) ->
    SimetricnaMatrica<decltype(l[0][0] - r[0][0])> {
    TestDimenzija(l, r);
    SimetricnaMatrica<decltype(l[0][0] - r[0][0])> ret(l.DajDimenziju());
    for(int i = 0; i < ret.DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j ++)
            ret[i][j] = l[i][j] - r[i][j];
    return ret;
}
#ifdef SUMA
template <class T1, class T2>
auto operator *(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) ->
    SimetricnaMatrica<decltype(l[0][0] * r[0][0])> {
    TestDimenzija(l, r);
    TestSimetricnostiProizvoda(l, r);
    SimetricnaMatrica<decltype(l[0][0] * r[0][0])> ret(l.DajDimenziju());
    for(int i = 0; i < l.DajDimenziju(); i++)
        for(int j = 0; j < r.DajDimenziju(); j ++) {
            auto suma = decltype(l[0][0] * r[0][0])();
            for(int k = 0; k < r.DajDimenziju(); k++)
                suma += (l[i][k] * r[k][j]);
            ret[i][j] = suma;
        }
    return ret;
}
#endif
#ifdef BEZSUME
template <class T1, class T2>
auto operator *(const SimetricnaMatrica<T1>& l, const SimetricnaMatrica<T2>& r) ->
    SimetricnaMatrica<decltype(l[0][0] * r[0][0])> {
    TestDimenzija(l, r);
    TestSimetricnostiProizvoda(l, r);
    SimetricnaMatrica<decltype(l[0][0] * r[0][0])> ret(l.DajDimenziju());
    for(int i = 0; i < l.DajDimenziju(); i++)
        for(int j = 0; j < r.DajDimenziju(); j ++) 
            for(int k = 0; k < r.DajDimenziju(); k++)
                ret[i][j] += (l[i][k] * r[k][j]);
    return ret;
}
#endif
template <class T1>
ostream& operator << (ostream& out, const SimetricnaMatrica<T1>& sm) {
    auto sirina(out.width());
    for(int i = 0; i < sm.DajDimenziju(); i++) {
        for(int j = 0; j < sm.DajDimenziju(); j++)
            out << setw(sirina) << sm[i][j];
        cout << endl;
    }
    return out;
}

template <class T1, class T2>
auto operator *(const SimetricnaMatrica<T1>& l, const T2& skalar) ->
    SimetricnaMatrica<decltype(l[0][0] * skalar)> {
    SimetricnaMatrica<decltype(l[0][0] * skalar)> ret(l);
    for(int i = 0; i < ret.DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j++)
            ret[i][j] *= skalar;
    return ret;
}

template <class T1, class T2>
auto operator *(const T2& skalar, const SimetricnaMatrica<T1>& r) ->
    SimetricnaMatrica<decltype(skalar * r[0][0])> {
    SimetricnaMatrica<decltype(skalar * r[0][0])> ret(r);
    for(int i = 0; i < ret.DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j++)
            ret[i][j] *= skalar;
    return ret;
}

template <class T1>
istream& operator >> (istream& out, SimetricnaMatrica<T1>& sm) {
    for(int i = 0; i < sm.DajDimenziju(); i++)
        for(int j = 0; j < i + 1; j++)
            out >> sm[i][j];

    return out;
}

int main() {
    {//test operatora [][], trebaju ostati samo finalne dodjele
    SimetricnaMatrica<short> m (3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    std::cout << m.DajDimenziju() << std::endl;
    std::cout.width(4); std::cout << m;
}
}

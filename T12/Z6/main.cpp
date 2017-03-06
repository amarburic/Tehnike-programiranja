#include <iostream>
#include <cmath>

using namespace std;

class Duzina {
    static constexpr double INCHA_U_M = 100 / 2.54;
    static constexpr int INCHA_U_STOPI = 12;
    static constexpr int STOPI_U_JARDI = 3;
    int jarde, stope, inchi;
    double KonverzijaUMetre(const int jarde, const int stope, const int inchi) const {
        return ((jarde * STOPI_U_JARDI + stope) * INCHA_U_STOPI + inchi) / INCHA_U_M; 
    } 
    void KonverzijaUImperijalne(const double metri, int& jarde, int& stope, int& inchi) const {
        inchi = round(metri * INCHA_U_M);
        stope = inchi / (double)INCHA_U_STOPI; inchi %= INCHA_U_STOPI;
        jarde = stope / (double)STOPI_U_JARDI; stope %= STOPI_U_JARDI;
    }
public: 
    Duzina(int jarde, int stope, int inchi) {
        KonverzijaUImperijalne(KonverzijaUMetre(jarde, stope, inchi), this->jarde, this->stope, this->inchi);
    }
    Duzina(double metri) {
        KonverzijaUImperijalne(metri, jarde, stope, inchi);
    }
    void Ocitaj(int& jarde, int& stope, int& inchi) const {
        jarde = this->jarde; stope = this->stope; inchi = this->inchi;
    }
    double DajMetre() const {
        return KonverzijaUMetre(jarde, stope, inchi);
    }
    Duzina& operator += (const Duzina& d) {
        return *this = *this + d;
    }
    Duzina& operator++() {
        return *this += {0, 0, 1}; 
    }
    Duzina operator++(int) {
        auto temp(*this);
        *this += {0, 0, 1};
        return temp;
    }
    friend Duzina operator + (const Duzina& d1, const Duzina& d2);
    friend Duzina operator * (double s, const Duzina& d);
    friend Duzina operator * (const Duzina& d, double s);
    friend double operator / (const Duzina& d1, const Duzina& d2);
    friend ostream& operator << (ostream& tok, const Duzina& d);
};

Duzina operator + (const Duzina& d1, const Duzina& d2) {
    return Duzina(d1.jarde + d2.jarde, d1.stope + d2.stope, d1.inchi + d2.inchi);
}

Duzina operator * (double s, const Duzina& d) {
    return Duzina(d.DajMetre() * s);
}

Duzina operator * (const Duzina& d, double s) {
    return s * d;
}

double operator / (const Duzina& d1, const Duzina& d2) {
    return d1.DajMetre() / d2.DajMetre();
}

ostream& operator << (ostream& tok, const Duzina& d) {
    tok << d.jarde << " yd " << d.stope << " ft " << d.inchi << " in";
    return tok;
}

int main() {
    std::cout << "Tutorijal 12, Zadatak 6";
    return 0;
}


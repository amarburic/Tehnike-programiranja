#include <iostream>
#include <cmath>

using namespace std;

class Vektor3d {
    double x, y, z;
public:
    Vektor3d() : x(0), y(0), z(0) {}
    Vektor3d(double x, double y, double z) : x(x), y(y), z(z) {}
    void Postavi (double x, double y, double z) {
        Vektor3d::x = x; Vektor3d::z = z; Vektor3d::y = y;
    }
    void Ocitaj (double &x, double &y, double &z) const {
        x = Vektor3d::x; y = Vektor3d::y; z = Vektor3d::z;
    }
    double DajX() const { return x; }
    double DajY() const { return y; }
    double DajZ() const { return z; }
    void PostaviX(double x) { Postavi(x, DajY(), DajZ()); }
    void PostaviY(double y) { Postavi(DajX(), y, DajZ()); }
    void PostaviZ(double z) { Postavi(DajX(), DajY(), z); }
    double DajDuzinu() const { return sqrt(DajX() * DajX() + DajY() * DajY() + DajZ() * DajZ()); }
    Vektor3d &operator *= (double s) { 
        Postavi(DajX() * s, DajY() * s, DajZ() * s); 
        return *this; 
    }
    Vektor3d &operator += (const Vektor3d &v) { 
        Postavi(DajX() + v.DajX(), DajY() + v.DajY(), DajZ() + v.DajZ()); 
        return *this;
    }
    friend Vektor3d operator + (const Vektor3d &v1, const Vektor3d &v2);
    friend ostream& operator << (ostream& tok, const Vektor3d& v);
};

Vektor3d operator + (const Vektor3d &v1, const Vektor3d &v2) {
    return Vektor3d(v1) += v2;
}

ostream& operator << (ostream& tok, const Vektor3d& v) {
    tok << "{" << v.DajX() << "," << v.DajY() << "," << v.DajZ() << "}";
    return tok;
}

int main() {
    double s, x, y, z;
    cout << "Unos 3 koordinate vektora v1: " << endl;
    cin >> x >> y >> z;
    Vektor3d v1(x, y, z);
    cout << "v1=" << v1 << endl;
    cout << "Duzina vektora v1: " << v1.DajDuzinu() << endl;
    cout << "Unos 3 koordinate vektora v2: " << endl;
    cin >> x >> y >> z;
    Vektor3d v2(x, y, z);
    cout << "v2=" << v2 << endl;
    cout << "Duzina vektora v2: " << v2.DajDuzinu() << endl;
    cout << "v3=v1+v2 (poziv funkcije ZbirVektora)" << endl;
    Vektor3d v3(v1 + v2);
    cout << "v3=" << v3 << endl;
    cout << "Unos skalara s: " << endl;
    cin >> s;
    cout << "v3*=s (poziv metode PomnoziSaSkalarom nad v3)" << endl;
    v3 *= s;
    cout << "v3=" << v3 << endl;
    cout << "v3+=v1 (poziv metode SaberiSa nad v3)" << endl;
    v3 += v1;
    cout << "v3=" << v3 << endl;
    cout << "v=v3 (poziv metode Ocitaj nad v3, pa metode Postavi nad v)" << endl;
    v3.Ocitaj(x, y, z); 
    Vektor3d v; v.PostaviX(x); v.PostaviY(y); v.PostaviZ(z); 
    cout << "v=" << v << endl;
    cout << "v=v1 (koristite getere i setere)" << endl;
    v.PostaviX(v1.DajX()); v.PostaviY(v1.DajY()); v.PostaviZ(v1.DajZ());
    cout << "v=" << v << endl;
    return 0;
}


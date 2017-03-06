#include <iostream>
#include <cmath>

using namespace std;

class Vektor3d {
    double koordinate[3];
public:
    void Postavi (double x, double y, double z) {
        koordinate[0] = x; koordinate[1] = y; koordinate[2] = z;
    }
    void Ocitaj (double &x, double &y, double &z) const {
        x = DajX(); y = DajY(); z = DajZ();
    }
    void Ispisi () const {
        cout << "{" << DajX() << "," << DajY() << "," << DajZ() << "}";
    }
    double DajX() const { return koordinate[0]; }
    double DajY() const { return koordinate[1]; }
    double DajZ() const { return koordinate[2]; }
    void PostaviX(double x) { Postavi(x, DajY(), DajZ()); }
    void PostaviY(double y) { Postavi(DajX(), y, DajZ()); }
    void PostaviZ(double z) { Postavi(DajX(), DajY(), z); }
    double DajDuzinu() const { return sqrt(DajX() * DajX() + DajY() * DajY() + DajZ() * DajZ()); }
    Vektor3d &PomnoziSaSkalarom(double s) { 
        Postavi(DajX() * s, DajY() * s, DajZ() * s); 
        return *this; 
    }
    Vektor3d &SaberiSa(const Vektor3d &v) { 
        Postavi(DajX() + v.DajX(), DajY() + v.DajY(), DajZ() + v.DajZ()); 
        return *this;
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
    Vektor3d v3;
    v3.Postavi(0, 0 ,0); 
    v3.SaberiSa(v1); 
    v3.SaberiSa(v2);
    return v3;
}
int main() {
    Vektor3d v1, v2, v3, v;
    double s, x, y, z;
    cout << "Unos 3 koordinate vektora v1: " << endl;
    cin >> x >> y >> z;
    v1.Postavi(x, y, z);
    cout << "v1="; v1.Ispisi(); cout << endl;
    cout << "Duzina vektora v1: " << v1.DajDuzinu() << endl;
    cout << "Unos 3 koordinate vektora v2: " << endl;
    cin >> x >> y >> z;
    v2.Postavi(x, y, z);
    cout << "v2="; v2.Ispisi(); cout << endl;
    cout << "Duzina vektora v2: " << v2.DajDuzinu() << endl;
    cout << "v3=v1+v2 (poziv funkcije ZbirVektora)" << endl;
    v3 = ZbirVektora(v1, v2);
    cout << "v3="; v3.Ispisi(); cout << endl;
    cout << "Unos skalara s: " << endl;
    cin >> s;
    cout << "v3*=s (poziv metode PomnoziSaSkalarom nad v3)" << endl;
    v3.PomnoziSaSkalarom(s);
    cout << "v3="; v3.Ispisi(); cout << endl;
    cout << "v3+=v1 (poziv metode SaberiSa nad v3)" << endl;
    v3.SaberiSa(v1);
    cout << "v3="; v3.Ispisi(); cout << endl;
    cout << "v=v3 (poziv metode Ocitaj nad v3, pa metode Postavi nad v)" << endl;
    v3.Ocitaj(x, y, z); v.PostaviX(x); v.PostaviY(y); v.PostaviZ(z); 
    cout << "v="; v.Ispisi(); cout << endl;
    cout << "v=v1 (koristite getere i setere)" << endl;
    v.PostaviX(v1.DajX()); v.PostaviY(v1.DajY()); v.PostaviZ(v1.DajZ());
    cout << "v="; v.Ispisi(); cout << endl;
    return 0;
}


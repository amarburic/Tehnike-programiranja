#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

class Lik {
protected:
    string naziv;
public:
    //Lik() {}
    virtual ~Lik() {}
    virtual void IspisiAtribute() const=0;
    virtual double DajObim() const=0;
    virtual double DajPovrsinu() const=0;
    virtual void IspisiPodatke() const=0;
    
};

class Krug : public Lik {
    double r;
    static constexpr double PI = atan(1) * 4;
public: 
    explicit Krug(double r) : r(r) { naziv = "Krug"; };
    void IspisiAtribute() const {
        cout << "Krug radiusa " << r;
    }
    double DajObim() const {
        return 2 * r * PI;
    }
    double DajPovrsinu() const {
        return r * r * PI;
    }
    void IspisiPodatke() const {
        IspisiAtribute(); cout << " obima: " << DajObim() 
        << " povrsine: " << DajPovrsinu() << "." <<  endl;
    }
    //~Krug() {};
};

class Pravougaonik : public Lik {
    double a, b;
public: 
    explicit Pravougaonik(double a, double b) : a(a), b(b) { naziv = "Pravougaonik"; };
    void IspisiAtribute() const {
        cout << naziv << " sa stranicama " << a << " i " << b;
    }
    double DajObim() const {
        return 2 * (a + b);
    }
    double DajPovrsinu() const {
        return a * b;
    }
    void IspisiPodatke() const {
        IspisiAtribute(); cout << " obima: " << DajObim() 
        << " povrsine: " << DajPovrsinu() << "." << endl;
    }
    //~Pravougaonik() {};
};

class Trougao : public Lik {
    double a, b, c;
public: 
    explicit Trougao(double a, double b, double c) : a(a), b(b), c(c) { naziv = "Trougao"; };
    void IspisiAtribute() const {
        cout << naziv << " sa stranicama " << a << ", " << b << " i " << c;
    }
    double DajObim() const {
        return a + b + c;
    }
    double DajPovrsinu() const {
        double s((a + b + c) / 2);
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    void IspisiPodatke() const {
        IspisiAtribute(); cout << " obima: " << DajObim() 
        << " povrsine: " << DajPovrsinu() << "." <<  endl;
    }
    //~Trougao() {};
};


int main() {
    int n;
    double a, b, c, r;
    char t;
    Lik* niz[100]{};
    cout << "Unesite broj likova: " << endl;
    cin >> n;
    try {
        for(int i = 0; i < n; i++) {
            cout << i + 1 
            << ". Unos kruga(Kr), pravougaonika(Pa,b), trougla(Ta,b,c):"
            << endl;
            cin >> t;
            switch(t) {
            case 'K': 
                cin >> r;
                cin >> ws;
                niz[i] = new Krug(r);
            break;
            case 'P': 
                cin >> a; cin >> t;
                cin >> b; cin >> ws;
                niz[i] = new Pravougaonik(a, b);
            break;
            case 'T': 
                cin >> a; cin >> t;
                cin >> b; cin >> t;
                cin >> c; cin >> ws;
                niz[i] = new Trougao(a, b, c);
            break;
            }
        }
    } catch(...) {
        for(int i = 0; i < 100; i++) delete niz[i];
        throw;
    }
    for(int i = 0; i < n; i++) niz[i]->IspisiPodatke();
    for(int i = 0; i < n; i++) delete niz[i];
    
}


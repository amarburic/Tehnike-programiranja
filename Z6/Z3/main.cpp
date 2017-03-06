#include <bits/stdc++.h>

using namespace std;

class ApstraktnoVozilo {
    int tezina;
public:
    ApstraktnoVozilo(int tezina) : tezina(tezina) {}
    int DajTezinu() const { return tezina; }
    virtual int DajUkupnuTezinu() const = 0;
    virtual ApstraktnoVozilo* DajKopiju() const = 0;
    virtual void IspisiPodatke() const = 0;
    virtual ~ApstraktnoVozilo() {};
};

class Automobil : public ApstraktnoVozilo {
    vector<int> tezine_putnika;
public:
    Automobil(int tezina, const vector<int>& tezine_putnika) :
        ApstraktnoVozilo(tezina), tezine_putnika(tezine_putnika) {}
    int DajUkupnuTezinu() const override {
        return DajTezinu() + accumulate(tezine_putnika.begin(), tezine_putnika.end(), 0);
    }
    Automobil* DajKopiju() const override { return new Automobil(*this); }
    void IspisiPodatke() const override {
        cout << "Vrsta vozila: Automobil" << endl;
        cout << "Vlastita tezina: " << DajTezinu() << " kg" << endl;
        cout << "Tezine putnika: ";
        for(int i = 0; i < tezine_putnika.size(); i++)
            cout << tezine_putnika[i] << " kg"
            << ((i != (tezine_putnika.size() - 1)) ? ", " : "");
        cout << endl;
        cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << endl;
    }
};

class Kamion : public ApstraktnoVozilo {
    int tezina_tereta;
public:
    Kamion(int tezina, int tezina_tereta) : ApstraktnoVozilo(tezina), tezina_tereta(tezina_tereta) {}
    int DajUkupnuTezinu() const override {
        return DajTezinu() + tezina_tereta;
    }
    Kamion* DajKopiju() const override { return new Kamion(*this); }
    void IspisiPodatke() const override {
        cout << "Vrsta vozila: Kamion" << endl;
        cout << "Vlastita tezina: " << DajTezinu() << " kg" << endl;
        cout << "Tezina tereta: " << tezina_tereta << " kg" << endl;
        cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << endl;
    }
};

class Autobus : public ApstraktnoVozilo {
    int broj_putnika;
    double prosjecna_tezina;
public:
    Autobus(int tezina, int broj_putnika, double prosjecna_tezina) :
        ApstraktnoVozilo(tezina), broj_putnika(broj_putnika),
        prosjecna_tezina(prosjecna_tezina) {}
    int DajUkupnuTezinu() const override {
        return DajTezinu() + broj_putnika * prosjecna_tezina;
    }
    Autobus* DajKopiju() const override { return new Autobus(*this); }
    void IspisiPodatke() const override {
        cout << "Vrsta vozila: Autobus" << endl;
        cout << "Vlastita tezina: " << DajTezinu() << " kg" << endl;
        cout << "Broj putnika: " << broj_putnika << endl;
        cout << "Prosjecna tezina putnika: " << prosjecna_tezina << " kg" << endl;
        cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << endl;
    }
};

class Vozilo {
    ApstraktnoVozilo *p_vozilo;
    void Test() const {
       if(!p_vozilo) throw std::logic_error("Nespecificirano vozilo!");
    }
public:
    Vozilo() : p_vozilo(nullptr) {};
    ~Vozilo() { delete p_vozilo; }
    Vozilo(const ApstraktnoVozilo &vozilo) : p_vozilo(vozilo.DajKopiju()) {}
    Vozilo(const Vozilo &vozilo) {
        if(!vozilo.p_vozilo) p_vozilo = nullptr;
        else p_vozilo = vozilo.p_vozilo->DajKopiju();
    }
    Vozilo(Vozilo &&vozilo) {
       p_vozilo = vozilo.p_vozilo; vozilo.p_vozilo = nullptr;
    }
    Vozilo &operator =(const Vozilo &vozilo) {
       if(&vozilo != this) {
           delete p_vozilo;
       if(!vozilo.p_vozilo) p_vozilo = nullptr;
       else p_vozilo = vozilo.p_vozilo->DajKopiju();
    }
       return *this;
    }
    Vozilo &operator =(Vozilo &&vozilo) {
       if(&vozilo != this) {
           delete p_vozilo;
           p_vozilo = vozilo.p_vozilo; vozilo.p_vozilo = nullptr;
       }
       return *this;
    }
    int DajTezinu() const { Test(); return p_vozilo->DajTezinu(); }
    int DajUkupnuTezinu() const { Test(); return p_vozilo->DajUkupnuTezinu(); }
    void IspisiPodatke() const { Test(); p_vozilo->IspisiPodatke(); }
};


int main() {
    ifstream citac("VOZILA.TXT");
    if(!citac) {
        cout << "Trazena datoteka ne postoji";
        return 1;
    }
    vector<Vozilo> vozila;
    bool neispravan_format(false);
    while(true) {
        char c;
        int tezina;
        if(!citac.ignore(10000, '/n'))
            break;
        citac >> c;
        if(c == 'A') {
            int broj_putnika, tezina_putnika;
            citac >> tezina >> broj_putnika;
            vector<int> tezine_putnika(broj_putnika);
            for(int i = 0; i < broj_putnika; i++)
                citac >> tezine_putnika[i];
            vozila.push_back(Automobil(tezina, tezine_putnika));
        }
        else if(c == 'B') {
            int broj_putnika;
            double prosjecna_tezina;
            citac >> tezina >> broj_putnika >> prosjecna_tezina;
            vozila.push_back(Autobus(tezina, broj_putnika, prosjecna_tezina));
        }
        else if(c == 'K') {
            int tezina_tereta;
            citac >> tezina >> tezina_tereta;
            vozila.push_back(Kamion(tezina, tezina_tereta));
        }
        else {
            neispravan_format = true;
            break;
        }
    }
    if(neispravan_format || citac.bad()) cout << "Problemi pri citanju";
    return 0;
}

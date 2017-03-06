#include <bits/stdc++.>

using namespace std;

class Spremnik {
protected:
    double tezina_spremnika;
    const char* naziv_sadrzaja, vrsta_spremnika;
public:
    Spremnik(double tezina_spremnika, const char* naziv_sadrzaja, const char* vrsta_spremnika) 
    : tezina_spremnika(tezina_spremnika), naziv_sadrzaja(naziv_sadrzaja), 
    vrsta_spremnika(vrsta_spremnika) {}
    virtual double DajTezinu() const { return tezina_spremnika; }
    virtual double DajUkupnuTezinu() const = 0;
    virtual Spremnik* DajKopiju() const = 0; 
    void Ispisi() const {
        cout << "Vrsta spremnika: " << vrsta_spremnika << endl;
        cout << "Sadrzaj: " << naziv_sadrzaja << endl;
        cout << "Vlastita tezina: " << tezina_spremnika << " kg" << endl;
        cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << endl;
    }
}

class Bure : public Spremnik {
    double tezina_tecnosti;
public:
    Bure(double tezina_spremnika, const char* naziv_tecnosti, double tezina_tecnosti) :
        Spremnik(tezina_spremnika, naziv_tecnosti, "Bure"), 
        tezina_tecnosti(tezina_tecnosti) {}
    double DajUkupnuTezinu() const override { return tezina_spremnika + tezina_tecnosti; }
    virtual Spremnik* DajKopiju() const { return new Bure(*this); }
}

class Sanduk : public Spremnik {
    int broj_predmeta;
    double tezina_predmeta;
public:
    Sanduk(double tezina_spremnika, const char* naziv_predmeta, 
        int broj_predmeta, double tezina_predmeta) :
        Spremnik(tezina_spremnika, naziv_predmeta, "Sanduk"), 
        broj_predmeta(broj_predmeta), tezina_predmeta(tezina_predmeta) {}
    double DajUkupnuTezinu() const override { return broj_predmeta * tezina_predmeta; }
    virtual Spremnik* DajKopiju() const { return new Sanduk(*this); }
}

class Skladiste {
    int max_spremnika, popunjeno;
    Spremnik** niz_spremnika;
public:
    explicit Skladiste(int max_spremnika) : 
        max_spremnika(max_spremnika), 
        niz_spremnika(new Spremnik*[max_spremnika]{},
        popunjeno(0) {}
    Skladiste(const Skladiste& r);
    Skladiste(Skladiste&& r);
    Skladiste& operator = (const Skladiste& r);
    Skladiste& operator = (Skladiste&& r);
    void DodajSanduk(double tezina_spremnika, const char* naziv_predmeta, 
        int broj_predmeta, double tezina_predmeta);
    void DodajBure(double tezina_spremnika, const char* naziv_tecnosti, double tezina_tecnosti);
    Spremnik& DajNajlaksi() {
        if(popunjeno == 0) throw range_error("Skladiste je prazno");
        return *min_element(niz_spremnika, niz_spremnika + popunjeno, 
        [](Spremnik *l, Spremnik *r) { return l->DajTezinu() < r->DajTezinu()});
    }
    int BrojPreteskih(int tezina) const {
        return count_if(niz_spremnika, niz_spremnika + popunjeno, 
        [tezina](Spremnik *s){ return s->DajUkupnuTezinu() > tezina;});
    }
    void IzlistajSkladiste() const {
        auto temp(*this);
        sort(temp.niz_spremnika, temp.niz_spremnika + popunjeno, 
        [](Spremnik *l, Spremnik *r){ return l->DajUkupnuTezinu() > r->DajUkupnuTezinu(); });
        for(int i = 0; i < popunjeno; i++) temp.niz_spremnika[i]->Ispisi();
    }
    Spremnik& DajNajtezi() {
         if(popunjeno == 0) throw range_error("Skladiste je prazno");
        return *max_element(niz_spremnika, niz_spremnika + popunjeno, 
        [](Spremnik *l, Spremnik *r) { return l->DajTezinu() < r->DajTezinu()});
    }
    ~Skladiste() { 
        for(int i = 0; i < max_spremnika; i++) delete niz_spremnika[i];
        delete[] niz_spremnika;
    }
    
}

void Skladiste::DodajSanduk(double tezina_spremnika, const char* naziv_predmeta, 
        int broj_predmeta, double tezina_predmeta) {
            if(popunjeno == max_spremnika) throw domain_error("Popunjeno skladiste");
            niz_spremnika[popunjeno] = new Sanduk(tezina_spremnika, naziv_predmeta, 
            broj_predmeta, tezina_predmeta);
            popunjeno++;
        }

void Skladiste::DodajBure(double tezina_spremnika, const char* naziv_tecnosti, double tezina_tecnosti) {
    if(popunjeno == max_spremnika) throw domain_error("Popunjeno skladiste");
    niz_spremnika[popunjeno] = new Sanduk(tezina_spremnika, naziv_tecnosti, tezina_tecnosti);
    popunjeno++;
    
}

Skladiste::Skladiste(const Skladiste& r) : 
    max_spremnika(r.max_spremnika), popunjeno(r.popunjeno), niz_spremnika(new Spremnik*[max_spremnika]{}) {
        try {
            for(int i = 0; i < popunjeno; i++) niz_spremnika[i] = r.niz_spremnika[i]->DajKopiju();
        } catch(...) {
            for(int i = 0; i < max_spremnika; i++) delete niz_spremnika[i];
            delete[] niz_spremnika;
            throw;
        }         
}

Skladiste::Skladiste(Skladiste&& r) : max_spremnika(r.max_spremnika), popunjeno(r.popunjeno), niz_spremnika(r.niz_spremnika) {
    r.max_spremnika = 0;
    r.niz_spremnika = nullptr;
}

Skladiste& Skladiste::operator = (const Skladiste& r) {
    if(this == &r) return *this;
    for(int i = 0; i < max_spremnika; i++) delete niz_spremnika[i];
    delete[] niz_spremnika;
    max_spremnika = r.max_spremnika;
    popunjeno = r.popunjeno;
    niz_spremnika = new Spremnik*[max_spremnika]{};
    try {
        for(int i = 0; i < popunjeno; i++) niz_spremnika[i] = r.niz_spremnika[i]->DajKopiju();
    } catch(...) {
        for(int i = 0; i < max_spremnika; i++) delete niz_spremnika[i];
        delete[] niz_spremnika;
        throw;
    }
    return *this;
}

Skladiste& Skladiste::operator = (Skladiste&& r) {
    if(this == &r) return *this;
    for(int i = 0; i < max_spremnika; i++) delete niz_spremnika[i];
    delete[] niz_spremnika;
    max_spremnika = r.max_spremnika;
    popunjeno = r.popunjeno;
    niz_spremnika = r.niz_spremnika;
    r.max_spremnika = 0;
    r.niz_spremnika = nullptr;
    return *this;
}

int main() {
    std::cout << "Ovo je nemoguce stic";
    return 0;
}


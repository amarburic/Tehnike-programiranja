#include <bits/stdc++.h>

using namespace std;

class Narudzba {
    const char* naziv_obroka, *narucilac;
    double cijena;
public:
    Narudzba(const char* naziv_obroka, double cijena, const char* narucilac) :
        naziv_obroka(naziv_obroka), narucilac(narucilac), cijena(cijena) {}
    string DajNazivObroka() const { return naziv_obroka; }
    double DajCijenuObroka() const { return cijena; }
    string DajNarucioca() const { return narucilac; }
    virtual double DajUkupnuCijenu() const { return cijena; }
    virtual void Ispisi() const {
        cout << "Obrok: " << DajNazivObroka() << endl;
        cout << "Cijena: " << DajCijenuObroka() <<  " KM" << endl;
        cout << "Narucilac: " << DajNarucioca() << endl;
    }
    virtual Narudzba* DajKopiju() const { return new Narudzba(*this); }
    virtual ~Narudzba() {}
};

class NarudzbaSaPicem : public Narudzba {
    const char* naziv_pica;
    double cijena_pica;
public:
    NarudzbaSaPicem(const char* naziv_obroka,
        double cijena, const char* narucilac,
        const char* naziv_pica, double cijena_pica) :
        Narudzba(naziv_obroka, cijena, narucilac),
        naziv_pica(naziv_pica), cijena_pica(cijena_pica) {}
    string DajNazivPica() const { return naziv_pica; }
    double DajCijenuPica() const { return cijena_pica; }
    double DajUkupnuCijenu() const override {
        return Narudzba::DajUkupnuCijenu() + DajCijenuPica();
    }
    void Ispisi() const override {
        cout << "Obrok: " << DajNazivObroka() << endl;
        cout << "Pice: " << DajNazivPica() << endl;
        cout << "Cijena: " << DajCijenuObroka() << " KM" <<  endl;
        cout << "Cijena pica: " << DajCijenuPica() << " KM" <<  endl;
        cout << "Ukupna cijena: " << DajUkupnuCijenu() << " KM" << endl;
        cout << "Narucilac: " << DajNarucioca() << endl;
    }
    NarudzbaSaPicem* DajKopiju() const override { return new NarudzbaSaPicem(*this); }
};

class Narudzbe {
    vector<Narudzba*> narudzbe;
    double PronadjiCijenu(string dat, string naziv) const;
public:
    Narudzbe() = default;
    Narudzbe(const Narudzbe& n) : narudzbe(n.narudzbe.size()) {
        for(int i = 0; i < narudzbe.size(); i++)
            narudzbe[i] = n.narudzbe[i]->DajKopiju();
    }
    Narudzbe(Narudzbe&& n) : narudzbe(n.narudzbe) {
        n.narudzbe.clear();
    }
    Narudzbe& operator =(const Narudzbe& n);
    Narudzbe& operator =(Narudzbe&& n);
    void NaruciObrok(const char* naziv_obroka,
        double cijena, const char* narucilac) {
            narudzbe.push_back(new Narudzba{naziv_obroka, cijena, narucilac});
    }
    void NaruciObrokSaPicem(const char* naziv_obroka,
        double cijena, const char* narucilac,
        const char* naziv_pica, double cijena_pica) {
            narudzbe.push_back(new NarudzbaSaPicem(naziv_obroka, cijena,
                narucilac, naziv_pica, cijena_pica));
    }
    void ObradiNarudzbu();
    bool DaLiImaNarudzbi() const { return !narudzbe.empty(); }
    int operator [](string narucilac) const;
    void UcitajIzDatoteka(string dat1, string dat2);
    ~Narudzbe() {
        for_each(narudzbe.begin(), narudzbe.end(),
            [](Narudzba* n){ delete n; });
    }
};

Narudzbe& Narudzbe::operator =(const Narudzbe& n) {
    if(this == &n) return *this;
    for_each(narudzbe.begin(), narudzbe.end(),
        [](Narudzba* n){ delete n; });
    narudzbe.resize(n.narudzbe.size());
    for(int i = 0; i < narudzbe.size(); i++)
        narudzbe[i] = n.narudzbe[i]->DajKopiju();
    return *this;
}

Narudzbe& Narudzbe::operator =(Narudzbe&& n) {
    if(this == &n) return *this;
    for_each(narudzbe.begin(), narudzbe.end(),
        [](Narudzba* n){ delete n; });
    narudzbe = n.narudzbe;
    n.narudzbe.clear();
    return *this;
}

void Narudzbe::ObradiNarudzbu() {
    if(narudzbe.empty())
        throw range_error("Nema vise narudzbi");
    narudzbe[0]->Ispisi();
    delete narudzbe[0];
    narudzbe.erase(narudzbe.begin());
}

int Narudzbe::operator [](string narucilac) const {
    int suma(0);
    for_each(narudzbe.begin(), narudzbe.end(),
        [&suma,&narucilac](Narudzba* n){ if(n->DajNarucioca() == narucilac) suma += n->DajUkupnuCijenu(); });
    return suma;
}

double Narudzbe::PronadjiCijenu(string dat, string naziv) const {
    ifstream citac(dat);
    if(!citac)
        throw logic_error("Trazena datoteka ne postoji");
    string procitano;
    double cijena;
    while(getline(citac, procitano)) {
//        cout << "    " << procitano << " ";
        if(naziv == procitano) {
            if(!(citac >> cijena))
                throw logic_error("Problemi pri citanju");
//            cout << "poklapa se " << cijena <<  endl;
            return cijena;
        }
        getline(citac, procitano);
//        cout << endl;
    }
    if(citac.fail() && !citac.eof())
        throw logic_error("Problemi pri citanju");
    throw logic_error("Nema odgovarajuce cijene");
}

void Narudzbe::UcitajIzDatoteka(string dat1, string dat2) {
    ifstream citac(dat1);
    if(!citac)
        throw logic_error("Trazena datoteka ne postoji");
    string narucilac, naziv_obroka, naziv_pica;
    double cijena_obroka, cijena_pica;
    while(getline(citac, narucilac)) {
        getline(citac, naziv_obroka);
        if(naziv_obroka.empty()) break;
//        cout << narucilac << " " << naziv_obroka << ": " << endl;
        cijena_obroka = PronadjiCijenu(dat2, naziv_obroka);
        getline(citac, naziv_pica);
//        cout <<endl << narucilac << " " << naziv_pica << ": "<< endl;
        if(!naziv_pica.empty())
            cijena_pica = PronadjiCijenu(dat2, naziv_pica);
        if(naziv_pica.empty())
            NaruciObrok(naziv_obroka.c_str(), cijena_obroka, narucilac.c_str());
        else
            NaruciObrokSaPicem(naziv_obroka.c_str(),
                cijena_obroka, narucilac.c_str(), naziv_pica.c_str(), cijena_pica);
//        cout << endl;
    }
    if(citac.fail() && !citac.eof())
        throw logic_error("Problemi pri citanju");
}


int main() {

    return 0;
}

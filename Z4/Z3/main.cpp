#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

class Datum {
    int dan, mjesec, godina;
    void ProvjeraDatuma(int dan, int mjesec, int godina);
public:
    Datum(int dan, int mjesec, int godina) : dan(dan), mjesec(mjesec), godina(godina) {
        ProvjeraDatuma(dan, mjesec, godina);
    };
    void Postavi(int dan, int mjesec, int godina) {
        ProvjeraDatuma(dan, mjesec, godina);
        this->dan = dan; this->mjesec = mjesec;
        this->godina = godina;
    };
    int DajDan() const { return dan; }
    int DajMjesec() const { return mjesec; }
    int DajGodinu() const { return godina; }
    void Ispisi() const {
        cout << dan << "/" << mjesec << "/" << godina;
    }
};

class Vrijeme {
    int sati, minute;
    void ProvjeraVremena(int sati, int minute);
public:
    Vrijeme(int sati, int minute) : sati(sati), minute(minute) {
        ProvjeraVremena(sati, minute);
    };
    void Postavi(int sati, int minute) {
        ProvjeraVremena(sati, minute);
        this->sati = sati; this->minute = minute;
    }
    int DajSate() const { return sati; }
    int DajMinute() const { return minute; }
    void Ispisi() const {
        cout << setfill('0') << setw(2) << right << sati << ":" << setw(2) << minute;
    }
};

class Pregled {
    string ime_pacijenta;
    Datum datum_pregleda;
    Vrijeme vrijeme_pregleda;
public:
    Pregled(const std::string &ime_pacijenta, const Datum &datum_pregleda,
        const Vrijeme &vrijeme_pregleda) : ime_pacijenta(ime_pacijenta),
        datum_pregleda(datum_pregleda), vrijeme_pregleda(vrijeme_pregleda) {};
    Pregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda,
        int godina_pregleda, int sati_pregleda, int minute_pregleda) :
        ime_pacijenta(ime_pacijenta), datum_pregleda(dan_pregleda, mjesec_pregleda, godina_pregleda),
        vrijeme_pregleda(sati_pregleda, minute_pregleda) {};
    void PromijeniPacijenta(const std::string &ime_pacijenta) { this->ime_pacijenta = ime_pacijenta; }
    void PromijeniDatum(const Datum &novi_datum) { datum_pregleda = novi_datum; }
    void PromijeniVrijeme(const Vrijeme &novo_vrijeme) { vrijeme_pregleda = novo_vrijeme; }
    void PomjeriDanUnaprijed();
    void PomjeriDanUnazad();
    std::string DajImePacijenta() const { return ime_pacijenta; }
    Datum DajDatumPregleda() const { return datum_pregleda; }
    Vrijeme DajVrijemePregleda() const { return vrijeme_pregleda; }
    friend bool DolaziPrije(const Pregled &p1, const Pregled &p2);
    void Ispisi() const {
        cout << left << setw(30) << setfill(' ') << ime_pacijenta;
        datum_pregleda.Ispisi(); cout << " "; vrijeme_pregleda.Ispisi();
        cout << endl;
    }
};

class Pregledi {
    int max_broj_pregleda, broj_registrovanih;
    Pregled **niz_pregleda;
    void PocistiMemoriju() {
        for(int i = 0; i < max_broj_pregleda; i++) delete niz_pregleda[i];
        delete[] niz_pregleda;
    }
    bool JednakiDatumi(const Datum &d1, const Datum &d2) {
        return d1.DajDan() == d2.DajDan() && d1.DajMjesec() == d2.DajMjesec()
           && d1.DajGodinu() == d2.DajGodinu();
    }
    bool JednakoVrijeme(const Vrijeme &v1, const Vrijeme &v2) {
        return v1.DajSate() == v2.DajSate()
        && v1.DajMinute() == v2.DajMinute();
    }
public:
    explicit Pregledi(int max_broj_pregleda) : max_broj_pregleda(max_broj_pregleda),
        broj_registrovanih(0), niz_pregleda(new Pregled*[max_broj_pregleda]{}) {};
    Pregledi(std::initializer_list<Pregled> spisak_pregleda);
    ~Pregledi() { PocistiMemoriju(); }
    Pregledi(const Pregledi &pregledi);
    Pregledi(Pregledi &&pregledi);
    Pregledi &operator =(const Pregledi &pregledi);
    Pregledi &operator =(Pregledi &&pregledi);
    void RegistrirajPregled(const std::string &ime_pacijenta,
     const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda);
    void RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda,
     int mjesec_pregleda, int godina_pregleda, int sati_pregleda,
     int minute_pregleda);
    void RegistrirajPregled(Pregled *pregled);
    int DajBrojPregleda() const { return broj_registrovanih; };
    int DajBrojPregledaNaDatum(const Datum &datum) const;
    Pregled &DajNajranijiPregled();
    Pregled DajNajranijiPregled() const;
    void IsprazniKolekciju();
    void ObrisiNajranijiPregled();
    void ObrisiPregledePacijenta(const std::string &ime_pacijenta);
    void IspisiPregledeNaDatum(Datum &datum) const;
    void IspisiSvePreglede() const;
};

void Datum::ProvjeraDatuma(int dan, int mjesec, int godina) {
    int dani_u_mjesecu[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0)
        dani_u_mjesecu[1]++;
    if(godina < 0 || mjesec < 1 || mjesec > 12 || dan < 1 || dan > dani_u_mjesecu[mjesec - 1])
        throw domain_error("Neispravan datum");
}

void Vrijeme::ProvjeraVremena(int sati, int minute) {
    if(sati < 0 || sati > 23 || minute < 0 || minute > 59)
        throw domain_error("Neispravno vrijeme");
}

void Pregled::PomjeriDanUnaprijed() {
    try {
        datum_pregleda.Postavi(datum_pregleda.DajDan() + 1,
            datum_pregleda.DajMjesec(), datum_pregleda.DajGodinu());
    }
    catch(...) {
        try {
            datum_pregleda.Postavi(1,
                datum_pregleda.DajMjesec() + 1, datum_pregleda.DajGodinu());
        }
        catch(...) {
            datum_pregleda.Postavi(1, 1, datum_pregleda.DajGodinu() + 1);
        }
    }
}

void Pregled::PomjeriDanUnazad() {
    if(datum_pregleda.DajDan() == 1) {
        if(datum_pregleda.DajMjesec() == 1)
            datum_pregleda.Postavi(31, 12, datum_pregleda.DajGodinu() - 1);
        else {
            int max_dana(31);
            bool uspjelo(false);
            while(!uspjelo) {
                try {
                    datum_pregleda.Postavi(max_dana--,
                        datum_pregleda.DajMjesec() - 1, datum_pregleda.DajGodinu());
                    uspjelo = true;
                }
                catch(...) {}
            }
        }
    }
    else
        datum_pregleda.Postavi(datum_pregleda.DajDan() - 1,
            datum_pregleda.DajMjesec(), datum_pregleda.DajGodinu());
}

bool DolaziPrije(const Pregled &p1, const Pregled &p2) {
    auto d1(p1.DajDatumPregleda()), d2(p2.DajDatumPregleda());
    auto v1(p1.DajVrijemePregleda()), v2(p2.DajVrijemePregleda());
    if(d1.DajGodinu() < d2.DajGodinu()) return true;
    else if(d1.DajGodinu() > d2.DajGodinu()) return false;
    else {
        if(d1.DajMjesec() < d2.DajMjesec()) return true;
        else if(d1.DajMjesec() > d2.DajMjesec()) return false;
        else {
            if(d1.DajDan() < d2.DajDan()) return true;
            else if(d1.DajDan() > d2.DajDan()) return false;
            else {
                if(v1.DajSate() < v2.DajSate()) return true;
                else if(v1.DajSate() > v2.DajSate()) return false;
                else return v1.DajMinute() < v2.DajMinute();
            }
        }
    }
}

Pregledi::Pregledi(std::initializer_list<Pregled> spisak_pregleda) :
    max_broj_pregleda(spisak_pregleda.size()), broj_registrovanih(spisak_pregleda.size()),
    niz_pregleda(new Pregled*[max_broj_pregleda]{}) {
    try {
        for(int i = 0; i < broj_registrovanih; i++)
            niz_pregleda[i] = new Pregled(*(spisak_pregleda.begin() + i));
    }
    catch(...) {
        PocistiMemoriju();
        throw;
    }
}

Pregledi::Pregledi(const Pregledi &pregledi) : max_broj_pregleda(pregledi.max_broj_pregleda),
    broj_registrovanih(pregledi.broj_registrovanih),
    niz_pregleda(new Pregled*[max_broj_pregleda]{}) {
    try {
        for(int i = 0; i < broj_registrovanih; i++)
            niz_pregleda[i] = new Pregled(*pregledi.niz_pregleda[i]);
    } catch(...) {
        PocistiMemoriju();
        throw;
    }
}

Pregledi::Pregledi(Pregledi &&pregledi) : max_broj_pregleda(pregledi.max_broj_pregleda),
    broj_registrovanih(pregledi.broj_registrovanih), niz_pregleda(pregledi.niz_pregleda) {
    pregledi.niz_pregleda = nullptr; pregledi.max_broj_pregleda = 0;
}

Pregledi &Pregledi::operator =(const Pregledi &pregledi) {
    if(&pregledi != this) {
        PocistiMemoriju();
        max_broj_pregleda = pregledi.max_broj_pregleda;
        broj_registrovanih = pregledi.broj_registrovanih;
        niz_pregleda = new Pregled*[max_broj_pregleda]{};
        for(int i = 0; i < broj_registrovanih; i++)
            niz_pregleda[i] = new Pregled(*pregledi.niz_pregleda[i]);
    }
    return *this;
}

Pregledi &Pregledi::operator =(Pregledi &&pregledi) {
    if(&pregledi != this) {
        PocistiMemoriju();
        max_broj_pregleda = pregledi.max_broj_pregleda;
        broj_registrovanih = pregledi.broj_registrovanih;
        niz_pregleda = pregledi.niz_pregleda;
        pregledi.niz_pregleda = nullptr;
        pregledi.max_broj_pregleda = 0;
    }
    return *this;
}

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta,
    const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda) {
    if(broj_registrovanih >= max_broj_pregleda)
        throw range_error("Dostignut maksimalni broj pregleda");
    niz_pregleda[broj_registrovanih++] = new Pregled(ime_pacijenta,
        datum_pregleda, vrijeme_pregleda);
}

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda,
    int mjesec_pregleda, int godina_pregleda, int sati_pregleda,
    int minute_pregleda) {
    if(broj_registrovanih >= max_broj_pregleda)
        throw range_error("Dostignut maksimalni broj pregleda");
    niz_pregleda[broj_registrovanih++] = new Pregled(ime_pacijenta, dan_pregleda,
        mjesec_pregleda, godina_pregleda, sati_pregleda, minute_pregleda);
}

void Pregledi::RegistrirajPregled(Pregled *pregled) {
    if(broj_registrovanih >= max_broj_pregleda) {
       delete pregled; throw range_error("Dostignut maksimalni broj pregleda");
    }
    niz_pregleda[broj_registrovanih++] = pregled;
}

int Pregledi::DajBrojPregledaNaDatum(const Datum &datum) const {
    return count_if(niz_pregleda, niz_pregleda + broj_registrovanih,
        [datum, this](Pregled* p) {
            return JednakiDatumi(datum, p->DajDatumPregleda());
        });
}

Pregled &Pregledi::DajNajranijiPregled() {
    if(DajBrojPregleda() == 0) throw domain_error("Nema registriranih pregleda");
    return **min_element(niz_pregleda, niz_pregleda + broj_registrovanih,
    [](Pregled *p1, Pregled *p2) { return DolaziPrije(*p1, *p2); });

}

Pregled Pregledi::DajNajranijiPregled() const {
    if(DajBrojPregleda() == 0) throw domain_error("Nema registriranih pregleda");
    return **min_element(niz_pregleda, niz_pregleda + broj_registrovanih,
    [](Pregled *p1, Pregled *p2) { return DolaziPrije(*p1, *p2); });
}

void Pregledi::IsprazniKolekciju() {
    for(int i = 0; i < broj_registrovanih; i++) delete niz_pregleda[i];
    broj_registrovanih = 0;
}

void Pregledi::ObrisiNajranijiPregled() {
    if(broj_registrovanih == 0)
        throw domain_error("Prazna kolekcija");
    auto najraniji(DajNajranijiPregled());
    for(int i = 0; i < broj_registrovanih; i++) {
        if(JednakiDatumi(najraniji.DajDatumPregleda(), niz_pregleda[i]->DajDatumPregleda())
           && JednakoVrijeme(najraniji.DajVrijemePregleda(), niz_pregleda[i]->DajVrijemePregleda())
           && najraniji.DajImePacijenta() == niz_pregleda[i]->DajImePacijenta()) {
            delete niz_pregleda[i];
            for(int j = i; j < broj_registrovanih - 1; j++)
                niz_pregleda[j] = niz_pregleda[j + 1];
            niz_pregleda[broj_registrovanih - 1] = nullptr;
            broj_registrovanih--;
            break;
        }
    }
}

void Pregledi::ObrisiPregledePacijenta(const std::string &ime_pacijenta) {
    for(int i = 0; i < broj_registrovanih; i++) {
        if(niz_pregleda[i]->DajImePacijenta() == ime_pacijenta) {
            delete niz_pregleda[i];
            for(int j = i; j < broj_registrovanih - 1; j++)
                niz_pregleda[j] = niz_pregleda[j + 1];
            niz_pregleda[broj_registrovanih - 1] = nullptr;
            broj_registrovanih--; i--;
        }
    }
}

void Pregledi::IspisiPregledeNaDatum(Datum &datum) const {
    vector<Pregled*> pregledi;
    copy_if(niz_pregleda, niz_pregleda + broj_registrovanih, back_inserter(pregledi),
        [datum, this](Pregled *p) { return JednakiDatumi(p->DajDatumPregleda(), datum); });
    sort(pregledi.begin(), pregledi.end(),
         [](Pregled* p1, Pregled* p2) { return DolaziPrije(*p1, *p2); });
    for(auto i : pregledi)
        i->Ispisi();
}

void Pregledi::IspisiSvePreglede() const {
    sort(niz_pregleda, niz_pregleda + broj_registrovanih,
         [](Pregled* p1, Pregled* p2) { return DolaziPrije(*p1, *p2); });
    for(int i = 0; i < broj_registrovanih; i++)
        niz_pregleda[i]->Ispisi();
}

int main() {
    Datum d1 (12,12,2015), d2(11,12,2014);

    Vrijeme v1(10,15) ,v2(23,59) ;
    Pregledi pregledi(5) ;

    pregledi.RegistrirajPregled("Benjamin", d1,v1) ;
    pregledi.RegistrirajPregled("Ante", 10,12,2015,15,0) ;
    pregledi.RegistrirajPregled("Ivan", 12,12,2015,10,0) ;
    pregledi.RegistrirajPregled("Emir", d2,v2) ;

    std::cout<<"NajranijiPregled : " << std::endl ;
    pregledi.DajNajranijiPregled().Ispisi() ;

    pregledi.ObrisiNajranijiPregled() ;
    std::cout<<"Ostali pregledi:" << std::endl ;

    pregledi.IspisiSvePreglede() ;
    return 0;
}

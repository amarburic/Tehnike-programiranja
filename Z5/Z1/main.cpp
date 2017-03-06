#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <vector>

using namespace std;

class Student {
    int indeks, g_studija;
    string ime_i_prezime, adresa, br_telefona;
    static bool NeispravanBrojTelefona(string br_telefona);
public:
    Student(int indeks, int g_studija,
        const char* ime_i_prezime, const char* adresa, const char* br_telefona);
    int DajIndeks() const { return indeks; }
    int DajGodinuStudija() const { return g_studija; }
    string DajImePrezime() const { return ime_i_prezime; }
    string DajAdresu() const { return adresa; }
    string DajTelefon() const { return br_telefona; }
    void Ispisi() const;
};

class Laptop {
    int broj;
    string naziv, karakteristike;
    bool je_zaduzen = false;
    Student* zaduzenik = nullptr;
public:
    Laptop(int broj, const char* naziv, const char* karakteristike) :
        broj(broj), naziv(naziv), karakteristike(karakteristike) {
        if(broj < 0) throw domain_error("Neispravni parametri");
    }
    int DajEvidencijskiBroj() const { return broj; }
    string DajNaziv() const { return naziv; }
    string DajKarakteristike() const { return karakteristike; }
    void Zaduzi(Student& s) {
        if(je_zaduzen) throw domain_error("Laptop vec zaduzen");
        je_zaduzen = true;
        zaduzenik = &s;
    }
    void Razduzi() { je_zaduzen = false; zaduzenik = nullptr; }
    bool DaLiJeZaduzen() const { return je_zaduzen; }
    Student& KodKogaJe() const {
        if(!je_zaduzen) throw domain_error("Laptop nije zaduzen");
        return *zaduzenik;
    }
    void Ispisi() const;
};

class Administracija {
    vector<shared_ptr<Student>> studenti;
    vector<shared_ptr<Laptop>> laptopi;
public:
    Administracija() = default;
    Administracija(const Administracija&) = delete;
    Administracija& operator = (const Administracija&) = delete;
    Administracija(Administracija&&) = default;
    Administracija& operator = (Administracija&&) = default;
    void RegistrirajNovogStudenta(int indeks, int g_studija,
        const char* ime_i_prezime, const char* adresa, const char* br_telefona);
    void RegistrirajNoviLaptop(int broj, const char* naziv, const char* karakteristike);
    Student& NadjiStudenta(int indeks);
    Student NadjiStudenta(int indeks) const;
    Laptop& NadjiLaptop(int broj);
    Laptop NadjiLaptop(int broj) const;
    void IzlistajStudente() const {
        for(const shared_ptr<Student>& s : studenti)
            s->Ispisi(), cout << endl;
    }
    void IzlistajLaptope() const;
    void ZaduziLaptop(int indeks, int broj);
    int NadjiSlobodniLaptop() const;
    void RazduziLaptop(int broj);
    void PrikaziZaduzenja() const;
 };

Student::Student(int indeks, int g_studija,
    const char* ime_i_prezime, const char* adresa, const char* br_telefona) :
    indeks(indeks), g_studija(g_studija), ime_i_prezime(ime_i_prezime),
    adresa(adresa), br_telefona(br_telefona) {
    if(indeks < 10000 || indeks > 99999 || g_studija > 8 || g_studija < 1
    || NeispravanBrojTelefona(br_telefona))
        throw domain_error("Neispravni parametri");
}

void Student::Ispisi() const {
    string ciklus[]{"I", "I", "I", "II", "II", "III", "III", "III"};
    int godina[]{1, 2, 3, 1, 2, 1, 2, 3};
    cout << "Broj indeksa: " << DajIndeks() << endl;
    cout << "Godina Studija: " << godina[DajGodinuStudija() - 1]
    << "/" << ciklus[DajGodinuStudija() - 1] << endl;
    cout << "Ime i prezime: " << DajImePrezime() << endl;
    cout << "Adresa: " << DajAdresu() << endl;
    cout << "Telefon: " << DajTelefon() << endl;
}

bool Student::NeispravanBrojTelefona(string br_telefona) {
    while(true) {
        if(br_telefona.size() < string("1/1-1").size()) return true;
        if(!isdigit(br_telefona[0]))
            return true;
        br_telefona.erase(br_telefona.begin());
        if(br_telefona[0] == '/') {
            br_telefona.erase(br_telefona.begin());
            break;
        }
    }
    while(true) {
        if(br_telefona.size() < string("1-1").size()) return true;
        if(!isdigit(br_telefona[0]))
            return true;
        br_telefona.erase(br_telefona.begin());
        if(br_telefona[0] == '-') {
            br_telefona.erase(br_telefona.begin());
            break;
        }
    }
    while(true) {
        if(br_telefona.empty() || !isdigit(br_telefona[0])) return true;
        br_telefona.erase(br_telefona.begin());
        if(br_telefona.empty()) break;
    }
    return false;
}

void Laptop::Ispisi() const {
    cout << "Evidencijski broj: " << DajEvidencijskiBroj() << endl;
    cout << "Naziv: " << DajNaziv() << endl;
    cout << "Karakteristike: " << DajKarakteristike() << endl;
}

void Administracija::RegistrirajNovogStudenta(int indeks, int g_studija,
    const char* ime_i_prezime, const char* adresa, const char* br_telefona) {
    if(find_if(studenti.begin(), studenti.end(),
        [indeks](shared_ptr<Student> s) { return s->DajIndeks() == indeks; })
        != studenti.end())
        throw domain_error("Student s tim indeksom vec postoji");
    studenti.emplace_back(make_shared<Student>(indeks, g_studija, ime_i_prezime, adresa, br_telefona));
}

void Administracija::RegistrirajNoviLaptop(int broj, const char* naziv, const char* karakteristike) {
    if(find_if(laptopi.begin(), laptopi.end(),
        [broj](shared_ptr<Laptop> l) { return l->DajEvidencijskiBroj() == broj; })
        != laptopi.end())
        throw domain_error("Laptop s tim evidencijskim brojem vec postoji");
    laptopi.emplace_back(make_shared<Laptop>(broj, naziv, karakteristike));
}

Student& Administracija::NadjiStudenta(int indeks) {
    auto s(find_if(studenti.begin(), studenti.end(),
    [indeks](shared_ptr<Student> s) { return s->DajIndeks() == indeks; }));
    if(s == studenti.end()) throw domain_error("Student nije nadjen");
    else return **s;
}

Student Administracija::NadjiStudenta(int indeks) const {
    auto s(find_if(studenti.begin(), studenti.end(),
    [indeks](shared_ptr<Student> s) { return s->DajIndeks() == indeks; }));
    if(s == studenti.end()) throw domain_error("Student nije nadjen");
    else return **s;
}

Laptop& Administracija::NadjiLaptop(int broj) {
    auto l(find_if(laptopi.begin(), laptopi.end(),
        [broj](shared_ptr<Laptop> l) { return l->DajEvidencijskiBroj() == broj; }));
    if(l == laptopi.end()) throw domain_error("Laptop nije nadjen");
    else return **l;
}

Laptop Administracija::NadjiLaptop(int broj) const {
    auto l(find_if(laptopi.begin(), laptopi.end(),
        [broj](shared_ptr<Laptop> l) { return l->DajEvidencijskiBroj() == broj; }));
    if(l == laptopi.end()) throw domain_error("Laptop nije nadjen");
    else return **l;
}

void Administracija::IzlistajLaptope() const {
    for(const shared_ptr<Laptop>& l : laptopi) {
        l->Ispisi();
        if(l->DaLiJeZaduzen()) {
            auto s(l->KodKogaJe());
            cout << "Zaduzio(la): " << s.DajImePrezime() << " (" << s.DajIndeks() << ")" << endl;
        }
        cout << endl;
    }
}

void Administracija::ZaduziLaptop(int indeks, int broj) {
    Student& s(NadjiStudenta(indeks));
    Laptop& l(NadjiLaptop(broj));
    if(l.DaLiJeZaduzen()) throw domain_error("Laptop vec zaduzen");
    if(find_if(laptopi.begin(), laptopi.end(),
        [indeks](shared_ptr<Laptop> l) { return l->DaLiJeZaduzen() && (l->KodKogaJe().DajIndeks() == indeks); })
        != laptopi.end()) throw domain_error("Student je vec zaduzio laptop");
    l.Zaduzi(s);
}

int Administracija::NadjiSlobodniLaptop() const {
    auto l(find_if(laptopi.begin(), laptopi.end(),
        [](shared_ptr<Laptop> l) { return l->DaLiJeZaduzen(); }));
    if(l == laptopi.end()) throw domain_error("Nema slobodnih laptopa");
    return (*l)->DajEvidencijskiBroj();
}

void Administracija::RazduziLaptop(int broj) {
    Laptop& l(NadjiLaptop(broj));
    if(!l.DaLiJeZaduzen()) throw domain_error("Laptop nije zaduzen");
    l.Razduzi();
}

void Administracija::PrikaziZaduzenja() const {
    bool ima_zaduzenja(false);
    for(auto l : laptopi) {
        if(l->DaLiJeZaduzen()) {
            ima_zaduzenja = true;
            cout << "Student " << l->KodKogaJe().DajImePrezime() << " (" << l->KodKogaJe().DajIndeks()
            << ") zaduzio/la laptop broj " << l->DajEvidencijskiBroj() << endl;
        }
   }
   if(!ima_zaduzenja) cout << "Nema zaduzenja" << endl;
}

int main() {

}

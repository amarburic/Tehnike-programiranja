#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum class Smjer {Nalijevo, Nadesno};
enum class Pravci {Sjever, Istok, Jug, Zapad};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar,
 NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};

bool UnosKomande(Komande&, int&, KodoviGresaka&);

void AktivirajRobota();
void DeaktivirajRobota();
void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu);
void Idi(int &x, int &y, Pravci orijentacija, int korak);
void IspisiPoziciju(int x, int y, Pravci orijentacija);
void PrijaviGresku(KodoviGresaka kod_greske);
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
 Pravci &orijentacija);

bool aktivan(true), kraj(false);

int main() {
    int x(0), y(0), parametar;
    Pravci orijentacija(Pravci::Sjever);
    Komande komanda;
    KodoviGresaka kod_greske;
    bool ispisi(true);
    while(!kraj) {
        if(ispisi) IspisiPoziciju(x, y, orijentacija);
        if(UnosKomande(komanda, parametar, kod_greske)) {
            if(aktivan || komanda == Komande::Aktiviraj)
                IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
            ispisi = true;
        }
        else {
            PrijaviGresku(kod_greske);
            ispisi = false;
        }
    }
    cout << "Dovidjenja!" << endl;
    return 0;
}

void AktivirajRobota() {
    aktivan = true;
}

void DeaktivirajRobota() {
    aktivan = false;
}

void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu) {
    if(na_koju_stranu == Smjer::Nadesno)
        orijentacija = Pravci((int(orijentacija) + 1) % 4);
    else if(na_koju_stranu == Smjer::Nalijevo) {
        if(orijentacija == Pravci::Sjever)
            orijentacija = Pravci::Zapad;
        else
            orijentacija = Pravci(int(orijentacija) - 1);
    }
}

void Idi(int &x, int &y, Pravci orijentacija, int korak) {
    switch(orijentacija) {
    case Pravci::Sjever:
        y += korak;
    break;
    case Pravci::Istok:
        x += korak;
    break;
    case Pravci::Jug:
        y -= korak;
    break;
    case Pravci::Zapad:
        x -= korak;
    break;
    }
}

void IspisiPoziciju(int x, int y, Pravci orijentacija) {
    cout << "Robot je trenutno "
    << (aktivan?"":"ne")
    << "aktivan, nalazi se na poziciji ("
    << x << "," << y << ") i gleda na ";
    switch(orijentacija) {
    case Pravci::Sjever:
        cout << "sjever";
    break;
    case Pravci::Istok:
        cout << "istok";
    break;
    case Pravci::Jug:
        cout << "jug";
    break;
    case Pravci::Zapad:
        cout << "zapad";
    break;
    }
    cout << "." << endl;
}

void PrijaviGresku(KodoviGresaka kod_greske) {
    switch(kod_greske) {
    case KodoviGresaka::PogresnaKomanda:
        cout << "Nerazumljiva komanda!" << endl;
    break;
    case KodoviGresaka::NedostajeParametar:
        cout << "Komanda trazi parametar koji nije naveden!" << endl;
    break;
    case KodoviGresaka::NeispravanParametar:
        cout << "Parametar komande nije ispravan!" << endl;
    break;
    case KodoviGresaka::SuvisanParametar:
        cout << "Zadan je suvisan parametar nakon komande!" << endl;
    break;
    }
}

void IzvrsiKomandu(Komande komanda, int parametar, int& x, int& y, Pravci& orijentacija) {
    switch(komanda) {
    case Komande::Aktiviraj:
        AktivirajRobota();
    break;
    case Komande::Deaktiviraj:
        DeaktivirajRobota();
    break;
    case Komande::Idi:
        Idi(x, y, orijentacija, parametar);
    break;
    case Komande::Nalijevo:
        Rotiraj(orijentacija, Smjer::Nalijevo);
    break;
    case Komande::Nadesno:
        Rotiraj(orijentacija, Smjer::Nadesno);
    break;
    case Komande::Kraj:
        kraj = true;
    break;
    }
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
    string unos, kljucne_rijeci("ALDIK");
    cout << "Unesi komandu: ";
    getline(cin, unos);
    if(unos.empty()) {
        kod_greske = KodoviGresaka::PogresnaKomanda;
        return false;
    }
    bool ima_komande(false), ima_parametra(true);
    for(int i = 0; i <= unos.size(); i++) {
        if(unos[i] == ' ' || unos[i] == '\t') continue;
        else if(i == unos.size()) {
            if(!ima_parametra) {
                kod_greske = KodoviGresaka::NedostajeParametar;
                return false;
            }
            if(!ima_komande) {
                kod_greske = KodoviGresaka::PogresnaKomanda;
                return false;
            }
            return true;
        }
        else if(find(kljucne_rijeci.begin(), kljucne_rijeci.end(), unos[i]) == kljucne_rijeci.end()) {
            if(!ima_komande) {
                kod_greske = KodoviGresaka::PogresnaKomanda;
                return false;
            } else {
                if(komanda == Komande::Idi) {
                    if(ima_parametra) {
                        kod_greske = KodoviGresaka::NeispravanParametar;
                        return false;
                    } else {
                        bool je_negativan(unos[i] == '-');
                        if(je_negativan) i++;
                        if(i == unos.size() || unos[i] < '0' || unos[i] > '9') {
                            kod_greske = KodoviGresaka::NeispravanParametar;
                            return false;
                        }
                        int broj(0);
                        while(i < unos.size() && unos[i] >= '0' && unos[i] <= '9') {
                            broj *= 10;
                            broj += unos[i++] - '0';
                        }
                        i--; ima_parametra = true;
                        parametar = broj;
                        if(je_negativan) parametar *= -1;
                    }
                } else {
                    kod_greske = KodoviGresaka::SuvisanParametar;
                    return false;
                }
            }
        } else {
            if(ima_komande) {
                if(!ima_parametra || komanda == Komande::Idi) {
                    kod_greske = KodoviGresaka::NeispravanParametar;
                    return false;
                } else {
                    kod_greske = KodoviGresaka::SuvisanParametar;
                    return false;
                }
            }
            ima_komande = true;
            switch(unos[i]) {
                case 'L':
                    komanda = Komande::Nalijevo;
                break;
                case 'D':
                    komanda = Komande::Nadesno;
                break;
                case 'K':
                    komanda = Komande::Kraj;
                break;
                case 'I':
                    komanda = Komande::Idi;
                    ima_parametra = false;
                break;
                case 'A':
                    if(i < unos.size() - 1 && (unos[i + 1] == '+' || unos[i + 1] == '-')) {
                        switch(unos[i + 1]) {
                            case '+':
                                komanda = Komande::Aktiviraj;
                            break;
                            case '-':
                                komanda = Komande::Deaktiviraj;
                            break;
                        }
                        i++;
                    } else {
                        kod_greske = KodoviGresaka::PogresnaKomanda;
                        return false;
                    }
                break;
            }
        }
    }
}

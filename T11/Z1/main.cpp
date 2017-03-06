#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

class Tim {
    char ime_tima[20];
    int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza,
    broj_datih, broj_primljenih, broj_poena;
public: 
    Tim(const char ime[]) : broj_odigranih(0), broj_pobjeda(0), broj_nerijesenih(0), broj_poraza(0),
    broj_datih(0), broj_primljenih(0), broj_poena(0) { strncpy(ime_tima, ime, 20); };
    void ObradiUtakmicu(int broj_datih, int broj_primljenih);
    const char *DajImeTima() const { return ime_tima; };
    int DajBrojPoena() const { return broj_poena; };
    int DajGolRazliku() const { return broj_datih - broj_primljenih; };
    void IspisiPodatke() const;
};

void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih) {
    broj_odigranih++;
    this->broj_datih += broj_datih;
    this->broj_primljenih += broj_primljenih;
    if(broj_datih == broj_primljenih) broj_poena++, broj_nerijesenih++;
    else if(broj_datih < broj_primljenih) broj_poraza++;
    else broj_poena += 3, broj_pobjeda++;
}

void Tim::IspisiPodatke() const {
    cout << left << setw(20) << ime_tima << right << setw(4) << broj_odigranih 
    << setw(4) << broj_pobjeda << setw(4) << broj_nerijesenih << setw(4)
    << broj_poraza << setw(4) << broj_datih << setw(4) << broj_primljenih 
    << setw(4) << broj_poena << endl;
}

int main() {
    Tim t1("FK Sarajevo") ;
    
    t1.ObradiUtakmicu(6,1) ;
    t1.ObradiUtakmicu(0,1) ;
    t1.ObradiUtakmicu(2,1) ;
    t1.ObradiUtakmicu(0,1) ;
    t1.ObradiUtakmicu(1,1) ;

    Tim t2("FK Zeljeznicar") ;

    t2.ObradiUtakmicu(0,1) ;
    t2.ObradiUtakmicu(1,2) ;
    t2.ObradiUtakmicu(1,0) ;
    t2.ObradiUtakmicu(1,1) ;
    t2.ObradiUtakmicu(2,1) ;
    t2.ObradiUtakmicu(2,1) ;
    t2.ObradiUtakmicu(0,0) ;
    t2.ObradiUtakmicu(1,0) ;
    t2.ObradiUtakmicu(3,2) ;
    t2.ObradiUtakmicu(0,2) ;


    t1.IspisiPodatke() ;
    t2.IspisiPodatke() ;
}

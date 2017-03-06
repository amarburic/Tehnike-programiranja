#include <iostream>
#include <set>
#include <list>
#include <stack>
#include <utility>
#include <stdexcept>
#include <iterator>
#include <functional>
#include <algorithm>
#include <iomanip>

using namespace std;

enum class Boje {Herc, Karo, Pik, Tref};

list<set<Boje>> KreirajSpil() {
    return list<set<Boje>>(13, {Boje::Herc, Boje::Karo, Boje::Pik, Boje::Tref});
}

stack<pair<string, string>> IzbaciKarte(list<set<Boje>> &spil, const pair<int, int> &za_izbaciti) {
    if(za_izbaciti.first < 1 || za_izbaciti.first > 52 || za_izbaciti.second < 1)
        throw logic_error("Neispravni elementi za izbacivanje!");
    if(spil.size() != 13) throw logic_error("Neispravna lista!");
    stack<pair<string, string>> izbacene;
    const char* boje[]{"Herc", "Karo", "Pik", "Tref"};
    const char* vrijednosti[]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    auto trenutna_boja(Boje::Tref);
    auto it_l = spil.end();
    it_l--;
    int preostalo(0);
    for(auto it_l : spil)
        for(auto it_s : it_l)
            preostalo++;
    for(int i = za_izbaciti.second; i > 0 && preostalo; i--) {
        int korak(za_izbaciti.first);
        while(korak) {
            it_l++;
            if(it_l == spil.end()) {
                it_l = spil.begin();
                trenutna_boja = Boje((int(trenutna_boja) + 1) % 4);
            }
            if(it_l->count(trenutna_boja))
                korak--;
        }
        izbacene.push({boje[int(trenutna_boja)], vrijednosti[distance(spil.begin(), it_l)]});
        it_l->erase(trenutna_boja);
        preostalo--;
    }
    return izbacene;
}

void VratiPosljednjihNKarata(list<set<Boje>> &spil, stack<pair<string, string>> &izbacene, int n) {
    const char* boje[]{"Herc", "Karo", "Pik", "Tref"};
    const char* vrijednosti[]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    if(n > izbacene.size()) throw range_error("“Nedovoljno karata u steku!");
    function<void(void)> rekurzija = [&](){
        auto gornja(izbacene.top());
        if(find(begin(boje), end(boje), gornja.first) == end(boje) ||
        find(begin(vrijednosti), end(vrijednosti), gornja.second) == end(vrijednosti))
            throw logic_error("Neispravne karte!");
        izbacene.pop();
        rekurzija();
        izbacene.push(gornja);
    };
    while(n > 0) {
        auto gornja(izbacene.top());
        izbacene.pop();
        n--;
        auto it_l(spil.begin());
        advance(it_l, distance(begin(vrijednosti),
        find(begin(vrijednosti), end(vrijednosti), gornja.second)));
        it_l->insert(Boje(distance(begin(boje), find(begin(boje), end(boje), gornja.first))));
    }
}

int PrebrojiKarte(const list<set<Boje>> &spil) {
    if(spil.size() != 13) throw logic_error("Neispravna lista!");
    int nedostaje(0);
    for(auto s : spil)
        nedostaje += 4 - s.size();
    return nedostaje;
}

int main() {
    auto spil(KreirajSpil());
    int n, r;
    cout << "Unesite korak razbrajanja: ";
    cin >> r;
    cout << "Unesite broj karata koje zelite izbaciti: ";
    cin >> n;
    try {
        auto izbacene(IzbaciKarte(spil, make_pair(r, n)));
        int size(0);
        for(auto s : spil)
            size += s.size();
        cout << "U spilu trenutno ima: " << size << " karata, i to: " << endl;
        const char* boje[]{"Herc", "Karo", "Pik", "Tref"};
        const char* vrijednosti[]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        for(auto p_b = begin(boje); p_b != end(boje); p_b++) {
            cout << left << setw(5) << string(*p_b) + ":";
            for(auto it_l = spil.begin(); it_l != spil.end(); it_l++)
                if(it_l->count(Boje(p_b - begin(boje))))
                    cout << " " << vrijednosti[distance(spil.begin(), it_l)];
            cout << endl;
        }
        cout << "Unesite broj karata koje zelite vratiti u spil: ";
        cin >> n;
        VratiPosljednjihNKarata(spil, izbacene, n);
        cout << "Broj karata u steku: " << izbacene.size() << endl;
        cout << "Trenutne karte u steku:" << endl;
        while(!izbacene.empty()) {
            cout << izbacene.top().first << " " << izbacene.top().second << endl;
            izbacene.pop();
        }
    } catch(domain_error e) {
        cout << "Izuzetak: " << e.what();
    } catch(logic_error e) {
        cout << "Izuzetak: " << e.what();
    }
return 0;
}

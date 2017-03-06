#include <iostream>
#include <vector>

using namespace std;

template <typename UporedivTip>
vector<UporedivTip> Presjek(vector<UporedivTip> &v1, vector<UporedivTip> &v2){
    vector<UporedivTip> v3;
    for(UporedivTip &i : v1)
        for(UporedivTip &j : v2) {
            if(i != j)
                continue;
            bool duplikat(false);
            for(UporedivTip &k : v3)
                if(i == k) {
                    duplikat = true;
                    break;
                }
            if(!duplikat) {
                v3.push_back(i);
                break;
            }
        }
    return v3;
}

template <typename UporedivTip>
void UcitajSkupoveIIspisiPresjek(string tip){
    int n;
    cout << "Unesite broj elemenata prvog vektora tipa " << tip << ": ";
    cin >> n;
    vector<UporedivTip> v1(n);
    cout << "Unesite elemente prvog vektora: ";
    for(UporedivTip &t : v1)
        cin >> t;
    cout << "Unesite broj elemenata drugog vektora tipa " << tip << ": ";
    cin >> n;
    vector<UporedivTip> v2(n);
    cout << "Unesite elemente drugog vektora: ";
    for(UporedivTip &t : v2)
        cin >> t;
    cout << "Presjek ta dva skupa je skup: ";
    for(UporedivTip &t: Presjek(v1, v2))
        cout << t << " ";
    cout << endl;
}

int main() {
    UcitajSkupoveIIspisiPresjek<double>("double");
    UcitajSkupoveIIspisiPresjek<string>("string");
    return 0;
}


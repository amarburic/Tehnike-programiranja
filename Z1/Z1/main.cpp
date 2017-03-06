#include <iostream>
#include <vector>

using namespace std;

int pow(int baza, int eksponent) {
        int rez(1);
        for(int i = 1; i <= eksponent; i++)
                rez*=baza;
        return rez;
}

int BrojCifara(int a) {
        int n(0);
        while(n++, (a/=10) != 0);
        return n;
}

vector<int> ArmstrongoviBrojevi(int p, int q) {
        vector<int> v;
        if(q < 0 || p > q)
                return v;
        if(p < 0)
                p = 0;
        for(int i = p; i <= q; i++) {
                int suma(0), broj(i), broj_cifara(BrojCifara(broj));
                do{
                        suma+=pow((broj%10),broj_cifara);
                        broj/=10;
                }while(broj != 0);
                if(suma == i) {
                        v.push_back(i);
                }
        }
        return v;
} 

int main() {
        int p, q;
        cout << "Unesite dva broja: ";
        cin >> p >> q;
        vector<int> v(ArmstrongoviBrojevi(p, q));
        if(v.size() == 0)
                cout << "Nema Armstrongovih brojeva u traženom opsegu";
        else {
                cout << "Armstrongovi brojevi u opsegu [" << p << ", " << q << "]: ";
                for(int i = 0; i < v.size(); i++){
                        if(i != 0)
                                cout << ",";
                        cout << v[i];
                }
        }
        return 0;
}


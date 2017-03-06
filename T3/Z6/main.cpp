#include <iostream>
#include <string>

using namespace std;

string IzdvojiRijec(string tekst, int n){
        if(n < 1)
                throw "N mora biti veci od 0";
        int brojac(0);
        for(int i = 0; i < tekst.length(); i++){
                if(tekst[i] != ' '){
                        brojac++;
                        int j(i+1);
                        for(; j <tekst.length() && tekst[j] != ' '; j++);
                        if(brojac<n){
                                if(j == tekst.length())
                                        throw "N je veci od broja rijeci u recenici";
                                else i = j;
                        }
                        else return tekst.substr(i, j-i);  
                }
        }
}
int main() {
        string tekst;
        int n;
        cout << "Unesi recenicu: " << endl;
        getline(cin, tekst);
        cout << "Unesi n: "; 
        cin >> n;
        try{
                cout << n << ". rijec u tekstu je: " << IzdvojiRijec(tekst, n);
        }catch(const char greska[]){
                cout << "Doslo je do sljedece greske : \n" << greska << endl; 
        }
        return 0;
}


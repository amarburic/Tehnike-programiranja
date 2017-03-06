#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Sortiraj(vector<int> &v) {
        for(int i = 0; i < v.size(); i ++)
                for(int j = i + 1; j < v.size(); j++)
                        if(v[i] < v[j]) {
                                int temp(v[i]);
                                v[i] = v[j]; v[j] = temp;
                        }
}

string IstakniFraze(string rec, vector<string> fraze) {
        vector<int> desna, lijeva;
        for(int i = 0; i < fraze.size(); i++)
                for(int j = 0; j < (int)rec.length() - (int)fraze[i].length() + 1; j++)
                        if(fraze[i].length() > 0 && rec.substr(j, fraze[i].length()) == fraze[i]) {
                                lijeva.push_back(j);
                                desna.push_back(j + fraze[i].length());
                                j += fraze[i].length();
                        }
        Sortiraj(desna); Sortiraj(lijeva);
        int pomak(0);
        while(desna.size() != 0) {
                if(lijeva.size() == 0 || lijeva[lijeva.size() - 1] >= desna[desna.size() - 1]) {
                        rec.insert(rec.begin() + desna[desna.size() - 1] + pomak++, ')');
                        desna.pop_back();
                } else {
                        rec.insert(rec.begin() + lijeva[lijeva.size() - 1] + pomak++, '(');
                        lijeva.pop_back();
                }
        }
        return rec;
}

int main() {
        
        string recenica, unos;
        vector<string> fraze; 
        cout << "Unesite recenicu:";
        getline(cin, recenica);
        cout << "\nUnesite fraze:";
        while(true) {
                getline(cin, unos);
                if(unos.length() == 0)
                        break;
                fraze.push_back(unos);
        }
        cout << "\nRecenica nakon modifikacije:\n"<< IstakniFraze(recenica, fraze);
        return 0;
        
}


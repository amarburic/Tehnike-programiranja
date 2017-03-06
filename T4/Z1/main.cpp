#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cout << "Unesite broj rijeci: ";
    cin >> n;
    vector<string> unos(n);
    for(string &s : unos)
        cin >> s;
    string min(unos[0]), max(unos[0]);
    for(string &s : unos){
        if(s < min)
            min = s;
        if(s > max)
            max = s;
    }
    for(int i = 0; i < unos.size(); i++)
        for(int j = i + 1; j < unos.size(); j++)
            if(unos[i] == unos[j])
                unos.erase(unos.begin() + j--);
    cout << "Prva rijec: " << min << ".\nPosljednja rijec: " << max << ".";
    for(string &s : unos)
        cout << "\n" << s;
    return 0;
}


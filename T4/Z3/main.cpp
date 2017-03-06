#include <iostream>
#include <string>

using namespace std;

void IzvrniString(string &s){

    for(int i = 0; i < s.length() / 2; i++){
        char temp(s[i]);
        s[i] = s[s.length() - i -1];
        s[s.length() - i -1] = temp;
    }
    
}
int main() {
    string s;
    cout << "Unesite string: ";
    getline(cin, s);
    IzvrniString(s);
    cout << s;
    return 0;
}


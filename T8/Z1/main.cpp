#include <iostream>
#include <iomanip>

using namespace std;

struct Vrijeme {
  int sati, minute, sekunde;
 };

void IspisiVrijeme (Vrijeme v) {
      cout << setfill('0') << setw(2) << v.sati << ":"
      << setfill('0') << setw(2) << v.minute << ":"
      << setfill('0') << setw(2) << v.sekunde;
}

Vrijeme SaberiVrijeme (Vrijeme v1, Vrijeme v2) {
    Vrijeme v3{v1.sati + v2.sati, v1.minute + v2.minute, v1.sekunde + v2.sekunde};
    if(v3.sekunde >= 60) v3.sekunde %= 60, v3.minute++;
    if(v3.minute >= 60) v3.minute %= 60, v3.sati++;
    if(v3.sati >= 24) v3.sati %= 24;
    return v3;
}

int main() {
    Vrijeme v1, v2;
    cout << "Unesite prvo vrijeme: ";
    cin >> v1.sati >> v1.minute >> v1.sekunde;
    cout << "Unesite drugo vrijeme: ";
    cin >> v2.sati >> v2.minute >> v2.sekunde;
    cout << "Njihov zbir: ";
    IspisiVrijeme(SaberiVrijeme(v1, v2));
    return 0;
}


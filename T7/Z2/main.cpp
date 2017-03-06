#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(1000, '\n');
    char**pokazivaci = new char*[n];
    for(int i = 1; i <= n; i++) {
        char unos[50];
        cin.getline(unos, 50);
        pokazivaci[i - 1] = new char[strlen(unos) + 1];
        strcpy(pokazivaci[i - 1], unos);
    }
    sort(pokazivaci, pokazivaci + n, [](char* lhs, char* rhs){return strcmp(lhs, rhs) < 0;});
    for(int i = 0; i < n; i++)
        cout << pokazivaci[i] << endl;
    for(int i = 0; i < n; i++) delete[] pokazivaci[i];
    delete[] pokazivaci;
    return 0;
}


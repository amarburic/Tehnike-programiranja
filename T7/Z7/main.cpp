#include <iostream>
#include <functional>

using namespace std;

function<int(int)> IteriranaFunkcija(int f(int), int n) {
    if(n == 1) return f;
    return [f, n](int a){return f(IteriranaFunkcija(f, n - 1)(a));};
}

int main() {
    return 0;
}


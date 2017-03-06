#include <iostream>
#include <functional>

using namespace std;


auto plus2(double x) {
    return [x](double y){return x + y;};
}

auto plus3(double x) {
    return [x](double y){return [x, y](double z){return x + y + z;};};
}

int main() {
    return 0;
}

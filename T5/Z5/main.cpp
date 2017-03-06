#include <iostream>
#include <cmath>
#define PI 3.14

using namespace std;

double TrapeznoPravilo(double f(double), double a, double b, int n) {
    double integral(0);
    for(int k = 1; k < n; k++)
        integral += f(a + ((b - a)/n)*k);
    integral += .5*f(a) + .5*f(b);
    integral *= (b - a)/n;
    return integral;
}
int main() {
    int n;
    double i1(-cos(PI) + cos(0)), i2(pow(10, 4)/4), i3(log(2));    
    cout << "F-ja sin(x) na intervalu [0, pi]: ";
    for(n = 1; fabs(TrapeznoPravilo(sin, 0, PI, n) - i1) > 0.00001; n++);
    cout << "Trapeznim pravilom sa n = " << n << ": " << TrapeznoPravilo(sin, 0, PI, n) << endl;
    cout << "Ispravno rjesenje: " << i1 << endl;
    
    cout << "F-ja x^3 na intervalu [0, 10]: ";
    for(n = 1; fabs(TrapeznoPravilo([](double x) -> double {return x*x*x;}, 0, 10, n) - i2) > 0.00001; n++);
    cout << "Trapeznim pravilom sa n = " << n << ": " 
    << TrapeznoPravilo([](double x) -> double {return x*x*x;}, 0, 10, n) << endl;
    cout << "Ispravno rjesenje: " << i2 << endl;
    
    cout << "F-ja 1/x na intervalu [1, 2]: ";
    for(n = 1; fabs(TrapeznoPravilo([](double x) -> double {return 1/x;}, 1, 2, n) - i3) > 0.00001; n++);
    cout << "Trapeznim pravilom sa n = " << n << ": " 
    << TrapeznoPravilo([](double x) -> double {return 1/x;}, 1, 2, n) << endl;
    cout << "Ispravno rjesenje: " << i3 << endl;
    return 0;
}


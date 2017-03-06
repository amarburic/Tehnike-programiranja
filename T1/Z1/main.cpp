#include <iostream>

using namespace std;

int main(){
    int wb, hb, lb;
    cout << "Unesi dimenzije bazena (axbxc) u metrima: ";
    cin >> wb >> lb >> hb;
    wb*=100;
    lb*=100;
    hb*=100;
    int wp, lp;
    cout << "Unesi dimenzije pločice (axb) u centimetrima: ";
    cin >> wp >> lp;
    int suma(0);
        suma += (wb / wp)*(hb / lp)*2;
        suma += (lb / lp)*(hb / lp)*2;
        suma += (wb / wp)*(lb / lp); 
    cout << "Za popločavanje bazena dimenzija " << wb/100 << "x" << lb/100 << "x" << 
    hb/100 << " m sa pločicama dimenzija " <<  wp << "x" 
    << lp << " cm potrebno je " << suma << " pločica.";
    return 0;
}
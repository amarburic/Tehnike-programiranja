#include <fstream>
#include <iostream>
#include <cmath>
#define EPSILON 0.00001

using namespace std;

struct Student {
     char ime[20], prezime[20];
     int indeks, broj_ocjena;
     int ocjene[30];
};

double DajProsjek(const Student& s) {
    if(s.broj_ocjena == 0) return 0;
    double prosjek(0);
    for(int i = 0; i < s.broj_ocjena; i++)
        prosjek += s.ocjene[i];
    return prosjek / s.broj_ocjena;
}

bool operator > (const Student& l, const Student& r) {
    return fabs(DajProsjek(l) - DajProsjek(r)) < EPSILON ? l.indeks > r.indeks : DajProsjek(l) > DajProsjek(r);
}

int _main() {
     Student neki_student1, neki_student2;
     fstream studenti("STUDENTI.DAT", ios::binary | ios::in | ios::out);
     while(studenti.read(reinterpret_cast<char*>(&neki_student1),
         sizeof(Student))) {
            int cur1(studenti.tellg());
            while(studenti.read(reinterpret_cast<char*>(&neki_student2),
                sizeof(Student))) {
                    if(neki_student1 > neki_student2) {
                        int cur2(studenti.tellg());
                        studenti.seekp(cur1 - sizeof(Student), ios::beg);
                        studenti.write(reinterpret_cast<char*>(&neki_student2),
                            sizeof(Student));
                        studenti.seekp(cur2 - sizeof(Student), ios::beg);
                        studenti.write(reinterpret_cast<char*>(&neki_student1),
                            sizeof(Student));
                        neki_student1 = neki_student2;
                        studenti.seekg(cur2, ios::beg);
                  }
                }
            studenti.clear();
            studenti.seekg(cur1, ios::beg);
    }
 return 0;
}

int main() {

std::ofstream studenti("STUDENTI.DAT", std::ios::binary);
 Student neki_studenti[6]{
   {"Ana","Anic",12345,5,{6,7,8,9,10}},
   {"Marko","Markovic",12346,5,{9,7,8,9,10}},
   {"Ivica","Ivic",12347,5,{6,6,8,9,10}},
   {"Maja","Majic",12348,5,{}},
   {"Ismet","Isovic",12348,5,{6,6,10,9,10}},
   {"Muharem","Muharemovic",12349,5,{7,7,10,9,10}}
   };

   for (int j = 0; j<6;j++)
       studenti.write((char*)&neki_studenti[j], sizeof(Student));
   studenti.flush();
   studenti.close();
_main();

std::ifstream studenti_ucit("STUDENTI.DAT", std::ios::binary);
   Student neki_student;
   while(studenti_ucit.read((char*)&neki_student, sizeof(Student))) {
     std::cout << neki_student.ime << " "
 << neki_student.prezime << " " << DajProsjek(neki_student) << " " << neki_student.indeks<< " " 
 << std::endl;
 }
}

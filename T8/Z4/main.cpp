#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

string ZamijeniPremaRjecniku (string s, const map<string, string> &m) {
    for(auto it_m = m.begin(); it_m != m.end(); it_m++)
        for(auto it_s = s.begin(); it_s < (s.end() - it_m->first.size() + 1); it_s++)
           if(!(it_s + it_m->first.length() != s.end() &&  *(it_s + it_m->first.length()) != ' ') 
            && !(it_s != s.begin() &&  *(it_s - 1) != ' ') 
            && equal(it_s, it_s + it_m->first.size(), it_m->first.begin()))
                s.replace(it_s, it_s + it_m->first.size(), it_m->second);
    return s;
}

int main() {
    std::map<std::string, std::string> moj_rjecnik{{"jabuka", "apple"},
    {"da", "yes"}, {"kako", "how"}, {"ne", "no"}, {"majmun", "monkey"}};
    std::cout << ZamijeniPremaRjecniku("kako da ne", moj_rjecnik);
    return 0;
}


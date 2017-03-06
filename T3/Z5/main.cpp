#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<int>> PascalovTrougao(int n)
{
        vector<vector<int>> trokut;
        for(int i = 0; i < n; i++) {
                vector<int> red(i+1);
                for(int j = 0; j < i+1; j++) {
                        if(j == 0 || i == j)
                                red[j] = 1;
                        else
                                red[j] = trokut[i-1][j-1] + trokut[i-1][j];


                }
                trokut.push_back(red);
        }
        return trokut;
}

int main()
{
        int n;
        cin >> n;
        for(vector<int> v: PascalovTrougao(n)) {
                for(int a: v)
                        cout << setw(5) << a;
                cout << endl;
        }
        return 0;
}

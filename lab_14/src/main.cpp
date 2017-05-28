#include <cstddef>
#include <iostream>
#include "matrix.h"

using namespace std;

int main(){
    Matrix m[10];
    string s;
    int i, j, a;
    char c, d;
    while (cin >> s){
        try{
            if (s == "exit")
                return 0;
            else
            if (s == "elem"){
                cin >> c >> c >> i >> j;
                a = m[c - '0'].get(i, j);
                cout << a << "\n";
            }else
            if (s == "add"){
                cin >> c >> c >> d >> d;
                m[c - '0'] += m[d - '0'];
            }else
            if (s == "mul"){
                cin >> c >> c >> d >> d;
                m[c - '0'] *= m[d - '0'];
            }else
            if (s == "print"){
                cin >> c >> c;
                cout << m[c - '0'] << "\n";
            }else
            if (s == "load"){
                cin >> c >> c >> s;
                m[c - '0'].load(s.c_str());
            }
        }

        catch (MatrixException &e){
            cout << e.what() << "\n";
        }
    }
}

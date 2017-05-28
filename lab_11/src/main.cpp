#include <stdio.h>
#include <iostream>
#include "../include/employees.h"

using namespace std;

int main() {
    EmployeesArray arr(1);
    string s;
    while (cin >> s){
        if (s == "add"){
            int type;
            cin >> type;
            Employee *e;
            if (type == 1){
                e = (Employee*)(new Developer());
            }else{
                e = (Employee*)(new SalesManager());
            }
            cin >> (*e);
            arr.add(e);
        }else
        if (s == "load"){
            cin >> s;
            ifstream in;
            in.open(s.c_str(), ifstream::binary);
            in >> arr;
            in.close();
        }else
        if (s == "list"){
            cout << arr;
        }else
        if (s == "save"){
            cin >> s;
            ofstream out;
            out.open(s.c_str(), ofstream::binary);
            out << arr;
            out.close();
        }else{
            return 0;
        }
    }
    return 0;
}

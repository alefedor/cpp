#include "../include/employees.h"
#include <cstring>
#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <string>

std::ostream& operator << (std::ostream& os, const Employee &a){
    (&a) -> print(os);
    return os;
}

std::istream& operator >> (std::istream& is, Employee& a){
    (&a) -> scan(is);
    return is;
}

std::ofstream& operator << (std::ofstream& os, const Employee &a){
    (&a) -> printf(os);
    return os;
}
std::ifstream& operator >> (std::ifstream& is, Employee& a){
    (&a) -> scanf(is);
    return is;
}

void Developer::print(std::ostream& os) const{
    os << "Developer\n";
    os << "Name: " << _name << "\n";
    os << "Base Salary: " << _base_salary << "\n";
    os << "Has bonus: " << (_has_bonus?"+":"-") << "\n";
}

void Developer::printf(std::ofstream& os) const{
    int32_t tmp = 1;
    char zero = 0;
    os.write((char*)(&tmp), sizeof(tmp));
    os.write(_name, strlen(_name));
    os.write(&zero, 1);
    os.write((char*)(&_base_salary), sizeof(_base_salary));
    os.write((char*)(&_has_bonus), 1);
}

void Developer::scan(std::istream& is){
    std::string tmp;
    is >> tmp;
    _name = new char[tmp.size() + 1];
    strcpy(_name, tmp.c_str());
    is >> _base_salary >> _has_bonus;
}

void Developer::scanf(std::ifstream& is){
    char c = 1;
    std::string tmp;
    while (c){
        is.read(&c, 1);
        tmp += c;
    }
    _name = new char[tmp.size() + 1];
    strcpy(_name, tmp.c_str());
    is.read((char*)(&_base_salary), sizeof(_base_salary));
    is.read((char*)(&_has_bonus), 1);
}

void SalesManager::print(std::ostream& os) const{
    os << "Sales Manager\n";
    os << "Name: " << _name << "\n";
    os << "Base Salary: " << _base_salary << "\n";
    os << "Sold items: " << _sold_nm << "\n";
    os << "Item price: " << _price << "\n";
}

void SalesManager::printf(std::ofstream& os) const{
    int32_t tmp = 2;
    char zero = 0;
    os.write((char*)(&tmp), sizeof(tmp));
    os.write(_name, strlen(_name));
    os.write(&zero, 1);
    os.write((char*)(&_base_salary), sizeof(_base_salary));
    os.write((char*)(&_sold_nm), sizeof(_sold_nm));
    os.write((char*)(&_price), sizeof(_price));
}

void SalesManager::scan(std::istream& is){
    std::string tmp;
    is >> tmp;
    _name = new char[tmp.size() + 1];
    strcpy(_name, tmp.c_str());
    is >> _base_salary >> _sold_nm >> _price;
}

void SalesManager::scanf(std::ifstream& is){
    char c = 1;
    std::string tmp;
    while (c){
        is.read(&c, 1);
        tmp += c;
    }
    _name = new char[tmp.size() + 1];
    strcpy(_name, tmp.c_str());
    is.read((char*)(&_base_salary), sizeof(_base_salary));
    is.read((char*)(&_sold_nm), sizeof(_sold_nm));
    is.read((char*)(&_price), sizeof(_price));
}

int Developer::salary() const
{
    int salary = _base_salary;
    if (_has_bonus){
        salary += 1000;
    }
    return salary;
}

Developer::~Developer(){
    delete[] _name;
}

int SalesManager::salary() const
{
    return _base_salary + _sold_nm * _price * 0.01;
}

SalesManager::~SalesManager(){
    delete[] _name;
}

EmployeesArray::EmployeesArray(int capacity):_capacity(capacity), _size(0){
    _employees = new Employee*[capacity];
};

void EmployeesArray::add(const Employee *e){
    if (_size == _capacity){
        Employee ** tmp = new Employee*[2*_capacity];
        memcpy(tmp, _employees, _capacity*sizeof(Employee*));
        _capacity *= 2;
        delete[] _employees;
        _employees = tmp;
    }
    _employees[_size++] = (Employee*)e;
}

EmployeesArray::~EmployeesArray(){
    for (int i = 0; i < _size; i++)
        delete _employees[i];
    delete[] _employees;
}

std::ostream& operator << (std::ostream& os, const EmployeesArray &a){
    int total = 0;
    char buffer[10];
    for (int i = 0; i < a._size; i++){
        sprintf(buffer,"%d",i+1);
        os << buffer << ". ";
        os << *(a._employees[i]);
        total += a._employees[i] -> salary();
    }
    os << "== Total salary: " << total << "\n\n";
}

std::ifstream& operator >> (std::ifstream& is, EmployeesArray& a){
    int32_t num;
    int32_t type;
    is.read((char*)(&num), sizeof(num));
    for (int i = 0; i < num; i++){
        Employee *e;
        is.read((char*)(&type), sizeof(type));
        if (type == 1){
            e = (Employee*)(new Developer());
        }else{
            e = (Employee*)(new SalesManager());
        }
        is >> (*e);
        a.add(e);
    }
}

std::ofstream& operator << (std::ofstream& os, const EmployeesArray& a){
    os.write((char*)(&a._size), sizeof(int32_t));
    for (int i = 0; i < a._size; i++){
        os << (*a._employees[i]);
    }
}

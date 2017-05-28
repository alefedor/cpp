#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <ostream>
#include <istream>
#include <fstream>

class Employee
{
public:
    Employee(){}
    virtual ~Employee(){}
    virtual void print(std::ostream& os) const = 0;
    virtual void printf(std::ofstream& os) const = 0;
    virtual void scan(std::istream& is) = 0;
    virtual void scanf(std::ifstream& is) = 0;
    virtual int salary() const = 0;

protected:
    Employee(const Employee& b);
    void operator=(const Employee& b);
    friend std::ostream& operator << (std::ostream& os, const Employee &a);
    friend std::istream& operator >> (std::istream& is, Employee& a);
    friend std::ofstream& operator << (std::ofstream& os, const Employee &a);
    friend std::ifstream& operator >> (std::ifstream& is, Employee& a);
};

class Developer: public Employee
{
public:
    int salary() const;
    ~Developer();
    void print(std::ostream& os) const;
    void printf(std::ofstream& os) const;
    void scan(std::istream& is);
    void scanf(std::ifstream& is);

private:
    char *_name;
    int32_t _base_salary;
    bool _has_bonus;
};

class SalesManager: public Employee
{
public:
    int salary() const;
    ~SalesManager();
    void print(std::ostream& os) const;
    void printf(std::ofstream& os) const;
    void scan(std::istream& is);
    void scanf(std::ifstream& is);

private:
    char *_name;
    int32_t _base_salary;
    int32_t _sold_nm, _price;
};

class EmployeesArray
{
public:
    EmployeesArray(int capacity);
    ~EmployeesArray();
    void add(const Employee *e);
    int total_salary() const;
    friend std::ostream& operator << (std::ostream& os, const EmployeesArray& a);
    friend std::ifstream& operator >> (std::ifstream& is, EmployeesArray& a);
    friend std::ofstream& operator << (std::ofstream& is, const EmployeesArray& a);

private:
    int _capacity;
    int _size;
    Employee **_employees;

    EmployeesArray(const EmployeesArray& b);
    void operator=(const EmployeesArray& b);
};

#endif

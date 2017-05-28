#include <iostream>
#include <cstring>

#include "../include/my_vector.h"
#define DO_CHECK(expr) check(expr, __FUNCTION__, __FILE__, __LINE__)

class Product{
public:
    Product(const char* name, int quantity, double price);
    Product();
    ~Product();
    Product(const Product &p);
    Product& operator=(const Product& other);
    bool operator==(const Product& other) const;

    friend std::ostream& operator << (std::ostream& os, const Product &a);

private:
    char *name_;
    int quantity_;
    double price_;
};

bool Product::operator==(const Product& other) const{
    return (quantity_ == other.quantity_ &&
            price_ == other.price_ &&
            strcmp(name_, other.name_) == 0);
}

Product::Product(){
    name_ = new char[6];
    strcpy(name_, "Vasya");
    quantity_ = 10;
    price_ = 1e9;
}

Product::Product(const char* name, int quantity, double price){
    name_ = new char[strlen(name)+1];
    strcpy(name_, name);
    quantity_ = quantity;
    price_ = price;
}

Product::~Product(){
    delete[] name_;
}

Product::Product(const Product &p){
    quantity_ = p.quantity_;
    price_ = p.price_;
    name_ = new char[strlen(p.name_)+1];
    strcpy(name_, p.name_);
}

Product& Product::operator=(const Product& other){
    Product tmp(other);
    std::swap(quantity_, tmp.quantity_);
    std::swap(price_, tmp.price_);
    std::swap(name_, tmp.name_);
    return *this;
}

std::ostream& operator << (std::ostream& os, const Product &a){
    os << a.name_ << " " << a.quantity_ << " " << a.price_;
    return os;
}

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

bool check(bool expr, const char *func, const char  *filename, size_t lineNum){
    if (!expr)
        std::cout << "Test failed " << func << " in line " << lineNum << " in file " << filename << std::endl;
}

template <typename T>
void test_my_vector(const T& a, const T& b){
    my_vector<T> v;
    DO_CHECK(v.size() == 0);
    DO_CHECK(v.empty());

    v.push_back(a);
    DO_CHECK(v.size() == 1);
    DO_CHECK(v.capacity() == 1);
    DO_CHECK(!v.empty());

    v.push_back(b);
    DO_CHECK(v.size() == 2);
    DO_CHECK(v.capacity() == 2);

    v.push_back(a);
    std::cout << v << std::endl;
    DO_CHECK(v.size() == 3);
    DO_CHECK(v.capacity() == 4);

    DO_CHECK(v[2] == a);
    v[2] = b;
    DO_CHECK(v[2] == b);

    v.resize(2);
    DO_CHECK(v.size() == 2);

    v.clear();
    DO_CHECK(v.size() == 0);

    v.resize(2);
    DO_CHECK(v.size() == 2);

    v.reserve(5);
    DO_CHECK(v.capacity() == 8);

    my_vector<T> u(v);
    DO_CHECK(u.size() == 2);

    my_vector<T> w(10);
    DO_CHECK(w.size() == 10);
    w = u;
    DO_CHECK(w.size() == 2);
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
    return 0;
}

#include <cstddef>
#include <ostream>
#include <iostream>

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(const my_vector& other);
    my_vector<T>& operator=(const my_vector& other);
    ~my_vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void resize(size_t n);
    void reserve(size_t n);
    T& operator[](size_t ind);
    const T& operator[](size_t ind) const;
    void push_back(const T& t);
    void pop_back();
    void clear();

    template <typename K>
    friend std::ostream& operator << (std::ostream& os, const my_vector<K> &a);

private:
    size_t capacity_;
    size_t size_;
    T* array_;
    void swap(my_vector<T> &v);
    size_t new_cp(size_t cp);
    my_vector(size_t cap, __attribute__((unused)) size_t n);
};

template <typename T>
my_vector<T>::my_vector(){
    size_ = 0;
    capacity_ = 0;
    array_ = NULL;
}

template <typename T>
my_vector<T>::my_vector(size_t n){
    size_ = 0;
    capacity_ = new_cp(n);
    array_ = (T*) new char[capacity_ * sizeof(T)];
    T elem;
    while (size_ != n)
        push_back(elem);
}

template <typename T>
my_vector<T>::my_vector(size_t cap, __attribute__((unused)) size_t n){
    size_ = 0;
    capacity_ = new_cp(cap);
    array_ = (T*) new char[capacity_ * sizeof(T)];
}

template <typename T>
my_vector<T>::my_vector(const my_vector& other){
    size_ = 0;
    capacity_ = 0;
    array_ = NULL;
    for (size_t i = 0; i < other.size_; i++)
        push_back(other.array_[i]);
}

template <typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector& other){
    my_vector<T> tmp(other);
    swap(tmp);
    return *this;
}

template <typename T>
my_vector<T>::~my_vector(){
    clear();
    if (array_)
        delete[] (char*)array_;
}

template <typename T>
size_t my_vector<T>::size() const{
    return size_;
}

template <typename T>
size_t my_vector<T>::capacity() const{
    return capacity_;
}

template <typename T>
bool my_vector<T>::empty() const{
    return (size_ == 0);
}

template <typename T>
T& my_vector<T>::operator[](size_t index){
    return array_[index];
}

template <typename T>
const T& my_vector<T>::operator[](size_t index) const{
    return array_[index];
}

template <typename T>
size_t my_vector<T>::new_cp(size_t cp){
    size_t res = 1;
    while (res < cp)
        res <<= 1;
    return res;
}

template <typename T>
void my_vector<T>::swap(my_vector<T> &v){
    std::swap(size_, v.size_);
    std::swap(capacity_, v.capacity_);
    std::swap(array_, v.array_);
}

template <typename T>
void my_vector<T>::resize(size_t n){
    if (n <= size_){
        while (size_ != n)
            pop_back();
    }
    T elem;
    while (size_ != n)
        push_back(elem);
}

template <typename T>
void my_vector<T>::reserve(size_t n){
    if (n <= capacity_)
        return;
    n = new_cp(n);
    my_vector<T> tmp(n, 0);
    for (size_t i = 0; i < size_; i++)
        tmp.push_back(array_[i]);
    swap(tmp);
}

template <typename T>
void my_vector<T>::push_back(const T& t){
    if (size_ + 1 > capacity_)
        reserve(size_ + 1);
    new (array_ + size_) T(t);
    size_++;
}

template <typename T>
void my_vector<T>::pop_back(){
    size_--;
    array_[size_].~T();
}

template <typename T>
void my_vector<T>::clear(){
    while (!empty())
        pop_back();
}

template <typename T>
std::ostream& operator << (std::ostream& os, const my_vector<T> &a){
    for (int i = 0; i < a.size_; i++){
        if (i)
            os << " ";
        os << a.array_[i];
    }
    return os;
}

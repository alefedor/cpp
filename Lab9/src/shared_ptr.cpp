#include "shared_ptr.h"
#include <algorithm>
#include <utility>

using namespace std;

shared_ptr::shared_ptr(Matrix* obj){
    this->storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr& other){
    other.storage_->incr();
    this->storage_ = other.storage_;
}

shared_ptr& shared_ptr::operator =(shared_ptr other){
    if (this == &other)
        return *this;
    shared_ptr tmp(other);
    swap(this->storage_, tmp.storage_);
    return *this;
}

shared_ptr::~shared_ptr(){
    this->storage_->decr();
    if (this->storage_->getCounter() == 0)
        delete this->storage_;
}

Matrix* shared_ptr::ptr() const{
    return this->storage_->getObject();
}

bool shared_ptr::isNull() const{
    return (this->storage_->getObject() == NULL);
}

void shared_ptr::reset(Matrix* obj){
    if (this->ptr() == obj)
        return;
    shared_ptr tmp(obj);
    swap(this->storage_, tmp.storage_);
}

Matrix* shared_ptr::operator->() const{
    return this->ptr();
}

Matrix& shared_ptr::operator*() const{
    return *this->ptr();
}

shared_ptr::Storage::Storage(Matrix* mtx){
    this->data_ = mtx;
    this->ref_count_=1;
}

shared_ptr::Storage::~Storage(){
    delete this->data_;
}

void shared_ptr::Storage::incr(){
    this->ref_count_++;
}

void shared_ptr::Storage::decr(){
    this->ref_count_--;
}

int shared_ptr::Storage::getCounter() const{
    return this->ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const{
    return this->data_;
}

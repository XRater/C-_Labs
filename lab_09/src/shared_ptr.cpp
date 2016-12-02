#include "shared_ptr.h"
#include <utility>
#include <iostream>

shared_ptr::Storage::Storage(Matrix* obj) {
    data_ = obj;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ref_count_ += 1;
}

void shared_ptr::Storage::decr() {
    ref_count_ -= 1;
    if (ref_count_ == 0)
        delete this;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}

shared_ptr::shared_ptr(Matrix* obj) {
    storage_ = new Storage(obj);
}

shared_ptr::~shared_ptr() {
    storage_->decr();  
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    storage_ = other.storage_;
    storage_->incr();
}

bool shared_ptr::isNull() const{    
    return !(storage_->getObject());
}

Matrix* shared_ptr::ptr() const {    
    return storage_->getObject();
}

void shared_ptr::reset(Matrix* obj) {    
    storage_->decr();
    storage_ = new Storage(obj);
}

Matrix* shared_ptr::operator->() const {    
    return storage_->getObject();    
}

Matrix& shared_ptr::operator*() const {    
    return *(storage_->getObject());    
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {    
    this->swap(other);
    return *this;
}

void shared_ptr::swap(shared_ptr& other) {
    std::swap(storage_, other.storage_);    
}


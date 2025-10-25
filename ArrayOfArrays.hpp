#pragma once
#include "helpers.hpp"

template<typename T>
struct ArrayOfArrays : public Array<Array<T>> {
    // Constructor - properly initializes inner arrays
    ArrayOfArrays(int size = 0) : Array<Array<T>>(size) {
        std::clog << "[ArrayOfArrays ctor] this=" << this << " size=" << size << "\n";
        // Initialize each inner Array
        for(int i = 0; i <= size; i++) {
            new (&this->pointer[i]) Array<T>();
        }
    }

    // Destructor - properly cleans up inner arrays
    ~ArrayOfArrays() {
        std::clog << "[ArrayOfArrays dtor] this=" << this << " maxSize=" << this->maxSize << "\n";
        if(this->pointer) {
            for(int i = 0; i <= this->maxSize; i++) {
                this->pointer[i].~Array<T>();
            }
        }
    }

    // Copy constructor
    ArrayOfArrays(const ArrayOfArrays<T>& other) : Array<Array<T>>(other) {
        std::clog << "[ArrayOfArrays copy ctor] this=" << this << " from=" << &other << "\n";
    }

    // Move constructor
    ArrayOfArrays(ArrayOfArrays<T>&& other) noexcept : Array<Array<T>>(std::move(other)) {
        std::clog << "[ArrayOfArrays move ctor] this=" << this << " from=" << &other << "\n";
    }

    // Copy assignment
    ArrayOfArrays& operator=(const ArrayOfArrays<T>& other) {
        Array<Array<T>>::operator=(other);
        return *this;
    }

    // Move assignment
    ArrayOfArrays& operator=(ArrayOfArrays<T>&& other) noexcept {
        Array<Array<T>>::operator=(std::move(other));
        return *this;
    }
};
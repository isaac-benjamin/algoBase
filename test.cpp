#include <iostream>
#include <memory>

#include "helpers.hpp"

using namespace std;

void Skapow(){
    unique_ptr<Array<int>> ptr = make_unique<Array<int>>(10);
}

int main(){
    Skapow();
    return 0;
}
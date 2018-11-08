//
// Created by Jonas Lippert and Maximilian Wiesmann
//

#include"largeint.h"
#include <iostream>
#include <vector>

static LargeInt one(1);

LargeInt factorial(LargeInt arg){
    LargeInt result(1);
    LargeInt iterator(2);
    while(iterator < arg + one){
        result *= iterator;
        iterator += one;
    }
    return result;
}

int main(){
    LargeInt a(1234567890);
    LargeInt b(98789876543);
    LargeInt c(999);
    a *= b;
    std::cout << a.decimal() << std::endl;
    std::cout << factorial(c).decimal() << std::endl;
    return 0;
}


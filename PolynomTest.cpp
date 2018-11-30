// Test program for Polynomial.h

#include <iostream>
#include "Polynomial.h"

int main() {
    Polynomial P;
    P.SetCoefficient(7, 1);
    P.SetCoefficient(3, 6);
    P.SetCoefficient(0,-1);
    std::cout << "     P = " <<        P.toString() << "\n";
    std::cout << "-1 * P = " << (-1 * P).toString() << "\n";
    std::cout << " 5 * P = " << ( 5 * P).toString() << "\n";
    std::cout << "-5 * P = " << (-5 * P).toString() << "\n";
    std::cout << " 0 * P = " << ( 0 * P).toString() << "\n";
}



// ktp.cpp (Berechnung Kreisteilungspolynom)

//
// Created by Jonas Lippert and Maximilian Wiesmann
//

#include <iostream>
#include <stdexcept>
#include "Polynomial.h"

int moebius(int n) {
    if (n == 1) {
        return 1;
    }

    int result = -1;

    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            n = n / i;
            if (n % i == 0) {
                return 0;
            }
            result = -result;
        }
    }

    return result;
}

int main()
{
    int n = 0;
    std::cin >> n;

    Polynomial d, ktp;
    ktp.SetCoefficient(0, 1);

    for (int i = n; i > 0; --i)
    {
        if (n % i == 0)
        {
            if (moebius(n/i) == 1)
            {
                d = 0 * d;
                d.SetCoefficient(i, 1);
                d.SetCoefficient(0,-1);
                ktp = ktp * d;
            }
        }
    }
    try
    {
        for (int i = n; i > 0; --i)
        {
            if (n % i == 0)
            {
                if (moebius(n/i) == -1)
                {
                    d = 0 * d;
                    d.SetCoefficient(i, 1);
                    d.SetCoefficient(0,-1);
                    ktp = ktp / d;
                }
            }
        }
        std::cout << "Das " << n << "-te Kreisteilungspolynom lautet: " << ktp.toString() << "\n";
    }
    catch (std::runtime_error e)
    {
        std::cout << "RUNTIME ERROR: " << e.what() << "\n";
    }

}

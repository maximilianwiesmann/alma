// Polynomial.cpp (class for polynomials - definition)

//
// Created by Jonas Lippert and Maximilian Wiesmann
//

#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

Polynomial operator*(int lhs, const Polynomial & rhs) // scalar multiplication
{
    Polynomial result;

    if (lhs == 0) return result;

    result = rhs;

    for (auto & i : result._coefficient)
    {
        i *= lhs;
    }

    return result;
}


Polynomial::Polynomial()                      // construct zero polynomial
{
    _coefficient.push_back(0);
}


void Polynomial::SetCoefficient(size_t index, int value)                   // set coefficient for x^index
{
    if (_coefficient.size() <= index) _coefficient.resize(index + 1, 0);
    _coefficient[index] = value;
    while(_coefficient.back() == 0 && _coefficient.size() != 1)
    {
         _coefficient.pop_back();                   //delete leading zeros
    }
}

const Polynomial Polynomial::operator-(const Polynomial & arg) const            // Subtraktion
{
    Polynomial res;
    res = *this;
    if (_coefficient.size() < arg._coefficient.size())  // Prüfe auf passende Größe
    {
        res._coefficient.resize(arg._coefficient.size(), 0);
    }

    for(size_t it2 = 0; it2 < arg._coefficient.size(); ++it2)
    {
        res._coefficient[it2] -= arg._coefficient[it2];
    }

    while(res._coefficient.back() == 0 && res._coefficient.size() != 1)
    {
         res._coefficient.pop_back();                //delete leading zeros
    }

    return res;
}

const Polynomial Polynomial::operator*(const Polynomial & arg) const            // Multiplikation
{
    Polynomial res;
    res._coefficient.resize(_coefficient.size()+arg._coefficient.size()-1, 0);  // Prüfe auf passende Größe

    for(size_t it1 = 0; it1 < _coefficient.size(); ++it1)
    {
        for(size_t it2 = 0; it2 < arg._coefficient.size(); ++it2)
        {
            res._coefficient[it1+it2] += _coefficient[it1]*arg._coefficient[it2];   // Multipliziere komponentenweise
        }
    }
    return res;
}

const Polynomial Polynomial::operator/(const Polynomial & arg) const            // Division
{
    Polynomial rest = *this, teiler, result;
    result._coefficient.resize(_coefficient.size(), 0);
    size_t index = 0, d = arg._coefficient.size() - 1;
    int value = 0, co = arg._coefficient.back();
    bool y = 1;

    for (size_t it = _coefficient.size() - 1; it >= d && y; --it)
    {
        teiler._coefficient.clear();

        if(rest._coefficient.back() % co == 0)
        {
            if(it < rest._coefficient.size())
            {
                index = it - d;                         // Exponent des aktuell zu berechnenden Monoms
                value = rest._coefficient[it] / co;     // Koeffizienten des aktuell zu berechnenden Monoms
                result._coefficient[index] += value;    // Addiere Monom zu result
                teiler.SetCoefficient(index, value);
                rest = rest - arg*teiler;               // Subtrahiere den gewonnenen Faktor
            }
        }
        else
        {
            throw std::runtime_error("Teilung ohne Rest nicht moeglich.");
        }


        for (auto i : rest._coefficient)    // Prüfe ob rest = 0
        {
            if(i)
            {
                y = 1;
                break;
            }
            else y = 0;
        }

        if (it == 0) break;     // size_t stellt keine negativen Zahlen dar
    }

    for (auto i : rest._coefficient)
    {
        if(i) throw std::runtime_error("Teilung ohne Rest nicht moeglich.");
    }

    while(result._coefficient.back() == 0 && result._coefficient.size() != 1)
    {
         result._coefficient.pop_back();       //delete leading zeros
    }

    return result;
}

std::string Polynomial::toString() const                         // convert to string
{
    std::string res = "";
    std::string coef = "";
    std::string pow = "";

    // Polynomgrad gleich 0

    if (_coefficient.size() == 1)
    {
        if (_coefficient[0] == 0)
        {
            res += "0";
        }
        else
        {
            if(_coefficient[0] < 0)
            {
                res += "- ";
                res += std::to_string((-1)*_coefficient[0]);
            }
            else
            {
                res += std::to_string(_coefficient[0]);
            }
        }
        return res;
    }

    //Größter Exponent

    size_t t = _coefficient.size() - 1;

    pow = std::to_string(t);

    if (_coefficient[t] < 0)
    {
        if(_coefficient[t] == -1)
        {
            res += "-";
            res += " x^";
            res += pow;
        }
        else
        {
            coef = std::to_string((-1)*_coefficient[t]);

            res += "- ";
            res += coef;
            res += " x^";
            res += pow;
        }
    }
    else
    {
        if(_coefficient[t] == 1)
        {
            res += "x^";
            res += pow;
        }
        else
        {
            coef = std::to_string(_coefficient[t]);

            res += coef;
            res += " x^";
            res += pow;
        }
    }

    // Mittlere Exponenten

    for (size_t it = _coefficient.size() - 2; it > 0; --it)
    {
        if (_coefficient[it] < 0)
        {
            pow = std::to_string(it);
            res += " - ";

            if (_coefficient[it] == -1)
            {
                res += "x^";
                res += pow;
            }
            else
            {
                coef = std::to_string((-1)*_coefficient[it]);

                res += coef;
                res += " x^";
                res += pow;
            }
        }
        if (_coefficient[it] > 0)
        {
            pow = std::to_string(it);
            res += " + ";

            if (_coefficient[it] == 1)
            {
                res += "x^";
                res += pow;
            }
            else
            {
                coef = std::to_string(_coefficient[it]);

                res += coef;
                res += " x^";
                res += pow;
            }
        }
    }

    // Konstante

    if(_coefficient[0] < 0)
    {
        res += " - ";
        res += std::to_string((-1)*_coefficient[0]);
    }
    if(_coefficient[0] > 0)
    {
        res += " + ";
        res += std::to_string(_coefficient[0]);
    }

    return res;
}



/* Test Programm
int main()
{
    Polynomial a,b,e;

    a.SetCoefficient(0, 1);
    a.SetCoefficient(1, 2);
    a.SetCoefficient(2, 4);

    b.SetCoefficient(1, 2);
    b.SetCoefficient(4, 5);

    std::cout << "a = " << a.toString() << "\n";
    std::cout << "b = " << b.toString() << "\n";

    Polynomial d = a*b;

    e.SetCoefficient(0,13);

    std::cout << "d = " << d.toString() << "\n\n";

    try
    {
        Polynomial c = d/b;
        std::cout << "d/b = " << c.toString() << "\n";
    }
    catch (std::runtime_error e)
    {
        std::cout << "RUNTIME ERROR: " << e.what() << "\n";
    }
}
*/

/*
std::cout << "index = " << index << "\n";
std::cout << "value = " << value << "\n";
std::cout << "result = " << result.toString() << "\n";
std::cout << "teiler = " << teiler.toString() << "\n";
std::cout << "rest = " << rest.toString() << "\n";
std::cout << "\n";
*/

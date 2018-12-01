// Polynomial.cpp (class for polynomials - definition)

#include <iostream>
#include <vector>
#include <string>
#include "Polynomial.h"

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


Polynomial::Polynomial()                                                    // construct zero polynomial
{
    _coefficient.push_back(0);
}


void Polynomial::SetCoefficient(size_t index, int value)                   // set coefficient for x^index
{
    if (_coefficient.size() <= index) _coefficient.resize(index + 1, 0);
    _coefficient[index] = value;
    //if(_coefficient.back() == 0 && _coefficient.size() != 1) _coefficient.pop_back(); //delete leading zeros
}



std::string Polynomial::toString() const                                   // convert to string
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
            res += "- ";
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

//
// Created by Jonas Lippert and Maximilian Wiesmann
//

// largeint.cpp (Implementation of Class LargeInt)

#include "largeint.h"
#include <iostream>
#include <stdexcept>

const std::string LargeInt::digits = "0123456789";

LargeInt::LargeInt(inputtype i)   // constructor, calls constructor of vector
{
    do {
        _v.push_back(i % 10);
        i /= 10;
    } while (i > 0);
}


std::string LargeInt::decimal() const   // returns decimal representation
{
    std::string s("");
    for (auto i : _v) {       // range for statement: i runs over all
        s = digits[i] + s;    // elements of _v
    }
    return s;
}


bool LargeInt::operator<(const LargeInt & arg) const   // checks if < arg
{
    if (_v.size() == arg._v.size()) {
        auto it2 = arg._v.rbegin();
        for (auto it1 = _v.rbegin(); it1 != _v.rend(); ++it1, ++it2) {
            if (*it1 < *it2) return true;
            if (*it1 > *it2) return false;
        }
        return false;
    }
    return _v.size() < arg._v.size();
}

bool LargeInt::is_even() const                      // Zahl gerade?
{
    return(1 - _v[0] % 2);
}

void LargeInt::div2()                              // Division durch 2
{
    if (_v == std::vector<short>(1,0)) return;

    if (_v[0] % 2)
    {
        throw std::runtime_error ("Division durch 2 nicht moeglich, da Zahl nicht gerade.");
    }

    short carry = 0;

    for (auto i = _v.rbegin(); i < _v.rend(); ++i)
    {
        *i += carry;
        carry = 0;

        if (*i % 2)
        {
            *i /= 2;
            carry = 10;
        }
        else *i /= 2;
    }

    for(auto it = _v.rbegin(); *it == 0; ++it)           //delete leading zeros
    {
        _v.pop_back();
    }
}

bool LargeInt::is_zero() const                         // Zahl gleich 0?
{
    for(auto i : _v)
    {
        if(i) return 0;
    }
    return 1;
}

LargeInt LargeInt::operator+(const LargeInt & arg) const  // addition
{
    LargeInt result(*this);
    result += arg;
    return result;
}


const LargeInt & LargeInt::operator+=(const LargeInt & arg)   // addition
{
    if (arg._v.size() > _v.size()) {
        _v.resize(arg._v.size(), 0);
    }
    auto it1 = _v.begin();
    for (auto it2 = arg._v.begin(); it2 != arg._v.end(); ++it2, ++it1) {
        *it1 += *it2;
    }
    short carry = 0;
    for (auto & i : _v) {
        i += carry;
        carry = i / 10;
        i %= 10;
    }
    if (carry != 0) _v.push_back(carry);
    return *this;
}

const LargeInt & LargeInt::operator-=(const LargeInt & arg)   // subtraction a-b nur gültig für b<=a
{
    if (*this < arg)
    {
        throw std::runtime_error("Negative numbers are not allowed.");
    }

    auto it1 = _v.begin();
    for (auto it2 = arg._v.begin(); it2 != arg._v.end(); ++it2, ++it1) {
        *it1 -= *it2;
    }
    short carry = 0;
    for (auto & i : _v) {
        i += carry;
        carry = i / 10;
        i %= 10;                 //Modulo scheint nicht in positive Zahlen umzuformen
        if (i < 0)
        {
            carry -= 1;
            i += 10;
        }
    }

    for(auto it = _v.rbegin(); *it == 0 and it < _v.rend() - 1; ++it)           //delete leading zeros
    {
        _v.pop_back();
    }

    return *this;
}

LargeInt LargeInt::operator-(const LargeInt & arg) const                 // subtraction
{
    LargeInt result(*this);
    result -= arg;
    return result;
}

LargeInt LargeInt::operator*(const LargeInt & arg) const {
    unsigned long max = (_v.size() >= arg._v.size()) ? _v.size() : arg._v.size();
    std::vector<short> result(2*max, 0);
    for(unsigned long i = 0; i < _v.size(); ++i){
        for(unsigned long j = 0; j < arg._v.size(); ++j){
            result[i+j] += _v[i]*arg._v[j];
        }
    }
    for(auto it = result.rbegin(); *it == 0; ++it){     //delete leading zeros
        result.pop_back();
    }
    short carry = 0;        //collect carries
    for (auto & i : result) {
        i += carry;
        carry = i / 10;
        i %= 10;
    }
    if (carry != 0) result.push_back(carry);
    LargeInt result_int(0);
    result_int._v = result;
    return result_int;
}

const LargeInt& LargeInt::operator*=(const LargeInt & arg) {
    *this = arg * *this;
    return *this;
}



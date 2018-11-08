//
// Created by Jonas Lippert and Maximilian Wiesmann
//

// largeint.cpp (Implementation of Class LargeInt)

#include "largeint.h"

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

LargeInt LargeInt::operator*(const LargeInt & arg) const {
    unsigned long max = (_v.size() >= arg._v.size()) ? _v.size() : arg._v.size();
    std::vector<short> result(2*max, 0);
    for(int i = 0; i < _v.size(); ++i){
        for(int j = 0; j < arg._v.size(); ++j){
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



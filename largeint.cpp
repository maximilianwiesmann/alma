//
// Created by Jonas Lippert and Maximilian Wiesmann
//

// largeint.cpp (Implementation of Class LargeInt)

#include "largeint.h"
#include <iostream>

const std::string LargeInt::digits = "0123456789";

LargeInt::LargeInt(inputtype i)   // constructor, calls constructor of vector
{
	if (i < 0)
		throw std::runtime_error("negative argument in LargeInt");
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
    unsigned long long max = (_v.size() >= arg._v.size()) ? _v.size() : arg._v.size();
    std::vector<short> result(2*max, 0);
    for(unsigned long long i = 0; i < _v.size(); ++i){
        for(unsigned long long j = 0; j < arg._v.size(); ++j){
            short temp = _v[i]*arg._v[j];
            result[i+j] += (temp % 10);
            result[i+j+1] += (temp/10);
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

bool LargeInt::is_zero() const {
    return this -> decimal() == "0";
	//std::vector<short> zero(1,0);
	//return _v == zero;
}

bool LargeInt::is_even() const {
    return (*_v.begin() % 2) == 0;
}

LargeInt LargeInt::operator-(const LargeInt & arg) const {
    if(*this < arg){
        throw std::runtime_error("result negative");
    }
    LargeInt result(0);
    result._v.resize(_v.size(),0);
    for (unsigned it = 0; it < arg._v.size(); ++it) {
        if(_v[it]-arg._v[it] < 0){
            result._v[it] += _v[it]-arg._v[it] + 10;
            --result._v[it + 1];
        }
        else{
            result._v[it] += _v[it]-arg._v[it];
        }
    }
    short carry = 0;
    for (auto & i : result._v) {
        i += carry;
        carry = i / 10;
        i %= 10;
    }
    if (carry != 0) result._v.push_back(carry%10);
    if(result._v.back() == 0) result._v.pop_back(); //delete leading zeros
    return result;
}


LargeInt LargeInt::div2(LargeInt arg) {
	if(not arg.is_even()){
		throw std::runtime_error("number not divisible by 2");
	}
    LargeInt result(0);
	if(arg.is_zero())
		return result;
    result._v.clear();
    for(unsigned int i = arg._v.size(); i-- > 0;){
        if(arg._v[i] != 1){
            result._v.insert(result._v.begin(), short(arg._v[i]/2));
            if(arg._v[i]%2 == 1){
                arg._v[i] = 1;
                ++i;
            }
        }
        else{
            result._v.insert(result._v.begin(), short((10+arg._v[i-1])/2));
            if((10+arg._v[i-1])%2 == 0){
                --i;
            }
        }
    }
	if(result._v.back() == 0) result._v.pop_back(); //delete leading zeros
    return result;
}

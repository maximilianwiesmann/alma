//
// Created by Jonas Lippert and Maximilian Wiesmann
//

#include <vector>
#include <string>
#include <stdexcept>


class LargeInt {
public:
    using inputtype = long long;

    LargeInt(inputtype);                           // constructor
    std::string decimal() const;                   // decimal representation
    bool operator<(const LargeInt &) const;        // comparison
    LargeInt operator+(const LargeInt &) const;    // addition
    const LargeInt & operator+=(const LargeInt &); // addition
    LargeInt operator*(const LargeInt &) const;    // multiplication
    const LargeInt & operator*=(const LargeInt &); // multiplication
    bool is_even() const;                          // parity
    LargeInt operator-(const LargeInt &) const;    // subtraction
    LargeInt div2(LargeInt);               		   // division by 2
	//LargeInt div2();
    bool is_zero() const;                          // zero

private:
    std::vector<short> _v;  // store single digits, last digit in _v[0]
    static const std::string digits;
};

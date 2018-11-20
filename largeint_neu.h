//
// Created by Jonas Lippert and Maximilian Wiesmann
//

#include <vector>
#include <string>


class LargeInt {
public:
    using inputtype = long long;

    LargeInt(inputtype);                           // constructor
    std::string decimal() const;                   // decimal representation
    bool operator<(const LargeInt &) const;        // comparison

    bool is_even() const;                          // Zahl gerade?
    void div2();                                   // Division durch 2
    bool is_zero() const;                          // Zahl gleich 0?

    LargeInt operator+(const LargeInt &) const;    // addition
    const LargeInt & operator+=(const LargeInt &); // addition
    LargeInt operator-(const LargeInt &) const;    // subtraction b-a nur gültig für a<=b
    const LargeInt & operator-=(const LargeInt &); // subtraction b-a nur gültig für a<=b
    LargeInt operator*(const LargeInt &) const;    // multiplication
    const LargeInt & operator*=(const LargeInt &); // multiplication
	LargeInt power(const LargeInt &) const;   	   // power

private:
    std::vector<short> _v;  // store single digits, last digit in _v[0]
    static const std::string digits;
};

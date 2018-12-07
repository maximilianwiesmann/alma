// Polynomial.h (class for polynomials - declaration)

//
// Created by Jonas Lippert and Maximilian Wiesmann
//

#include <vector>
#include <string>

class Polynomial{

friend Polynomial operator*(int lhs, const Polynomial & rhs);

public:
    Polynomial();                                           // construct zero polynomial
    void SetCoefficient(size_t index, int value);           // set coefficient for x^index
    const Polynomial operator-(const Polynomial &) const;   // Subtraktion
    const Polynomial operator*(const Polynomial &) const;   // Multiplikation
    const Polynomial operator/(const Polynomial &) const;   // Division
    std::string toString() const;                           // convert to string

private:
    std::vector<int> _coefficient;
};


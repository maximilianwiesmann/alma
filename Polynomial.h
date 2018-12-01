// Polynomial.h (class for polynomials - declaration)

#include <vector>
#include <string>

class Polynomial{

friend Polynomial operator*(int lhs, const Polynomial & rhs);

public:
    Polynomial();                                 // construct zero polynomial
    void SetCoefficient(size_t index, int value); // set coefficient for x^index
    std::string toString() const;                 // convert to string

private:
    std::vector<int> _coefficient;
};


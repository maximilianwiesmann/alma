// fraction.h (Class Fraction)

#include <iostream>
#include <stdexcept>
#include <limits>


class Fraction {
public:
    using inttype = int;

    Fraction(inttype n, inttype d): _numerator(n), _denominator(d)
    {   // constructor
        if (d < 1) error_zero();
    }

    void print()                                // Ausgabe
	{
		std::cout << numerator() << "/" << denominator() << std::endl;
	}

    inttype numerator() const                   // return numerator
    {
        return _numerator;
    }

    inttype denominator() const                 // return denominator
    {
        return _denominator;
    }

    void reciprocal()                           // replaces a/b by b/a
    {
        if (numerator() == 0) {
            error_zero();
        } else {
            std::swap(_numerator, _denominator);
            if (denominator() < 0) {
                _numerator   = -_numerator;
                _denominator = -_denominator;
            }
        }
    }

    bool operator<(const Fraction & x) const     // comparison
    {
        return numerator() * x.denominator() < x.numerator() * denominator();
    }

    Fraction operator+(const Fraction & x) const // Addition
    {
        if (abs(numerator()) < std::numeric_limits<inttype>::max()/abs(x.denominator())
            and abs(denominator()) < std::numeric_limits<inttype>::max()/abs(x.numerator()))
        {
            if (abs(numerator() * x.denominator()) < std::numeric_limits<inttype>::max()-abs(x.numerator() * denominator())
                and abs(denominator()) < std::numeric_limits<inttype>::max()/abs(x.denominator()))
            {
                Fraction y(numerator() * x.denominator() +
                        x.numerator() * denominator(),
                        denominator() * x.denominator());
                y.cancel();
                return y;
            }
            else
            {
                throw std::runtime_error("Ueberlauf");
            }
        }
        else
        {
            throw std::runtime_error("Ueberlauf");
        }

    }

    Fraction operator-(const Fraction & x) const // Subtraction
    {
        if (abs(numerator()) < std::numeric_limits<inttype>::max()/abs(x.denominator())
            and abs(denominator()) < std::numeric_limits<inttype>::max()/abs(x.numerator()))
        {
            if (abs(numerator() * x.denominator()) < std::numeric_limits<inttype>::max()-abs(x.numerator() * denominator())
                and abs(denominator()) < std::numeric_limits<inttype>::max()/abs(x.denominator()))
            {
                Fraction y(numerator() * x.denominator() -
                        x.numerator() * denominator(),
                        denominator() * x.denominator());
                y.cancel();
                return y;
            }
            else
            {
                throw std::runtime_error("Ueberlauf");
            }
        }
        else
        {
            throw std::runtime_error("Ueberlauf");
        }


    }

    Fraction operator*(const Fraction & x) const // Multiplikation
    {
        if (abs(numerator()) < std::numeric_limits<inttype>::max()/abs(x.numerator())
            and abs(denominator()) < std::numeric_limits<inttype>::max()/abs(x.denominator()))
        {
            Fraction y(numerator() * x.numerator(), denominator() * x.denominator());
            y.cancel();
            return y;
        }
        else
        {
            throw std::runtime_error("Ueberlauf");
        }
    }

    Fraction operator/(const Fraction & x) const // Division
    {
        if (x.numerator() == 0)
        {
            throw std::runtime_error("Denominator < 1 not allowed in Fraction.");
        }
        else
        {
            if (abs(numerator()) < std::numeric_limits<inttype>::max()/abs(x.denominator())
            and abs(denominator()) < std::numeric_limits<inttype>::max()/abs(x.numerator()))
            {
                Fraction y(numerator() * x.denominator(), denominator() * x.numerator());
                y.cancel();
                return y;
            }
            else
            {
                throw std::runtime_error("Ueberlauf");
            }
        }
    }



private:
    inttype _numerator;
    inttype _denominator;

    void cancel()                               // Kürzen
	{
		inttype a = _numerator, b = _denominator;

		if (a == 0)
		{
			_numerator = 0;
			_denominator = 1;
		}
		else
		{
			if (a<0)
            {
                a = -a;
            }
            while (b > 0)
			{
				if (a > b) a = a-b;
				else b = b-a;
			}

			_numerator = _numerator/a;
			_denominator = _denominator/a;
		}
	}

    void error_zero()
    {
        throw std::runtime_error("Denominator < 1 not allowed in Fraction.");
    }
};

int main()
{
    try
    {
        Fraction a(6,1);
        Fraction b(0,1);
        Fraction c = a/b;
        c.print();
    }
    catch(std::runtime_error e)
    {
        std::cout <<"RUNTIME ERROR: " << e.what() << "\n";
        return 1;
    }
}


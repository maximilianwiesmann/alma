//
// Created by Jonas Lippert and Maximilian Wiesmann
//

// largeint.cpp (Implementation of Class LargeInt)

#include "largeint.h"
#include <iostream>
#include <stdexcept>

using myint = long long;

LargeInt gcd2(LargeInt a, LargeInt b)
{
    if (b.is_zero())
    {
		return a;
	}
	else if (a.is_even())
    {
		if (b.is_even())
        {
            b.div2();
            a.div2();
			return LargeInt(2) * gcd2(b, a);
		}
		else
		{
            a.div2();
			return  gcd2(b, a);
		}
	}
	else
	{

		if (b.is_even())
		{
		    b.div2();
			return  gcd2(a, b);
		}
		else if (a < b)
		{
		    b = b - a;
		    b.div2();
            return gcd2(a, b);
		}
		else
		{
		    a = a - b;
            a.div2();
			return  gcd2(b, a);
		}
	}
}

int main()
{

   myint a, b;
   std::cout << "This program computes the greatest common divisor.\n"
              << "Enter two natural numbers, separated by blank: ";
   std::cin >> a >> b;

   std::cout << "gcd: " << gcd2(LargeInt(a), LargeInt(b)).decimal() << "\n";


   return 0;
}

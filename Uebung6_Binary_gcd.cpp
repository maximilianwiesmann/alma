//
// Created by Maximilian Wiesmann on 16.11.2018.
//

#include "largeint.h"
#include <iostream>

using myint = long long;

void test(){
	LargeInt a(111);
    LargeInt b(12345678);
    try{
        std::cout << (a-b).decimal() << std::endl;
    }
    catch(std::runtime_error e){
        std::cout << "RUNTIME ERROR: " << e.what() << std::endl;
    }
    std::cout << b.div2(b).decimal() << std::endl;
	std::cout << a.is_even() << std::endl;
}

LargeInt gcd2(LargeInt a, LargeInt b)
{
    if (b.is_zero()){
		return a;
	}
	else if (a.is_even()){
		if (b.is_even()){  
			return LargeInt(2) * gcd2(b.div2(b), a.div2(a));
		}
		else { 
			return  gcd2(b, a.div2(a));
		}
	}
	else{
		if (b.is_even()) {
			return  gcd2(a, b.div2(b));
		}
		else if (a < b) {
			return  gcd2(a, b.div2(b-a));
		}
		else  {
			return  gcd2(b, a.div2(a-b));
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



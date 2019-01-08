#include <iostream>
#include <vector>
#include <random>

std::default_random_engine generator(time(NULL));

template <typename T> // Muss kompatibel mit < sein
void quicksort(std::vector<T> &v, size_t first, size_t last)
{
	if (first == last) return;
	
	std::uniform_int_distribution<size_t> distribution(first, last);
	size_t x = distribution(generator);
	x = distribution(generator);
	
	std::vector<T> Sx, S1, S2;
	
	for(size_t i = first; i <= last; ++i)
	{
		v[i] < v[x] ? 	S1.push_back(v[i]) : 
						v[i] == v[x] ? 
						Sx.push_back(v[i]) : S2.push_back(v[i]);
	}
	
	size_t l1 = 0;
	size_t l2 = 0;

	if (S1.size() > 0) l1 = S1.size()-1;
	if (S2.size() > 0) l2 = S2.size()-1;
	
	quicksort(S1, 0, l1);
	quicksort(S2, 0, l2);
	
	v = S1;
	
	for(auto i : Sx)
	{
		v.push_back(i);
	}
		
	for(auto i : S2)
	{
		v.push_back(i);
	}		
}

int main()
{
	std::uniform_int_distribution<int> distribution(100, 999);
	
	std::vector<int> myints;
	
	int a = 0, k = 0;
	
	std::cin >> k;
	
	std::cout << "\n\n";
	a = distribution(generator);
	
	for(int i = 1; i <= k; ++i)
	{
		a = distribution(generator);
		myints.push_back(a);
		std::cout << a << ", ";
	}
	
	std::cout << "\n\n";
	
	quicksort(myints, 0, k-1);
	
	for(int i = 0; i <= k-1; ++i)
	{
		std::cout << myints.at(i) << ", ";
	}

	std::cout << "\n\n";
}

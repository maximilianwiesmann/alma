//
// Created by Maximilian Wiesmann on 20.11.2018.
//

#include <iostream>
#include <vector>
#include <cmath>

std::vector<bool> is_prime((unsigned)pow(10,7),true);
std::vector<int> primes;

void sieve(){
    is_prime[0] = false;
    is_prime[1] = false;
    for(unsigned i = 2; i < is_prime.size(); ++i){
        if(is_prime[i] == true){
            for(unsigned j = 2; i*j < is_prime.size(); ++j){
                is_prime[i*j] = false;
            }
        }
    }
}

void init_primes(){
    for(unsigned i = 0; i < is_prime.size(); ++i){
        if(is_prime[i])
            primes.push_back(i);
    }
}

int moebius(int n){
    if(n == 1)
        return 1;
    else if(is_prime[n]){
        return -1;
    }
    else{
        unsigned j = 0;
        while(n % primes[j]){++j;}
        if(n/primes[j] % primes[j] == 0)
            return 0;
        else
            return (-1)*moebius(n/primes[j]);
    }
}

int main(){
    sieve();
    init_primes();
    int result = 0;
    for(unsigned i = 1; i <= (unsigned)pow(10,7); ++i){
        result += moebius(i);
    }
    std::cout << result << std::endl;
    return 0;
}


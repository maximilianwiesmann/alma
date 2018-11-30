//
// Created by Jonas Lippert and Maximilian Wiesmann
//

#include <vector>
#include <string>
#include <iostream>

class Polynomial{

    friend Polynomial operator*(int lhs, const Polynomial & rhs);

public:
    Polynomial(){                                  // construct zero polynomial

    }
    void SetCoefficient(size_t index, int value){  // set coefficient for x^index
        if(_coefficient.size() < index){
            _coefficient.resize(index + 1, 0);
        }
        _coefficient[index] = value;
    }
    std::string toString() const {                 // convert to string
        std::string poly_string = "";
        for(auto i = _coefficient.size(); i-- > 0;){
            if(i == 0){
                if(_coefficient.size() == 1){
                    poly_string = std::to_string(_coefficient[0]);
                }
                else{
                    if(_coefficient[i] < 0)
                        poly_string += (" - " + std::to_string(std::abs(_coefficient[i])));
                    else if(_coefficient[i] > 0)
                        poly_string += (" + " + std::to_string(_coefficient[i]));
                }
            }
            else if(i == _coefficient.size() - 1){
                if(_coefficient[i] < -1)
                    poly_string += ("- " + std::to_string(std::abs(_coefficient[i])) + " x^" + std::to_string(i));
                else if(_coefficient[i] == -1)
                    poly_string += ("- x^" + std::to_string(i));
                else if(_coefficient[i] == 1)
                    poly_string += ("x^" + std::to_string(i));
                else if(_coefficient[i] > 1)
                    poly_string += (std::to_string(_coefficient[i]) + " x^" + std::to_string(i));
            }
            else{
                if(_coefficient[i] < -1)
                    poly_string += (" - " + std::to_string(std::abs(_coefficient[i])) + " x^" + std::to_string(i));
                else if(_coefficient[i] == -1)
                    poly_string += (" - x^" + std::to_string(i));
                else if(_coefficient[i] == 1)
                    poly_string += (" x^" + std::to_string(i));
                else if(_coefficient[i] > 1)
                    poly_string += (" + " + std::to_string(_coefficient[i]) + " x^" + std::to_string(i));
            }
        }
        return poly_string;
    }

private:
    std::vector<int> _coefficient;
};

Polynomial operator*(int lhs, const Polynomial & rhs) {     // scalar multiplication
    Polynomial result;
    if(lhs == 0){
        result._coefficient.push_back(0);
        return result;
    }
    else{
        for(size_t i = 0; i < rhs._coefficient.size(); ++i){
            result._coefficient.push_back(lhs * rhs._coefficient[i]);
        }
    }
    return result;
}


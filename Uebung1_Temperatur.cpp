//1. Übungsblatt
//Aufgabe 4, Programmieraufgabe
//by Maximilian Wiesmann

#include <iostream>

int main() 
{
    double temperatur_in_fahrenheit;
    std::cout << "Geben Sie eine Temperatur in °F ein" << std::endl;
    std::cin >> temperatur_in_fahrenheit;
    double temperatur_in_celsius = (temperatur_in_fahrenheit - 32)/1.8;
    std::cout << "Diese Temperatur entspricht " << temperatur_in_celsius << "°C" << std::endl;
    std::cout << "Geben Sie nun eine Temperatur in °C ein" << std::endl;
    std::cin >> temperatur_in_celsius;
    temperatur_in_fahrenheit = (temperatur_in_celsius * 1.8) + 32;
    std::cout << "Diese Temperatur entspricht " << temperatur_in_fahrenheit << "°F" << std::endl;
    return 0;
}

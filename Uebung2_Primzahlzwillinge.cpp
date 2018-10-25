//
// Created by Jonas Lippert and Maximilian Wiesmann
// Matr.-Nr. 3234472
// Uebungsgruppe 4
//
// 2. Uebungsblatt
//

#include<iostream>
#include <vector>

std::vector<bool> is_prime(1000000,true);
int anzahl_zwillinge = 0;   //speichert die Anzahl gefundener Primzahlzwillinge

//Die folgende Methode implementiert das Sieb des Eratosthenes
//Im Vektor is_prime wird an der Stelle n gespeichert, ob n prim ist oder nicht
void sieb(){
    is_prime[0] = false;
    is_prime[1] = false;
    for(int i = 2; i < is_prime.size(); ++i){
        if(is_prime[i] == true){
            for(int j = 2; i*j < is_prime.size(); ++j){
                is_prime[i*j] = false;
            }
        }
    }
}

//Wenn im Vektor is_prime an zwei Stellen mit Differenz 2 ein true zu finden ist, also beide Stellen prim sind, wird das Paar ausgegeben
void suche_zwillinge(){
    for(int i = 0; i < is_prime.size()-2; ++i){
        if((is_prime[i] == true) and (is_prime[i+2] == true)){
            std::cout << "(" << i << "," << i+2 << "), " << std::endl;
            ++anzahl_zwillinge;     //ein Primzahlzwilling wurde gefunden, daher wird die Anzahl um 1 erhöht
        }
    }
}

int main(){
    sieb();
    suche_zwillinge();
    std::cout << "Es gibt " << anzahl_zwillinge << " viele Primzahlzwillinge < 10^6" << std::endl;
}


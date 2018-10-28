//
// Created by Jonas Lippert and Maximilian Wiesmann
// Blatt 3, Programmieraufgabe
//

#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

using zahl = long long;

//Die Collatz-Folge wird berechnet
unsigned collatz(zahl n){
    unsigned folgenlaenge = 1;  //gibt die Laenge der aktuellen Collatz-Folge an
    while(n > 1){
        if(n % 2 == 0){
            n /= 2;
        }
        else{
            //ist das neue Folgenglied groeßer als die maximale Zahl, die mit dem verwendeten
            //Datentyp gespeichert werden kann, wird ein Fehler geworfen
            if(n >= (1./3) * std::numeric_limits<zahl>::max()){
                throw std::runtime_error("Das naechste Collatz-Folgenglied wird "
                                         "groeßer als der verwendete Datentyp zulaesst");
            }
            n = 3*n +1;
        }
        //wird die Folge laenger, als in unsigned gespeichert werden kann, gibt es auch einen Fehler
        if(folgenlaenge == std::numeric_limits<unsigned>::max()){
            throw std::runtime_error("Die Folgenlaenge wird groeßer als der Datentyp"
                                     "unsigned zulaesst");
        }
        ++folgenlaenge;
    }
    return folgenlaenge;
}

//fuer alle Anfangswerte bis einschliesslich n wird die Laenge der Collatz-Folge
//in dem Vektor folgenlaengen gespeichert, welcher schliesslich zurueck gegeben wird
std::vector<unsigned> berechne_folgenlaengen(zahl n){
    std::vector<unsigned> folgenlaengen;
    for(zahl i = 1; i <= n; ++i){
        folgenlaengen.push_back(collatz(i));
    }
    return folgenlaengen;
}

int main(){
    try{
        zahl n = 1000000;
        std::vector<unsigned> folgenlaengen = berechne_folgenlaengen(n);
        unsigned max_eingabe = 1;
        unsigned max_laenge = 1;
        for(unsigned i = 0; i < folgenlaengen.size(); ++i){     //das Maximum der Folgenlaengen wird gesucht
            if(folgenlaengen[i] > max_laenge){
                max_laenge = folgenlaengen[i];
                max_eingabe = i + 1;
            }
            //fuer jedes n, 1<=n<=10^6, als Startwert wird die resultierende Folgenlaenge ausgegeben
            std::cout << "Anfangswert: " << i+1 << "; Folgenlaenge: " << folgenlaengen[i] << std::endl;
        }
        std::cout << "Die laengste Collatz-Folge fuer Anfangswerte zwischen 1 und 1000000 "
                     "erhaelt man fuer n* = " << max_eingabe << " mit Laenge " << max_laenge << std::endl;
    }
    //der Fehler wird aufgefangen und die Fehlermeldung ausgegeben
    catch (std::runtime_error e){
        std::cout << "RUNTIME ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}


#include <iostream>
#include <stdexcept>
#include <limits>

// Mit int erhalten wir den Fehler "ueberlauf". Läuft fehlerfrei mit unsigned long.
using myint = int;


// Hier drei eigene Fehlertypen
class n_zu_klein
{
};

class n_zu_gross
{
};

class ueberlauf
{
};

// Berechnung der Laenge der Collatz-Folge mit Startwert i
myint collatz (myint i)
{
    myint laenge = 1;

    while (i>1)
    {
        if (i % 2 == 0)
        {
            i = i/2;
        }
        else
        {
            if (i < (1./3)*std::numeric_limits<myint>::max())
            {
                i = 3*i+1;
            }
            else
            {
                throw ueberlauf();
            }
        }

        if (laenge < laenge + 1)
        {
            ++laenge;
        }
        else
        {
            throw ueberlauf();
        }
    }

    return laenge;
}


void eingabe(myint & n)
{
    std::cout << "Bitte geben sie eine natuerliche Zahl zwischen 1 und 1.000.000 ein." << std::endl;
    std::cin >> n;

    if (n < 1)
    {
        throw n_zu_klein();
    }
    if (n > 1000000)
    {
        throw n_zu_gross();
    }
}


int main()
{
    myint n = 0;

    eingabe:
    try
    {
        eingabe(n);
    }
    catch (n_zu_klein)
    {
        std::cout << "\nDie eingegebene Zahl ist kleiner als 1." << std::endl;
        goto eingabe;
    }
    catch (n_zu_gross)
    {
        std::cout << "\nDie eingegebene Zahl ist zu gross." << std::endl;
        goto eingabe;
    }

    myint laenge_n = 0; // Länge von n
    myint laenge_max = 0; // Länge der längsten Folge
    myint n_max = 0; // Startwert der längsten Folge

    // Für Schleife:
    myint laenge = 0;
    myint j = 1;

    // Berechnung
    try
    {
        for(myint i = 2; i <= 1000000; ++i)
        {
            laenge = collatz(i);

            if (laenge > laenge_max)
            {
                laenge_max = laenge;
                n_max = i;
            }

            if (i == n)
            {
                laenge_n = laenge;
            }

            j = i;
        }
    }
    catch(ueberlauf)
    {
        std::cout << "\nDer verwendete Datentyp ist zu klein fuer die auftretenden Collatz-Folgen!\n\n";
        goto ende;
    }

    ende:
    if (n <= j)
    {
        std::cout << "Die mit " << n << " startende Collatz-Folge hat die Laenge " << laenge_n << "." << std::endl;
    }
    std::cout << "Die laengste Collatz-Folge mit Startwert von 1 bis " << j << " beginnt mit " << n_max << " und hat die Laenge " << laenge_max << "." << std::endl;
}

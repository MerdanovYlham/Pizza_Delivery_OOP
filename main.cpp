/*
PROIECT: Pizza Delivery

DESCRIEREA PROBLEMEI:
Acest program simuleaza un sistem simplu de livrare pizza. Se gestioneaza
lista de pizza disponibile, clientii si comenzile acestora.

DATE DE INTRARE:
* pizza: denumire, pret, dimensiune
* client: nume, telefon
- adresa: oras, strada, numar
- comanda: lista de indexi ai pizzei alese
- optional date din fisier (pizza.txt)

OPERATII POSIBILE:
- afisare lista pizza
- afisare lista clienti
- verificare pizza premium (pret > 45)
- adaugare pizza si clienti
- calcul total comanda
- incarcare pizza din fisier

CLASE FOLOSITE:
- Pizza
- Adresa
- Client
- PizzaDelivery

OBSERVATII:
Programul foloseste concepte POO: constructori, constructor de copiere,
operator=, destructor si operator<< pentru afisare.
Sunt folosite si functii const unde este nevoie.

In main se creeaza obiecte si se apeleaza functiile pentru a simula
functionarea sistemului. Programul genereaza date la pornire si permitie
interactiunea printr-un meniu simplu.
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
class Pizza
{
private:
    char denumire[50];
    float pret;
    char dimensiunea[20];

public:
    Pizza() // constructor fara parametr
    {
        strcpy(denumire, "na");
        pret = 0;
        strcpy(dimensiunea, "na");
    }

    Pizza(const char *d, float p, const char *dim)
    {
        strcpy(denumire, d);
        pret = p;
        strcpy(dimensiunea, dim);
    }

    Pizza(const Pizza &p)
    {
        strcpy(denumire, p.denumire);
        strcpy(dimensiunea, p.dimensiunea);
        pret = p.pret;
    }
    Pizza &operator=(const Pizza &p) // Operator egal
    {
        if (this != &p)
        {
            strcpy(denumire, p.denumire);
            pret = p.pret;
            strcpy(dimensiunea, p.dimensiunea);
        }
        return *this;
    }

    ~Pizza()
    {
    }

    float getpret() const
    {
        return pret;
    }

    const char *getdenumire() const
    {
        return denumire;
    }

    bool isPremium() const
    {
        return pret > 45;
    }

    friend std::ostream &operator<<(std::ostream &out, const Pizza &p)
    {
        out << " denumire: " << p.denumire
            << " pret: " << p.pret
            << " dimensiunea: " << p.dimensiunea;
        return out;
    }
};
class Adresa
{
private:
    char oras[50];
    char strada[50];
    int nr;

public:
    Adresa() // constructor fara parametr
    {
        strcpy(oras, "na");
        strcpy(strada, "na");
        nr = 0;
    }

    Adresa(const char *o, const char *str, int n)
    {
        strcpy(oras, o);
        strcpy(strada, str);
        nr = n;
    }

    Adresa(const Adresa &a)
    {
        strcpy(oras, a.oras);
        strcpy(strada, a.strada);
        nr = a.nr;
    }

    friend std::ostream &operator<<(std::ostream &out, const Adresa &a)
    {
        out << " oras: " << a.oras
            << " strada: " << a.strada
            << " nr strada: " << a.nr;
        return out;
    }

    Adresa &operator=(const Adresa &a)
    {
        if (this != &a)
        {
            strcpy(oras, a.oras);
            strcpy(strada, a.strada);
            nr = a.nr;
        }
        return *this;
    }

    ~Adresa() {}

    const char *getoras() const
    {
        return oras;
    }
};

class Client
{
private:
    char nume[50];
    char telefon[20];
    Adresa adresa; // Has a

public:
    Client() // constructor fara parametr
    {
        {
            strcpy(nume, "na");
            strcpy(telefon, "000");
        }
    }
    Client(const char *n, const char *t, const Adresa &a)
    {
        strcpy(nume, n);
        strcpy(telefon, t);
        adresa = a;
    }
    Client(const Client &c) : adresa(c.adresa)
    {
        strcpy(nume, c.nume);
        strcpy(telefon, c.telefon); // constructor  de copiere
    }
    friend std::ostream &operator<<(std::ostream &out, const Client &c)
    {
        out << " Nume: " << c.nume
            << " Telefon: " << c.telefon
            << " Adresa: " << c.adresa;
        return out;
    }

    Client &operator=(const Client &c)
    {
        if (this != &c)
        {
            strcpy(nume, c.nume);
            strcpy(telefon, c.telefon);
            adresa = c.adresa;
        }
        return *this;
    }

    ~Client() {}
};

class PizzaDelivery
{
private:
    std::vector<Pizza> pizzaDisponibila; // has-a
    std::vector<Client> clienti;         // has-a

public:
    void incarcaPizzaDinFisier(const std::string &numeFisier)
    {
        std::ifstream fin(numeFisier);
        if (!fin)
        {
            std::cout << "Fisierul nu a fost gasit -> se adauga pizza implicit\n";
            pizzaDisponibila.push_back(Pizza("Margherita", 30, "Medie"));
            pizzaDisponibila.push_back(Pizza("Pepperoni", 42, "Mare"));
            pizzaDisponibila.push_back(Pizza("QuattroFormaggi", 45, "Mare"));
            return;
        }

        std::string nume, dimensiune;
        float pret;
        while (fin >> nume >> pret >> dimensiune)
        {
            pizzaDisponibila.push_back(Pizza(nume.c_str(), pret, dimensiune.c_str()));
        }
    }

    void adaugaPizza(const Pizza &p) // adauga pizza in lista de pizza disponibila
    {
        pizzaDisponibila.push_back(p);
    }

    void adaugaClient(const Client &c)
    {
        clienti.push_back(c);
    }

    void afisarePizzas() const
    {
        std::cout << "\n--- Lista Pizza ---\n";
        for (int i = 0; i < pizzaDisponibila.size(); i++)
            std::cout << i << ". " << pizzaDisponibila[i] << std::endl;
    }
    void afisareClienti() const
    {
        std::cout << "\n---Lista de Client---\n";
        for (const Client &c : clienti)
            std::cout << c << std::endl;
    }

    float calculcomandaTotal(const std::vector<int> &indice) const // comanda total calcul
    {
        float total = 0;

        for (int index : indice)
        {
            if (index < pizzaDisponibila.size())
            {
                total += pizzaDisponibila[index].getpret();
            }
        }

        return total;
    }
};

int main()
{
    PizzaDelivery system;

    Pizza p;
    Pizza p1("Margherita", 50, "medium"); // constructor cu parametr
    Pizza p2("Pepperoni", 24.99, "mare");
    Pizza p3("Veggie", 39.90, "mic");
    Pizza p4("Pizza kebab de Curcan", 27.50, "mic");
    Pizza p5("Chicken corn", 29.50, "mare");
    Pizza p6 = p5; // constructor de copiere.

    Adresa a;
    Adresa a1("Bucuresti", "Libertatii", 10);
    Adresa a2("Bucuresti", "Avram Iancu", 25);

    Adresa a3 = a1;

    Client c;
    Client c1("Andrei Popescu", "0747569540", a1);
    Client c2("Maria Ionescu", "0755616060", a2);
    Client c3("Mihai Dumitrescu", "0775002534", a3);
    Client c4("Stefan  Andrei:", "0763140530", a2);
    Client c5 = c2;

    std::cout << p << std::endl;  // a apela la ecran operator<<
    std::cout << p1 << std::endl; //  ostream afisare.
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;

    std::cout << p6 << std::endl;

    p2 = p3; // operator egal.
    std::cout << p2 << std::endl;

    std::cout << "denumire pizza: " << p1.getdenumire() << std::endl;
    std::cout << "pret pizza: " << p1.getpret() << std::endl;

    std::cout << "denumire pizza: " << p3.getdenumire() << std::endl;
    std::cout << "pret pizza: " << p3.getpret() << std::endl;

    if (p1.isPremium()) // bool true false.
    {
        std::cout << p1.getdenumire() << " este pizza premium" << std::endl;
    }
    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;

    std::cout << a3 << std::endl;
    a2 = a1;
    std::cout << a2 << std::endl;

    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    std::cout << c5 << std::endl;

    c2 = c3; // operator egal.
    std::cout << c2 << std::endl;

    system.adaugaPizza(p1);
    system.adaugaPizza(p2);

    system.adaugaClient(c1);

    system.afisarePizzas();
    system.afisareClienti();
    std::vector<int> comanda = {0, 1, 2, 3, 4};
    std::cout << "\nTotal  pret comanda: "
              << system.calculcomandaTotal(comanda)
              << std::endl;

    // incarcare pizza din fisier
    system.incarcaPizzaDinFisier("pizza.txt");

    int optiune;
    do
    {
        std::cout << "\n--- Meniu Livrare Pizza ---\n";
        std::cout << "1. Afiseaza pizza\n";
        std::cout << "2. Afiseaza clienti\n";
        std::cout << "3. Adauga comanda\n";
        std::cout << "4. Iesire\n";
        std::cout << "Optiune: ";
        std::cin >> optiune;

        switch (optiune)
        {
        case 1:
            system.afisarePizzas();
            break;
        case 2:
            system.afisareClienti();
            break;
        case 3:
        {
            int n;
            std::cout << "Cate pizza vrei sa comanzi? ";
            std::cin >> n;
            std::vector<int> comanda;
            for (int i = 0; i < n; i++)
            {
                int index;
                std::cout << "Introdu index pizza: ";
                std::cin >> index;
                comanda.push_back(index);
            }
            std::cout << "Pret total comanda: "
                      << system.calculcomandaTotal(comanda)
                      << std::endl;
            break;
        }
        case 4:
            std::cout << "La revedere!\n";
            break;
        default:
            std::cout << "Optiune invalida!\n";
        }
    } while (optiune != 4);
    return 0;
}
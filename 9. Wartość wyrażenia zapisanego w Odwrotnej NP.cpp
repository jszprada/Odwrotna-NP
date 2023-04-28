#include <iostream>
#include <cassert>

using namespace std;
 
template <class T> class Link;
// ======================================================================
//                    Zamiana na double
// ======================================================================
double naDouble (string zmien) {
   
double przed = 0, po = 0, wynik;
int i = 0, licznikp = 0, potega = 1;
bool negacja = false;
   
if (zmien[i] == '-') {
    negacja = true;
    i++;
}
while (zmien[i] and zmien[i] != '.') {
    przed = przed * 10 + (zmien[i] - '0');    
    i++;
}
if ( zmien[i] == '.') {
    i++;

while (zmien[i]) {
    po = po * 10 + (zmien[i] - '0');    
    licznikp++;
    i++;
}
for (int j = 0; j < licznikp; j++) {
    potega = potega * 10;
}
    wynik = przed + (po / potega);
if( negacja ) {
    return (-1 * wynik);
}
    return wynik;
}
if( negacja ) {
    return (-1 * przed);
}
return przed;
}
// ======================================================================
//                    Deklaracja Stos
// ======================================================================
template <class T>
class Stos {
protected:
    Link <T> *first;                
 
public:
    Stos() : first(nullptr) {}      
    Stos(const Stos &source);      
    virtual ~Stos() {};                
 
    virtual void push(T value);
    T firstElement() const;        
    virtual void removeFirst();
    T pop();
    void dodaj();
    void odejmij();
    void mnoz();
    void dziel();
};
template <class T> T Stos <T> ::firstElement() const
{
    assert(first != nullptr);
    return first->value;
}
template <class T> void Stos <T> ::removeFirst() {
    assert(first != nullptr);
    Link <T> *ptr = first;  
    first = ptr->next;      
    delete ptr;
}
// ======================================================================
//                    Deklaracja pop
// ======================================================================
template <class T> T Stos <T> ::pop()
{
    T tmp = Stos <T>::firstElement();
    Stos <T>::removeFirst();
    return tmp;
}
// ======================================================================
//                    Deklaracja push
// ======================================================================
template <class T> void Stos <T> ::push(T value)
{
    first = new Link <T>(value, first);
}
// ======================================================================
//                    Deklaracja dodawania
// ======================================================================
template <class T> void Stos <T> ::dodaj()
{
    T a, b;
    b = Stos <T> ::pop();
    a = Stos <T> ::pop();
    Stos <T> ::push(a + b);
}
// ======================================================================
//                    Deklaracja odejmowania
// ======================================================================
template <class T> void Stos <T> ::odejmij()
{
    T a, b;
    b = Stos <T> ::pop();
    a = Stos <T> ::pop();
    Stos <T> ::push(a - b);
}
// ======================================================================
//                    Deklaracja mnozenia
// ====================================================================== 
template <class T> void Stos <T> ::mnoz()
{
    T a, b;
    b = Stos <T> ::pop();
    a = Stos <T> ::pop();
    Stos <T> ::push(a * b);
}
// ======================================================================
//                    Deklaracja dzielenia
// ====================================================================== 
template <class T> void Stos <T> ::dziel()
{
    T a, b;
    b = Stos <T> ::pop();
    a = Stos <T> ::pop();
   
    if ( b != 0) {
      Stos <T> ::push(a / b);  
    } else {
        cout << "Nie mozna dzielic pzrez 0!";
    }
}
// ======================================================================
//                    Deklaracja Link
// ======================================================================
template <class T>
class Link {
private:
    T value;
    Link <T> *next;
 
    Link(T val, Link *ptr) : value(val), next(ptr) { }
public:
    Link <T> *insert(T value);      
    friend class Stos <T>;
};
template <class T> Link <T> * Link <T> ::insert(T value)
{
    next = new Link <T>(value, next);
    return next;
}
// ======================================================================
//                              ONP
// ======================================================================
double ONP(string licz) {
    string wartosc = "";
    double dododania;
    Stos <double> stosONP;
    int i = 0;
    
while (licz[i]) {
    switch(licz[i]) {
        case 43:
            {
            stosONP.dodaj();
            break;
            }
        case 45:
            {
            if (licz[i + 1] >= 48 and licz[i + 1] <= 57) {
                wartosc = "";
                while(licz[i] != ' ') {
                    wartosc += licz[i];
                    i++;
                }
                dododania = naDouble(wartosc);
                stosONP.push(dododania);
                break;  
                }
            stosONP.odejmij();
            break;
            }
        case 42:
            {
            stosONP.mnoz();
            break;
            }
        case 47:
            {
            stosONP.dziel();
            break;
            }
        default:
            {
            if( licz[i] != ' ') {
                wartosc = "";
                while(licz[i] != ' ') {
                    wartosc += licz[i];
                    i++;
                }
                dododania = naDouble(wartosc);
                stosONP.push(dododania);
            }
            break;
            }
        }
        i++;
    }
    return stosONP.pop();
}
// ======================================================================
//                    Sprawdzanie wprowadzonych danych
// ======================================================================
bool sprDane(string doSpr) {
    int i = 0;
    while (doSpr[i]) {
        if (doSpr[i] != ' ' and doSpr[i] != '.' and doSpr[i] != 43 and doSpr[i] != 45 and doSpr[i] != 42 and doSpr[i] != 47 and doSpr[i] < 48 or doSpr[i] > 57) {
             return false;
}
        i++;
}
    return true;
}
bool sprDouble(string dane, int &i) {
    int licznik = 0;
    bool nie = false;
if (dane[i] == '-') {
    i++;
}
while (dane[i] and dane[i] != ' ') {
    if ((dane[i] < 48 or dane[i] > 57) and dane[i] != '.') {
    return false;
}
    if (dane[i] == '.') {
    nie = true;
    licznik++;
    if (dane[i + 1] < 47 or dane[i + 1] > 57) return false;
}
    i++;
}
    if (nie and licznik > 1) {
    return false;
}
    return true;
}
bool dwieNapocz(string dane) {
    int i = 0;
    if (dane[i] != '-' and (dane[i] < 48 or dane[i] > 58)) return false;
    if (!sprDouble(dane, i)) return false;
    if (dane[i] != ' ') return false;
    i++;
    if (!sprDouble(dane, i)) return false;
    if (dane[i] != ' ') return false;
   return true;
}
bool spr(string dane) {
if (sprDane(dane) and dwieNapocz(dane)) {
    int i = 0, rozmiar = dane.length();
        while (dane[i]) {
            switch (dane[i]) {
            case 43: //dodac
            {
                if (i < rozmiar - 1) {
                    if (dane[i + 1] != ' ') return false;
                    if (dane[i - 1] != ' ') return false;
                }
                else if (i == rozmiar - 1) {
                    if (dane[i - 1] != ' ') return false;
                }
                break;
}
                case 45: //odjac
                {
                if (dane[i + 1] >= 48 and dane[i + 1] <= 57) {
                    if (!sprDouble(dane, i)) return false;
                    break;
                }
                if (i < rozmiar - 1) {
                    if (dane[i + 1] != ' ') return false;
                    if (dane[i - 1] != ' ') return false;
                }
                else if (i == rozmiar - 1) {
                    if (dane[i - 1] != ' ') return false;
                }
                break;
}
            case 42: //mnozyc
            {
                if (i < rozmiar - 1) {
                    if (dane[i + 1] != ' ') return false;
                    if (dane[i - 1] != ' ') return false;
                }
                else if (i == rozmiar - 1) {
                    if (dane[i - 1] != ' ') return false;
                }
 
                break;
}
            case 47: //dzielic
            {
                if (i < rozmiar - 1) {
 
                    if (dane[i + 1] != ' ') return false;
                    if (dane[i - 1] != ' ') return false;
                }
                else if (i == rozmiar - 1) {
                    if (dane[i - 1] != ' ') return false;
                }
 
                break;
}
            default:
            {
                if (dane[i + 1] >= 48 and dane[i + 1] <= 57) {
                    if (!sprDouble(dane, i)) return false;
                }
                break;
}
 
        }
        i++;
        }
    if (i == rozmiar) return true;
}
    return false;
}
// ======================================================================
//                              main
// ======================================================================
int main()
{
    string ONPstr;
    do {
        getline(cin,ONPstr);
    } while (!spr(ONPstr));
   
    cout << ONP(ONPstr);

    return 1;
}
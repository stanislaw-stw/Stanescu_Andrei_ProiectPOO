#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Sirena;
class AparatFotografiat;
class Antena;

// Prototipurile funcțiilor globale prietene
void afiseazaDetaliiSirena(const Sirena& s);
void afiseazaDetaliiAparat(const AparatFotografiat& a);
void afiseazaDetaliiAntena(const Antena& ant);

class Sirena {
private:
    int intensitate;
    string culoare;
    double* frecventa;
    static int numarTotalDeSirene;
    const string tipSirena;

public:
    // Constructori
    Sirena(int _intensitate, string _culoare, double _frecventa, string _tipSirena)
            : intensitate(_intensitate), culoare(_culoare), frecventa(new double(_frecventa)), tipSirena(_tipSirena) {
        numarTotalDeSirene++;
    }

    Sirena(int _intensitate, string _culoare)
            : Sirena(_intensitate, _culoare, 100.0, "Standard") {}

    Sirena()
            : Sirena(5, "Rosu", 100.0, "Standard") {}

    // Destructor
    ~Sirena() {
        delete frecventa;
        numarTotalDeSirene--;
    }

    // Constructor de copiere
    Sirena(const Sirena& other)
            : intensitate(other.intensitate), culoare(other.culoare), frecventa(new double(*other.frecventa)), tipSirena(other.tipSirena) {
        numarTotalDeSirene++;
    }

    Sirena& operator=(const Sirena& other) {
        if (this != &other) {
            intensitate = other.intensitate;
            culoare = other.culoare;
            *frecventa = *other.frecventa;
        }
        return *this;
    }
    // Overloading the prefix increment operator
    Sirena& operator++() {
        ++intensitate;
        return *this;
    }
    // Overloading the addition operator
    Sirena operator+(const Sirena& other) const {
        return Sirena(intensitate + other.intensitate, culoare, *frecventa + *other.frecventa, tipSirena);
    }
    // Overloading the equality operator
    bool operator==(const Sirena& other) const {
        return intensitate == other.intensitate && culoare == other.culoare && *frecventa == *other.frecventa;
    }

    friend istream& operator>>(istream& in, Sirena& s) {
        cout << "Introduceti intensitatea: " << endl;
        in >> s.intensitate;
        cout << "Introduceti culoarea: " << endl;
        in >> s.culoare;
        cout << "Introduceti frecventa:" << endl;
        in >> *s.frecventa;
        return in;
    }

// Supraincarcare operator << pentru clasa Sirena
    friend ostream& operator<<(ostream& out, const Sirena& s) {
        out << "Sirena de tip " << s.tipSirena << " cu culoarea " << s.culoare
            << " are intensitatea " << s.intensitate << " și frecventa de " << *s.frecventa << " Hz." << endl;
        return out;
    }

    // Get-eri
    int getIntensitate() const { return intensitate; }
    string getCuloare() const { return culoare; }
    double getFrecventa() const { return *frecventa; }
    static int getNumarTotalDeSirene() { return numarTotalDeSirene; }
    string getTipSirena() const { return tipSirena; }

    // Set-eri
    void setIntensitate(int _intensitate) { intensitate = _intensitate; }
    void setCuloare(string _culoare) { culoare = _culoare; }
    void setFrecventa(double _frecventa) { *frecventa = _frecventa; }

    // Funcție statică
    static void afiseazaNumarSirene() {
        cout << "Numar total de sirene: " << numarTotalDeSirene << endl;
    }

};


int Sirena::numarTotalDeSirene = 0;

class AparatFotografiat {
private:
    int rezolutie;
    string tipSenzor;
    double* dimensiuneSenzor;
    static int numarTotalDeAparate;
    const string marca;

public:
    // Constructori
    AparatFotografiat(int _rezolutie, string _tipSenzor, double _dimensiuneSenzor, string _marca)
            : rezolutie(_rezolutie), tipSenzor(_tipSenzor), marca(_marca) {
        dimensiuneSenzor = new double(_dimensiuneSenzor);
        numarTotalDeAparate++;
    }

    AparatFotografiat(int _rezolutie, string _tipSenzor)
            : AparatFotografiat(_rezolutie, _tipSenzor, 35.0, "Canon") {}

    AparatFotografiat()
            : AparatFotografiat(20, "CMOS", 35.0, "Canon") {}

    // Destructor
    ~AparatFotografiat() {
        delete dimensiuneSenzor;
        numarTotalDeAparate--;
    }

    // Constructor de copiere
    AparatFotografiat(const AparatFotografiat& other)
            : rezolutie(other.rezolutie), tipSenzor(other.tipSenzor), dimensiuneSenzor(new double(*other.dimensiuneSenzor)), marca(other.marca) {
        numarTotalDeAparate++;
    }

    AparatFotografiat& operator=(const AparatFotografiat& other) {
        if (this != &other) {
            rezolutie = other.rezolutie;
            tipSenzor = other.tipSenzor;
            *dimensiuneSenzor = *other.dimensiuneSenzor;
        }
        return *this;
    }
    // Overloading the addition operator
    AparatFotografiat operator+(int extraRezolutie) const {
        return AparatFotografiat(rezolutie + extraRezolutie, tipSenzor, *dimensiuneSenzor, marca);
    }
    // Overloading the subtraction operator
    AparatFotografiat operator-(int lessRezolutie) const {
        return AparatFotografiat(rezolutie - lessRezolutie, tipSenzor, *dimensiuneSenzor, marca);
    }
    // Overloading the inequality operator
    bool operator!=(const AparatFotografiat& other) const {
        return rezolutie != other.rezolutie || tipSenzor != other.tipSenzor || *dimensiuneSenzor != *other.dimensiuneSenzor;
    }
    friend istream& operator>>(istream& in, AparatFotografiat& a) {
        // Presupunem că avem acces la membrii privați datorită prieteniei.
        cout << "Introduceti rezolutia: " << endl;
        in >> a.rezolutie;
        cout << "Introduceti tipul senzorului: " << endl;
        in >> a.tipSenzor;
        cout << "Introcueti dimensiunea senzorului: " << endl;
        in >> *a.dimensiuneSenzor;
        return in;
    }

    friend ostream& operator<<(ostream& out, const AparatFotografiat& a) {
        out << "Aparatul fotografic marca " << a.marca << " cu senzorul " << a.tipSenzor
            << " are rezolutie de " << a.rezolutie << " megapixeli si dimensiunea senzorului de "
            << *a.dimensiuneSenzor << " mm." << endl;
        return out;
    }

    // Get-eri
    int getRezolutie() const { return rezolutie; }
    string getTipSenzor() const { return tipSenzor; }
    double getDimensiuneSenzor() const { return *dimensiuneSenzor; }
    static int getNumarTotalDeAparate() { return numarTotalDeAparate; }
    string getMarca() const { return marca; }

    // Set-eri
    void setRezolutie(int _rezolutie) { rezolutie = _rezolutie; }
    void setTipSenzor(string _tipSenzor) { tipSenzor = _tipSenzor; }
    void setDimensiuneSenzor(double _dimensiuneSenzor) { *dimensiuneSenzor = _dimensiuneSenzor; }

    // Funcție statică
    static void afiseazaNumarAparate() {
        cout << "Numar total de aparate: " << numarTotalDeAparate << endl;
    }

};


int AparatFotografiat::numarTotalDeAparate = 0;

class Antena {
private:
    double inaltime;
    string tip;
    double* lungimeUnda;
    static int numarTotalDeAntene;
    const string material;

public:
    // Constructori
    Antena(double _inaltime, string _tip, double _lungimeUnda, string _material)
            : inaltime(_inaltime), tip(_tip), material(_material) {
        lungimeUnda = new double(_lungimeUnda);
        numarTotalDeAntene++;
    }

    Antena(double _inaltime, string _tip)
            : Antena(_inaltime, _tip, 100.0, "Metal") {}

    Antena()
            : Antena(10.0, "Omni", 100.0, "Metal") {}

    // Destructor
    ~Antena() {
        delete lungimeUnda;
        numarTotalDeAntene--;
    }

    // Constructor de copiere
    Antena(const Antena& other)
            : inaltime(other.inaltime), tip(other.tip), lungimeUnda(new double(*other.lungimeUnda)), material(other.material) {
        numarTotalDeAntene++;
    }

    Antena& operator=(const Antena& other) {
        if (this != &other) {
            inaltime = other.inaltime;
            tip = other.tip;
            *lungimeUnda = *other.lungimeUnda;
        }
        return *this;
    }
    // Overloading the addition operator
    Antena operator+(double extraInaltime) const {
        return Antena(inaltime + extraInaltime, tip, *lungimeUnda, material);
    }
    // Overloading the subtraction operator
    Antena operator-(double lessLungimeUnda) const {
        return Antena(inaltime, tip, *lungimeUnda - lessLungimeUnda, material);
    }
    // Overloading the less than operator
    bool operator<(const Antena& other) const {
        return inaltime < other.inaltime;
    }

    // Get-eri
    double getInaltime() const { return inaltime; }
    string getTip() const { return tip; }
    double getLungimeUnda() const { return *lungimeUnda; }
    static int getNumarTotalDeAntene() { return numarTotalDeAntene; }
    string getMaterial() const { return material; }

    // Set-eri
    void setInaltime(double _inaltime) { inaltime = _inaltime; }
    void setTip(string _tip) { tip = _tip; }
    void setLungimeUnda(double _lungimeUnda) { *lungimeUnda = _lungimeUnda; }

    // Funcție statică
    static void afiseazaNumarAntene() {
        cout << "Numar total de antene: " << numarTotalDeAntene << endl;
    }
    void afiseazaDetaliiAntena(const Antena& ant);
    // Supraincarcare operator >> pentru clasa Antena
    friend istream& operator>>(istream& in, Antena& ant) {
        cout << "Introduceti inaltimea: " << endl;
        in >> ant.inaltime;
        cout << "Introduceti tipul: " << endl;
        in >> ant.tip;
        cout << "Introduceti lungimea de unda" << endl;
        in >> *ant.lungimeUnda;
        return in;
    }

// Supraincarcare operator << pentru clasa Antena
    friend ostream& operator<<(ostream& out, const Antena& ant) {
        out << "Antena de tip " << ant.tip << " din materialul " << ant.material
            << " are inaltimea de " << ant.inaltime << " metri si lungimea de unde de "
            << *ant.lungimeUnda << " metri." << endl;
        return out;
    }

};

int Antena::numarTotalDeAntene = 0;

void Antena::afiseazaDetaliiAntena(const Antena &ant) {
    cout << "Antena de tip " << ant.tip << " din materialul " << ant.material
         << " are inaltimea de " << ant.inaltime << " metri si lungimea de unde de " << *ant.lungimeUnda << " metri." << endl;
}


void afiseazaDetaliiSirena(const Sirena& s) {
    cout << "Sirena de tip " << s.getTipSirena() << " cu culoarea " << s.getCuloare()
         << " are intensitatea " << s.getIntensitate() << " și frecventa de " << s.getFrecventa() << " Hz." << endl;
}
void afiseazaDetaliiAparat(const AparatFotografiat& a) {
    cout << "Aparatul fotografic marca " << a.getMarca() << " cu senzorul " << a.getTipSenzor()
         << " are rezolutie de " << a.getRezolutie() << " megapixeli si dimensiunea senzorului de "
         << a.getDimensiuneSenzor() << " mm." << endl;
}



class EchipamentDeUrgenta {
private:
    Sirena sirena;
    AparatFotografiat aparatFotografiat;
    Antena antena;
    string locatie;
    bool esteFunctional;

public:
    // Constructor fără parametri
    EchipamentDeUrgenta()
            : sirena(), aparatFotografiat(), antena(), locatie("Nedefinit"), esteFunctional(false) {}

    // Constructor cu parametri
    EchipamentDeUrgenta(const Sirena& _sirena, const AparatFotografiat& _aparat, const Antena& _antena, const string& _locatie, bool _esteFunctional)
            : sirena(_sirena), aparatFotografiat(_aparat), antena(_antena), locatie(_locatie), esteFunctional(_esteFunctional) {}

    // Getteri și Setteri
    Sirena getSirena() const { return sirena; }
    void setSirena(const Sirena& _sirena) { sirena = _sirena; }

    AparatFotografiat getAparatFotografiat() const { return aparatFotografiat; }
    void setAparatFotografiat(const AparatFotografiat& _aparat) { aparatFotografiat = _aparat; }

    Antena getAntena() const { return antena; }
    void setAntena(const Antena& _antena) { antena = _antena; }

    string getLocatie() const { return locatie; }
    void setLocatie(const string& _locatie) { locatie = _locatie; }

    bool getEsteFunctional() const { return esteFunctional; }
    void setEsteFunctional(bool _esteFunctional) { esteFunctional = _esteFunctional; }

    // Operatori
    EchipamentDeUrgenta& operator++() {
        ++(sirena.operator++()); // Chemăm explicit operatorul ++ pentru sirena
        return *this;
    }


    bool operator==(const EchipamentDeUrgenta& other) const {
        // Compară atribute specifice în loc de întregul obiect
        return (sirena == other.sirena && aparatFotografiat.getRezolutie() == other.aparatFotografiat.getRezolutie() && antena.getInaltime() == other.antena.getInaltime());
    }

    EchipamentDeUrgenta operator+(const EchipamentDeUrgenta& other) const {
        // Combina doar sirenele și fol atributele unuia dintre echipamente pentru restul
        return EchipamentDeUrgenta(sirena + other.sirena, aparatFotografiat, antena, locatie, esteFunctional || other.esteFunctional);
    }

    // Operator de atribuire
    EchipamentDeUrgenta& operator=(const EchipamentDeUrgenta& other) {
        if (this != &other) {
            sirena = other.sirena;
            aparatFotografiat = other.aparatFotografiat;
            antena = other.antena;

            locatie = other.locatie;
            esteFunctional = other.esteFunctional;
        }
        return *this;
    }

};



int main() {
    Sirena s1(10, "Verde", 150.0, "Acustica");
    Sirena s2(15, "Albastru");
    s2.setCuloare("Verde");
    s1.setIntensitate(11);
    s2.setFrecventa(12.0);
    Sirena s3;

    AparatFotografiat a1(24, "CCD", 50.0, "Nikon");
    AparatFotografiat a2(20, "CMOS");
    a1.setDimensiuneSenzor(51.0);
    a2.setTipSenzor("DDC");
    a2.setRezolutie(50);
    AparatFotografiat a3;

    Antena ant1(15.0, "Directional", 200.0, "Plastic");
    Antena ant2(12.0, "Omni");
    Antena ant3;
    ant1.setInaltime(20.1);
    ant2.setLungimeUnda(200.1);
    ant2.setTip("Directional");

    Sirena::afiseazaNumarSirene();
    AparatFotografiat::afiseazaNumarAparate();
    Antena::afiseazaNumarAntene();
    Sirena s4, s5;
    s4 = s1; // Using the overloaded assignment operator
    s5 = s2;
    ++s4; // Using the overloaded prefix increment operator
    Sirena s6 = s1 + s2; // Using the overloaded addition operator
    bool equal = s6 == s3; // Using the overloaded equality operator
    cout << "Sirena 6 este egala cu sirena 3: " << equal;
    AparatFotografiat a4, a5;
    a4 = a1; // Using the overloaded assignment operator
    a5 = a2;
    AparatFotografiat a6 = a1 + 10; // Using the overloaded addition operator
    AparatFotografiat a7 = a3 - 5; // Using the overloaded subtraction operator
    bool notEqual = a1 != a4; // Using the overloaded inequality operator
    cout << "Aparatul 1 nu este egala cu Aparatul 4 " << notEqual;
    Antena ant4, ant5;
    ant4 = ant1; // Using the overloaded assignment operator
    ant5 = ant2;
    Antena ant6 = ant1 + 5.0; // Using the overloaded addition operator
    Antena ant7 = ant3 - 2.0; // Using the overloaded subtraction operator
    bool lessThan = ant1 < ant4; // Using the overloaded less than operator
    cout << "Antena 1 este mai mica ca antena 4: " << lessThan;
    // Calling friend functions to display details of the objects
    afiseazaDetaliiSirena(s1);
    afiseazaDetaliiAparat(a1);
    Antena ant8;
    ant8.afiseazaDetaliiAntena(ant7);

    int numarRanduri, numarColoane;
    cout << "Introduceti numarul de randuri pentru matricea de sirene: "<< endl;
    cin >> numarRanduri;
    cout << "Introduceti numarul de coloane pentru matricea de sirene: "<< endl;
    cin >> numarColoane;

// Crearea unei matrice de sirene folosind un vector de vectori.
    vector<vector<Sirena>> matriceSirene(numarRanduri, vector<Sirena>(numarColoane));

// Citirea sirenelor în matrice.
    for (int i = 0; i < numarRanduri; ++i) {
        for (int j = 0; j < numarColoane; ++j) {
            cout << "Introduceti date pentru sirena de la randul " << i + 1 << ", coloana " << j + 1 << ": " << endl;
            cin >> matriceSirene[i][j];
        }
    }

// Afișarea matricei de sirene.
    cout << "\nMatricea de sirene: \n";
    for (int i = 0; i < numarRanduri; ++i) {
        for (int j = 0; j < numarColoane; ++j) {
            cout << matriceSirene[i][j];
        }
        cout << endl; // Săritură de linie între rânduri pentru o mai bună lizibilitate.
    }

    vector<Sirena> vectorSirene;
    vector<AparatFotografiat> vectorAparate;
    vector<Antena> vectorAntene;

// Citirea și adăugarea sirenelor în vector:
    int numarSirene;
    cout << "Introduceti numarul de sirene: ";
    cin >> numarSirene;
    for (int i = 0; i < numarSirene; ++i) {
        Sirena sirena;
        cout << "Introduceti datele pentru sirena " << i+1 << ": " ;
        cin >> sirena;
        vectorSirene.push_back(sirena);
    }

// Afișarea sirenelor:
    for (const auto& sirena : vectorSirene) {
        afiseazaDetaliiSirena(sirena);
    }

    int numarAparate;
    cout << "Introduceti numarul de aparate fotografice: ";
    cin >> numarAparate;

    for (int i = 0; i < numarAparate; ++i) {
        AparatFotografiat aparat;
        cout << "Introduceti datele pentru aparatul fotografic " << i + 1 << ": ";
        cin >> aparat;
        vectorAparate.push_back(aparat);
    }

// Afișarea aparatelor fotografice:
    for (const auto& aparat : vectorAparate) {
        cout << aparat;
    }

    int numarAntene;
    cout << "Introduceti numarul de antene: ";
    cin >> numarAntene;

    for (int i = 0; i < numarAntene; ++i) {
        Antena antena;
        cout << "Introduceti datele pentru antena " << i + 1 << ": ";
        cin >> antena;
        vectorAntene.push_back(antena);
    }

// Afișarea antenelor:
    for (const auto& antena : vectorAntene) {
        cout << antena;
    }

    // testare clasa EchipamentDeUrgenta

    // Testare constructor fără parametri
    EchipamentDeUrgenta echipamentDefault;
    cout << "Echipament default - Locatie: " << echipamentDefault.getLocatie() << ", Este functional: " << (echipamentDefault.getEsteFunctional() ? "Da" : "Nu") << endl;

    // Testare constructor cu parametri
    Sirena sirenaNoua(15, "Albastru", 120.0, "Digital");
    AparatFotografiat aparatNou(25, "CMOS", 36.0, "Sony");
    Antena antenaNoua(20.0, "Directionala", 300.0, "Aluminiu");
    EchipamentDeUrgenta echipament(sirenaNoua, aparatNou, antenaNoua, "Cluj-Napoca", true);
    cout << "Echipament - Locatie: " << echipament.getLocatie() << ", Este functional: " << (echipament.getEsteFunctional() ? "Da" : "Nu") << endl;

    // Testare getteri și setteri
    echipament.setLocatie("Bucuresti");
    echipament.setEsteFunctional(false);
    cout << "Echipament actualizat - Locatie: " << echipament.getLocatie() << ", Este functional: " << (echipament.getEsteFunctional() ? "Da" : "Nu") << endl;

    // Testare operatori
    // Afișarea detaliilor înainte de incrementare
    cout << "Inainte de incrementare: " << endl;
    cout << "Intensitate sirena: " << echipament.getSirena().getIntensitate() << endl;
    ++echipament; // Testare operator ++
    // Afișarea detaliilor după incrementare
    cout << "Dupa incrementare: " << endl;
    cout << "Intensitate sirena: " << echipament.getSirena().getIntensitate() << endl;

    EchipamentDeUrgenta echipamentCopiat = echipament; // Testare operator de atribuire
    bool suntEgale = (echipament == echipamentCopiat); // Testare operator ==
    cout << "Echipamentele sunt egale: " << (suntEgale ? "Da" : "Nu") << endl;

    EchipamentDeUrgenta echipamentCombinat = echipament + echipamentCopiat; // Testare operator +
    cout << "Echipament combinat - Locatie: " << echipamentCombinat.getLocatie() << ", Este functional: " << (echipamentCombinat.getEsteFunctional() ? "Da" : "Nu") << endl;
    // Afișarea detaliilor componente ale echipamentului combinat
    cout << "Sirena - Intensitate: " << echipamentCombinat.getSirena().getIntensitate() << ", Culoare: " << echipamentCombinat.getSirena().getCuloare() << endl;
    cout << "Aparat Fotografiat - Rezolutie: " << echipamentCombinat.getAparatFotografiat().getRezolutie() << ", Tip Senzor: " << echipamentCombinat.getAparatFotografiat().getTipSenzor() << endl;
    cout << "Antena - Inaltime: " << echipamentCombinat.getAntena().getInaltime() << ", Tip: " << echipamentCombinat.getAntena().getTip() << endl;

}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Sirena;
class AparatFotografiat;
class Antena;
class EchipamentDeUrgenta;


// Prototipurile functiilor globale prietene
void afiseazaDetaliiSirena(const Sirena& s);
void afiseazaDetaliiAparat(const AparatFotografiat& a);
void afiseazaDetaliiAntena(const Antena& ant);


class EmitatorSunet {
public:
    virtual void scrieInFisierBinar(ofstream& out) const = 0;
    virtual void citesteDinFisierBinar(ifstream& in) = 0;
    virtual EmitatorSunet* clone() const = 0;
    virtual int getIntensitate() const = 0;
    virtual string getCuloare() const = 0;
    virtual ~EmitatorSunet() {}
};

class CaptorImagine {
public:
    virtual int getRezolutie() const = 0;
    virtual string getTipSenzor() const = 0;
    virtual void scrieInFisierBinar(ofstream& out) const = 0;
    virtual void citesteDinFisierBinar(ifstream& in) = 0;
    virtual CaptorImagine* clone() const = 0;
    virtual ~CaptorImagine() {}
};



class Sirena : public EmitatorSunet {
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
    int getIntensitate() const override {
        return intensitate;
    }

    string getCuloare() const override {
        return culoare;
    }

    double getFrecventa() const { return *frecventa; }
    static int getNumarTotalDeSirene() { return numarTotalDeSirene; }
    string getTipSirena() const { return tipSirena; }

    // Set-eri
    void setIntensitate(int _intensitate) { intensitate = _intensitate; }
    void setCuloare(string _culoare) { culoare = _culoare; }
    void setFrecventa(double _frecventa) { *frecventa = _frecventa; }

    // Functia statica
    static void afiseazaNumarSirene() {
        cout << "Numar total de sirene: " << numarTotalDeSirene << endl;
    }

    // Metode pentru lucrul cu fisiere text
    void scrieInFisierText(const string& numeFisier) {
        ofstream out(numeFisier);
        if (out) {
            out << intensitate << endl << culoare << endl << *frecventa << endl;
        }
    }

    void citesteDinFisierText(const string& numeFisier) {
        ifstream in(numeFisier);
        if (in) {
            in >> intensitate >> culoare >> *frecventa;
        }
    }

    // Metode pentru lucrul cu fisiere binare
    void scrieInFisierBinar(ofstream& out) const override {
        if (out) {
            out.write(reinterpret_cast<const char*>(&intensitate), sizeof(intensitate));
            size_t lungimeCuloare = culoare.size();
            out.write(reinterpret_cast<const char*>(&lungimeCuloare), sizeof(lungimeCuloare));
            out.write(culoare.c_str(), lungimeCuloare);
            out.write(reinterpret_cast<const char*>(frecventa), sizeof(double));
        }
    }

    void citesteDinFisierBinar(ifstream& in) override {
        if (in) {
            in.read(reinterpret_cast<char*>(&intensitate), sizeof(intensitate));
            size_t lungimeCuloare;
            in.read(reinterpret_cast<char*>(&lungimeCuloare), sizeof(lungimeCuloare));
            char* buffer = new char[lungimeCuloare + 1];
            in.read(buffer, lungimeCuloare);
            buffer[lungimeCuloare] = '\0';
            culoare = string(buffer);
            delete[] buffer;
            double tempFrecventa;
            in.read(reinterpret_cast<char*>(&tempFrecventa), sizeof(double));
            if (frecventa != nullptr) {
                *frecventa = tempFrecventa;
            } else {
                frecventa = new double(tempFrecventa);
            }
        }
    }

    Sirena* clone() const override {
        return new Sirena(*this);
    }

};

int Sirena::numarTotalDeSirene = 0;

class AparatFotografiat : public CaptorImagine {
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
            << " are rezolutieDigitala de " << a.rezolutie << " megapixeli si dimensiunea senzorului de "
            << *a.dimensiuneSenzor << " mm." << endl;
        return out;
    }

    // Get-eri
    int getRezolutie() const override {
        return rezolutie;
    }

    string getTipSenzor() const override {
        return tipSenzor;
    }

    double getDimensiuneSenzor() const { return *dimensiuneSenzor; }
    static int getNumarTotalDeAparate() { return numarTotalDeAparate; }
    string getMarca() const { return marca; }

    // Set-eri
    void setRezolutie(int _rezolutie) { rezolutie = _rezolutie; }
    void setTipSenzor(string _tipSenzor) { tipSenzor = _tipSenzor; }
    void setDimensiuneSenzor(double _dimensiuneSenzor) { *dimensiuneSenzor = _dimensiuneSenzor; }

    // Functia statica
    static void afiseazaNumarAparate() {
        cout << "Numar total de aparate: " << numarTotalDeAparate << endl;
    }

    // Metode pentru lucrul cu fisiere text
    void scrieInFisierText(const string& numeFisier) {
        ofstream out(numeFisier);
        if (out) {
            out << rezolutie << endl << tipSenzor << endl << *dimensiuneSenzor << endl;
        }
    }

    void citesteDinFisierText(const string& numeFisier) {
        ifstream in(numeFisier);
        if (in) {
            in >> rezolutie >> tipSenzor >> *dimensiuneSenzor;
        }
    }

    // Metode pentru lucrul cu fisiere binare
    void scrieInFisierBinar(ofstream& out) const override {
        if (out) {
            out.write(reinterpret_cast<const char*>(&rezolutie), sizeof(rezolutie));
            size_t lungimeTipSenzor = tipSenzor.size();
            out.write(reinterpret_cast<const char*>(&lungimeTipSenzor), sizeof(lungimeTipSenzor));
            out.write(tipSenzor.c_str(), lungimeTipSenzor);
            out.write(reinterpret_cast<const char*>(dimensiuneSenzor), sizeof(double));
        }
    }

    void citesteDinFisierBinar(ifstream& in) override{
        if (in) {
            in.read(reinterpret_cast<char*>(&rezolutie), sizeof(rezolutie));
            size_t lungimeTipSenzor;
            in.read(reinterpret_cast<char*>(&lungimeTipSenzor), sizeof(lungimeTipSenzor));
            char* buffer = new char[lungimeTipSenzor + 1];
            in.read(buffer, lungimeTipSenzor);
            buffer[lungimeTipSenzor] = '\0';
            tipSenzor = string(buffer);
            delete[] buffer;
            double tempDimensiuneSenzor;
            in.read(reinterpret_cast<char*>(&tempDimensiuneSenzor), sizeof(double));
            if (dimensiuneSenzor != nullptr) {
                *dimensiuneSenzor = tempDimensiuneSenzor;
            } else {
                dimensiuneSenzor = new double(tempDimensiuneSenzor);
            }
        }
    }

    AparatFotografiat* clone() const override {
        return new AparatFotografiat(*this);
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

    // Functia statica
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

    // Metode pentru lucrul cu fisiere binare
    void scrieInFisierBinar(ofstream& out) {
        if (out) {
            out.write(reinterpret_cast<const char*>(&inaltime), sizeof(inaltime));
            out.write(reinterpret_cast<const char*>(lungimeUnda), sizeof(double));
        }
    }

    void citesteDinFisierBinar(ifstream& in) {
        if (in) {
            in.read(reinterpret_cast<char*>(&inaltime), sizeof(inaltime));
            double tempLungimeUnda;
            in.read(reinterpret_cast<char*>(&tempLungimeUnda), sizeof(double));
            if (lungimeUnda != nullptr) {
                *lungimeUnda = tempLungimeUnda;
            } else {
                lungimeUnda = new double(tempLungimeUnda);
            }
        }
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
         << " are rezolutieDigitala de " << a.getRezolutie() << " megapixeli si dimensiunea senzorului de "
         << a.getDimensiuneSenzor() << " mm." << endl;
}


class SirenaAvansata : public Sirena {
private:
    bool areSistemDeConectare;
public:
    // Constructor fara parametri
    SirenaAvansata() : Sirena(), areSistemDeConectare(false) {}

    // Constructor existent
    SirenaAvansata(int _intensitate, string _culoare, double _frecventa, string _tipSirena, bool _areSistemDeConectare)
            : Sirena(_intensitate, _culoare, _frecventa, _tipSirena), areSistemDeConectare(_areSistemDeConectare) {}

    bool getAreSistemDeConectare() const {
        return areSistemDeConectare;
    }

    void setAreSistemDeConectare(bool _areSistemDeConectare) {
        areSistemDeConectare = _areSistemDeConectare;
    }

    void afiseazaDetalii() const {
        cout << "Sirena Avansata: " << endl;
        afiseazaDetaliiSirena(*this);
        cout << "Are sistem de conectare: " << (areSistemDeConectare ? "Da" : "Nu") << endl;
    }

    SirenaAvansata* clone() const override {
        return new SirenaAvansata(*this);
    }

    void scrieInFisierBinar(ofstream& out) const override {
        Sirena::scrieInFisierBinar(out); // Scrie mai intai datele din clasa de baza
        out.write(reinterpret_cast<const char*>(&areSistemDeConectare), sizeof(areSistemDeConectare));
    }

    void citesteDinFisierBinar(ifstream& in) override {
        Sirena::citesteDinFisierBinar(in); // Citeste mai intai datele din clasa de baza
        in.read(reinterpret_cast<char*>(&areSistemDeConectare), sizeof(areSistemDeConectare));
    }

};

class AparatFotografiatDigital : public AparatFotografiat {
private:
    int rezolutieDigitala;

public:
    // Constructor fara parametri
    AparatFotografiatDigital() : AparatFotografiat(), rezolutieDigitala(0) {}

    // Constructor existent
    AparatFotografiatDigital(int _rezolutie, string _tipSenzor, double _dimensiuneSenzor, string _marca, int _rezolutieDigitala)
            : AparatFotografiat(_rezolutie, _tipSenzor, _dimensiuneSenzor, _marca), rezolutieDigitala(_rezolutieDigitala) {}

    int getRezolutieDigitala() const {
        return rezolutieDigitala;
    }

    void setRezolutie(int _rezolutieDigitala) {
        rezolutieDigitala = _rezolutieDigitala;
    }

    void afiseazaDetalii() const {
        cout << "Aparat Fotografiat Digital: " << endl;
        afiseazaDetaliiAparat(*this);
        cout << "Rezolutie digitala: " << rezolutieDigitala << " MP" << endl;
    }

    AparatFotografiatDigital* clone() const override {
        return new AparatFotografiatDigital(*this);
    }

    void scrieInFisierBinar(ofstream& out) const override {
        AparatFotografiat::scrieInFisierBinar(out); // Scrie mai întâi datele din clasa de bază
        out.write(reinterpret_cast<const char*>(&rezolutieDigitala), sizeof(rezolutieDigitala));
    }

    void citesteDinFisierBinar(ifstream& in) override {
        AparatFotografiat::citesteDinFisierBinar(in); // Citește mai întâi datele din clasa de bază
        in.read(reinterpret_cast<char*>(&rezolutieDigitala), sizeof(rezolutieDigitala));
    }

};


class EchipamentDeUrgenta {
private:
    EmitatorSunet* sirena;
    CaptorImagine* aparatFotografiat;
    Antena antena;
    string locatie;
    bool esteFunctional;

public:
    // Constructor fara parametri
    EchipamentDeUrgenta() : sirena(nullptr), aparatFotografiat(nullptr), antena(), locatie("Nedefinit"), esteFunctional(false) {}

    // Constructor cu parametri
    EchipamentDeUrgenta(EmitatorSunet* _sirena, CaptorImagine* _aparatFotografiat, const Antena& _antena, const string& _locatie, bool _esteFunctional)
            : sirena(_sirena), aparatFotografiat(_aparatFotografiat), antena(_antena), locatie(_locatie), esteFunctional(_esteFunctional) {}

    ~EchipamentDeUrgenta() {
        delete sirena;
        delete aparatFotografiat;
    }

    // Getteri si Setteri actualizati
    EmitatorSunet* getSirena() const { return sirena; }
    void setSirena(EmitatorSunet* _sirena) {
        delete sirena;
        sirena = _sirena;
    }

    CaptorImagine* getAparatFotografiat() const { return aparatFotografiat; }
    void setAparatFotografiat(CaptorImagine* _aparat) {
        delete aparatFotografiat;
        aparatFotografiat = _aparat;
    }

    Antena getAntena() const { return antena; }
    void setAntena(const Antena& _antena) { antena = _antena; }

    string getLocatie() const { return locatie; }
    void setLocatie(const string& _locatie) { locatie = _locatie; }

    bool getEsteFunctional() const { return esteFunctional; }
    void setEsteFunctional(bool _esteFunctional) { esteFunctional = _esteFunctional; }

    // Operatori
    EchipamentDeUrgenta& operator++() {
        if (sirena) {
            Sirena* sirenaSpecific = dynamic_cast<Sirena*>(sirena);
            if (sirenaSpecific) {
                ++(*sirenaSpecific);
            }
        }
        return *this;
    }

    bool operator==(const EchipamentDeUrgenta& other) const {
        // Compara atribute specifice
        return (sirena == other.sirena && aparatFotografiat == other.aparatFotografiat && antena.getInaltime() == other.antena.getInaltime());
    }

    EchipamentDeUrgenta operator+(const EchipamentDeUrgenta& other) const {
        // Combina doar sirenele si foloseste atributele unuia dintre echipamente pentru restul
        EmitatorSunet* nouaSirena = sirena ? sirena : other.sirena;
        CaptorImagine* nouAparat = aparatFotografiat ? aparatFotografiat : other.aparatFotografiat;
        return EchipamentDeUrgenta(nouaSirena, nouAparat, antena, locatie, esteFunctional || other.esteFunctional);
    }

    // Operator de atribuire
    EchipamentDeUrgenta& operator=(const EchipamentDeUrgenta& other) {
        if (this != &other) {
            delete sirena;
            delete aparatFotografiat;
            sirena = other.sirena ? other.sirena->clone() : nullptr;
            aparatFotografiat = other.aparatFotografiat ? other.aparatFotografiat->clone() : nullptr;
            antena = other.antena;
            locatie = other.locatie;
            esteFunctional = other.esteFunctional;
        }
        return *this;
    }

    // Metode pentru lucrul cu fisiere binare
    void scrieInFisierBinar(ofstream& out) {
        if (out) {
            // Scrierea inf despre sirena
            if (sirena) {
                int tipSirena = dynamic_cast<Sirena*>(sirena) ? 1 : 0;
                out.write(reinterpret_cast<const char*>(&tipSirena), sizeof(tipSirena));
                sirena->scrieInFisierBinar(out);
            }

            // Scrierea inf despre aparatul fotografiat
            if (aparatFotografiat) {
                int tipAparat = dynamic_cast<AparatFotografiat*>(aparatFotografiat) ? 1 : 0;
                out.write(reinterpret_cast<const char*>(&tipAparat), sizeof(tipAparat));
                aparatFotografiat->scrieInFisierBinar(out);
            }

            // Scrierea inf despre antena
            antena.scrieInFisierBinar(out);

            // Scrierea starii functionale
            out.write(reinterpret_cast<const char*>(&esteFunctional), sizeof(esteFunctional));
        }
    }

    void citesteDinFisierBinar(ifstream& in) {
        if (in) {
            // Citirea inf despre sirena
            int tipSirena;
            in.read(reinterpret_cast<char*>(&tipSirena), sizeof(tipSirena));
            if (tipSirena == 1) {
                sirena = new Sirena();
            } else {
                sirena = new SirenaAvansata();
            }
            sirena->citesteDinFisierBinar(in);

            // Citirea inf despre aparatul fotografiat
            int tipAparat;
            in.read(reinterpret_cast<char*>(&tipAparat), sizeof(tipAparat));
            if (tipAparat == 1) {
                aparatFotografiat = new AparatFotografiat();
            } else {
                aparatFotografiat = new AparatFotografiatDigital();
            }
            aparatFotografiat->citesteDinFisierBinar(in);

            // Citirea inf despre antena
            antena.citesteDinFisierBinar(in);

            // Citirea starii functionale
            in.read(reinterpret_cast<char*>(&esteFunctional), sizeof(esteFunctional));
        }
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
        cout << endl;
    }

    vector<Sirena> vectorSirene;
    vector<AparatFotografiat> vectorAparate;
    vector<Antena> vectorAntene;

    // Citirea + adaugarea sirenelor în vector:
    int numarSirene;
    cout << "Introduceti numarul de sirene: ";
    cin >> numarSirene;
    for (int i = 0; i < numarSirene; ++i) {
        Sirena sirena;
        cout << "Introduceti datele pentru sirena " << i+1 << ": " ;
        cin >> sirena;
        vectorSirene.push_back(sirena);
    }

    // Afisarea sirenelor:
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

    // Afisarea aparatelor fotografice:
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

    // Afisarea antenelor:
    for (const auto& antena : vectorAntene) {
        cout << antena;
    }

    // testare clasa EchipamentDeUrgenta
    // Testare constructor fara parametri
    EchipamentDeUrgenta echipamentDefault;
    cout << "Echipament default - Locatie: " << echipamentDefault.getLocatie() << ", Este functional: " << (echipamentDefault.getEsteFunctional() ? "Da" : "Nu") << endl;

    // Testare constructor cu parametri
    Sirena sirenaNoua(15, "Albastru", 120.0, "Digital");
    AparatFotografiat aparatNou(25, "CMOS", 36.0, "Sony");
    Antena antenaNoua(20.0, "Directionala", 300.0, "Aluminiu");

    EchipamentDeUrgenta echipament(&sirenaNoua, &aparatNou, antenaNoua, "Cluj-Napoca", true);
    cout << "Echipament - Locatie: " << echipament.getLocatie() << ", Este functional: " << (echipament.getEsteFunctional() ? "Da" : "Nu") << endl;

    // Testare getteri și setteri
    echipament.setLocatie("Bucuresti");
    echipament.setEsteFunctional(false);
    cout << "Echipament actualizat - Locatie: " << echipament.getLocatie() << ", Este functional: " << (echipament.getEsteFunctional() ? "Da" : "Nu") << endl;

    // Testare operatori
    // Afisarea detaliilor înainte de incrementare
    cout << "Inainte de incrementare: " << endl;
    cout << "Intensitate sirena: " << echipament.getSirena()->getIntensitate() << endl;
    ++echipament; // Testare operator ++
    // Afisarea detaliilor după incrementare
    cout << "Dupa incrementare: " << endl;
    cout << "Intensitate sirena: " << echipament.getSirena()->getIntensitate() << endl;

    EchipamentDeUrgenta echipamentCopiat = echipament; // Testare operator de atribuire
    bool suntEgale = (echipament == echipamentCopiat); // Testare operator ==
    cout << "Echipamentele sunt egale: " << (suntEgale ? "Da" : "Nu") << endl;

    EchipamentDeUrgenta echipamentCombinat = echipament + echipamentCopiat; // Testare operator +
    cout << "Echipament combinat - Locatie: " << echipamentCombinat.getLocatie() << ", Este functional: " << (echipamentCombinat.getEsteFunctional() ? "Da" : "Nu") << endl;
    // Afisarea detaliilor componente ale echipamentului combinat
    cout << "Sirena - Intensitate: " << echipamentCombinat.getSirena()->getIntensitate() << ", Culoare: " << echipamentCombinat.getSirena()->getCuloare() << endl;
    cout << "Aparat Fotografiat - Rezolutie: " << echipamentCombinat.getAparatFotografiat()->getRezolutie() << ", Tip Senzor: " << echipamentCombinat.getAparatFotografiat()->getTipSenzor() << endl;
    cout << "Antena - Inaltime: " << echipamentCombinat.getAntena().getInaltime() << ", Tip: " << echipamentCombinat.getAntena().getTip() << endl;

    // Testarea metodelor de lucru cu fisere text pentru Sirena și AparatFotografiat
    Sirena s;
    s.scrieInFisierText("sirena.txt");
    s.citesteDinFisierText("sirena.txt");
    cout << "Sirena din fisierul text: " << endl;
    cout << s;

    AparatFotografiat a;
    a.scrieInFisierText("aparat.txt");
    a.citesteDinFisierText("aparat.txt");
    cout << "Aparat Fotografiat din fisierul text: " << endl;
    cout << a;

    // Testarea metodelor de lucru cu fisiere binare
    Antena ant;
    ofstream outAntena("antena.bin", ios::binary);
    if (outAntena) {
        ant.scrieInFisierBinar(outAntena);
        outAntena.close();
    }

    ifstream inAntena("antena.bin", ios::binary);
    if (inAntena) {
        ant.citesteDinFisierBinar(inAntena);
        inAntena.close();
    }
    cout << "Antena din fisierul binar: " << endl;
    cout << ant;

    EchipamentDeUrgenta e;
    ofstream outEchipament("echipament.bin", ios::binary);
    if (outEchipament) {
        e.scrieInFisierBinar(outEchipament);
        outEchipament.close();
    }

    ifstream inEchipament("echipament.bin", ios::binary);
    if (inEchipament) {
        e.citesteDinFisierBinar(inEchipament);
        inEchipament.close();
    }


    SirenaAvansata sirena1(10, "Alba", 120.0, "Tip1", true);
    AparatFotografiatDigital aparat1(24, "CMOS", 35.0, "Nikon", 24);

    Sirena *sirenaUpcast = &sirena1;
    AparatFotografiat *aparatUpcast = &aparat1;

    sirena1.afiseazaDetalii();
    aparat1.afiseazaDetalii();


    // Crearea unui vector de pointeri la tipul abstract EmitatorSunet
    vector<EmitatorSunet*> emitatoriSunet;
    emitatoriSunet.push_back(new Sirena(10, "Rosu", 100.0, "Standard"));
    emitatoriSunet.push_back(new SirenaAvansata(15, "Albastru", 120.0, "Digital", true));

    // Demonstrarea late-binding-ului pentru EmitatorSunet
    for (EmitatorSunet* emitator : emitatoriSunet) {
        cout << "Intensitate: " << emitator->getIntensitate()
             << ", Culoare: " << emitator->getCuloare() << endl;
    }

    // Eliberarea memoriei
    for (EmitatorSunet* emitator : emitatoriSunet) {
        delete emitator;
    }

    // Crearea unui vector de pointeri la tipul abstract CaptorImagine
    vector<CaptorImagine*> captoriImagine;
    captoriImagine.push_back(new AparatFotografiat(20, "CMOS", 35.0, "Canon"));
    captoriImagine.push_back(new AparatFotografiatDigital(24, "CMOS", 35.0, "Nikon", 24));

    // Demonstrarea late-binding-ului pentru CaptorImagine
    for (CaptorImagine* captor : captoriImagine) {
        cout << "Rezolutie: " << captor->getRezolutie()
             << ", Tip Senzor: " << captor->getTipSenzor() << endl;
    }

    // Eliberarea memoriei
    for (CaptorImagine* captor : captoriImagine) {
        delete captor;
    }

}
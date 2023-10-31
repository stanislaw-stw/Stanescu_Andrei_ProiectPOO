#include <iostream>
#include <string>
using namespace std;

// domeniu ales: Andrei Stanescu - Sisteme de alarma

class Sirena {
public:
    int intensitate;
    string culoare;
    double* frecventa;
    static int numarTotalDeSirene;
    const string tipSirena;
    int getIntensitate() const { return intensitate; }
    string getCuloare() const { return culoare; }
    double getFrecventa() const { return *frecventa; }
    static int getNumarTotalDeSirene() { return numarTotalDeSirene; }
    string getTipSirena() const { return tipSirena; }



    Sirena(int _intensitate, string _culoare, double _frecventa, string _tipSirena)
            : intensitate(_intensitate), culoare(_culoare), tipSirena(_tipSirena) {
        frecventa = new double(_frecventa);
        numarTotalDeSirene++;
    }

    Sirena(int _intensitate, string _culoare)
            : intensitate(_intensitate), culoare(_culoare), tipSirena("Standard") {
        frecventa = new double(100.0);
        numarTotalDeSirene++;
    }

    Sirena()
            : intensitate(5), culoare("Rosu"), tipSirena("Standard") {
        frecventa = new double(100.0);
        numarTotalDeSirene++;
    }

    ~Sirena() {
        delete frecventa;
    }

    static void afiseazaNumarSirene() {
        cout << "Numar total de sirene: " << numarTotalDeSirene << endl;
    }
};

int Sirena::numarTotalDeSirene = 0;

class AparatFotografiat {
public:
    int rezolutie;
    string tipSenzor;
    double* dimensiuneSenzor;
    static int numarTotalDeAparate;
    const string marca;

    int getRezolutie() const { return rezolutie; }
    string getTipSenzor() const { return tipSenzor; }
    double getDimensiuneSenzor() const { return *dimensiuneSenzor; }
    static int getNumarTotalDeAparate() { return numarTotalDeAparate; }
    string getMarca() const { return marca; }

    void setRezolutie(int _rezolutie) { rezolutie = _rezolutie; }
    void setTipSenzor(string _tipSenzor) { tipSenzor = _tipSenzor; }
    void setDimensiuneSenzor(double _dimensiuneSenzor) { *dimensiuneSenzor = _dimensiuneSenzor; }

    AparatFotografiat(int _rezolutie, string _tipSenzor, double _dimensiuneSenzor, string _marca)
            : rezolutie(_rezolutie), tipSenzor(_tipSenzor), marca(_marca) {
        dimensiuneSenzor = new double(_dimensiuneSenzor);
        numarTotalDeAparate++;
    }

    AparatFotografiat(int _rezolutie, string _tipSenzor)
            : rezolutie(_rezolutie), tipSenzor(_tipSenzor), marca("Canon") {
        dimensiuneSenzor = new double(35.0);
        numarTotalDeAparate++;
    }

    AparatFotografiat()
            : rezolutie(20), tipSenzor("CMOS"), marca("Canon") {
        dimensiuneSenzor = new double(35.0);
        numarTotalDeAparate++;
    }

    ~AparatFotografiat() {
        delete dimensiuneSenzor;
    }

    static void afiseazaNumarAparate() {
        cout << "Numar total de aparate: " << numarTotalDeAparate << endl;
    }
};

int AparatFotografiat::numarTotalDeAparate = 0;

class Antena {
public:
    double inaltime;
    string tip;
    double* lungimeUnda;
    static int numarTotalDeAntene;
    const string material;

    double getInaltime() const { return inaltime; }
    string getTip() const { return tip; }
    double getLungimeUnda() const { return *lungimeUnda; }
    static int getNumarTotalDeAntene() { return numarTotalDeAntene; }
    string getMaterial() const { return material; }

    // Setters
    void setInaltime(double _inaltime) { inaltime = _inaltime; }
    void setTip(string _tip) { tip = _tip; }
    void setLungimeUnda(double _lungimeUnda) { *lungimeUnda = _lungimeUnda; }

    Antena(double _inaltime, string _tip, double _lungimeUnda, string _material)
            : inaltime(_inaltime), tip(_tip), material(_material) {
        lungimeUnda = new double(_lungimeUnda);
        numarTotalDeAntene++;
    }

    Antena(double _inaltime, string _tip)
            : inaltime(_inaltime), tip(_tip), material("Metal") {
        lungimeUnda = new double(100.0);
        numarTotalDeAntene++;
    }

    Antena()
            : inaltime(10.0), tip("Omni"), material("Metal") {
        lungimeUnda = new double(100.0);
        numarTotalDeAntene++;
    }

    ~Antena() {
        delete lungimeUnda;
    }

    static void afiseazaNumarAntene() {
        cout << "Numar total de antene: " << numarTotalDeAntene << endl;
    }
};

int Antena::numarTotalDeAntene = 0;

int main() {
    Sirena s1(10, "Verde", 150.0, "Acustica");
    Sirena s2(15, "Albastru");
    Sirena s3;

    AparatFotografiat a1(24, "CCD", 50.0, "Nikon");
    AparatFotografiat a2(20, "CMOS");
    AparatFotografiat a3;

    Antena ant1(15.0, "Directional", 200.0, "Plastic");
    Antena ant2(12.0, "Omni");
    Antena ant3;

    Sirena::afiseazaNumarSirene();
    AparatFotografiat::afiseazaNumarAparate();
    Antena::afiseazaNumarAntene();

    return 0;
}

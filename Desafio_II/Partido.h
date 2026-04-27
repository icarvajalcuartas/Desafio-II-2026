#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "Equipo.h"
using namespace std;

class Partido{
private:
    Equipo *equipo1;
    Equipo *equipo2;
    string fecha;
    string sede;
    string hora;
    string arbitro1;
    string arbitro2;
    string arbitro3;
    int goladoresEquipo1[11];
    int goladoresEquipo2[11];
    int indicesJugadores1[11];
    int indicesJugadores2[11];
    int cantGoladoresEquipo1;
    int cantGoladoresEquipo2;
    unsigned short int golesEquipo1;
    unsigned short int golesEquipo2;
    bool jugado;

public:
    Partido();
    Partido(Equipo &e1, Equipo &e2, string f);
    Partido(const Partido &copiaPartido);

    Equipo* getEquipo1() const;
    Equipo* getEquipo2() const;
    string getFecha() const;
    string getSede() const;
    unsigned short int getGolesEquipo1() const;
    unsigned short int getGolesEquipo2() const;
    bool getJugado() const;
    void getIndicesJugadores(int out1[11], int out2[11]) const;
    void setFecha(string f);
    void setSede(string s);
    void setArbitros(string a1, string a2, string a3);
    void agregarGolesEquipo1(int g);
    void agregarGolesEquipo2(int g);
    void agregarGoleadorEquipo1(int numCamiseta);
    void agregarGoleadorEquipo2(int numCamiseta);
    Partido& operator=(const Partido& otro);
    void simularPartido();
    const int* getGoladoresEquipo1() const;
    const int* getGoladoresEquipo2() const;
    int getCantGoladoresEquipo1() const;
    int getCantGoladoresEquipo2() const;
    void print() const;

    ~Partido();
};

#endif // PARTIDO_H

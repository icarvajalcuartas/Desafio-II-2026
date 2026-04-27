#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include "Equipo.h"
using namespace std;

class Grupo{
private:
    char letra;
    Equipo *equipos;
    unsigned short int cantEquipos;

public:
    Grupo();
    Grupo(char l);
    Grupo(const Grupo &copiaGrupo);
    Grupo& operator=(const Grupo &otro);

    char getLetra() const;
    unsigned short int getCantEquipos() const;
    const Equipo& getEquipo(unsigned short int pos) const;

    void setLetra(char l);

    bool puedeAgregarEquipo(const Equipo &equipo) const;
    bool agregarEquipo(const Equipo &equipo);
    bool quitarUltimoEquipo();

    void print() const;

    ~Grupo();
};

#endif // GRUPO_H

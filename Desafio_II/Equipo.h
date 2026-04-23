#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
#include "Jugador.h"
#include "HistoricoEquipo.h"
using namespace std;

class Equipo{
private:
    string pais;
    string federacion;
    string confederacion;
    string directorTecnico;
    unsigned short int rankingFIFA;
    char grupo;

    HistoricoEquipo historico;

    Jugador *jugadores;
    unsigned short int cantJugadores;

public:
    Equipo();
    Equipo(string p, string f, string c, string dt, unsigned short int r, char g);
    Equipo(const Equipo &copiaEquipo);
    Equipo& operator=(const Equipo &otro);

    string getPais() const;
    string getFederacion() const;
    string getConfederacion() const;
    string getDirectorTecnico() const;
    unsigned short int getRankingFIFA() const;
    char getGrupo() const;

    HistoricoEquipo getHistorico() const;

    unsigned short int getCantJugadores() const;
    Jugador* getJugadores() const;
    Jugador getJugador(unsigned short int pos) const;

    void setPais(string p);
    void setFederacion(string f);
    void setConfederacion(string c);
    void setDirectorTecnico(string dt);
    void setRankingFIFA(unsigned short int r);
    void setGrupo(char g);

    void setHistorico(const HistoricoEquipo &h);

    void inicializarJugadores();
    void actualizarHistoricoEquipo(unsigned short int gf, unsigned short int gc,
                                   unsigned short int ta, unsigned short int tr,
                                   unsigned short int fa);

    void print() const;
    void printJugadores() const;

    bool operator>(const Equipo &otro) const;
    bool operator<(const Equipo &otro) const;

    ~Equipo();
};

#endif
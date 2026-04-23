#ifndef EQUIPO_H
#define EQUIPO_H
#include"Equipo.h"
#include <iostream>
#include <string>
#include "Jugador.h"
using namespace std;

class Equipo{
private:
    string pais;
    string federacion;
    string confederacion;
    string directorTecnico;
    unsigned short int rankingFIFA;
    char grupo;

    unsigned short int golesFavor;
    unsigned short int golesContra;
    unsigned short int partidosGanados;
    unsigned short int partidosEmpatados;
    unsigned short int partidosPerdidos;
    unsigned short int tarjetasAmarillas;
    unsigned short int tarjetasRojas;
    unsigned short int faltas;

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

    unsigned short int getGolesFavor() const;
    unsigned short int getGolesContra() const;
    unsigned short int getPartidosGanados() const;
    unsigned short int getPartidosEmpatados() const;
    unsigned short int getPartidosPerdidos() const;
    unsigned short int getTarjetasAmarillas() const;
    unsigned short int getTarjetasRojas() const;
    unsigned short int getFaltas() const;

    unsigned short int getCantJugadores() const;
    Jugador* getJugadores() const;
    Jugador getJugador(unsigned short int pos) const;

    void setPais(string p);
    void setFederacion(string f);
    void setConfederacion(string c);
    void setDirectorTecnico(string dt);
    void setRankingFIFA(unsigned short int r);
    void setGrupo(char g);

    void setGolesFavor(unsigned short int gf);
    void setGolesContra(unsigned short int gc);
    void setPartidosGanados(unsigned short int pg);
    void setPartidosEmpatados(unsigned short int pe);
    void setPartidosPerdidos(unsigned short int pp);
    void setTarjetasAmarillas(unsigned short int ta);
    void setTarjetasRojas(unsigned short int tr);
    void setFaltas(unsigned short int fa);

    void inicializarJugadores();
    void actualizarHistoricoEquipo(unsigned short int gf, unsigned short int gc,
                                   unsigned short int ta, unsigned short int tr,
                                   unsigned short int fa);

    void print() const;
    void printJugadores() const;

    bool operator>(const Equipo &otro) const;
    bool operator<(const Equipo &otro) const;

    friend void leerHistoricoEquipo(Equipo &equipo, const string &lineaCSV);
    friend void cargarEquipoDesdeArchivo(Equipo &equipo, const string &nombreArchivo, const string &paisBuscado);

    ~Equipo();
};

#endif // EQUIPO_H

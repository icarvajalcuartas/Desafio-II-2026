#ifndef TORNEO_H
#define TORNEO_H
#include <string>
#include"Equipo.h"
#include"Grupo.h"
#include"Partido.h"
using namespace std;

const int NUM_EQUIPOS=48;
const int NUM_GRUPOS=12;
const int PARTIDOS_POR_GRUPO=6;
const int TOTAL_PARTIDOS_GRUPOS=NUM_GRUPOS*PARTIDOS_POR_GRUPO;
const int DIAS_FASE_GRUPOS=19;
const int MAX_PARTIDOS_POR_DIA=4;

class Torneo{
private:
    Equipo equipos[NUM_EQUIPOS];
    unsigned short int totalEquipos;
    int bombo1[NUM_GRUPOS],in_b1;
    int bombo2[NUM_GRUPOS],in_b2;
    int bombo3[NUM_GRUPOS],in_b3;
    int bombo4[NUM_GRUPOS],in_b4;
    Grupo grupos[NUM_GRUPOS];
    Partido partidosGrupos[TOTAL_PARTIDOS_GRUPOS];
    Partido partidosR16[16];
    Partido partidosR8[8];
    Partido partidosQF[4];
    Partido partidosSF[2];
    Partido partidosTercero[1];
    Partido partidosFinal[1];
    int numPartidosGrupos;
    long long iteraciones;
    Equipo* resolverEmpate(Partido& p);
    bool construirGruposRec(int pot,int g,bool usado[4][NUM_GRUPOS]);
    Equipo* buscarEquipoRealPorPais(const string& pais);
    void setFechaString(unsigned short int desfase, string& out)const;
    int buscarGrupoDeEquipo(const Equipo* eq);

public:
    Torneo();
    Partido& getPartidoGrupo(int idx);
    long long getIteraciones() const;
    bool cargarEquiposDesdeArchivo(const string &nombreArchivo);
    void clasificarEnBombos();
    void printBombos()const;
    bool crearGrupos();
    void printGrupos()const;
    bool configurarPartidosGrupos();
    void printPartidosGrupos()const;
    void simularFaseGrupos();
    void clasificarYArmarR16();
    void simularR16();
    void simularR8();
    void simularQF();
    void simularSF();
    void simularFinal();
    void generarEstadisticas();

};

#endif // TORNEO_H

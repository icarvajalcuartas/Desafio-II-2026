#ifndef TORNEO_H
#define TORNEO_H
#include <string>
#include"Equipo.h"
using namespace std;

const int NUM_EQUIPOS=48;
const int NUM_GRUPOS=12;
const unsigned short int RMI_BOMBO1=1;
const unsigned short int RMA_BOMBO1=12;
const unsigned short int RMI_BOMBO2=13;
const unsigned short int RMA_BOMBO2=24;
const unsigned short int RMI_BOMBO3=25;
const unsigned short int RMA_BOMBO3=36;
const unsigned short int RMI_BOMBO4=37;
const unsigned short int RMA_BOMBO4=48;

class Torneo{
private:
    Equipo equipos[NUM_EQUIPOS];
    unsigned short int totalEquipos;
    int bombo1[NUM_GRUPOS],in_b1;
    int bombo2[NUM_GRUPOS],in_b2;
    int bombo3[NUM_GRUPOS],in_b3;
    int bombo4[NUM_GRUPOS],in_b4;

public:
    Torneo();
    bool cargarEquiposDesdeArchivo(const string &nombreArchivo);
    void clasificarEnBombos();
    void printBombos()const;
};

#endif // TORNEO_H

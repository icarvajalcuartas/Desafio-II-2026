#ifndef JUGADOR_H
#define JUGADOR_H

#include "HistoricoJugador.h"

class Jugador{
private:
    unsigned short int numCamiseta;
    HistoricoJugador historico;
public:
    Jugador();
    Jugador(unsigned short int numC);
    Jugador (const Jugador &copiaJugador);
    const HistoricoJugador& gethistorico()const;
    unsigned short int getnumCamiseta()const;
    void setnumCamiseta(unsigned short int num);
    void sethistorico(unsigned short c, unsigned short m, unsigned short tA, unsigned short tR, unsigned short fA);
    void print()const;
    ~Jugador();
};

#endif // JUGADOR_H

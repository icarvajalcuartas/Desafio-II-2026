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
    const HistoricoJugador& gethistorico()const;
    void sethistorico(unsigned short c, unsigned short m, unsigned short tA, unsigned short tR, unsigned short fA);
    ~Jugador();
};

#endif // JUGADOR_H

#include"Jugador.h"
#include <iostream>
using namespace std;
Jugador::Jugador()
{
    numCamiseta=0;
    //historico=HistoricoJugador();
}

Jugador::Jugador(unsigned short numC)
{
    numCamiseta=numC;
    //historico=HistoricoJugador();
}

const HistoricoJugador& Jugador::gethistorico() const
{
    return historico;
}

void Jugador::sethistorico(unsigned short c, unsigned short m,unsigned short tA, unsigned short tR, unsigned short fA)
{
    historico.actualizarHistorico(c,m,tA,tR,fA);
}

Jugador::~Jugador()
{
    cout<<"la instancia de jugador ha sido destruida exitosamente"<<endl;
}

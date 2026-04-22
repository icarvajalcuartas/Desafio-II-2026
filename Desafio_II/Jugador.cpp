#include"Jugador.h"
#include <iostream>
using namespace std;
Jugador::Jugador():numCamiseta(0),historico(HistoricoJugador()){}

Jugador::Jugador(unsigned short numC):numCamiseta(numC),historico(HistoricoJugador()){}

Jugador::Jugador(const Jugador &copiaJugador):numCamiseta(copiaJugador.numCamiseta),historico(copiaJugador.historico){}

const HistoricoJugador& Jugador::gethistorico() const
{
    return historico;
}

unsigned short Jugador::getnumCamiseta() const
{
    return numCamiseta;
}

void Jugador::setnumCamiseta(unsigned short num)
{
    numCamiseta=num;
}

void Jugador::sethistorico(unsigned short c, unsigned short m,unsigned short tA, unsigned short tR, unsigned short fA)
{
    historico.actualizarHistorico(c,m,tA,tR,fA);
}

void Jugador::print() const
{
    cout<<"\n Numero de camiseta: "<<numCamiseta;
    this->historico.print();
}

Jugador::~Jugador()
{
    cout<<"\n la instancia de jugador ha sido destruida exitosamente"<<endl;
}

#include "HistoricoJugador.h"
#include <iostream>
using namespace std;

HistoricoJugador::HistoricoJugador()
{
    partJugados=0;
    cantGoles=0;
    minJugados=0;
    asistencias=0;
    tarAmarillas=0;
    tarRojas=0;
    faltAcumuladas=0;
}

void HistoricoJugador::actualizarHistorico(unsigned short cG, unsigned short mJ, unsigned short tAm, unsigned short tRo, unsigned short fAcc)
{
    partJugados+=1;
    cantGoles+=cG;
    minJugados+=mJ;
    tarAmarillas+=tAm;
    tarRojas+=tRo;
    faltAcumuladas+=fAcc;
}

unsigned short HistoricoJugador::getpartJugados() const
{
    return partJugados;
}

unsigned short HistoricoJugador::getcantGoles() const
{
    return cantGoles;
}

unsigned short HistoricoJugador::getminJugados() const
{
    return minJugados;
}

unsigned short HistoricoJugador::getasistencias() const
{
    return asistencias;
}

unsigned short HistoricoJugador::gettarAmarillas() const
{
    return tarAmarillas;
}

unsigned short HistoricoJugador::gettarRojas() const
{
    return tarRojas;
}

unsigned short HistoricoJugador::getfaltAcumuladas()const
{
    return faltAcumuladas;
}

HistoricoJugador::~HistoricoJugador()
{
    cout<<"La instancia de historico ha sido eliminada correctamente"<<endl;
}





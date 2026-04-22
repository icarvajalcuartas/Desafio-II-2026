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

HistoricoJugador::HistoricoJugador(unsigned short pJ, unsigned short cG, unsigned short mJ, unsigned short as, unsigned short tAm, unsigned short tRo, unsigned short fAc)
    :partJugados(pJ),cantGoles(cG),minJugados(mJ),asistencias(as),tarAmarillas(tAm),tarRojas(tRo),faltAcumuladas(fAc){}

HistoricoJugador::HistoricoJugador(const HistoricoJugador &copiahistorico)
    :partJugados(copiahistorico.partJugados),
    cantGoles(copiahistorico.cantGoles),
    minJugados(copiahistorico.minJugados),
    asistencias(copiahistorico.asistencias),
    tarAmarillas(copiahistorico.tarAmarillas),
    tarRojas(copiahistorico.tarRojas),
    faltAcumuladas(copiahistorico.faltAcumuladas){}

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

void HistoricoJugador::setpartJugados(unsigned short part)
{
    partJugados=part;
}

void HistoricoJugador::setcantGoles(unsigned short gol)
{
    cantGoles=gol;
}

void HistoricoJugador::setminJugados(unsigned short min)
{
    minJugados=min;
}

void HistoricoJugador::setasistencias(unsigned short asi)
{
    asistencias=asi;
}

void HistoricoJugador::settarAmarillas(unsigned short am)
{
    tarAmarillas=am;
}

void HistoricoJugador::settarRojas(unsigned short ro)
{
    tarRojas=ro;
}

void HistoricoJugador::setfaltAcumuladas(unsigned short fal)
{
    faltAcumuladas=fal;
}

void HistoricoJugador::print() const
{
    cout<<"\n Historico:{"<<" Partidos jugados: "<<partJugados<<"\n Cantidad de goles:"<<cantGoles<<
    " \n Minutos jugados: "<<minJugados<<"\n Asistencias: "<<asistencias<<
    " \n Tarjetas amarillas: "<<tarAmarillas<<"\n Tarjetas rojas: "<<tarRojas<<
        "\n Faltas acumuladas: "<<faltAcumuladas<<"}";
}

HistoricoJugador::~HistoricoJugador()
{
    cout<<"\n La instancia de historico ha sido destruida correctamente"<<endl;
}





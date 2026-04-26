#include "HistoricoEquipo.h"
#include <iostream>
using namespace std;

HistoricoEquipo::HistoricoEquipo()
{
    golesFavor=0;
    golesContra=0;
    partidosGanados=0;
    partidosEmpatados=0;
    partidosPerdidos=0;
    tarjetasAmarillas=0;
    tarjetasRojas=0;
    faltas=0;
}

HistoricoEquipo::HistoricoEquipo(unsigned short int gf, unsigned short int gc,
                                 unsigned short int pg, unsigned short int pe,
                                 unsigned short int pp, unsigned short int ta,
                                 unsigned short int tr, unsigned short int fa)
    :golesFavor(gf), golesContra(gc),
    partidosGanados(pg), partidosEmpatados(pe),
    partidosPerdidos(pp), tarjetasAmarillas(ta),
    tarjetasRojas(tr), faltas(fa){}

HistoricoEquipo::HistoricoEquipo(const HistoricoEquipo &copia)
    :golesFavor(copia.golesFavor),
    golesContra(copia.golesContra),
    partidosGanados(copia.partidosGanados),
    partidosEmpatados(copia.partidosEmpatados),
    partidosPerdidos(copia.partidosPerdidos),
    tarjetasAmarillas(copia.tarjetasAmarillas),
    tarjetasRojas(copia.tarjetasRojas),
    faltas(copia.faltas){}

HistoricoEquipo &HistoricoEquipo::operator=(const HistoricoEquipo &otro)
{
    if(this != &otro){
        golesFavor= otro.golesFavor;
        golesContra=otro.golesContra;
        partidosGanados=otro.partidosGanados;
        partidosEmpatados=otro.partidosEmpatados;
        partidosPerdidos=otro.partidosPerdidos;
        tarjetasAmarillas=otro.tarjetasAmarillas;
        tarjetasRojas=otro.tarjetasRojas;
        faltas=otro.faltas;
    }
    return *this;
}

void HistoricoEquipo::actualizarHistorico(unsigned short int gf, unsigned short int gc,
                                          unsigned short int ta, unsigned short int tr,
                                          unsigned short int fa)
{
    golesFavor += gf;
    golesContra += gc;
    tarjetasAmarillas += ta;
    tarjetasRojas += tr;
    faltas += fa;

    if(gf > gc){
        partidosGanados++;
    }
    else if(gf < gc){
        partidosPerdidos++;
    }
    else{
        partidosEmpatados++;
    }
}

unsigned short int HistoricoEquipo::getGolesFavor() const
{
    return golesFavor;
}

unsigned short int HistoricoEquipo::getGolesContra() const
{
    return golesContra;
}

unsigned short int HistoricoEquipo::getPartidosGanados() const
{
    return partidosGanados;
}

unsigned short int HistoricoEquipo::getPartidosEmpatados() const
{
    return partidosEmpatados;
}

unsigned short int HistoricoEquipo::getPartidosPerdidos() const
{
    return partidosPerdidos;
}

unsigned short int HistoricoEquipo::getTarjetasAmarillas() const
{
    return tarjetasAmarillas;
}

unsigned short int HistoricoEquipo::getTarjetasRojas() const
{
    return tarjetasRojas;
}

unsigned short int HistoricoEquipo::getFaltas() const
{
    return faltas;
}

void HistoricoEquipo::setGolesFavor(unsigned short int gf)
{
    golesFavor=gf;
}

void HistoricoEquipo::setGolesContra(unsigned short int gc)
{
    golesContra=gc;
}

void HistoricoEquipo::setPartidosGanados(unsigned short int pg)
{
    partidosGanados=pg;
}

void HistoricoEquipo::setPartidosEmpatados(unsigned short int pe)
{
    partidosEmpatados=pe;
}

void HistoricoEquipo::setPartidosPerdidos(unsigned short int pp)
{
    partidosPerdidos=pp;
}

void HistoricoEquipo::setTarjetasAmarillas(unsigned short int ta)
{
    tarjetasAmarillas=ta;
}

void HistoricoEquipo::setTarjetasRojas(unsigned short int tr)
{
    tarjetasRojas=tr;
}

void HistoricoEquipo::setFaltas(unsigned short int fa)
{
    faltas=fa;
}

void HistoricoEquipo::print() const
{
    cout<<"\n Historico Equipo:{"
         <<"\n Goles a favor: "<<golesFavor
         <<"\n Goles en contra: "<<golesContra
         <<"\n Partidos ganados: "<<partidosGanados
         <<"\n Partidos empatados: "<<partidosEmpatados
         <<"\n Partidos perdidos: "<<partidosPerdidos
         <<"\n Tarjetas amarillas: "<<tarjetasAmarillas
         <<"\n Tarjetas rojas: "<<tarjetasRojas
         <<"\n Faltas: "<<faltas
         <<"\n }"<<endl;
}

HistoricoEquipo::~HistoricoEquipo()
{
    cout<<"\n La instancia de historico equipo ha sido destruida correctamente"<<endl;
}

#include "Equipo.h"
using namespace std;

Equipo::Equipo()
{
    pais="";
    federacion="";
    confederacion="";
    directorTecnico="";
    rankingFIFA=0;
    grupo=' ';

    golesFavor=0;
    golesContra=0;
    partidosGanados=0;
    partidosEmpatados=0;
    partidosPerdidos=0;
    tarjetasAmarillas=0;
    tarjetasRojas=0;
    faltas=0;

    cantJugadores=26;
    jugadores=new Jugador[cantJugadores];

    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i]=Jugador(i+1);
    }
}

Equipo::Equipo(string p, string f, string c, string dt, unsigned short int r, char g)
{
    pais=p;
    federacion=f;
    confederacion=c;
    directorTecnico=dt;
    rankingFIFA=r;
    grupo=g;

    golesFavor=0;
    golesContra=0;
    partidosGanados=0;
    partidosEmpatados=0;
    partidosPerdidos=0;
    tarjetasAmarillas=0;
    tarjetasRojas=0;
    faltas=0;

    cantJugadores=26;
    jugadores=new Jugador[cantJugadores];

    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i]=Jugador(i+1);
    }
}

Equipo::Equipo(const Equipo &copiaEquipo)
{
    pais=copiaEquipo.pais;
    federacion=copiaEquipo.federacion;
    confederacion=copiaEquipo.confederacion;
    directorTecnico=copiaEquipo.directorTecnico;
    rankingFIFA=copiaEquipo.rankingFIFA;
    grupo=copiaEquipo.grupo;

    golesFavor=copiaEquipo.golesFavor;
    golesContra=copiaEquipo.golesContra;
    partidosGanados=copiaEquipo.partidosGanados;
    partidosEmpatados=copiaEquipo.partidosEmpatados;
    partidosPerdidos=copiaEquipo.partidosPerdidos;
    tarjetasAmarillas=copiaEquipo.tarjetasAmarillas;
    tarjetasRojas=copiaEquipo.tarjetasRojas;
    faltas=copiaEquipo.faltas;

    cantJugadores=copiaEquipo.cantJugadores;
    jugadores=new Jugador[cantJugadores];

    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i]=copiaEquipo.jugadores[i];
    }
}

Equipo& Equipo::operator=(const Equipo &otro)
{
    if(this != &otro){
        delete[] jugadores;

        pais=otro.pais;
        federacion=otro.federacion;
        confederacion=otro.confederacion;
        directorTecnico=otro.directorTecnico;
        rankingFIFA=otro.rankingFIFA;
        grupo=otro.grupo;

        golesFavor=otro.golesFavor;
        golesContra=otro.golesContra;
        partidosGanados=otro.partidosGanados;
        partidosEmpatados=otro.partidosEmpatados;
        partidosPerdidos=otro.partidosPerdidos;
        tarjetasAmarillas=otro.tarjetasAmarillas;
        tarjetasRojas=otro.tarjetasRojas;
        faltas=otro.faltas;

        cantJugadores=otro.cantJugadores;
        jugadores=new Jugador[cantJugadores];

        for(unsigned short int i=0; i<cantJugadores; i++){
            jugadores[i]=otro.jugadores[i];
        }
    }

    return *this;
}

string Equipo::getPais() const
{
    return pais;
}

string Equipo::getFederacion() const
{
    return federacion;
}

string Equipo::getConfederacion() const
{
    return confederacion;
}

string Equipo::getDirectorTecnico() const
{
    return directorTecnico;
}

unsigned short int Equipo::getRankingFIFA() const
{
    return rankingFIFA;
}

char Equipo::getGrupo() const
{
    return grupo;
}

unsigned short int Equipo::getGolesFavor() const
{
    return golesFavor;
}

unsigned short int Equipo::getGolesContra() const
{
    return golesContra;
}

unsigned short int Equipo::getPartidosGanados() const
{
    return partidosGanados;
}

unsigned short int Equipo::getPartidosEmpatados() const
{
    return partidosEmpatados;
}

unsigned short int Equipo::getPartidosPerdidos() const
{
    return partidosPerdidos;
}

unsigned short int Equipo::getTarjetasAmarillas() const
{
    return tarjetasAmarillas;
}

unsigned short int Equipo::getTarjetasRojas() const
{
    return tarjetasRojas;
}

unsigned short int Equipo::getFaltas() const
{
    return faltas;
}

unsigned short int Equipo::getCantJugadores() const
{
    return cantJugadores;
}

Jugador* Equipo::getJugadores() const
{
    return jugadores;
}

Jugador Equipo::getJugador(unsigned short int pos) const
{
    return jugadores[pos];
}

void Equipo::setPais(string p)
{
    pais=p;
}

void Equipo::setFederacion(string f)
{
    federacion=f;
}

void Equipo::setConfederacion(string c)
{
    confederacion=c;
}

void Equipo::setDirectorTecnico(string dt)
{
    directorTecnico=dt;
}

void Equipo::setRankingFIFA(unsigned short int r)
{
    rankingFIFA=r;
}

void Equipo::setGrupo(char g)
{
    grupo=g;
}

void Equipo::setGolesFavor(unsigned short int gf)
{
    golesFavor=gf;
}

void Equipo::setGolesContra(unsigned short int gc)
{
    golesContra=gc;
}

void Equipo::setPartidosGanados(unsigned short int pg)
{
    partidosGanados=pg;
}

void Equipo::setPartidosEmpatados(unsigned short int pe)
{
    partidosEmpatados=pe;
}

void Equipo::setPartidosPerdidos(unsigned short int pp)
{
    partidosPerdidos=pp;
}

void Equipo::setTarjetasAmarillas(unsigned short int ta)
{
    tarjetasAmarillas=ta;
}

void Equipo::setTarjetasRojas(unsigned short int tr)
{
    tarjetasRojas=tr;
}

void Equipo::setFaltas(unsigned short int fa)
{
    faltas=fa;
}

void Equipo::inicializarJugadores()
{
    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i]=Jugador(i+1);
    }
}

void Equipo::actualizarHistoricoEquipo(unsigned short int gf, unsigned short int gc,
                                       unsigned short int ta, unsigned short int tr,
                                       unsigned short int fa)
{
    golesFavor+=gf;
    golesContra+=gc;
    tarjetasAmarillas+=ta;
    tarjetasRojas+=tr;
    faltas+=fa;

    if(gf>gc){
        partidosGanados++;
    }
    else if(gf<gc){
        partidosPerdidos++;
    }
    else{
        partidosEmpatados++;
    }
}

void Equipo::print() const
{
    cout<<"\n Equipo:{";
    cout<<"\n Pais: "<<pais;
    cout<<"\n Federacion: "<<federacion;
    cout<<"\n Confederacion: "<<confederacion;
    cout<<"\n Director tecnico: "<<directorTecnico;
    cout<<"\n Ranking FIFA: "<<rankingFIFA;
    cout<<"\n Grupo: "<<grupo;
    cout<<"\n Goles a favor: "<<golesFavor;
    cout<<"\n Goles en contra: "<<golesContra;
    cout<<"\n Partidos ganados: "<<partidosGanados;
    cout<<"\n Partidos empatados: "<<partidosEmpatados;
    cout<<"\n Partidos perdidos: "<<partidosPerdidos;
    cout<<"\n Tarjetas amarillas: "<<tarjetasAmarillas;
    cout<<"\n Tarjetas rojas: "<<tarjetasRojas;
    cout<<"\n Faltas: "<<faltas;
    cout<<"\n Cantidad de jugadores: "<<cantJugadores;
    cout<<"\n }"<<endl;
}

void Equipo::printJugadores() const
{
    cout<<"\n Jugadores del equipo "<<pais<<":"<<endl;
    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i].print();
        cout<<endl;
    }
}

bool Equipo::operator>(const Equipo &otro) const
{
    return rankingFIFA < otro.rankingFIFA;
}

bool Equipo::operator<(const Equipo &otro) const
{
    return rankingFIFA > otro.rankingFIFA;
}

Equipo::~Equipo()
{
    delete[] jugadores;
    cout<<"\n La instancia de equipo ha sido destruida correctamente"<<endl;
}
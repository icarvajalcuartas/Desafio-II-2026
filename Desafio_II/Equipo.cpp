#include "HistoricoEquipo.h"
#include "Equipo.h"
using namespace std;

Equipo::Equipo():pais(""),federacion(""),confederacion(""),directorTecnico(""),rankingFIFA(0),grupo(' '),historico(HistoricoEquipo())
{

    cantJugadores=26;
    jugadores=new Jugador[cantJugadores];

    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i]=Jugador(i);
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

    historico = HistoricoEquipo();

    cantJugadores=26;
    jugadores=new Jugador[cantJugadores];

    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i]=Jugador(i);
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

    historico=copiaEquipo.historico;

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

        historico=otro.historico;

        cantJugadores=otro.cantJugadores;
        jugadores=new Jugador[cantJugadores];

        for(unsigned short int i=0; i<cantJugadores; i++){
            jugadores[i]=otro.jugadores[i];
        }
    }

    return *this;
}

void Equipo::seleccionarJugadores(int indices[]) const
{
    bool usado[26] = {};

    for (int i = 0; i < 11; ++i)
    {
        int idx;
        do {
            idx = rand() % cantJugadores;
        } while (usado[idx]);

        usado[idx] = true;
        indices[i] = idx;
    }
}

string Equipo::getPais() const { return pais; }
string Equipo::getFederacion() const { return federacion; }
string Equipo::getConfederacion() const { return confederacion; }
string Equipo::getDirectorTecnico() const { return directorTecnico; }
unsigned short int Equipo::getRankingFIFA() const { return rankingFIFA; }
char Equipo::getGrupo() const { return grupo; }

HistoricoEquipo Equipo::getHistorico() const
{
    return historico;
}

unsigned short int Equipo::getCantJugadores() const { return cantJugadores; }

Jugador* Equipo::getJugadores() const { return jugadores; }

Jugador Equipo::getJugador(unsigned short int pos) const
{
    return jugadores[pos];
}

Jugador &Equipo::getJugadorRef(int idx)
{
    return jugadores[idx];
}

void Equipo::setPais(string p){ pais=p; }
void Equipo::setFederacion(string f){ federacion=f; }
void Equipo::setConfederacion(string c){ confederacion=c; }
void Equipo::setDirectorTecnico(string dt){ directorTecnico=dt; }
void Equipo::setRankingFIFA(unsigned short int r){ rankingFIFA=r; }
void Equipo::setGrupo(char g){ grupo=g; }

void Equipo::setHistorico(const HistoricoEquipo &h)
{
    historico=h;
}

void Equipo::setHistoricoJugador(unsigned short numeroC, unsigned short c, unsigned short m, unsigned short tA, unsigned short tR, unsigned short fA)
{
    jugadores[numeroC].sethistorico(c,m,tA,tR,fA);

}

void Equipo::inicializarJugadores()
{
    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i]=Jugador(i);
    }
}

void Equipo::actualizarHistoricoEquipo(unsigned short int gf, unsigned short int gc,
                                       unsigned short int ta, unsigned short int tr,
                                       unsigned short int fa)
{
    historico.actualizarHistorico(gf, gc, ta, tr, fa);
}

void Equipo::print() const
{
    cout<<"------Detalles del equipo "<<pais<<"------"<<endl;
    cout<<"Equipo:{"<<endl
         <<"Pais: "<<pais<<endl
         <<"Federacion: "<<federacion<<endl
         <<"Confederacion: "<<confederacion<<endl
         <<"Director tecnico: "<<directorTecnico<<endl
         <<"Ranking FIFA: "<<rankingFIFA<<endl
         <<"Grupo: "<<grupo<<endl;

    historico.print();

    cout<<"Cantidad de jugadores: "<<cantJugadores<<endl;
    cout<<"}"<<endl;
}

void Equipo::printJugadores() const
{
    cout<<"\n Jugadores del equipo "<<pais<<":"<<endl;
    for(unsigned short int i=0; i<cantJugadores; i++){
        jugadores[i].print();
        cout<<endl;
    }
}

void Equipo::printJugador(unsigned short numeroC)
{
    cout<<"Detalles del jugador "<<numeroC<<" del equipo "<<pais<<":"<<endl;
    jugadores[numeroC].print();
    cout<<"------------------------"<<endl;
}

bool Equipo::operator>(const Equipo &otro) const
{
    return rankingFIFA > otro.rankingFIFA;
}

bool Equipo::operator<(const Equipo &otro) const
{
    return rankingFIFA < otro.rankingFIFA;
}

Equipo::~Equipo()
{
    delete[] jugadores;
    //cout<<"\n La instancia de equipo ha sido destruida correctamente"<<endl;
}

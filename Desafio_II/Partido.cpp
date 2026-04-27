#include "Partido.h"
#include<cmath>
#include "ArchivoEquipo.h"
#include "archivos.h"

Partido::Partido()
{
    equipo1=NULL;
    equipo2=NULL;
    fecha="";
    sede="nombreSede";
    arbitro1="codArbitro1";
    arbitro2="codArbitro2";
    arbitro3="codArbitro3";
    hora="00:00";
    golesEquipo1=0;
    golesEquipo2=0;
    jugado=false;
    cantGoladoresEquipo1 = 0;
    cantGoladoresEquipo2 = 0;
    for (int i = 0; i < 11; ++i) {
        goladoresEquipo1[i] = -1;
        goladoresEquipo2[i] = -1;
        indicesJugadores1[i] = -1;
        indicesJugadores2[i] = -1;
    }
}

Partido::Partido(Equipo &e1, Equipo &e2, string f):
    equipo1(&e1),equipo2(&e2),fecha(f),sede("nombreSede"),
    arbitro1("codArbitro1"),arbitro2("codArbitro2"),arbitro3("codArbitro3"),golesEquipo1(0),
    golesEquipo2(0),jugado(false)
{
    cantGoladoresEquipo1 = 0;
    cantGoladoresEquipo2 = 0;
    for (int i = 0; i < 11; ++i) {
        goladoresEquipo1[i] = -1;
        goladoresEquipo2[i] = -1;
        indicesJugadores1[i] = -1;
        indicesJugadores2[i] = -1;
    }
}

Partido::Partido(const Partido &copiaPartido)
{
    equipo1=copiaPartido.equipo1;
    equipo2=copiaPartido.equipo2;
    fecha=copiaPartido.fecha;
    sede=copiaPartido.sede;
    arbitro1=copiaPartido.arbitro1;
    arbitro2=copiaPartido.arbitro2;
    arbitro3=copiaPartido.arbitro3;
    golesEquipo1=copiaPartido.golesEquipo1;
    golesEquipo2=copiaPartido.golesEquipo2;
    jugado=copiaPartido.jugado;
    cantGoladoresEquipo1 = copiaPartido.cantGoladoresEquipo1;
    cantGoladoresEquipo2 = copiaPartido.cantGoladoresEquipo2;
    for (int i = 0; i < 11; ++i) {
        goladoresEquipo1[i] = copiaPartido.goladoresEquipo1[i];
        goladoresEquipo2[i] = copiaPartido.goladoresEquipo2[i];
        indicesJugadores1[i] = copiaPartido.indicesJugadores1[i];
        indicesJugadores2[i] = copiaPartido.indicesJugadores2[i];
    }
}

Equipo* Partido::getEquipo1() const
{
    return equipo1;
}

Equipo* Partido::getEquipo2() const
{
    return equipo2;
}

string Partido::getFecha() const
{
    return fecha;
}

string Partido::getSede() const
{
    return sede;
}

unsigned short int Partido::getGolesEquipo1() const
{
    return golesEquipo1;
}

unsigned short int Partido::getGolesEquipo2() const
{
    return golesEquipo2;
}

bool Partido::getJugado() const
{
    return jugado;
}

void Partido::getIndicesJugadores(int out1[], int out2[]) const
{
    for (int i = 0; i < 11; ++i)
    {
        out1[i] = indicesJugadores1[i];
        out2[i] = indicesJugadores2[i];
    }
}

void Partido::setFecha(string f)
{
    fecha=f;
}

void Partido::setSede(string s)
{
    sede=s;
}

void Partido::setArbitros(string a1, string a2, string a3)
{
    arbitro1=a1;
    arbitro2=a2;
    arbitro3=a3;
}
void Partido::agregarGolesEquipo1(int g)
{
    golesEquipo1 += g;
}

void Partido::agregarGolesEquipo2(int g)
{
    golesEquipo2 += g;
}

void Partido::agregarGoleadorEquipo1(int numCamiseta)
{
    if (cantGoladoresEquipo1 < 11)
        goladoresEquipo1[cantGoladoresEquipo1++] = numCamiseta;
}

void Partido::agregarGoleadorEquipo2(int numCamiseta)
{
    if (cantGoladoresEquipo2 < 11)
        goladoresEquipo2[cantGoladoresEquipo2++] = numCamiseta;
}

Partido &Partido::operator=(const Partido &otro)
{
    if (this != &otro)
    {
        equipo1 = otro.equipo1;
        equipo2 = otro.equipo2;
        fecha = otro.fecha;
        sede = otro.sede;
        hora = otro.hora;
        arbitro1 = otro.arbitro1;
        arbitro2 = otro.arbitro2;
        arbitro3 = otro.arbitro3;
        golesEquipo1 = otro.golesEquipo1;
        golesEquipo2 = otro.golesEquipo2;
        jugado = otro.jugado;
        cantGoladoresEquipo1 = otro.cantGoladoresEquipo1;
        cantGoladoresEquipo2 = otro.cantGoladoresEquipo2;
        for (int i = 0; i < 11; ++i) {
            goladoresEquipo1[i] = otro.goladoresEquipo1[i];
            goladoresEquipo2[i] = otro.goladoresEquipo2[i];
            indicesJugadores1[i] = otro.indicesJugadores1[i];
            indicesJugadores2[i] = otro.indicesJugadores2[i];
        }
    }
    return *this;
}
const int* Partido::getGoladoresEquipo1() const { return goladoresEquipo1; }
const int* Partido::getGoladoresEquipo2() const { return goladoresEquipo2; }
int Partido::getCantGoladoresEquipo1() const { return cantGoladoresEquipo1; }
int Partido::getCantGoladoresEquipo2() const { return cantGoladoresEquipo2; }


void Partido::simularPartido()
{
    if (equipo1 == NULL || equipo2 == NULL) {
        cout << "\nNo se puede simular: falta un equipo." << endl;
        return;
    }
    if (jugado) {
        cout << "\nEste partido ya fue simulado." << endl;
        return;
    }

    equipo1->seleccionarJugadores(indicesJugadores1);
    equipo2->seleccionarJugadores(indicesJugadores2);


    const double MIU   = 1.35;
    const double ALPHA = 0.6;
    const double BETA  = 0.4;

    int partE1 = equipo1->getHistorico().getPartidosGanados()
                 + equipo1->getHistorico().getPartidosEmpatados()
                 + equipo1->getHistorico().getPartidosPerdidos();
    int partE2 = equipo2->getHistorico().getPartidosGanados()
                 + equipo2->getHistorico().getPartidosEmpatados()
                 + equipo2->getHistorico().getPartidosPerdidos();

    if (partE1 == 0) partE1 = 1;
    if (partE2 == 0) partE2 = 1;

    double gfA = (double)equipo1->getHistorico().getGolesFavor()  / partE1;
    double gcA = (double)equipo1->getHistorico().getGolesContra() / partE1;
    double gfB = (double)equipo2->getHistorico().getGolesFavor()  / partE2;
    double gcB = (double)equipo2->getHistorico().getGolesContra() / partE2;

    if (gfA < 0.01) gfA = 0.5;
    if (gfB < 0.01) gfB = 0.5;
    if (gcA < 0.01) gcA = 0.5;
    if (gcB < 0.01) gcB = 0.5;


    double lambdaA = MIU * pow(gfA / MIU, ALPHA) * pow(gcB / MIU, BETA);
    double lambdaB = MIU * pow(gfB / MIU, ALPHA) * pow(gcA / MIU, BETA);


    int golesEspA = (int)(lambdaA + 0.5);
    int golesEspB = (int)(lambdaB + 0.5);
    if (golesEspA < 0) golesEspA = 0;
    if (golesEspB < 0) golesEspB = 0;


    double pesoA = (1.0 / equipo1->getRankingFIFA()) * (1.0 + gfA);
    double pesoB = (1.0 / equipo2->getRankingFIFA()) * (1.0 + gfB);
    double posesionA = pesoA / (pesoA + pesoB) * 100.0;
    double posesionB = 100.0 - posesionA;



    golesEquipo1 = 0;
    golesEquipo2 = 0;
    cantGoladoresEquipo1 = 0;
    cantGoladoresEquipo2 = 0;
//para equipo 1
    unsigned short taAcum1[11] = {};
    unsigned short fAcum1[11]  = {};
    unsigned short gAcum1[11]  = {};
    unsigned short rojas1[11]  = {};

    for (int i = 0; i < 11; ++i)
    {

        if (golesEquipo1 < golesEspA)
        {
            if ((rand() % 100) < 4)
            {
                gAcum1[i]++;
                golesEquipo1++;
                goladoresEquipo1[cantGoladoresEquipo1++] =
                    equipo1->getJugadorRef(indicesJugadores1[i]).getnumCamiseta();
            }
        }


        if ((rand() % 10000) < 600)
        {
            taAcum1[i]++;
            if ((rand() % 10000) < 115)
            {
                taAcum1[i]++;
                rojas1[i] = 1;
            }
        }

        if ((rand() % 10000) < 1300)
        {
            fAcum1[i]++;
            if ((rand() % 10000) < 275)
            {
                fAcum1[i]++;
                if ((rand() % 10000) < 70)
                {
                    fAcum1[i]++;
                }
            }
        }
    }

    //para equipo 2:
    unsigned short taAcum2[11] = {};
    unsigned short fAcum2[11]  = {};
    unsigned short gAcum2[11]  = {};
    unsigned short rojas2[11]  = {};

    for (int i = 0; i < 11; ++i)
    {
        if (golesEquipo2 < golesEspB)
        {
            if ((rand() % 100) < 4)
            {
                gAcum2[i]++;
                golesEquipo2++;
                goladoresEquipo2[cantGoladoresEquipo2++] =
                     equipo2->getJugadorRef(indicesJugadores2[i]).getnumCamiseta();
            }
        }

        if ((rand() % 10000) < 600)
        {
            taAcum2[i]++;
            if ((rand() % 10000) < 115)
            {
                taAcum2[i]++;
                rojas2[i] = 1;
            }
        }

        if ((rand() % 10000) < 1300)
        {
            fAcum2[i]++;
            if ((rand() % 10000) < 275)
            {
                fAcum2[i]++;
                if ((rand() % 10000) < 70)
                {
                    fAcum2[i]++;
                }
            }
        }
    }


    unsigned short taTotal1 = 0, trTotal1 = 0, fTotal1 = 0;
    for (int i = 0; i < 11; ++i)
    {
        equipo1->getJugadorRef(indicesJugadores1[i]).sethistorico(
            gAcum1[i], 90, taAcum1[i], rojas1[i], fAcum1[i]);
        taTotal1 += taAcum1[i];
        trTotal1 += rojas1[i];
        fTotal1  += fAcum1[i];
    }

    unsigned short taTotal2 = 0, trTotal2 = 0, fTotal2 = 0;
    for (int i = 0; i < 11; ++i)
    {
        equipo2->getJugadorRef(indicesJugadores2[i]).sethistorico(
            gAcum2[i], 90, taAcum2[i], rojas2[i], fAcum2[i]);
        taTotal2 += taAcum2[i];
        trTotal2 += rojas2[i];
        fTotal2  += fAcum2[i];
    }


    equipo1->actualizarHistoricoEquipo(golesEquipo1, golesEquipo2,
                                       taTotal1, trTotal1, fTotal1);
    equipo2->actualizarHistoricoEquipo(golesEquipo2, golesEquipo1,
                                       taTotal2, trTotal2, fTotal2);

    actualizarHistoricoEquipoArchivo(*equipo1, "Historico_equipos.csv");
    actualizarHistoricoEquipoArchivo(*equipo2, "Historico_equipos.csv");

    for (int i = 0; i < 11; ++i)
    {
        actualizarArchivo(
            equipo1->getJugadorRef(indicesJugadores1[i]).gethistorico(),
            equipo1->getJugadorRef(indicesJugadores1[i]).getnumCamiseta(),
            equipo1->getPais());

        actualizarArchivo(
            equipo2->getJugadorRef(indicesJugadores2[i]).gethistorico(),
            equipo2->getJugadorRef(indicesJugadores2[i]).getnumCamiseta(),
            equipo2->getPais());
    }
    jugado = true;


    int posA_entero = (int)posesionA;
    int posA_dec    = (int)(fabs(posesionA - posA_entero) * 10 + 0.5);
    int posB_entero = (int)posesionB;
    int posB_dec    = (int)(fabs(posesionB - posB_entero) * 10 + 0.5);

    cout << "\n Posesion: " << equipo1->getPais() << " "
         << posA_entero << "." << posA_dec << "% - "
         << equipo2->getPais() << " "
         << posB_entero << "." << posB_dec << "%" << endl;
}

void Partido::print() const
{
    cout<<"\n Partido:{";
    cout<<"\n Fecha: "<<fecha;
    cout<<"\n Sede: "<<sede;
    cout<<"\n Arbitros: "<<arbitro1<<", "<<arbitro2<<", "<<arbitro3;

    if(equipo1!=NULL && equipo2!=NULL){
        cout<<"\n Equipo 1: "<<equipo1->getPais();
        cout<<"\n Equipo 2: "<<equipo2->getPais();
    }

    if(jugado){
        cout<<"\n Resultado: "<<golesEquipo1<<" - "<<golesEquipo2;
    }
    else{
        cout<<"\n Resultado: partido no jugado";
    }

    cout<<"\n }"<<endl;
}

Partido::~Partido()
{
}

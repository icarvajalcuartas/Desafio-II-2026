#include "Torneo.h"
#include"ArchivoEquipo.h"
#include<iostream>
using namespace std;

static void imprimirEtapa(const string& nombre, Partido* partidos, int n);
Torneo::Torneo():totalEquipos(0),in_b1(0),in_b2(0),in_b3(0),in_b4(0),numPartidosGrupos(0),iteraciones(0)
{}

Equipo *Torneo::resolverEmpate(Partido &p)
{
    Equipo* e1 = p.getEquipo1();
    Equipo* e2 = p.getEquipo2();

    int idx1[11], idx2[11];
    p.getIndicesJugadores(idx1, idx2);

    double pesoE1 = 1.0 / (double)e1->getRankingFIFA();
    double pesoE2 = 1.0 / (double)e2->getRankingFIFA();
    int umbral    = (int)(pesoE1 / (pesoE1 + pesoE2) * 1000);
    Equipo* ganador = (rand() % 1000 < umbral) ? e1 : e2;

    if (ganador == e1)
    {
        p.agregarGolesEquipo1(1);
        p.agregarGoleadorEquipo1(e1->getJugadorRef(idx1[0]).getnumCamiseta());
        e1->actualizarHistoricoEquipo(1, 0, 0, 0, 0);
    }
    else
    {
        p.agregarGolesEquipo2(1);
         p.agregarGoleadorEquipo2(e2->getJugadorRef(idx2[0]).getnumCamiseta());
        e2->actualizarHistoricoEquipo(1, 0, 0, 0, 0);
    }

    for (int i = 0; i < 11; ++i)
    {
        iteraciones++;
        e1->getJugadorRef(idx1[i]).sethistorico(0, 30, 0, 0, 0);
        e2->getJugadorRef(idx2[i]).sethistorico(0, 30, 0, 0, 0);
    }

    actualizarHistoricoEquipoArchivo(*e1, "Historico_equipos.csv");
    actualizarHistoricoEquipoArchivo(*e2, "Historico_equipos.csv");

    return ganador;
}

bool Torneo::construirGruposRec(int pot, int g, bool usado[4][NUM_GRUPOS])
{
    if(pot==4){
        return true;
    }
    if(g==NUM_GRUPOS){
        return construirGruposRec(pot+1,0,usado);
    }

    int *bombo=nullptr;
    if(pot==0){
        bombo=bombo1;
    }
    else if(pot==1){
        bombo=bombo2;
    }
    else if(pot==2){
        bombo=bombo3;
    }
    else{
        bombo=bombo4;
    }
    for(int i=0;i<NUM_GRUPOS;++i){
        iteraciones++;
        if(usado[pot][i]){
            continue;
        }
        int idxEquipo=bombo[i];
        Equipo &eq=equipos[idxEquipo];

        if(grupos[g].agregarEquipo(eq)){
            usado[pot][i]=true;
            if (construirGruposRec(pot,g+1,usado)){
                return true;
            }
            grupos[g].quitarUltimoEquipo();
            usado[pot][i]=false;
        }
    }
    return false;
}

Equipo *Torneo::buscarEquipoRealPorPais(const string &pais)
{
    for(int i=0;i<totalEquipos;++i){
        iteraciones++;
        if(equipos[i].getPais()==pais){
            return &equipos[i];
        }
    }
    return nullptr;
}

void Torneo::setFechaString(unsigned short int desfase, string &out) const
{
    unsigned short int dia=20+desfase;
    unsigned short int mes=6;
    unsigned short int anio=2026;

    if(dia>30){
        dia-=30;
        mes=7;
    }
    string dd=(dia<10?"0":"")+to_string(dia);
    string mm=(mes<10 ? "0" : "")+to_string(mes);
    out=dd+"/"+mm+"/"+to_string(anio);
}


int Torneo::buscarGrupoDeEquipo(const Equipo *eq)
{
    for (int g = 0; g < NUM_GRUPOS; ++g){
        iteraciones++;
        for (int e = 0; e < 4; ++e){
        iteraciones++;
            if (buscarEquipoRealPorPais(grupos[g].getEquipo(e).getPais()) == eq){
                return g;
           }
        }
    }
    return -1;
}



Partido &Torneo::getPartidoGrupo(int idx)
{
    return partidosGrupos[idx];
}

long long Torneo::getIteraciones() const
{
    return iteraciones;
}

bool Torneo::cargarEquiposDesdeArchivo(const string &nombreArchivo)
{
    totalEquipos=cargarTodosLosEquipos(equipos,NUM_EQUIPOS,nombreArchivo);
    return totalEquipos>0;
}

void Torneo::clasificarEnBombos()
{
    in_b1=in_b2=in_b3=in_b4=0;

    int idx[NUM_EQUIPOS];
    for(int i=0; i<totalEquipos;++i){
        iteraciones++;
        idx[i]=i;
    }


    for(int i=0;i<totalEquipos-1;++i){
        iteraciones++;
        int minPos=i;
        for (int j= i+1; j<totalEquipos;++j){
            iteraciones++;
            if(equipos[idx[j]]<equipos[idx[minPos]]){
                minPos=j;
            }

        }
        int tmp=idx[i];
        idx[i]=idx[minPos];
        idx[minPos]=tmp;
    }
    int usaPos=-1;
    for (int i=0; i<totalEquipos; ++i)
    {
        iteraciones++;
        if (equipos[idx[i]].getPais()=="United States")
        {
            usaPos=i;
            break;
        }
    }

    if (usaPos==-1)
    {
        cout << "No se encontró United States.\n";
        return;
    }

    int usaIdx = idx[usaPos];

    int ord[NUM_EQUIPOS];
    int nOrd = 0;
    for (int i = 0; i < totalEquipos; ++i)
    {
        iteraciones++;
        if (i == usaPos)
        {
            continue;
        }
        ord[nOrd] = idx[i];
        nOrd++;
    }

    bombo1[in_b1] = usaIdx;
    in_b1++;

    int p = 0;
    while (in_b1 < NUM_GRUPOS && p < nOrd)
    {
        iteraciones++;
        bombo1[in_b1] = ord[p];
        in_b1++;
        p++;
    }

    while (in_b2 < NUM_GRUPOS && p < nOrd)
    {
        iteraciones++;
        bombo2[in_b2] = ord[p];
        in_b2++;
        p++;
    }

    while (in_b3 < NUM_GRUPOS && p < nOrd)
    {
        iteraciones++;
        bombo3[in_b3] = ord[p];
        in_b3++;
        p++;
    }

    while (in_b4 < NUM_GRUPOS && p < nOrd)
    {
        iteraciones++;
        bombo4[in_b4] = ord[p];
        in_b4++;
        p++;
    }


}

void Torneo::printBombos() const
{
    cout<<"----BOMBO 1----"<<endl;
    for (int i=0; i<in_b1;i++){
        //iteraciones++;
        int in_equipo=bombo1[i];
        cout<<equipos[in_equipo].getRankingFIFA()<<"-"
             <<equipos[in_equipo].getPais()<<"-"
             <<equipos[in_equipo].getConfederacion()<<endl;
    }
    cout<<"----BOMBO 2----"<<endl;
    for (int i=0; i<in_b2;i++){
        //iteraciones++;
        int in_equipo=bombo2[i];
        cout<<equipos[in_equipo].getRankingFIFA()<<"-"
             <<equipos[in_equipo].getPais()<<"-"
             <<equipos[in_equipo].getConfederacion()<<endl;
    }
    cout<<"----BOMBO 3----"<<endl;
    for (int i=0; i<in_b3;i++){
        //iteraciones++;
        int in_equipo=bombo3[i];
        cout<<equipos[in_equipo].getRankingFIFA()<<"-"
             <<equipos[in_equipo].getPais()<<"-"
             <<equipos[in_equipo].getConfederacion()<<endl;
    }
    cout<<"----BOMBO 4----"<<endl;
    for (int i=0; i<in_b4;i++){
        //iteraciones++;
        int in_equipo=bombo4[i];
        cout<<equipos[in_equipo].getRankingFIFA()<<"-"
             <<equipos[in_equipo].getPais()<<"-"
             <<equipos[in_equipo].getConfederacion()<<endl;
    }
}

bool Torneo::crearGrupos()
{
    for(int g=0;g<NUM_GRUPOS;++g){
        iteraciones++;
        grupos[g]=Grupo(char('A'+g));
    }
    bool usado[4][NUM_GRUPOS];
    for(int p=0;p<4;++p){
        iteraciones++;
        for(int i=0;i<NUM_GRUPOS;++i){
            iteraciones++;
            usado[p][i]=false;
        }
    }
    if(in_b1!=NUM_GRUPOS||in_b2!=NUM_GRUPOS || in_b3!=NUM_GRUPOS||in_b4 !=NUM_GRUPOS){
        cout<<"Error: no hay "<<NUM_GRUPOS<<" en cada bombo"<<endl;
        return false;
    }
    cout << in_b1 << " " << in_b2 << " " << in_b3 << " " << in_b4 << endl;
    return construirGruposRec(0,0,usado);
}

void Torneo::printGrupos() const
{
    for(int g=0;g<NUM_GRUPOS;++g){
        grupos[g].print();
    }
}
bool Torneo::configurarPartidosGrupos()
{
    numPartidosGrupos = 0;


    const int Aj[3][2] = { {0,2}, {0,1}, {0,1} };
    const int Bj[3][2] = { {1,3}, {2,3}, {3,2} };


    struct Info { int idxA; int idxB; int jornada; };
    Info lista[TOTAL_PARTIDOS_GRUPOS];
    int total = 0;

    for (int j = 0; j < 3; ++j)
    {
        iteraciones++;
        for (int g = 0; g < NUM_GRUPOS; ++g)
        {
            iteraciones++;
            Equipo* p[4];
            for (int k = 0; k < 4; ++k){
                iteraciones++;
                p[k] = buscarEquipoRealPorPais(grupos[g].getEquipo(k).getPais());
            }
            if (!p[0]||!p[1]||!p[2]||!p[3]) {
                cout << "Error grupo " << grupos[g].getLetra() << "\n";
                return false;
            }

            for (int m = 0; m < 2; ++m)
            {
                iteraciones++;
                int idxA = int(p[Aj[j][m]] - &equipos[0]);
                int idxB = int(p[Bj[j][m]] - &equipos[0]);
                lista[total++] = { idxA, idxB, j };

                partidosGrupos[numPartidosGrupos++] =
                    Partido(*p[Aj[j][m]], *p[Bj[j][m]], "");
            }
        }
    }

    if (numPartidosGrupos != TOTAL_PARTIDOS_GRUPOS) {
        cout << "Error: " << numPartidosGrupos << " partidos\n";
        return false;
    }


    int ultimoDia[NUM_EQUIPOS];
    for (int i = 0; i < NUM_EQUIPOS; ++i) ultimoDia[i] = -10;

    int partidosPorDia[DIAS_FASE_GRUPOS] = {};


    const int diaMinJornada[3] = { 0, 6, 12 };
    const int diaMaxJornada[3] = { 8, 14, 18 };

    for (int p = 0; p < TOTAL_PARTIDOS_GRUPOS; ++p)
    {
        iteraciones++;
        int idxA = lista[p].idxA;
        int idxB = lista[p].idxB;
        int j    = lista[p].jornada;

        bool asignado = false;
        for (int d = diaMinJornada[j]; d <= diaMaxJornada[j]; ++d)
        {
            iteraciones++;
            if (partidosPorDia[d] >= MAX_PARTIDOS_POR_DIA) continue;
            if (d - ultimoDia[idxA] < 4)                   continue;
            if (d - ultimoDia[idxB] < 4)                   continue;

            string f;
            setFechaString((unsigned short)d, f);
            partidosGrupos[p].setFecha(f);
            partidosPorDia[d]++;
            ultimoDia[idxA] = d;
            ultimoDia[idxB] = d;
            asignado = true;
            break;
        }

        if (!asignado) {
            cout << "Error: sin día para partido " << p
                 << " (jornada " << j+1 << ")\n";
            return false;
        }
    }

    cout << "Partidos configurados: " << numPartidosGrupos << endl;
    return true;
}

void Torneo::printPartidosGrupos() const
{
    for (int i = 0; i < numPartidosGrupos; ++i)
    {
        partidosGrupos[i].print();
    }
}

void Torneo::simularFaseGrupos()
{

    for (int i = 0; i < numPartidosGrupos; ++i){
        iteraciones++;
        partidosGrupos[i].simularPartido();
    }

    Equipo* tabEquipo[NUM_GRUPOS][4];
    int     tabPJ [NUM_GRUPOS][4];
    int     tabPG [NUM_GRUPOS][4];
    int     tabPE [NUM_GRUPOS][4];
    int     tabPP [NUM_GRUPOS][4];
    int     tabGF [NUM_GRUPOS][4];
    int     tabGC [NUM_GRUPOS][4];
    int     tabDG [NUM_GRUPOS][4];
    int     tabPTS[NUM_GRUPOS][4];


    for (int g = 0; g < NUM_GRUPOS; ++g)
    {
        iteraciones++;
        for (int e = 0; e < 4; ++e)
        {
            iteraciones++;
            tabEquipo[g][e] = buscarEquipoRealPorPais(
                grupos[g].getEquipo(e).getPais());
            tabPJ [g][e] = 0;
            tabPG [g][e] = 0;
            tabPE [g][e] = 0;
            tabPP [g][e] = 0;
            tabGF [g][e] = 0;
            tabGC [g][e] = 0;
            tabDG [g][e] = 0;
            tabPTS[g][e] = 0;
        }
    }


    for (int i = 0; i < numPartidosGrupos; ++i)
    {
        iteraciones++;
        Partido& p  = partidosGrupos[i];
        int g       = buscarGrupoDeEquipo(p.getEquipo1());
        if (g == -1) {
            cout << "ADVERTENCIA: grupo no encontrado para "
                 << p.getEquipo1()->getPais() << endl;
            continue;
        }
        int ge1 = p.getGolesEquipo1();
        int ge2 = p.getGolesEquipo2();


        int e1 = -1, e2 = -1;
        for (int e = 0; e < 4; ++e)
        {
            iteraciones++;
            if (tabEquipo[g][e] == p.getEquipo1()) e1 = e;
            if (tabEquipo[g][e] == p.getEquipo2()) e2 = e;
        }
        if (e1 == -1 || e2 == -1) continue;

        // para equipo 1
        tabPJ[g][e1]++;
        tabGF[g][e1] += ge1;
        tabGC[g][e1] += ge2;
        if      (ge1 > ge2) { tabPG[g][e1]++; tabPTS[g][e1] += 3; }
        else if (ge1 == ge2) { tabPE[g][e1]++; tabPTS[g][e1] += 1; }
        else                  { tabPP[g][e1]++; }

        // para equipo 2
        tabPJ[g][e2]++;
        tabGF[g][e2] += ge2;
        tabGC[g][e2] += ge1;
        if      (ge2 > ge1) { tabPG[g][e2]++; tabPTS[g][e2] += 3; }
        else if (ge2 == ge1) { tabPE[g][e2]++; tabPTS[g][e2] += 1; }
        else                  { tabPP[g][e2]++; }
    }


    for (int g = 0; g < NUM_GRUPOS; ++g){
        iteraciones++;
        for (int e = 0; e < 4; ++e){
            iteraciones++;
            tabDG[g][e] = tabGF[g][e] - tabGC[g][e];
        }
    }

    for (int g = 0; g < NUM_GRUPOS; ++g)
    {
        iteraciones++;
        for (int i = 0; i < 3; ++i)
        {
            iteraciones++;
            for (int j = i + 1; j < 4; ++j)
            {
                iteraciones++;
                bool swap = false;
                if (tabPTS[g][i] < tabPTS[g][j]) swap = true;
                else if (tabPTS[g][i] == tabPTS[g][j])
                {
                    if (tabDG[g][i] < tabDG[g][j]) swap = true;
                    else if (tabDG[g][i] == tabDG[g][j])
                        if (tabGF[g][i] < tabGF[g][j]) swap = true;
                }
                if (swap)
                {

                    Equipo* tmpEq  = tabEquipo[g][i];
                    int tmpPJ      = tabPJ [g][i];
                    int tmpPG      = tabPG [g][i];
                    int tmpPE      = tabPE [g][i];
                    int tmpPP      = tabPP [g][i];
                    int tmpGF      = tabGF [g][i];
                    int tmpGC      = tabGC [g][i];
                    int tmpDG      = tabDG [g][i];
                    int tmpPTS     = tabPTS[g][i];

                    tabEquipo[g][i] = tabEquipo[g][j];
                    tabPJ [g][i]    = tabPJ [g][j];
                    tabPG [g][i]    = tabPG [g][j];
                    tabPE [g][i]    = tabPE [g][j];
                    tabPP [g][i]    = tabPP [g][j];
                    tabGF [g][i]    = tabGF [g][j];
                    tabGC [g][i]    = tabGC [g][j];
                    tabDG [g][i]    = tabDG [g][j];
                    tabPTS[g][i]    = tabPTS[g][j];

                    tabEquipo[g][j] = tmpEq;
                    tabPJ [g][j]    = tmpPJ;
                    tabPG [g][j]    = tmpPG;
                    tabPE [g][j]    = tmpPE;
                    tabPP [g][j]    = tmpPP;
                    tabGF [g][j]    = tmpGF;
                    tabGC [g][j]    = tmpGC;
                    tabDG [g][j]    = tmpDG;
                    tabPTS[g][j]    = tmpPTS;
                }
            }
        }
    }


    cout << "\n========================================" << endl;
    cout << "   GOLEADORES POR PARTIDO" << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < numPartidosGrupos; ++i)
    {
        iteraciones++;
        Partido& p = partidosGrupos[i];
        p.print();
        cout << "  Goleadores " << p.getEquipo1()->getPais() << ": ";
        for (int j = 0; j < p.getCantGoladoresEquipo1(); ++j){
            iteraciones++;
            cout << p.getGoladoresEquipo1()[j] << " ";
        }
        if (p.getCantGoladoresEquipo1() == 0) cout << "ninguno";
        cout << endl;

        cout << "  Goleadores " << p.getEquipo2()->getPais() << ": ";
        for (int j = 0; j < p.getCantGoladoresEquipo2(); ++j){
            iteraciones++;
            cout << p.getGoladoresEquipo2()[j] << " ";
        }
        if (p.getCantGoladoresEquipo2() == 0) cout << "ninguno";
        cout << endl;
    }

    cout << "\n========================================" << endl;
    cout << "   TABLAS DE CLASIFICACION - FASE DE GRUPOS" << endl;
    cout << "========================================" << endl;

    for (int g = 0; g < NUM_GRUPOS; ++g)
    {   iteraciones++;
        cout << "\nGrupo " << char('A' + g) << ":" << endl;
        cout << "  Equipo                    PJ  PG  PE  PP  GF  GC  DG  PTS" << endl;
        cout << "  -------------------------------------------------------" << endl;
        for (int e = 0; e < 4; ++e)
        {
            iteraciones++;
            cout << "  " << tabEquipo[g][e]->getPais();
            int espacios = 24 - (int)tabEquipo[g][e]->getPais().size();
            for (int s = 0; s < espacios; ++s) {
                iteraciones++;
                cout << " ";
            }
            cout << tabPJ [g][e] << "   "
                 << tabPG [g][e] << "   "
                 << tabPE [g][e] << "   "
                 << tabPP [g][e] << "   "
                 << tabGF [g][e] << "   "
                 << tabGC [g][e] << "   "
                 << tabDG [g][e] << "   "
                 << tabPTS[g][e] << endl;
        }
    }

}

void Torneo::clasificarYArmarR16()
{
    Equipo* tabEquipo[NUM_GRUPOS][4];
    int tabPJ [NUM_GRUPOS][4];
    int tabPG [NUM_GRUPOS][4];
    int tabPE [NUM_GRUPOS][4];
    int tabPP [NUM_GRUPOS][4];
    int tabGF [NUM_GRUPOS][4];
    int tabGC [NUM_GRUPOS][4];
    int tabDG [NUM_GRUPOS][4];
    int tabPTS[NUM_GRUPOS][4];

    for (int g = 0; g < NUM_GRUPOS; ++g){
        iteraciones++;
        for (int e = 0; e < 4; ++e)
        {
            iteraciones++;
            tabEquipo[g][e] = buscarEquipoRealPorPais(
                grupos[g].getEquipo(e).getPais());
            tabPJ[g][e]=tabPG[g][e]=tabPE[g][e]=tabPP[g][e]=0;
            tabGF[g][e]=tabGC[g][e]=tabDG[g][e]=tabPTS[g][e]=0;
        }
    }

    for (int i = 0; i < numPartidosGrupos; ++i)
    {
        iteraciones++;
        Partido& p = partidosGrupos[i];
        int g = buscarGrupoDeEquipo(p.getEquipo1());
        if (g == -1) continue;
        int ge1 = p.getGolesEquipo1();
        int ge2 = p.getGolesEquipo2();
        int e1 = -1, e2 = -1;
        for (int e = 0; e < 4; ++e)
        {
            iteraciones++;
            if (tabEquipo[g][e] == p.getEquipo1()) e1 = e;
            if (tabEquipo[g][e] == p.getEquipo2()) e2 = e;
        }
        if (e1==-1||e2==-1) continue;

        tabPJ[g][e1]++; tabGF[g][e1]+=ge1; tabGC[g][e1]+=ge2;
        if      (ge1>ge2){tabPG[g][e1]++;tabPTS[g][e1]+=3;}
        else if (ge1==ge2){tabPE[g][e1]++;tabPTS[g][e1]+=1;}
        else               tabPP[g][e1]++;

        tabPJ[g][e2]++; tabGF[g][e2]+=ge2; tabGC[g][e2]+=ge1;
        if      (ge2>ge1){tabPG[g][e2]++;tabPTS[g][e2]+=3;}
        else if (ge2==ge1){tabPE[g][e2]++;tabPTS[g][e2]+=1;}
        else               tabPP[g][e2]++;
    }
    for (int g=0;g<NUM_GRUPOS;++g){
        iteraciones++;
        for (int e=0;e<4;++e){
        iteraciones++;
            tabDG[g][e]=tabGF[g][e]-tabGC[g][e];
        }
    }

    for (int g = 0; g < NUM_GRUPOS; ++g){
        iteraciones++;
        for (int i = 0; i < 3; ++i){
            iteraciones++;
            for (int j = i+1; j < 4; ++j)
            {
                iteraciones++;
                bool sw = false;
                if (tabPTS[g][i]<tabPTS[g][j]) sw=true;
                else if (tabPTS[g][i]==tabPTS[g][j])
                {
                    if (tabDG[g][i]<tabDG[g][j]) sw=true;
                    else if (tabDG[g][i]==tabDG[g][j])
                        if (tabGF[g][i]<tabGF[g][j]) sw=true;
                }
                if (sw)
                {
                    Equipo* tmpE=tabEquipo[g][i];
                    int p1=tabPJ[g][i],p2=tabPG[g][i],p3=tabPE[g][i],
                        p4=tabPP[g][i],p5=tabGF[g][i],p6=tabGC[g][i],
                        p7=tabDG[g][i],p8=tabPTS[g][i];
                    tabEquipo[g][i]=tabEquipo[g][j];
                    tabPJ[g][i]=tabPJ[g][j]; tabPG[g][i]=tabPG[g][j];
                    tabPE[g][i]=tabPE[g][j]; tabPP[g][i]=tabPP[g][j];
                    tabGF[g][i]=tabGF[g][j]; tabGC[g][i]=tabGC[g][j];
                    tabDG[g][i]=tabDG[g][j]; tabPTS[g][i]=tabPTS[g][j];
                    tabEquipo[g][j]=tmpE;
                    tabPJ[g][j]=p1; tabPG[g][j]=p2; tabPE[g][j]=p3;
                    tabPP[g][j]=p4; tabGF[g][j]=p5; tabGC[g][j]=p6;
                    tabDG[g][j]=p7; tabPTS[g][j]=p8;
                }
            }
        }
    }

    Equipo* primeros[NUM_GRUPOS];
    Equipo* segundos[NUM_GRUPOS];
    Equipo* terceros[NUM_GRUPOS];
    int     tercPTS[NUM_GRUPOS];
    int     tercDG [NUM_GRUPOS];
    int     tercGF [NUM_GRUPOS];
    int     tercGrupo[NUM_GRUPOS];

    for (int g = 0; g < NUM_GRUPOS; ++g)
    {
        iteraciones++;
        primeros[g]   = tabEquipo[g][0];
        segundos[g]   = tabEquipo[g][1];
        terceros[g]   = tabEquipo[g][2];
        tercPTS[g]    = tabPTS[g][2];
        tercDG[g]     = tabDG[g][2];
        tercGF[g]     = tabGF[g][2];
        tercGrupo[g]  = g;
    }

    for (int i = 0; i < NUM_GRUPOS-1; ++i){
        iteraciones++;
        for (int j = i+1; j < NUM_GRUPOS; ++j)
        {
            iteraciones++;
            bool sw = false;
            if (tercPTS[i]<tercPTS[j]) sw=true;
            else if (tercPTS[i]==tercPTS[j])
            {
                if (tercDG[i]<tercDG[j]) sw=true;
                else if (tercDG[i]==tercDG[j])
                    if (tercGF[i]<tercGF[j]) sw=true;
            }
            if (sw)
            {
                Equipo* tmpE=terceros[i];
                int tp=tercPTS[i],td=tercDG[i],tg=tercGF[i],tgr=tercGrupo[i];
                terceros[i]=terceros[j]; tercPTS[i]=tercPTS[j];
                tercDG[i]=tercDG[j];     tercGF[i]=tercGF[j];
                tercGrupo[i]=tercGrupo[j];
                terceros[j]=tmpE; tercPTS[j]=tp;
                tercDG[j]=td;     tercGF[j]=tg;
                tercGrupo[j]=tgr;
            }
        }
    }
    Equipo* segundosOrd[NUM_GRUPOS];
    int     segGrupo[NUM_GRUPOS];
    int     segPTS[NUM_GRUPOS], segDG[NUM_GRUPOS], segGF2[NUM_GRUPOS];

    for (int g = 0; g < NUM_GRUPOS; ++g)
    {
        iteraciones++;
        segundosOrd[g] = segundos[g];
        segGrupo[g]    = g;
        segPTS[g]      = tabPTS[g][1];
        segDG[g]       = tabDG[g][1];
        segGF2[g]      = tabGF[g][1];
    }

    for (int i = 0; i < NUM_GRUPOS-1; ++i)
        for (int j = i+1; j < NUM_GRUPOS; ++j)
        {
            iteraciones++;
            bool sw = false;
            if (segPTS[i] < segPTS[j]) sw = true;
            else if (segPTS[i] == segPTS[j])
            {
                if (segDG[i] < segDG[j]) sw = true;
                else if (segDG[i] == segDG[j])
                    if (segGF2[i] < segGF2[j]) sw = true;
            }
            if (sw)
            {
                Equipo* tmpE  = segundosOrd[i];
                int tp = segPTS[i], td = segDG[i], tg = segGF2[i], tgr = segGrupo[i];
                segundosOrd[i] = segundosOrd[j]; segPTS[i]  = segPTS[j];
                segDG[i]       = segDG[j];       segGF2[i]  = segGF2[j];
                segGrupo[i]    = segGrupo[j];
                segundosOrd[j] = tmpE; segPTS[j]  = tp;
                segDG[j]       = td;  segGF2[j]  = tg;
                segGrupo[j]    = tgr;
            }
        }

    bool tercUsado   [8]          = {};
    bool primeroUsado[NUM_GRUPOS] = {};
    int  numR16 = 0;

    for (int g = 0; g < NUM_GRUPOS && numR16 < 8; ++g)
    {
        iteraciones++;
        for (int t = 0; t < 8; ++t)
        {
            iteraciones++;
            if (tercUsado[t]) continue;
            if (tercGrupo[t] == g) continue;

            partidosR16[numR16] = Partido(*primeros[g], *terceros[t],
                                          "10/07/2026");
            primeroUsado[g]  = true;
            tercUsado[t]     = true;
            numR16++;
            break;
        }
    }

    bool segundoUsadoB[NUM_GRUPOS] = {};

    for (int g = 0; g < NUM_GRUPOS && numR16 < 12; ++g)
    {
        iteraciones++;
        if (primeroUsado[g]) continue;
        bool ok = false;
        for (int s = 8; s < NUM_GRUPOS; ++s)
        {
            iteraciones++;
            if (segundoUsadoB[s]) continue;
            if (segGrupo[s] == g) continue;
            partidosR16[numR16++] = Partido(*primeros[g], *segundosOrd[s],
                                            "10/07/2026");
            primeroUsado[g]  = true;
            segundoUsadoB[s] = true;
            ok = true;
            break;
        }
        if (!ok)
        {
            for (int s = 8; s < NUM_GRUPOS; ++s)
            {
                iteraciones++;
                if (segundoUsadoB[s]) continue;
                partidosR16[numR16++] = Partido(*primeros[g], *segundosOrd[s],
                                                "10/07/2026");
                primeroUsado[g]  = true;
                segundoUsadoB[s] = true;
                break;
            }
        }
    }

    bool mejSegUsado[8] = {};
    for (int i = 0; i < 8 && numR16 < 16; ++i)
    {
        iteraciones++;
        if (mejSegUsado[i]) continue;

        bool ok = false;
        for (int j = i+1; j < 8; ++j)
        {
            iteraciones++;
            if (mejSegUsado[j]) continue;
            if (segGrupo[i] == segGrupo[j]) continue;
            partidosR16[numR16++] = Partido(*segundosOrd[i], *segundosOrd[j],
                                            "10/07/2026");
            mejSegUsado[i] = true;
            mejSegUsado[j] = true;
            ok = true;
            break;
        }
        if (!ok)
        {
            for (int j = i+1; j < 8; ++j)
            {
                iteraciones++;
                if (mejSegUsado[j]) continue;
                partidosR16[numR16++] = Partido(*segundosOrd[i], *segundosOrd[j],
                                                "10/07/2026");
                mejSegUsado[i] = true;
                mejSegUsado[j] = true;
                break;
            }
        }
    }

    cout << "\n========================================" << endl;
    cout << "   CLASIFICADOS A R16" << endl;
    cout << "========================================" << endl;

    cout << "\nPrimeros de grupo:" << endl;
    for (int g=0;g<NUM_GRUPOS;++g)
        cout << "  " << char('A'+g) << "1: " << primeros[g]->getPais() << endl;

    cout << "\nSegundos de grupo:" << endl;
    for (int g=0;g<NUM_GRUPOS;++g)
        cout << "  " << char('A'+g) << "2: " << segundos[g]->getPais() << endl;

    cout << "\n8 mejores terceros clasificados:" << endl;
    for (int t=0;t<8;++t)
        cout << "  " << (t+1) << ": " << terceros[t]->getPais()
             << " (Grupo " << char('A'+tercGrupo[t]) << ")"
             << "  PTS:" << tercPTS[t]
             << "  DG:"  << tercDG[t]
             << "  GF:"  << tercGF[t] << endl;

    cout << "\n========================================" << endl;
    cout << "   PARTIDOS R16 (dieciseisavos)" << endl;
    cout << "========================================" << endl;
    for (int i=0;i<16;++i){
        iteraciones++;
        partidosR16[i].print();
    }
    if (numR16 != 16)
        cout << "ADVERTENCIA: solo se armaron " << numR16 << " partidos de R16\n";
}

void Torneo::simularR16()
{
    for (int i = 0; i < 16; ++i)
    {
        iteraciones++;
        partidosR16[i].simularPartido();

        Equipo* ganador = nullptr;
        if (partidosR16[i].getGolesEquipo1() == partidosR16[i].getGolesEquipo2())
            ganador = resolverEmpate(partidosR16[i]);
        else
            ganador = (partidosR16[i].getGolesEquipo1() >
                       partidosR16[i].getGolesEquipo2())
                          ? partidosR16[i].getEquipo1()
                          : partidosR16[i].getEquipo2();

        if (i % 2 == 1)
        {
            Equipo* ganadorAnterior =
                (partidosR16[i-1].getGolesEquipo1() >
                 partidosR16[i-1].getGolesEquipo2())
                    ? partidosR16[i-1].getEquipo1()
                    : partidosR16[i-1].getEquipo2();

            partidosR8[i/2] = Partido(*ganadorAnterior, *ganador, "10/07/2026");
        }
    }

    imprimirEtapa("RESULTADOS R16 - Dieciseisavos", partidosR16, 16);

    cout << "\n========================================" << endl;
    cout << "   PARTIDOS R8 (octavos) CONFIGURADOS"    << endl;
    cout << "========================================" << endl;
    for (int i = 0; i < 8; ++i){
        iteraciones++;
        partidosR8[i].print();
    }
}

void Torneo::simularR8()
{
    for (int i = 0; i < 8; ++i)
    {
        iteraciones++;
        partidosR8[i].simularPartido();

        Equipo* ganador = nullptr;
        if (partidosR8[i].getGolesEquipo1() == partidosR8[i].getGolesEquipo2())
            ganador = resolverEmpate(partidosR8[i]);
        else
            ganador = (partidosR8[i].getGolesEquipo1() >
                       partidosR8[i].getGolesEquipo2())
                          ? partidosR8[i].getEquipo1()
                          : partidosR8[i].getEquipo2();

        if (i % 2 == 1)
        {
            Equipo* ganadorAnterior =
                (partidosR8[i-1].getGolesEquipo1() >
                 partidosR8[i-1].getGolesEquipo2())
                    ? partidosR8[i-1].getEquipo1()
                    : partidosR8[i-1].getEquipo2();

            partidosQF[i/2] = Partido(*ganadorAnterior, *ganador, "10/07/2026");
        }
    }

    imprimirEtapa("RESULTADOS R8 - Octavos de final", partidosR8, 8);

    cout << "\n========================================" << endl;
    cout << "   PARTIDOS QF (cuartos) CONFIGURADOS"    << endl;
    cout << "========================================" << endl;
    for (int i = 0; i < 4; ++i){
        iteraciones++;
        partidosQF[i].print();
    }
}

void Torneo::simularQF()
{
    for (int i = 0; i < 4; ++i)
    {
        iteraciones++;
        partidosQF[i].simularPartido();

        Equipo* ganador = nullptr;
        if (partidosQF[i].getGolesEquipo1() == partidosQF[i].getGolesEquipo2())
            ganador = resolverEmpate(partidosQF[i]);
        else
            ganador = (partidosQF[i].getGolesEquipo1() >
                       partidosQF[i].getGolesEquipo2())
                          ? partidosQF[i].getEquipo1()
                          : partidosQF[i].getEquipo2();

        if (i % 2 == 1)
        {
            Equipo* ganadorAnterior =
                (partidosQF[i-1].getGolesEquipo1() >
                 partidosQF[i-1].getGolesEquipo2())
                    ? partidosQF[i-1].getEquipo1()
                    : partidosQF[i-1].getEquipo2();

            partidosSF[i/2] = Partido(*ganadorAnterior, *ganador, "10/07/2026");
        }
    }

    imprimirEtapa("RESULTADOS QF - Cuartos de final", partidosQF, 4);

    cout << "\n========================================" << endl;
    cout << "   PARTIDOS SF (semifinales) CONFIGURADOS" << endl;
    cout << "========================================"  << endl;
    for (int i = 0; i < 2; ++i){
        iteraciones++;
        partidosSF[i].print();
    }
}

void Torneo::simularSF()
{
    Equipo* perdedores[2] = {nullptr, nullptr};
    Equipo* ganadores[2]  = {nullptr, nullptr};

    for (int i = 0; i < 2; ++i)
    {
        iteraciones++;
        partidosSF[i].simularPartido();

        if (partidosSF[i].getGolesEquipo1() == partidosSF[i].getGolesEquipo2())
            ganadores[i] = resolverEmpate(partidosSF[i]);
        else
            ganadores[i] = (partidosSF[i].getGolesEquipo1() >
                            partidosSF[i].getGolesEquipo2())
                               ? partidosSF[i].getEquipo1()
                               : partidosSF[i].getEquipo2();

        perdedores[i] = (ganadores[i] == partidosSF[i].getEquipo1())
                            ? partidosSF[i].getEquipo2()
                            : partidosSF[i].getEquipo1();
    }

    partidosFinal[0]   = Partido(*ganadores[0],  *ganadores[1],  "10/07/2026");
    partidosTercero[0] = Partido(*perdedores[0], *perdedores[1], "10/07/2026");

    imprimirEtapa("RESULTADOS SF - Semifinales", partidosSF, 2);

    cout << "\n========================================" << endl;
    cout << "   PARTIDO 3ER PUESTO CONFIGURADO"        << endl;
    cout << "========================================" << endl;
    partidosTercero[0].print();

    cout << "\n========================================" << endl;
    cout << "   FINAL CONFIGURADA"                      << endl;
    cout << "========================================" << endl;
    partidosFinal[0].print();
}

void Torneo::simularFinal()
{
    partidosTercero[0].simularPartido();
    if (partidosTercero[0].getGolesEquipo1() ==
        partidosTercero[0].getGolesEquipo2())
        resolverEmpate(partidosTercero[0]);

    imprimirEtapa("RESULTADO 3ER PUESTO", partidosTercero, 1);

    partidosFinal[0].simularPartido();
    if (partidosFinal[0].getGolesEquipo1() ==
        partidosFinal[0].getGolesEquipo2())
        resolverEmpate(partidosFinal[0]);

    imprimirEtapa("RESULTADO FINAL", partidosFinal, 1);

    Equipo* campeon = (partidosFinal[0].getGolesEquipo1() >
                       partidosFinal[0].getGolesEquipo2())
                          ? partidosFinal[0].getEquipo1()
                          : partidosFinal[0].getEquipo2();

    Equipo* subcampeon = (campeon == partidosFinal[0].getEquipo1())
                             ? partidosFinal[0].getEquipo2()
                             : partidosFinal[0].getEquipo1();

    Equipo* tercero = (partidosTercero[0].getGolesEquipo1() >
                       partidosTercero[0].getGolesEquipo2())
                          ? partidosTercero[0].getEquipo1()
                          : partidosTercero[0].getEquipo2();

    Equipo* cuarto = (tercero == partidosTercero[0].getEquipo1())
                         ? partidosTercero[0].getEquipo2()
                         : partidosTercero[0].getEquipo1();

    cout << "\n========================================" << endl;
    cout << "   PODIO FINAL DEL MUNDIAL 2026"           << endl;
    cout << "========================================" << endl;
    cout << "  1er puesto: " << campeon->getPais()    << endl;
    cout << "  2do puesto: " << subcampeon->getPais() << endl;
    cout << "  3er puesto: " << tercero->getPais()    << endl;
    cout << "  4to puesto: " << cuarto->getPais()     << endl;
}

static void imprimirEtapa(const string& nombre, Partido* partidos, int n)
{
    cout << "\n========================================" << endl;
    cout << "   " << nombre << endl;
    cout << "========================================" << endl;
    for (int i = 0; i < n; ++i)
    {
        partidos[i].print();

        cout << "  Goleadores " << partidos[i].getEquipo1()->getPais() << ": ";
        for (int j = 0; j < partidos[i].getCantGoladoresEquipo1(); ++j)
            cout << partidos[i].getGoladoresEquipo1()[j] << " ";
        if (partidos[i].getCantGoladoresEquipo1() == 0) cout << "ninguno";
        cout << endl;

        cout << "  Goleadores " << partidos[i].getEquipo2()->getPais() << ": ";
        for (int j = 0; j < partidos[i].getCantGoladoresEquipo2(); ++j)
            cout << partidos[i].getGoladoresEquipo2()[j] << " ";
        if (partidos[i].getCantGoladoresEquipo2() == 0) cout << "ninguno";
        cout << endl;
    }
}

void Torneo::generarEstadisticas()
{
    cout << "\n========================================" << endl;
    cout << "   ESTADISTICAS FINALES DEL MUNDIAL 2026" << endl;
    cout << "========================================" << endl;


    Equipo* campeon = (partidosFinal[0].getGolesEquipo1() >
                       partidosFinal[0].getGolesEquipo2())
                          ? partidosFinal[0].getEquipo1()
                          : partidosFinal[0].getEquipo2();

    Equipo* subcampeon = (campeon == partidosFinal[0].getEquipo1())
                             ? partidosFinal[0].getEquipo2()
                             : partidosFinal[0].getEquipo1();

    Equipo* tercero = (partidosTercero[0].getGolesEquipo1() >
                       partidosTercero[0].getGolesEquipo2())
                          ? partidosTercero[0].getEquipo1()
                          : partidosTercero[0].getEquipo2();

    Equipo* cuarto = (tercero == partidosTercero[0].getEquipo1())
                         ? partidosTercero[0].getEquipo2()
                         : partidosTercero[0].getEquipo1();

    cout << "\n--- 1. Ranking final ---" << endl;
    cout << "  1er puesto: " << campeon->getPais()    << endl;
    cout << "  2do puesto: " << subcampeon->getPais() << endl;
    cout << "  3er puesto: " << tercero->getPais()    << endl;
    cout << "  4to puesto: " << cuarto->getPais()     << endl;

    cout << "\n--- 2. Maximo goleador del campeon ("
         << campeon->getPais() << ") ---" << endl;

    int maxGoles    = -1;
    int maxCamiseta = -1;

    for (int j = 0; j < campeon->getCantJugadores(); ++j)
    {
        int goles = campeon->getJugadorRef(j).gethistorico().getcantGoles();
        if (goles > maxGoles)
        {
            maxGoles    = goles;
            maxCamiseta = campeon->getJugadorRef(j).getnumCamiseta();
        }
    }
    cout << "  Camiseta: " << maxCamiseta
         << "  Goles: "    << maxGoles << endl;


    cout << "\n--- 3. Tres mayores goleadores del mundial ---" << endl;

    int    top3Goles   [3] = {-1, -1, -1};
    int    top3Camiseta[3] = {-1, -1, -1};
    string top3Pais    [3] = {"",  "",  ""};

    for (int i = 0; i < totalEquipos; ++i)
    {
        iteraciones++;
        for (int j = 0; j < equipos[i].getCantJugadores(); ++j)
        {
            iteraciones++;
            Jugador& jug = equipos[i].getJugadorRef(j);
            int g = jug.gethistorico().getcantGoles();
            int c = jug.getnumCamiseta();

            for (int k = 0; k < 3; ++k)
            {
                iteraciones++;
                if (g > top3Goles[k])
                {
                    for (int m = 2; m > k; --m)
                    {
                        iteraciones++;
                        top3Goles   [m] = top3Goles   [m-1];
                        top3Camiseta[m] = top3Camiseta[m-1];
                        top3Pais    [m] = top3Pais    [m-1];
                    }
                    top3Goles   [k] = g;
                    top3Camiseta[k] = c;
                    top3Pais    [k] = equipos[i].getPais();
                    break;
                }
            }
        }
    }

    for (int k = 0; k < 3; ++k)
    {
        iteraciones++;
        cout << "  " << (k+1) << ". "
             << top3Pais[k] << " - Camiseta: " << top3Camiseta[k]
             << "  Goles: "  << top3Goles[k]   << endl;
    }


    cout << "\n--- 4. Equipo con mas goles historicos ---" << endl;

    int    maxGolesEq     = -1;
    string maxGolesEqPais = "";

    for (int i = 0; i < totalEquipos; ++i)
    {
        iteraciones++;
        int gf = equipos[i].getHistorico().getGolesFavor();
        if (gf > maxGolesEq)
        {
            maxGolesEq     = gf;
            maxGolesEqPais = equipos[i].getPais();
        }
    }
    cout << "  " << maxGolesEqPais
         << "  Goles historicos: " << maxGolesEq << endl;


    cout << "\n--- 5. Confederacion dominante por etapa ---" << endl;


    Partido* etapas[3]   = { partidosR16, partidosR8, partidosQF };
    int      tamanos[3]  = { 16, 8, 4 };
    string   nombres[3]  = { "R16", "R8", "R4" };

    for (int e = 0; e < 3; ++e)
    {
        iteraciones++;
        string confNombres[12];
        int    confConteo [12] = {};
        int    numConf = 0;

        for (int i = 0; i < tamanos[e]; ++i)
        {
            iteraciones++;
            for (int q = 0; q < 2; ++q)
            {
                iteraciones++;
                string conf = (q == 0)
                ? etapas[e][i].getEquipo1()->getConfederacion()
                : etapas[e][i].getEquipo2()->getConfederacion();

                bool encontrado = false;
                for (int k = 0; k < numConf; ++k)
                {
                    iteraciones++;
                    if (confNombres[k] == conf)
                    {
                        confConteo[k]++;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado)
                {
                    confNombres[numConf] = conf;
                    confConteo [numConf] = 1;
                    numConf++;
                }
            }
        }

        int    maxC    = -1;
        string maxConf = "";
        for (int k = 0; k < numConf; ++k)
        {
            iteraciones++;
            if (confConteo[k] > maxC)
            {
                maxC    = confConteo[k];
                maxConf = confNombres[k];
            }
        }

        cout << "  " << nombres[e] << ": " << maxConf << endl;
    }

}


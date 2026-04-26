#include "Torneo.h"
#include"ArchivoEquipo.h"
#include<iostream>
using namespace std;


Torneo::Torneo():totalEquipos(0),in_b1(0),in_b2(0),in_b3(0),in_b4(0)
{}

bool Torneo::cargarEquiposDesdeArchivo(const string &nombreArchivo)
{
    totalEquipos=cargarTodosLosEquipos(equipos,NUM_EQUIPOS,nombreArchivo);
    return totalEquipos>0;
}

void Torneo::clasificarEnBombos()
{
    for(int i=0;i<totalEquipos;++i){
        unsigned short int ran=equipos[i].getRankingFIFA();
        string pais=equipos[i].getPais();
        bool esUSA=(pais=="United States");
        if(esUSA){
            bombo1[in_b1++]=i;
        }
        else if(ran>=RMI_BOMBO1 && ran<= RMA_BOMBO1){
            bombo1[in_b1++]=i;
        }
        else if(ran>=RMI_BOMBO2 && ran<= RMA_BOMBO2){
            bombo2[in_b2++]=i;
        }
        else if(ran>=RMI_BOMBO3 && ran<= RMA_BOMBO3){
            bombo3[in_b3++]=i;
        }
        else if(ran>=RMI_BOMBO4 && ran<= RMA_BOMBO4){
            bombo4[in_b4++]=i;
        }
        else{
            cout<<"El equipo: "<<pais<<" con ranking"<<ran<<" esta fuera de rango de bombos"<<endl;
        }
    }
}

void Torneo::printBombos() const
{
    cout<<"----BOMBO 1----"<<endl;
    for (int i=0; i<in_b1;i++){
        int in_equipo=bombo1[i];
        cout<<equipos[in_equipo].getRankingFIFA()<<"-"
             <<equipos[in_equipo].getPais()<<"-"
             <<equipos[in_equipo].getConfederacion()<<endl;
    }
    cout<<"----BOMBO 2----"<<endl;
    for (int i=0; i<in_b2;i++){
        int in_equipo=bombo2[i];
        cout<<equipos[in_equipo].getRankingFIFA()<<"-"
             <<equipos[in_equipo].getPais()<<"-"
             <<equipos[in_equipo].getConfederacion()<<endl;
    }
    cout<<"----BOMBO 3----"<<endl;
    for (int i=0; i<in_b3;i++){
        int in_equipo=bombo3[i];
        cout<<equipos[in_equipo].getRankingFIFA()<<"-"
             <<equipos[in_equipo].getPais()<<"-"
             <<equipos[in_equipo].getConfederacion()<<endl;
    }
    cout<<"----BOMBO 4----"<<endl;
    for (int i=0; i<in_b4;i++){
        int in_equipo=bombo4[i];
        cout<<equipos[in_equipo].getRankingFIFA()<<"-"
             <<equipos[in_equipo].getPais()<<"-"
             <<equipos[in_equipo].getConfederacion()<<endl;
    }
}


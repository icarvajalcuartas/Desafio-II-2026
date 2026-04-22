#include <iostream>
#include"HistoricoJugador.h"
#include"archivos.h"
#include"Jugador.h"
using namespace std;

int main()
{
    // cout << "Hello World!" << endl;
    // HistoricoJugador stats= HistoricoJugador();
    // stats=HistoricoJugador();
    // cout<< "Partidos Jugados:"<<stats.getpartJugados()<<endl;
    // cout<<"Cantidad de goles: "<<stats.getcantGoles()<<endl;
    // cout<<"Cantidad de minutos jugados: "<<stats.getminJugados()<<endl;
    // cout<<"Asistencias: "<<stats.getasistencias()<<endl;
    // cout<<"Tarjetas amarillas: "<<stats.gettarAmarillas()<<endl;
    // cout<<"Tarjetas rojas: "<<stats.gettarRojas()<<endl;
    // cout<<"Faltas acumuladas: "<<stats.getfaltAcumuladas()<<endl;
    // cout<<"Tamaño de la clase Historico: "<<sizeof(stats)<<endl;

    // stats.actualizarHistorico(20,2,3,4,5);
    // stats.actualizarHistorico(20,2,3,4,5);
    // cout<< "Partidos Jugados:"<<stats.getpartJugados()<<endl;
    // cout<<"Cantidad de goles: "<<stats.getcantGoles()<<endl;
    // cout<<"Cantidad de minutos jugados: "<<stats.getminJugados()<<endl;
    // cout<<"Asistencias: "<<stats.getasistencias()<<endl;
    // cout<<"Tarjetas amarillas: "<<stats.gettarAmarillas()<<endl;
    // cout<<"Tarjetas rojas: "<<stats.gettarRojas()<<endl;
    // cout<<"Faltas acumuladas: "<<stats.getfaltAcumuladas()<<endl;
    // cout<<"Tamaño de la clase Historico: "<<sizeof(stats)<<endl;

    // // actualizarArchivo(stats);
    // unsigned short int partJugados=0;
    unsigned short int cantGoles=2;
    unsigned short int minJugados=2;
    //unsigned short int asistencias=7;
    unsigned short int tarAmarillas=2;
    unsigned short int tarRojas=2;
    unsigned short int faltAcumuladas=2;
    unsigned short int num=66;

    // Jugador jugador(num);
    // jugador.sethistorico(cantGoles,minJugados,tarAmarillas,tarRojas,faltAcumuladas);
    // actualizarArchivo(jugador.gethistorico(),num);
    Jugador jugador(1);
    jugador.sethistorico(cantGoles,minJugados,tarAmarillas,tarRojas,faltAcumuladas);
    actualizarArchivo(jugador.gethistorico(),1);

    // for (int i=0;i<100;i++){
    //     jugador.sethistorico(cantGoles,minJugados,tarAmarillas,tarRojas,faltAcumuladas);
    //     actualizarArchivo(jugador.gethistorico(),100);
    // }

    // Jugador jugador(1);
    // jugador.sethistorico(cantGoles,minJugados,tarAmarillas,tarRojas,faltAcumuladas);
    // actualizarArchivo(jugador.gethistorico(),1);
    // jugador.sethistorico(cantGoles,minJugados,tarAmarillas,tarRojas,faltAcumuladas);
    // actualizarArchivo(jugador.gethistorico(),1);
    // jugador.sethistorico(cantGoles,minJugados,tarAmarillas,tarRojas,faltAcumuladas);
    // actualizarArchivo(jugador.gethistorico(),1);
    return 0;
}

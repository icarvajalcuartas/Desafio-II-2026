#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <iostream>
#include <fstream>
#include <string>
#include"HistoricoJugador.h"
using namespace std;

int actualizarArchivo(const HistoricoJugador &estadisticas, unsigned short int numeroCamiseta);
string crearLineaJugador(unsigned short int numCamiseta,unsigned short int partJugados,unsigned short int cantGoles,unsigned short int minJugados,unsigned short int asistencias,unsigned short int tarAmarillas,unsigned short int tarRojas,unsigned short int faltAcumuladas);
bool compararPrimeraColumna(const string& linea, unsigned short int numCamiseta,int &it);
void actualizarArchivoCSV(const string& nombreArchivo,unsigned short int numCamiseta, unsigned short int partJugados, unsigned short int cantGoles, unsigned short int minJugados, unsigned short int asistencias, unsigned short int tarAmarillas, unsigned short int tarRojas,unsigned short int faltAcumuladas, int &it);

#endif // ARCHIVOS_H

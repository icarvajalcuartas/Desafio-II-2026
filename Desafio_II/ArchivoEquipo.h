#ifndef ARCHIVOEQUIPO_H
#define ARCHIVOEQUIPO_H

#include <iostream>
#include <fstream>
#include <string>
#include "Equipo.h"
#include "HistoricoEquipo.h"
using namespace std;

void leerHistoricoEquipo(Equipo &equipo, const string &lineaCSV);
void cargarEquipoDesdeArchivo(Equipo &equipo, const string &nombreArchivo, const string &paisBuscado);
string crearLineaHistoricoEquipo(const Equipo &equipo);
void actualizarHistoricoEquipoArchivo(const Equipo &equipo, const string &nombreArchivo);
int cargarTodosLosEquipos(Equipo equipos[], int maxEquipos, const string &nombreArchivo);

#endif // ARCHIVOEQUIPO_H

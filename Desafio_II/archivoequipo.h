#ifndef ARCHIVOSEQUIPO_H
#define ARCHIVOSEQUIPO_H

#include <iostream>
#include <fstream>
#include <string>
#include "Equipo.h"
using namespace std;

void leerHistoricoEquipo(Equipo &equipo, const string &lineaCSV);
void cargarEquipoDesdeArchivo(Equipo &equipo, const string &nombreArchivo, const string &paisBuscado);

#endif // ARCHIVOSEQUIPO_H
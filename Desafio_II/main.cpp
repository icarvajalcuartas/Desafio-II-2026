#include <iostream>
#include"HistoricoJugador.h"
#include"archivos.h"
#include"Jugador.h"
#include "Equipo.h"
#include "ArchivoEquipo.h"
#include"Torneo.h"
using namespace std;

//const int num_equipos = 48;
int main()
{

    // Equipo equipos[num_equipos];
    // int totalEquipos = cargarTodosLosEquipos(equipos,num_equipos,"selecciones_clasificadas_mundial.csv");
    // cout << "Se cargaron " << totalEquipos << " equipos.\n\n";
    // int iteraciones=0;
    // for (int i = 0; i < totalEquipos; ++i) {
    //     cout << "Equipo #" << (i + 1) << ":\n";
    //     actualizarHistoricoEquipoArchivo(equipos[i],"Historico_equipos.csv");
    //     //equipos[i].print();
    //     for(int n=0;n<26;n++){
    //         iteraciones=actualizarArchivo(equipos[i].getJugador(n).gethistorico(),n,equipos[i].getPais());
    //     }
    //     cout << "-----------------------------\n";
    // }
    // cout<<"Cantidad de iteraciones: "<<iteraciones<<endl;

    Torneo mundial;

    if (!mundial.cargarEquiposDesdeArchivo("selecciones_clasificadas_mundial.csv")) {
        cout << "No se pudieron cargar los equipos.\n";
        return 1;
    }

    mundial.clasificarEnBombos();
    mundial.printBombos();
    return 0;
}



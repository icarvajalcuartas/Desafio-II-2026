#include <iostream>
#include"HistoricoJugador.h"
#include"archivos.h"
#include"Jugador.h"
#include "Equipo.h"
#include "ArchivoEquipo.h"
#include"Torneo.h"
#include<ctime>
using namespace std;

int main()
{

    Torneo mundial;

    srand(time(0));
    if (!mundial.cargarEquiposDesdeArchivo("selecciones_clasificadas_mundial.csv")) {
        cout << "No se pudieron cargar los equipos.\n";
        return 1;
    }

    cout<<"*********ETAPA 2**********"<<endl;
    mundial.clasificarEnBombos();
    //mundial.printBombos();
    if(!mundial.crearGrupos()){
        cout<<"No se pudieron crear los grupos"<<endl;
    }
    mundial.printGrupos();
    if (!mundial.configurarPartidosGrupos())
    {
        cout << "No se pudo configurar el calendario cumpliendo restricciones.\n";
        return 1;
    }
    cout << "Iteraciones acumuladas: " << mundial.getIteraciones() << endl;

    cout<<"*********ETAPA 3**********"<<endl;
    //mundial.printPartidosGrupos();
    mundial.simularFaseGrupos();
    mundial.clasificarYArmarR16();
    mundial.simularR16();
    mundial.simularR8();
    mundial.simularQF();
    mundial.simularSF();
    mundial.simularFinal();
    cout << "Iteraciones acumuladas: " << mundial.getIteraciones() << endl;

    cout<<"*********ETAPA 4**********"<<endl;
    mundial.generarEstadisticas();
    cout << "Iteraciones acumuladas: " << mundial.getIteraciones() << endl;

    cout<<"*********ETAPA 5**********"<<endl;
    long long memoria = 0;
    memoria += sizeof(Torneo);
    memoria += NUM_EQUIPOS * 26 * sizeof(Jugador);
    cout << "Memoria total aproximada: " << memoria << " bytes" << endl;
    cout << "Iteraciones totales: " << mundial.getIteraciones() << endl;

    return 0;
}



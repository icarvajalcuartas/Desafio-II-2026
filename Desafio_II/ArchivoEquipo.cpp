#include "ArchivoEquipo.h"
#include <fstream>

void leerHistoricoEquipo(Equipo &equipo, const string &lineaCSV)
{
    string dato = "";
    string columnas[10];
    int j = 0;

    for (unsigned int i = 0; i < lineaCSV.size(); i++) {
        if (lineaCSV[i] == ';') {
            columnas[j] = dato;
            j++;
            dato = "";
        }
        else {
            dato += lineaCSV[i];
        }
    }
    columnas[j] = dato;

    equipo.rankingFIFA = (unsigned short int)stoi(columnas[0]);
    equipo.pais = columnas[1];
    equipo.directorTecnico = columnas[2];
    equipo.federacion = columnas[3];
    equipo.confederacion = columnas[4];

    HistoricoEquipo h;
    h.setGolesFavor((unsigned short int)stoi(columnas[5]));
    h.setGolesContra((unsigned short int)stoi(columnas[6]));
    h.setPartidosGanados((unsigned short int)stoi(columnas[7]));
    h.setPartidosEmpatados((unsigned short int)stoi(columnas[8]));
    h.setPartidosPerdidos((unsigned short int)stoi(columnas[9]));
    h.setTarjetasAmarillas(0);
    h.setTarjetasRojas(0);
    h.setFaltas(0);

    equipo.historico = h;

}

string crearLineaEquipo(const Equipo &equipo)
{
    HistoricoEquipo h = equipo.historico;

    string linea = "";

    linea += to_string(equipo.rankingFIFA) + ";";
    linea += equipo.pais + ";";
    linea += equipo.directorTecnico + ";";
    linea += equipo.federacion + ";";
    linea += equipo.confederacion + ";";
    linea += to_string(h.getGolesFavor()) + ";";
    linea += to_string(h.getGolesContra()) + ";";
    linea += to_string(h.getPartidosGanados()) + ";";
    linea += to_string(h.getPartidosEmpatados()) + ";";
    linea += to_string(h.getPartidosPerdidos());

    return linea;
}

void cargarEquipoDesdeArchivo(Equipo &equipo, const string &nombreArchivo, const string &paisBuscado)
{
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cout << "\n No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    getline(archivo, linea);
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        string paisLeido = "";
        unsigned int i = 0;

        while (i < linea.size() && linea[i] != ';') {
            string dato = "";
            string columnas[10];
            int j = 0;

            for(unsigned int i = 0; i < linea.size(); i++){
                if(linea[i] == ';'){
                    columnas[j] = dato;
                    j++;
                    dato = "";
                }
                else{
                    dato += linea[i];
                }
            }
            columnas[j] = dato;

            if(columnas[1] == paisBuscado){
                leerHistoricoEquipo(equipo, linea);
                archivo.close();
                return;
            }
        }

    cout << "\n No se encontro el equipo " << paisBuscado << " en el archivo." << endl;
    archivo.close();
    }
}

void actualizarEquipoEnArchivo(const Equipo &equipo, const string &nombreArchivo){
    ifstream archivo(nombreArchivo);
    string lineas[60];
    string linea;
    int totalLineas = 0;

    if(!archivo.is_open()){
        cout << "\n No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    while(getline(archivo, linea) && totalLineas < 60){
        lineas[totalLineas] = linea;
        totalLineas++;
    }

    archivo.close();

    for(int i = 2; i < totalLineas; i++){
        string dato = "";
        string columnas[10];
        int j = 0;

        for(unsigned int k = 0; k < lineas[i].size(); k++){
            if(lineas[i][k] == ';'){
                columnas[j] = dato;
                j++;
                dato = "";
            }
            else{
                dato += lineas[i][k];
            }
        }
        columnas[j] = dato;

        if(columnas[1] == equipo.pais){
            lineas[i] = crearLineaEquipo(equipo);
            break;
        }
    }

    ofstream salida(nombreArchivo, ios::trunc);

    for(int i = 0; i < totalLineas; i++){
        salida << lineas[i] << endl;
    }

    salida.close();
}

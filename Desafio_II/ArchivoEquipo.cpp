#include "ArchivoEquipo.h"
#include"Equipo.h"
#include "HistoricoEquipo.h"
#include <fstream>
#include <string>
static bool empiezaConDigito(const string& s);

void leerHistoricoEquipo(Equipo &equipo, const string &lineaCSV)
{
    string dato = "";
    string columnas[15];
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
    for (int k = 0; k <= 9; ++k)
    {
        if (!columnas[k].empty() && columnas[k].back() == '\r')
        {
            columnas[k].pop_back();
        }
    }
    if (columnas[0].size() >= 3 &&
        (unsigned char)columnas[0][0] == 0xEF &&
        (unsigned char)columnas[0][1] == 0xBB &&
        (unsigned char)columnas[0][2] == 0xBF)
    {
        columnas[0] = columnas[0].substr(3);
    }
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
    equipo.setHistorico(h);

}

string crearLineaHistoricoEquipo(const Equipo &equipo)
{
    HistoricoEquipo h = equipo.historico;

    string linea = "";

    linea += to_string(equipo.rankingFIFA) + ";";
    linea += equipo.pais + ";";
    linea += to_string(h.getGolesFavor()) + ";";
    linea += to_string(h.getGolesContra()) + ";";
    linea += to_string(h.getPartidosGanados()) + ";";
    linea += to_string(h.getPartidosEmpatados()) + ";";
    linea += to_string(h.getPartidosPerdidos())+";";
    linea += to_string(h.getTarjetasAmarillas()) + ";";
    linea += to_string(h.getTarjetasRojas()) + ";";
    linea += to_string(h.getFaltas());

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


    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') { linea.pop_back(); }
        if (!empiezaConDigito(linea)) { continue; }
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

void actualizarHistoricoEquipoArchivo(const Equipo &equipo, const string &nombreArchivo){
    ifstream archivo(nombreArchivo);
    const int filasMax=100;
    string lineas[filasMax];
    string linea;
    int totalLineas = 0;

    if(archivo.is_open()){
        while(getline(archivo, linea) && totalLineas < filasMax){
            lineas[totalLineas] = linea;
            totalLineas++;
        }

        archivo.close();
    }

    bool encontrado=false;

    for(int i = 1; i < totalLineas; i++){
        string &l = lineas[i];
        unsigned int len = (unsigned int)l.size();
        string paisLeido = "";
        unsigned int j = 0;
        while (j < len && l[j] != ';') {
            j++;
        }
        if (j < len && l[j] == ';') j++;
        while (j < len && l[j] != ';') {
            paisLeido += l[j];
            j++;
        }
        if(paisLeido == equipo.pais){
            lineas[i] = crearLineaHistoricoEquipo(equipo);
            encontrado = true;
            break;
        }
    }
    if(!encontrado){
        if(totalLineas == 0){
            lineas[totalLineas] = "Ranking FIFA;Pais;GolesFavor;GolesContra;PartidosGanados;PartidosEmpatados;PartidosPerdidos;TarjetasAmarillas;TarjetasRojas;Faltas";
            totalLineas++;
        }

        if(totalLineas < filasMax){
            lineas[totalLineas] = crearLineaHistoricoEquipo(equipo);
            totalLineas++;
        }
    }


    ofstream salida(nombreArchivo, ios::trunc);

    for(int i = 0; i < totalLineas; i++){
        salida << lineas[i] << endl;
    }

    salida.close();
}

static bool empiezaConDigito(const string& s)
{
    int i = 0;
    while (i <(int)s.size() && (s[i]== ' ' || s[i]== '\t')) {
        i++;
    }
    return (i <(int)s.size() && s[i]>= '0' && s[i]<= '9');
}

int cargarTodosLosEquipos(Equipo equipos[], int maxEquipos, const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    string linea;
    int total = 0;

    if (!archivo.is_open()) {
        cout << "\n No se pudo abrir el archivo " << nombreArchivo << endl;
        return 0;
    }


    while (getline(archivo, linea) && total < maxEquipos) {
        if (!linea.empty() && linea.back() == '\r') { linea.pop_back(); }
        if (!empiezaConDigito(linea)) { continue; }
        leerHistoricoEquipo(equipos[total], linea);
        total++;
    }

    archivo.close();
    return total;

}


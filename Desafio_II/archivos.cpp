#include "archivos.h"
#include <fstream>
#include <string>


string crearLineaJugador(unsigned short int numCamiseta,unsigned short int partJugados,unsigned short int cantGoles,unsigned short int minJugados,unsigned short int asistencias,unsigned short int tarAmarillas,unsigned short int tarRojas,unsigned short int faltAcumuladas){
    string resultado = "Nombre"+to_string(numCamiseta)+";"+"Apellido"+to_string(numCamiseta)+";"+
                       to_string(numCamiseta) + ";" +to_string(partJugados) + ";" +
                       to_string(cantGoles) + ";" +to_string(minJugados) + ";" +
                       to_string(asistencias) + ";" +to_string(tarAmarillas) + ";" +
                       to_string(tarRojas) + ";" +to_string(faltAcumuladas);

    return resultado;
}
bool compararPrimeraColumna(const string& linea, unsigned short int numCamiseta,int&it){
    int i = 0;
    string columna = "";
    while (i < (int)linea.size() && linea[i] != ';') {
        columna += linea[i+6];
        ++i;
        it+=1;
    }
    unsigned short int numeroLinea = static_cast<unsigned short int>(stoi(columna));
    return numeroLinea == numCamiseta;
}
void actualizarArchivoCSV(const string& nombreArchivo,unsigned short int numCamiseta, unsigned short int partJugados, unsigned short int cantGoles, unsigned short int minJugados, unsigned short int asistencias, unsigned short int tarAmarillas, unsigned short int tarRojas,unsigned short int faltAcumuladas, int &it){
    ifstream archivo(nombreArchivo);
    const int filasMax = 1050;
    string* lineas[filasMax];
    int totalLineas = 0;
    string temp;

    while (getline(archivo, temp) && totalLineas < filasMax) {
        lineas[totalLineas++] = new string(temp);
        it+=1;
    }

    archivo.close();

    bool encontrada = false;
    for (int i = 1; i < totalLineas; ++i) {
        it+=1;
        if (compararPrimeraColumna(*lineas[i], numCamiseta,it)) {
            delete lineas[i];
            lineas[i] = new string(crearLineaJugador(
                numCamiseta, partJugados, cantGoles,
                minJugados, asistencias, tarAmarillas,
                tarRojas, faltAcumuladas));
            encontrada = true;
            break;
        }
    }

    if (!encontrada) {
        if (totalLineas < filasMax) {
            lineas[totalLineas++] = new string(crearLineaJugador(
                numCamiseta, partJugados, cantGoles,
                minJugados, asistencias, tarAmarillas,
                tarRojas, faltAcumuladas));
        } else {
            cout << "Error: Límite máximo de líneas alcanzado." << endl;
        }
    }

    ofstream cerrarArchivo(nombreArchivo, ios::trunc);
    for (int i = 0; i < totalLineas; ++i) {
        cerrarArchivo << *lineas[i] << endl;
        delete lineas[i];
        it+=1;
    }
    cerrarArchivo.close();
}
void actualizarArchivo(const HistoricoJugador& estadisticas,unsigned short int numeroCamiseta)
{
    string archivo="Historico_jugadores.CSV";
    int iteraciones=0;
    actualizarArchivoCSV(archivo,numeroCamiseta,estadisticas.getpartJugados(),estadisticas.getcantGoles(),estadisticas.getminJugados(),estadisticas.getasistencias(),estadisticas.gettarAmarillas(),estadisticas.gettarRojas(),estadisticas.getfaltAcumuladas(),iteraciones);
    cout<<"iteraciones: "<<iteraciones<<endl;
}

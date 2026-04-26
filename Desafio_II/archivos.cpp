#include "archivos.h"
#include <fstream>
#include <string>

static const string encabezado_Jugadores="Nombre Jugador;Apellido Jugador;Numero de camiseta;Cantidad de partidos jugados;Cantidad de asistencias;Cantidad de tarjetas amarillas;Cantidad de tarjetas rojas;Cantidad de faltas acumuladas";
string crearLineaJugador(unsigned short int numCamiseta,unsigned short int partJugados,
                         unsigned short int cantGoles,unsigned short int minJugados,
                         unsigned short int asistencias,unsigned short int tarAmarillas,
                         unsigned short int tarRojas,unsigned short int faltAcumuladas){
    string resultado = "Nombre"+to_string(numCamiseta)+";"+"Apellido"+to_string(numCamiseta)+";"+
                       to_string(numCamiseta) + ";" +to_string(partJugados) + ";" +
                       to_string(cantGoles) + ";" +to_string(minJugados) + ";" +
                       to_string(asistencias) + ";" +to_string(tarAmarillas) + ";" +
                       to_string(tarRojas) + ";" +to_string(faltAcumuladas);

    return resultado;
}
unsigned short int extraerNumeroCamiseta(const string &linea, int &it){
    int len = (int)linea.size();
    int contadorPuntos=0;
    int inicioNum=-1;
    int finNum=-1;

    for (int i=0;i<len;++i) {
        it ++;
        if (linea[i]==';') {
            contadorPuntos++;
            if (contadorPuntos==2) {
                inicioNum=i+1;
            } else if (contadorPuntos==3) {
                finNum=i-1;
                break;
            }
        }
    }

    if (inicioNum!= -1&&finNum==-1) {
        finNum = len - 1;
    }

    if (inicioNum==-1||finNum<inicioNum) {
        return 0;
    }

    string numStr="";
    for (int i=inicioNum;i<=finNum;++i) {
        numStr+=linea[i];
    }

    return (unsigned short int)stoi(numStr);
}
bool insertarLinea(string* lineas[], int &totalLineas, int filasMax, int pos, const string &contenido)
{
    if (totalLineas >= filasMax) return false;
    for (int i = totalLineas; i > pos; --i) {
        lineas[i] = lineas[i - 1];
    }
    lineas[pos] = new string(contenido);
    totalLineas++;
    return true;
}


void actualizarArchivoCSV(const string& nombreArchivo, const string &equipo,unsigned short int numCamiseta,
                          unsigned short int partJugados, unsigned short int cantGoles,
                          unsigned short int minJugados, unsigned short int asistencias,
                          unsigned short int tarAmarillas, unsigned short int tarRojas,
                          unsigned short int faltAcumuladas, int &it){
    ifstream archivo(nombreArchivo);
    const int filasMax = 2000;
    string* lineas[filasMax];
    int totalLineas = 0;
    string temp;

    while (getline(archivo, temp) && totalLineas < filasMax) {
        lineas[totalLineas++] = new string(temp);
        it++;
    }

    archivo.close();

    if(totalLineas==0){
        lineas[totalLineas++]=new string(encabezado_Jugadores);
    }

    string lineaEquipoBuscada ="equipo;"+equipo+";";
    int idxEquipo=-1;

    for (int i=0;i<totalLineas;++i) {
        it++;
        string &l=*lineas[i];
        int lenBus=(int)lineaEquipoBuscada.size();
        if ((int)l.size()>=lenBus) {
            bool coincide=true;
            for (int j=0;j<lenBus;++j) {
                it++;
                if (l[j]!=lineaEquipoBuscada[j]) {
                    coincide = false;
                    break;
                }
            }
            if (coincide) {
                idxEquipo=i;
                break;
            }
        }
    }
    if (idxEquipo==-1) {

        if (totalLineas+3>filasMax) {
            cout << "Error: limite maximo de lineas alcanzado." << endl;
        } else {
            lineas[totalLineas++] = new string("equipo;" + equipo + ";;;;;");
            lineas[totalLineas++] = new string(encabezado_Jugadores);
            lineas[totalLineas++] = new string(
                crearLineaJugador(numCamiseta, partJugados, cantGoles,
                                  minJugados, asistencias,
                                  tarAmarillas, tarRojas, faltAcumuladas)
                );
        }
    } else {
        int idxEncabezadoJug=idxEquipo+1;

        bool hayEncabezado = (idxEncabezadoJug<totalLineas &&
                              *lineas[idxEncabezadoJug]==encabezado_Jugadores);

        if (!hayEncabezado) {
            if (!insertarLinea(lineas, totalLineas, filasMax, idxEncabezadoJug, encabezado_Jugadores)) {
                cout << "Error: limite maximo de lineas alcanzado al insertar encabezado." << endl;
            }
        }

        idxEncabezadoJug=idxEquipo+1;
        int idxInicioJugadores=idxEncabezadoJug+1;

        int idxFinBloque=totalLineas;
        for (int i=idxInicioJugadores;i < totalLineas; ++i) {
            it++;
            string &l = *lineas[i];
            if (l.size() >= 7 &&
                l[0] == 'e' && l[1] == 'q' && l[2] == 'u' &&
                l[3] == 'i' && l[4] == 'p' && l[5] == 'o' &&
                l[6] == ';')
            {
                idxFinBloque = i;
                break;
            }
        }

        bool encontrado = false;
        for (int i = idxInicioJugadores; i < idxFinBloque; ++i) {
            it++;
            unsigned short int numLinea = extraerNumeroCamiseta(*lineas[i],it);
            if (numLinea == numCamiseta) {
                delete lineas[i];
                lineas[i] = new string(
                    crearLineaJugador(numCamiseta, partJugados, cantGoles,
                                      minJugados, asistencias,
                                      tarAmarillas, tarRojas, faltAcumuladas)
                    );
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            if (!insertarLinea(lineas, totalLineas, filasMax, idxFinBloque,
                               crearLineaJugador(numCamiseta, partJugados, cantGoles,
                                                 minJugados, asistencias,
                                                 tarAmarillas, tarRojas, faltAcumuladas)))
            {
                cout << "Error: limite maximo de lineas alcanzado al insertar jugador." << endl;
            }
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
int actualizarArchivo(const HistoricoJugador& estadisticas,unsigned short int numeroCamiseta,const string &equipo)
{
    string archivo="Historico_jugadores.CSV";
    int iteraciones=0;
    actualizarArchivoCSV(archivo,equipo,numeroCamiseta,
                         estadisticas.getpartJugados(),estadisticas.getcantGoles(),
                         estadisticas.getminJugados(),estadisticas.getasistencias(),
                         estadisticas.gettarAmarillas(),estadisticas.gettarRojas(),estadisticas.getfaltAcumuladas(),
                         iteraciones);
    //cout<<"iteraciones: "<<iteraciones<<endl;
    return iteraciones;
}

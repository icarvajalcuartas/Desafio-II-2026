#include "archivoEquipo.h"

void leerHistoricoEquipo(Equipo &equipo, const string &lineaCSV)
{
    string dato="";
    string columnas[15];
    int j=0;

    for(unsigned int i=0; i<lineaCSV.size(); i++){
        if(lineaCSV[i]==';'){
            columnas[j]=dato;
            j++;
            dato="";
        }
        else{
            dato+=lineaCSV[i];
        }
    }
    columnas[j]=dato;

   //Ejemplo

    equipo.setPais(columnas[0]);
    equipo.setFederacion(columnas[1]);
    equipo.setConfederacion(columnas[2]);
    equipo.setDirectorTecnico(columnas[3]);
    equipo.setRankingFIFA((unsigned short int)stoi(columnas[4]));
    equipo.setGolesFavor((unsigned short int)stoi(columnas[5]));
    equipo.setGolesContra((unsigned short int)stoi(columnas[6]));
    equipo.setPartidosGanados((unsigned short int)stoi(columnas[7]));
    equipo.setPartidosEmpatados((unsigned short int)stoi(columnas[8]));
    equipo.setPartidosPerdidos((unsigned short int)stoi(columnas[9]));
    equipo.setTarjetasAmarillas((unsigned short int)stoi(columnas[10]));
    equipo.setTarjetasRojas((unsigned short int)stoi(columnas[11]));
    equipo.setFaltas((unsigned short int)stoi(columnas[12]));
}

void cargarEquipoDesdeArchivo(Equipo &equipo, const string &nombreArchivo, const string &paisBuscado)
{
    ifstream archivo(nombreArchivo);
    string linea;

    if(!archivo.is_open()){
        cout<<"\n No se pudo abrir el archivo "<<nombreArchivo<<endl;
        return;
    }


    getline(archivo, linea);

    while(getline(archivo, linea)){
        string paisLeido="";
        unsigned int i=0;

        while(i<linea.size() && linea[i]!=';'){
            paisLeido+=linea[i];
            i++;
        }

        if(paisLeido==paisBuscado){
            leerHistoricoEquipo(equipo, linea);
            archivo.close();
            return;
        }
    }

    cout<<"\n No se encontro el equipo "<<paisBuscado<<" en el archivo."<<endl;
    archivo.close();
}
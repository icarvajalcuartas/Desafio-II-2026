#include "Grupo.h"

Grupo::Grupo()
{
    letra=' ';
    cantEquipos=0;
    equipos=new Equipo[4];
}

Grupo::Grupo(char l)
{
    letra=l;
    cantEquipos=0;
    equipos=new Equipo[4];
}

Grupo::Grupo(const Grupo &copiaGrupo)
{
    letra=copiaGrupo.letra;
    cantEquipos=copiaGrupo.cantEquipos;
    equipos=new Equipo[4];

    for(unsigned short int i=0; i<cantEquipos; i++){
        equipos[i]=copiaGrupo.equipos[i];
    }
}

Grupo& Grupo::operator=(const Grupo &otro)
{
    if(this != &otro){
        delete[] equipos;

        letra=otro.letra;
        cantEquipos=otro.cantEquipos;
        equipos=new Equipo[4];

        for(unsigned short int i=0; i<cantEquipos; i++){
            equipos[i]=otro.equipos[i];
        }
    }

    return *this;
}

char Grupo::getLetra() const
{
    return letra;
}

unsigned short int Grupo::getCantEquipos() const
{
    return cantEquipos;
}

const Equipo& Grupo::getEquipo(unsigned short int pos) const
{
    return equipos[pos];
}

void Grupo::setLetra(char l)
{
    letra=l;
}

bool Grupo::puedeAgregarEquipo(const Equipo &equipo) const
{
    if(cantEquipos>=4){
        return false;
    }

    unsigned short int contadorConfederacion=0;

    for(unsigned short int i=0; i<cantEquipos; i++){
        if(equipos[i].getPais()==equipo.getPais()){
            return false;
        }

        if(equipos[i].getConfederacion()==equipo.getConfederacion()){
            contadorConfederacion++;
        }
    }

    if(equipo.getConfederacion()=="UEFA"){
        return contadorConfederacion<2;
    }

    return contadorConfederacion==0;
}

bool Grupo::agregarEquipo(const Equipo &equipo)
{
    if(puedeAgregarEquipo(equipo)){
        equipos[cantEquipos]=equipo;
        cantEquipos++;
        return true;
    }

    return false;
}

bool Grupo::quitarUltimoEquipo()
{
    if(cantEquipos==0){
        return false;
    }
    cantEquipos--;
    return true;
}

void Grupo::print() const
{
    cout<<"Grupo "<<letra<<":"<<endl;

    for(unsigned short int i=0; i<cantEquipos; i++){
        cout<<"Equipo "<<i+1<<": ";
        cout<<equipos[i].getPais()<<" - "<<equipos[i].getConfederacion()<<endl;
    }

    cout<<endl;
}

Grupo::~Grupo()
{
    delete[] equipos;
}

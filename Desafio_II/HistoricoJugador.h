#ifndef HISTORICOJUGADOR_H
#define HISTORICOJUGADOR_H
#include <string>
using namespace std;
class HistoricoJugador{
private:
    unsigned short int partJugados;
    unsigned short int cantGoles;
    unsigned short int minJugados;
    unsigned short int asistencias;
    unsigned short int tarAmarillas;
    unsigned short int tarRojas;
    unsigned short int faltAcumuladas;
public:
    HistoricoJugador();
    HistoricoJugador(unsigned short int pJ,unsigned short int cG,unsigned short int mJ, unsigned short int as, unsigned short int tAm, unsigned short int tRo, unsigned short int fAc);
    HistoricoJugador(const HistoricoJugador &copiahistorico);
    HistoricoJugador& operator =(const HistoricoJugador &otro);
    void actualizarHistorico(unsigned short int cG, unsigned short int mJ, unsigned short int tAm,unsigned short int tRo,unsigned short int fAcc);
    unsigned short int getpartJugados()const;
    unsigned short int getcantGoles()const;
    unsigned short int getminJugados()const;
    unsigned short int getasistencias()const;
    unsigned short int gettarAmarillas()const;
    unsigned short int gettarRojas()const;
    unsigned short int getfaltAcumuladas()const;
    void setpartJugados(unsigned short int part);
    void setcantGoles(unsigned short int gol);
    void setminJugados(unsigned short int min);
    void setasistencias(unsigned short int asi);
    void settarAmarillas(unsigned short int am);
    void settarRojas(unsigned short int ro);
    void setfaltAcumuladas(unsigned short int fal);
    void print()const;
    friend int actualizarArchivo(const HistoricoJugador &estadisticas, unsigned short int numeroCamiseta, const string &equipo);
    ~HistoricoJugador();
};

#endif // HISTORICOJUGADOR_H

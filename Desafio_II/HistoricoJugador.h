#ifndef HISTORICOJUGADOR_H
#define HISTORICOJUGADOR_H


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
    void actualizarHistorico(unsigned short int cG, unsigned short int mJ, unsigned short int tAm,unsigned short int tRo,unsigned short int fAcc);
    unsigned short int getpartJugados()const;
    unsigned short int getcantGoles()const;
    unsigned short int getminJugados()const;
    unsigned short int getasistencias()const;
    unsigned short int gettarAmarillas()const;
    unsigned short int gettarRojas()const;
    unsigned short int getfaltAcumuladas()const;
    friend void actualizarArchivo(const HistoricoJugador &estadisticas, unsigned short int numeroCamiseta);
    ~HistoricoJugador();
};

#endif // HISTORICOJUGADOR_H

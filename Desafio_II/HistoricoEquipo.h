#ifndef HISTORICOEQUIPO_H
#define HISTORICOEQUIPO_H

class HistoricoEquipo{
private:
    unsigned short int golesFavor;
    unsigned short int golesContra;
    unsigned short int partidosGanados;
    unsigned short int partidosEmpatados;
    unsigned short int partidosPerdidos;
    unsigned short int tarjetasAmarillas;
    unsigned short int tarjetasRojas;
    unsigned short int faltas;

public:
    HistoricoEquipo();
    HistoricoEquipo(unsigned short int gf, unsigned short int gc,
                    unsigned short int pg, unsigned short int pe,
                    unsigned short int pp, unsigned short int ta,
                    unsigned short int tr, unsigned short int fa);
    HistoricoEquipo(const HistoricoEquipo &copia);

    void actualizarHistorico(unsigned short int gf, unsigned short int gc,
                             unsigned short int ta, unsigned short int tr,
                             unsigned short int fa);

    unsigned short int getGolesFavor() const;
    unsigned short int getGolesContra() const;
    unsigned short int getPartidosGanados() const;
    unsigned short int getPartidosEmpatados() const;
    unsigned short int getPartidosPerdidos() const;
    unsigned short int getTarjetasAmarillas() const;
    unsigned short int getTarjetasRojas() const;
    unsigned short int getFaltas() const;

    void setGolesFavor(unsigned short int gf);
    void setGolesContra(unsigned short int gc);
    void setPartidosGanados(unsigned short int pg);
    void setPartidosEmpatados(unsigned short int pe);
    void setPartidosPerdidos(unsigned short int pp);
    void setTarjetasAmarillas(unsigned short int ta);
    void setTarjetasRojas(unsigned short int tr);
    void setFaltas(unsigned short int fa);

    void print() const;


    ~HistoricoEquipo();
};

#endif // HISTORICOEQUIPO_H
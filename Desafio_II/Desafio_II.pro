TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Equipo.cpp \
        HistoricoJugador.cpp \
        Jugador.cpp \
        archivoequipo.cpp \
        archivos.cpp \
        main.cpp

HEADERS += \
    Equipo.h \
    HistoricoJugador.h \
    Jugador.h \
    archivoequipo.h \
    archivos.h

DISTFILES += \
    Historico_jugadores.csv

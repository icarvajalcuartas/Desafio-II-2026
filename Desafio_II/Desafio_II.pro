TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        HistoricoJugador.cpp \
        Jugador.cpp \
        archivos.cpp \
        main.cpp

HEADERS += \
    HistoricoJugador.h \
    Jugador.h \
    archivos.h

DISTFILES += \
    Historico_jugadores.csv

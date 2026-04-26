TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ArchivoEquipo.cpp \
        Equipo.cpp \
        HistoricoEquipo.cpp \
        HistoricoJugador.cpp \
        Jugador.cpp \
        archivos.cpp \
        main.cpp

HEADERS += \
    ArchivoEquipo.h \
    Equipo.h \
    HistoricoEquipo.h \
    HistoricoJugador.h \
    Jugador.h \
    archivos.h

DISTFILES += \
    Historico_equipos.csv \
    Historico_jugadores.csv \
    selecciones_clasificadas_mundial.csv

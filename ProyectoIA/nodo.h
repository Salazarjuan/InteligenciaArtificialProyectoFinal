#ifndef NODO_H
#define NODO_H
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <math.h>
using namespace std;


class Nodo
{
public:
    Nodo();
    Nodo(int posI, int posJ, int municion, Nodo* padre, int profundidad, int costo, std::string operacion);

    int posI = 0;
    int posJ = 0;

    int municion;
    Nodo* padre;
    int profundidad;
    int costo;
    std::string operacion;
    std::vector<Nodo> amplitud;
    bool expandido;
    std::vector<Nodo> profundidadStack;



    bool esMeta(int valorCasilla);
    bool esMeta(int pos, int mapa[12][12]);

    void expandirPorAmplitudSD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorAmplitudCD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorCostoUniformeSD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorCostoUniformeCD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorPreferenteProfundidadSD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorPreferenteProfundidadCD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorBusquedaAvaraSD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorAEstrellaSD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorAEstrellaCD(int posI, int posJ, int municion, int mapa[12][12]);


    bool yaVisitado(Nodo nodo);

};



#endif // NODO_H


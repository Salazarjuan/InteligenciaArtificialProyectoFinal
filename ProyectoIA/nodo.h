#ifndef NODO_H
#define NODO_H
#include <string>
#include <vector>
#include <iostream>
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



    bool esMeta(int valorCasilla);
    void expandirPorAmplitudSD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorAmplitudCD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorCostoUniformeSD(int posI, int posJ, int municion, int mapa[12][12]);
    void expandirPorCostoUniformeCD(int posI, int posJ, int municion, int mapa[12][12]);


};



#endif // NODO_H


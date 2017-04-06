#ifndef NODO_H
#define NODO_H
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <math.h>
#include <QLabel>
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
    bool yaVisitado(Nodo nodo);

    std::vector<int> expandirPorAmplitudSD(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos);  
    std::vector<int> expandirPorCostoUniformeSD(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos);    
    std::vector<int> expandirPorPreferenteProfundidadSC(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos);
    std::vector<int> expandirPorBusquedaAvaraSD(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos);
    std::vector<int> expandirPorAEstrellaSD(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos);

    //Variantes adicionales
    //std::vector<int> expandirPorAmplitudCD(int posI, int posJ, int municion, int mapa[12][12]);
    //std::vector<int> expandirPorCostoUniformeCD(int posI, int posJ, int municion, int mapa[12][12]);
    //std::vector<int> expandirPorPreferenteProfundidadCC(int posI, int posJ, int municion, int mapa[12][12]);


};



#endif // NODO_H


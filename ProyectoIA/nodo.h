#ifndef NODO_H
#define NODO_H
#include <string>


class Nodo
{
public:
    Nodo();
    int posI = 0;
    int posJ = 0;
    int municion;
    Nodo padre;
    int profundidad;
    int costo;
    std::string operacion;

    Nodo(int posI, int posJ, int municion, Nodo padre, int profundidad, int costo, std::string operacion);


    bool esMeta(int valorCasilla);
    void expandir();


};



#endif // NODO_H

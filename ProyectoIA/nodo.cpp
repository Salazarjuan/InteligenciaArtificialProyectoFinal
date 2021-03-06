#include "nodo.h"

Nodo::Nodo()
{

}

Nodo::Nodo(int posI, int posJ, int municion, Nodo* padre, int profundidad, int costo, std::string operacion){
    this->posI = posI;
    this->posJ = posJ;
    this->municion = municion;
    this->padre = padre;
    this->profundidad = profundidad;
    this->costo = costo;
    this->operacion = operacion;
    amplitud.resize(0);
    profundidadStack.resize(0);
    expandido = false;
}

/*
 * esMeta(int)
 * Objetivo: Comparar si el valor de la casilla del mapa es 4
 */

bool Nodo::esMeta(int valorCasilla){
    if(valorCasilla == 4){
        return true;
    }
    return false;
}

/*
 * esMeta(int, int[][])
 * Objetivo: Comparar si el valor de la casilla que apunta un objeto en un arreglo de nodos, es 4
 */

bool Nodo::esMeta(int pos, int mapa[12][12]){
    if(mapa[profundidadStack[pos].posI][profundidadStack[pos].posJ] == 4){
        return true;
    }
    return false;
}

/*
 * Amplitud
 * Idea: se pasan las posiciones iniciales y se expande el nodo raiz, este es agregado a un vector. Se verifica si ees meta, si no lo es se expande. Para ahorrar memoria, se crea
 *       un solo arreglo, y para simular amplitud, lo que se hace es simular el borrado del primer elemento del vector con un iterador que indica la "primera posicion" del arreglo, este
 *       aumenta cada vez que se expande.
 */

std::vector<int> Nodo::expandirPorAmplitudSD(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos){
    amplitud.clear();
    int nodosExpandidosCounter = 1;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);
    int i = 0;
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        nodosExpandidosCounter++;
        if(amplitud.at(i).padre == NULL){
            if((mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1)){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Arriba");
                amplitud.push_back(nodoArriba);
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1)){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Izquierda");
                amplitud.push_back(nodoIzquierda);
            }
            if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1)){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Abajo");
                amplitud.push_back(nodoAbajo);
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1)){
                Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Derecha");
                amplitud.push_back(nodoDerecha);
                //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
            }
        }else{
            if((mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1) && (amplitud.at(i).padre->posI != amplitud.at(i).posI - 1)){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Arriba");
                amplitud.push_back(nodoArriba);
                //cout << nodoArriba.posI << nodoArriba.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1) && (amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1)){
                Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Izquierda");
                amplitud.push_back(nodoIzquierda);
                //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1) && (amplitud.at(i).padre->posI != amplitud.at(i).posI + 1)){
                Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Abajo");
                amplitud.push_back(nodoAbajo);
                //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
            }
            if((mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1) && (amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1)){
                Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Derecha");
                amplitud.push_back(nodoDerecha);
                //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
            }
        }
        i++;
        //cout << profundidad << endl;
    }
    cout<<i<<" "<<amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<<" "<<amplitud.at(i).profundidad<<endl;

    Nodo solucion = amplitud.at(i);
    profundidad->setText("Profundidad: " + QString::number(solucion.profundidad));
    nodosExpandidos->setText("Nodos expandidos: " + QString::number(nodosExpandidosCounter));
    Nodo * padres = solucion.padre;
    std::vector<int> posSolucion;
    posSolucion.resize(0);
    posSolucion.push_back(solucion.posI);
    posSolucion.push_back(solucion.posJ);

    while(padres->padre != NULL){
        posSolucion.push_back(padres->posI);
        posSolucion.push_back(padres->posJ);
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            posSolucion.push_back(padres->posI);
            posSolucion.push_back(padres->posJ);
        }

    }
    posSolucion.push_back(padres->posI);
    posSolucion.push_back(padres->posJ);

    return posSolucion;

}


/*
 * Costo
 * Idea: se pasan las posiciones iniciales y se expande el nodo raiz, este es agregado a un vector. Se verifica si es meta, si no lo es se expande. En este caso se hace uso de una adicion a la
 *       clase nodo, el atributo expandido(boolean). Si el noto raiz no es meta se cambia el estado a nodo expaandido, y se busca el nodo con menor costo que no haya sido expandido, y asi hasta
 *       encontrar la meta. Nuevamente usamos un solo arreglo y la posicion a expandir sera indicada por un iterado qque apunta a la posicion donde esta el nodo con menor costo que no haaya sido expandido.
 *
 *       Se tiene en cuenta que si se pasa por una casilla enemiga, el costo aumenta en 4, mas el paso, para un total de +5 si se pasa por una casilla enemiga y se descuenta el numero de tiros
 */

std::vector<int> Nodo::expandirPorCostoUniformeSD(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos){
    amplitud.clear();
    int i = 0;
    int nodosExpandidosCounter = 1;
    int menor = 9999999999;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);

    if(raiz.municion > 0){
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }else{
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }

    //amplitud.erase(amplitud.begin() + i);
    amplitud.at(i).expandido = true;
    for(int j = 0; j < amplitud.size(); j++){
        if(amplitud.at(j).expandido == false){
            if(amplitud.at(j).costo < menor){
                menor = amplitud.at(j).costo;
                i = j;

            }
        }
    }
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        nodosExpandidosCounter++;
        if(amplitud.at(i).municion > 0){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI - 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI + 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }else{
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI - 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI + 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }

        menor = 99999999;
        amplitud.at(i).expandido = true;
        for(int j = 0; j < amplitud.size(); j++){
            if(amplitud.at(j).expandido == false){
                if(amplitud.at(j).costo < menor){
                    menor = amplitud.at(j).costo;
                    i = j;

                }
            }
        }

    }

    Nodo solucion = amplitud.at(i);
    profundidad->setText("Profundidad: " + QString::number(solucion.profundidad));
    nodosExpandidos->setText("Nodos expandidos: " + QString::number(nodosExpandidosCounter));
    Nodo * padres = solucion.padre;
    std::vector<int> posSolucion;
    posSolucion.resize(0);
    posSolucion.push_back(solucion.posI);
    posSolucion.push_back(solucion.posJ);
    while(padres->padre != NULL){
        posSolucion.push_back(padres->posI);
        posSolucion.push_back(padres->posJ);
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            posSolucion.push_back(padres->posI);
            posSolucion.push_back(padres->posJ);
        }

    }
    posSolucion.push_back(padres->posI);
    posSolucion.push_back(padres->posJ);

    return posSolucion;
}

/*
 * Profundidad sin ciclos
 * Idea: se pasan las posiciones iniciales y se expande el nodo raiz, este es agregado a un vector. Este vector lo que pretende es simular una pila.
 *
 *
 *       D
 *       C
 *       B
 *       A       A B C D
 *      Pila      Lista
 *
 *      La idea consiste en buscar en la lista el ultimo elemento, el que esta mas arriba en la pila. Nuevamente usamos el atributo expandido, y en cada iteracion
 *      buscamos el ultimo nodo que no ha sido expandido. En este algoritmo no borramos ningun nodo, por lo cual aumentamos la complejidad temporal a O(b^d), pero se hace con
 *      el motivo de no tener otro arreglo que nos permita recuperar la ruta de la solucion. Cuando hacemos el borrado logico se se pone en expandido el ultimo nodo y se vuelve a buscar
 *      el ultimo nodo que no se haya expandido
 *
 */
std::vector<int> Nodo::expandirPorPreferenteProfundidadSC(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos){

    profundidadStack.clear();
    int nodosExpandidosCounter = 1;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");

    raiz.expandido = true;
    int ultimaPos = 0;

    if((mapa[raiz.posI + 1][raiz.posJ] != 1)){
        Nodo nodoAbajo(raiz.posI + 1, raiz.posJ, municion, &raiz, raiz.profundidad + 1, 0, "Abajo");
        profundidadStack.push_back(nodoAbajo);
    }
    if((mapa[raiz.posI][raiz.posJ - 1] != 1)){
        Nodo nodoIzquierda(raiz.posI, raiz.posJ - 1, municion, &raiz, raiz.profundidad + 1, 0, "Izquierda");
        profundidadStack.push_back(nodoIzquierda);
    }
    if(mapa[raiz.posI-1][raiz.posJ] != 1){
        Nodo nodoArriba(raiz.posI - 1, raiz.posJ, municion, &raiz, raiz.profundidad + 1, 0, "Arriba");
        profundidadStack.push_back(nodoArriba);
    }
    if((mapa[raiz.posI][raiz.posJ + 1] != 1)){
        Nodo nodoDerecha(raiz.posI, raiz.posJ + 1, municion, &raiz, raiz.profundidad + 1, 0, "Derecha");
        profundidadStack.push_back(nodoDerecha);
    }

    for(int j = 0; j < profundidadStack.size(); j++){
        (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
    }

    while(!esMeta(ultimaPos, mapa)){
        nodosExpandidosCounter++;
        for(int j = 0; j < profundidadStack.size(); j++){
            (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
        }
        if(yaVisitado(profundidadStack[ultimaPos])){
            profundidadStack.at(ultimaPos).expandido = true;

            for(int j = 0; j < profundidadStack.size(); j++){
                (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
            }
        }

       profundidadStack[ultimaPos].expandido = true;

        if((mapa[profundidadStack[ultimaPos].posI + 1][profundidadStack[ultimaPos].posJ] != 1) && (profundidadStack[ultimaPos].padre->posI != profundidadStack[ultimaPos].posI + 1)){
            Nodo nodoAbajo(profundidadStack[ultimaPos].posI + 1, profundidadStack[ultimaPos].posJ, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Abajo");
            profundidadStack.push_back(nodoAbajo);
        }
        if((mapa[profundidadStack[ultimaPos].posI][profundidadStack[ultimaPos].posJ - 1] != 1) && (profundidadStack[ultimaPos].padre->posJ != profundidadStack[ultimaPos].posJ - 1)){
            Nodo nodoIzquierda(profundidadStack[ultimaPos].posI, profundidadStack[ultimaPos].posJ - 1, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Izquierda");
            profundidadStack.push_back(nodoIzquierda);
        }
        if((mapa[profundidadStack[ultimaPos].posI - 1][profundidadStack[ultimaPos].posJ] != 1) && (profundidadStack[ultimaPos].padre->posI != profundidadStack[ultimaPos].posI - 1)){
            Nodo nodoArriba(profundidadStack[ultimaPos].posI - 1, profundidadStack[ultimaPos].posJ, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Arriba");
            profundidadStack.push_back(nodoArriba);
        }
        if((mapa[profundidadStack[ultimaPos].posI][profundidadStack[ultimaPos].posJ + 1] != 1) && (profundidadStack[ultimaPos].padre->posJ != profundidadStack[ultimaPos].posJ + 1)){
            Nodo nodoDerecha(profundidadStack[ultimaPos].posI, profundidadStack[ultimaPos].posJ + 1, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Derecha");
            profundidadStack.push_back(nodoDerecha);

        }

    }

    cout<<"Meta encontrada: "<<profundidadStack[ultimaPos].posI<<" "<<profundidadStack[ultimaPos].posJ<<" "<<profundidadStack[ultimaPos].profundidad<<endl;

    Nodo solucion = profundidadStack[ultimaPos];
    profundidad->setText("Profundidad: " + QString::number(solucion.profundidad));
    nodosExpandidos->setText("Nodos expandidos: " + QString::number(nodosExpandidosCounter));
    Nodo * padres = solucion.padre;
    std::vector<int> posSolucion;
    posSolucion.resize(0);
    posSolucion.push_back(solucion.posI);
    posSolucion.push_back(solucion.posJ);
    while(padres->padre != NULL){
        posSolucion.push_back(padres->posI);
        posSolucion.push_back(padres->posJ);
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            posSolucion.push_back(padres->posI);
            posSolucion.push_back(padres->posJ);
        }

    }
    posSolucion.push_back(padres->posI);
    posSolucion.push_back(padres->posJ);

    return posSolucion;
}

/*
 * Avara
 * Idea: Se calcula el valor de laa heuristica, distancia de manhattan, para cada posicion del mapa. Se crea el nodo raiz con las pocisiones iniciales y se le pasa por costo el valor
 *       de la heuristica. Se expande y se pasan los valores de la heuristica como el costo del nodo, se busca el nodo no expandido de menor heuristica haciendo uso del costo del nodo
 *       y del atributo expandido. Se hace uso del iterador para seleccionar la posicion de menoor heuristica y expandirla. Como no es completo, se coloca un maximo de 10000 iteraciones
 *       y se detiene el proceso
 */

std::vector<int> Nodo::expandirPorBusquedaAvaraSD(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos){
    int counter = 0;
    int posIFinal = 0;
    int posJFinal = 0;
    int matrixManhattam[12][12];

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            matrixManhattam[i][j] = -1;
        }
    }

    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            if(mapa[i][j] == 4){
                posIFinal = i;
                posJFinal = j;
            }
        }
    }

    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            matrixManhattam[i][j] = (abs(posIFinal-i) + abs(posJFinal-j));
        }
    }

    amplitud.clear();
    int i = 0;
    int nodosExpandidosCounter = 1;
    int menor = 9999999999;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);

    if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
        Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, matrixManhattam[amplitud.at(i).posI - 1][amplitud.at(i).posJ], "Arriba");
        amplitud.push_back(nodoArriba);
    }

    if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
        Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, matrixManhattam[amplitud.at(i).posI + 1][amplitud.at(i).posJ], "Abajo");
        amplitud.push_back(nodoArriba);
    }

    if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
        Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, matrixManhattam[amplitud.at(i).posI][amplitud.at(i).posJ - 1], "Izquierda");
        amplitud.push_back(nodoArriba);
    }

    if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
        Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, matrixManhattam[amplitud.at(i).posI][amplitud.at(i).posJ + 1], "Derecha");
        amplitud.push_back(nodoArriba);
    }

    amplitud.at(i).expandido = true;
    for(int j = 0; j < amplitud.size(); j++){
        if(amplitud.at(j).expandido == false){
            if(amplitud.at(j).costo < menor){
                menor = amplitud.at(j).costo;
                i = j;

            }
        }
    }

    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ]) && (counter < 10000)){
        nodosExpandidosCounter++;
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, matrixManhattam[amplitud.at(i).posI - 1][amplitud.at(i).posJ], "Arriba");
            amplitud.push_back(nodoArriba);
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, matrixManhattam[amplitud.at(i).posI + 1][amplitud.at(i).posJ], "Abajo");
            amplitud.push_back(nodoArriba);
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, matrixManhattam[amplitud.at(i).posI][amplitud.at(i).posJ - 1], "Izquierda");
            amplitud.push_back(nodoArriba);
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, matrixManhattam[amplitud.at(i).posI][amplitud.at(i).posJ + 1], "Derecha");
            amplitud.push_back(nodoArriba);
        }

        //amplitud.erase(amplitud.begin() + i);
        menor = 99999999;
        amplitud.at(i).expandido = true;
        for(int j = 0; j < amplitud.size(); j++){
            if(amplitud.at(j).expandido == false){
                if(amplitud.at(j).costo < menor){
                    menor = amplitud.at(j).costo;
                    i = j;
                }
            }
        }
        counter++;
    }

    if(counter >= 10000){
        std::vector<int> solucionVacia;
        solucionVacia.resize(0);
        profundidad->setText("Demasiadas iteraciones, no hay solucion");
        return solucionVacia;
    }

    Nodo solucion = amplitud.at(i);
    profundidad->setText("Profundidad: " + QString::number(solucion.profundidad));
    nodosExpandidos->setText("Nodos expandidos: " + QString::number(nodosExpandidosCounter));
    Nodo * padres = solucion.padre;
    std::vector<int> posSolucion;
    posSolucion.resize(0);
    posSolucion.push_back(solucion.posI);
    posSolucion.push_back(solucion.posJ);
    while(padres->padre != NULL){
        posSolucion.push_back(padres->posI);
        posSolucion.push_back(padres->posJ);
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            posSolucion.push_back(padres->posI);
            posSolucion.push_back(padres->posJ);
        }

    }
    posSolucion.push_back(padres->posI);
    posSolucion.push_back(padres->posJ);

    return posSolucion;
}

/*
 * A*
 * Idea: Se calcula el valor de laa heuristica, distancia de manhattan, para cada posicion del mapa. Se crea el nodo raiz con las pocisiones iniciales y se inicia con un costo de 0.
 *       Se expande y al igual que en costo se empiezan a acumular los valores por paso de casillaa y paso por enemigo, la penalizaacion y la disminucion de disparos.
 *       Se hace uso del iterador para apuntar cual es la posicion que tiene el menor costo acumulado g(n) + f(n) y se expande esa posicion.
 */

std::vector<int> Nodo::expandirPorAEstrellaSD(int posI, int posJ, int municion, int mapa[12][12], QLabel *profundidad, QLabel *nodosExpandidos)
{
    int posIFinal = 0;
    int posJFinal = 0;
    int matrixManhattam[12][12];

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            matrixManhattam[i][j] = -1;
        }
    }

    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            if(mapa[i][j] == 4){
                posIFinal = i;
                posJFinal = j;
            }
        }
    }

    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            matrixManhattam[i][j] = (abs(posIFinal-i) + abs(posJFinal-j));
        }
    }

    amplitud.clear();
    int i = 0;
    int menor = 9999999999;
    int nodosExpandidosCounter = 1;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);

    if(raiz.municion > 0){
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }else{
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }

    //amplitud.erase(amplitud.begin() + i);
    amplitud.at(i).expandido = true;
    for(int j = 0; j < amplitud.size(); j++){
        if(amplitud.at(j).expandido == false){
            if((amplitud.at(j).costo + matrixManhattam[amplitud.at(j).posI][amplitud.at(j).posJ]) < menor){
                menor = amplitud.at(j).costo + matrixManhattam[amplitud.at(j).posI][amplitud.at(j).posJ];
                i = j;

            }
        }
    }
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        nodosExpandidosCounter++;
        if(amplitud.at(i).municion > 0){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI - 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI + 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }else{
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI - 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1 && amplitud.at(i).padre->posI != amplitud.at(i).posI + 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ - 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1 && amplitud.at(i).padre->posJ != amplitud.at(i).posJ + 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }

        menor = 99999999;
        amplitud.at(i).expandido = true;
        for(int j = 0; j < amplitud.size(); j++){
            if(amplitud.at(j).expandido == false){
                if((amplitud.at(j).costo + matrixManhattam[amplitud.at(j).posI][amplitud.at(j).posJ]) < menor){
                    menor = amplitud.at(j).costo + matrixManhattam[amplitud.at(j).posI][amplitud.at(j).posJ];
                    i = j;

                }
            }
        }

    }
    cout<<i<<" "<<amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<<" "<<amplitud.at(i).profundidad<<endl;

    Nodo solucion = amplitud.at(i);
    profundidad->setText("Profundidad: " + QString::number(solucion.profundidad));
    nodosExpandidos->setText("Nodos expandidos: " + QString::number(nodosExpandidosCounter));
    Nodo * padres = solucion.padre;

    std::vector<int> posSolucion;
    posSolucion.resize(0);
    posSolucion.push_back(solucion.posI);
    posSolucion.push_back(solucion.posJ);
    while(padres->padre != NULL){
        posSolucion.push_back(padres->posI);
        posSolucion.push_back(padres->posJ);
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            posSolucion.push_back(padres->posI);
            posSolucion.push_back(padres->posJ);
        }

    }
    posSolucion.push_back(padres->posI);
    posSolucion.push_back(padres->posJ);

    return posSolucion;

}


bool Nodo::yaVisitado(Nodo nodo){
    Nodo unNodo = nodo;
    while(unNodo.padre != NULL){
        unNodo = * unNodo.padre;
        if(unNodo.posI == nodo.posI && unNodo.posJ == nodo.posJ){
            return true;
        }
    }
    return false;
}

/* ALGORITMOS ADICIONALES QUE NO SE PIDEN PERO QUE SE IMPLEMENTARON */

/*
std::vector<int> Nodo::expandirPorAmplitudCD(int posI, int posJ, int municion, int mapa[12][12]){
    amplitud.clear();
    int i = 0;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        //cout << mapa[amplitud.at(i).posI][amplitud.at(i).posJ] << endl;

        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Arriba");
            amplitud.push_back(nodoArriba);
            //cout << nodoArriba.posI << nodoArriba.posJ << endl;
        }
        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            Nodo nodoIzquierda(amplitud.at(i).posI, amplitud.at(i).posJ - 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Izquierda");
            amplitud.push_back(nodoIzquierda);
            //cout << nodoIzquierda.posI << nodoIzquierda.posJ << endl;
        }
        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            Nodo nodoAbajo(amplitud.at(i).posI + 1, amplitud.at(i).posJ, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Abajo");
            amplitud.push_back(nodoAbajo);
            //cout << nodoAbajo.posI << nodoAbajo.posJ << endl;
        }
        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            Nodo nodoDerecha(amplitud.at(i).posI, amplitud.at(i).posJ + 1, municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 0, "Derecha");
            amplitud.push_back(nodoDerecha);
            //cout << nodoDerecha.posI << "," << nodoDerecha.posJ << endl;
        }
        i++;
        //cout << profundidad << endl;
    }
    cout<<i<<" "<<amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<<endl;

    Nodo solucion = amplitud.at(i);
    Nodo * padres = solucion.padre;
    std::vector<int> posSolucion;
    posSolucion.resize(0);
    posSolucion.push_back(solucion.posI);
    posSolucion.push_back(solucion.posJ);
    while(padres->padre != NULL){
        posSolucion.push_back(padres->posI);
        posSolucion.push_back(padres->posJ);
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            posSolucion.push_back(padres->posI);
            posSolucion.push_back(padres->posJ);
        }

    }
    posSolucion.push_back(padres->posI);
    posSolucion.push_back(padres->posJ);

    return posSolucion;
}
*


/*
std::vector<int> Nodo::expandirPorCostoUniformeCD(int posI, int posJ, int municion, int mapa[12][12]){
    amplitud.clear();
    int i = 0;
    int menor = 9999999999;
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");
    amplitud.push_back(raiz);

    if(raiz.municion > 0){
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }else{
        if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Arriba");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Arriba");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Abajo");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Abajo");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Izquierda");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Izquierda");
                amplitud.push_back(nodoArriba);
            }
        }

        if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, 5, "Derecha");
                amplitud.push_back(nodoArriba);
            }else{
                Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, 1, "Derecha");
                amplitud.push_back(nodoArriba);
            }
        }
    }

    //amplitud.erase(amplitud.begin() + i);
    amplitud.at(i).expandido = true;
    for(int j = 0; j < amplitud.size(); j++){
        if(amplitud.at(j).expandido == false){
            if(amplitud.at(j).costo < menor){
                menor = amplitud.at(j).costo;
                i = j;

            }
        }
    }
    while(!esMeta(mapa[amplitud.at(i).posI][amplitud.at(i).posJ])){
        //cout << mapa[amplitud.at(i).posI][amplitud.at(i).posJ] << endl;
        //cout << amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<< endl;
        if(amplitud.at(i).municion > 0){
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }else{
            if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] != 1){
                if(mapa[amplitud.at(i).posI - 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Arriba");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI - 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Arriba");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] != 1){
                if(mapa[amplitud.at(i).posI + 1][amplitud.at(i).posJ] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Abajo");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI + 1, amplitud.at(i).posJ, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Abajo");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] != 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ - 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ - 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Izquierda");
                    amplitud.push_back(nodoArriba);
                }
            }

            if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] != 1){
                if(mapa[amplitud.at(i).posI][amplitud.at(i).posJ + 1] == 3){
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion - 1, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 5, "Derecha");
                    amplitud.push_back(nodoArriba);
                }else{
                    Nodo nodoArriba(amplitud.at(i).posI, amplitud.at(i).posJ + 1, amplitud.at(i).municion, &amplitud.at(i), amplitud.at(i).profundidad + 1, amplitud.at(i).costo + 1, "Derecha");
                    amplitud.push_back(nodoArriba);
                }
            }
        }

        //amplitud.erase(amplitud.begin() + i);
        menor = 99999999;
        amplitud.at(i).expandido = true;
        for(int j = 0; j < amplitud.size(); j++){
            if(amplitud.at(j).expandido == false){
                if(amplitud.at(j).costo < menor){
                    menor = amplitud.at(j).costo;
                    i = j;

                }
            }
        }

    }
    cout<<i<<" "<<amplitud.at(i).posI<<" "<<amplitud.at(i).posJ<<" "<<amplitud.at(i).profundidad<<endl;

    Nodo solucion = amplitud.at(i);
    Nodo * padres = solucion.padre;
    std::vector<int> posSolucion;
    posSolucion.resize(0);
    posSolucion.push_back(solucion.posI);
    posSolucion.push_back(solucion.posJ);
    while(padres->padre != NULL){
        posSolucion.push_back(padres->posI);
        posSolucion.push_back(padres->posJ);
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            posSolucion.push_back(padres->posI);
            posSolucion.push_back(padres->posJ);
        }

    }
    posSolucion.push_back(padres->posI);
    posSolucion.push_back(padres->posJ);

    return posSolucion;
}

std::vector<int> Nodo::expandirPorPreferenteProfundidadCC(int posI, int posJ, int municion, int mapa[12][12]){
    profundidadStack.clear();
    Nodo raiz(posI, posJ, municion, NULL, 0, 0, "");

    raiz.expandido = true;
    int ultimaPos = 0, i = 0;

    if((mapa[raiz.posI + 1][raiz.posJ] != 1)){
        Nodo nodoAbajo(raiz.posI + 1, raiz.posJ, municion, &raiz, raiz.profundidad + 1, 0, "Abajo");
        profundidadStack.push_back(nodoAbajo);
    }
    if((mapa[raiz.posI][raiz.posJ - 1] != 1)){
        Nodo nodoIzquierda(raiz.posI, raiz.posJ - 1, municion, &raiz, raiz.profundidad + 1, 0, "Izquierda");
        profundidadStack.push_back(nodoIzquierda);
    }
    if(mapa[raiz.posI-1][raiz.posJ] != 1){
        Nodo nodoArriba(raiz.posI - 1, raiz.posJ, municion, &raiz, raiz.profundidad + 1, 0, "Arriba");
        profundidadStack.push_back(nodoArriba);
    }
    if((mapa[raiz.posI][raiz.posJ + 1] != 1)){
        Nodo nodoDerecha(raiz.posI, raiz.posJ + 1, municion, &raiz, raiz.profundidad + 1, 0, "Derecha");
        profundidadStack.push_back(nodoDerecha);
    }

    for(int j = 0; j < profundidadStack.size(); j++){
        (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
    }

    while(!esMeta(ultimaPos, mapa) && i < 10000){
        for(int j = 0; j < profundidadStack.size(); j++){
            (profundidadStack[j].expandido == false)?  ultimaPos = j: 0;
        }

        profundidadStack[ultimaPos].expandido = true;

        if((mapa[profundidadStack[ultimaPos].posI + 1][profundidadStack[ultimaPos].posJ] != 1) && (profundidadStack[ultimaPos].padre->posI != profundidadStack[ultimaPos].posI + 1)){
            Nodo nodoAbajo(profundidadStack[ultimaPos].posI + 1, profundidadStack[ultimaPos].posJ, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Abajo");
            profundidadStack.push_back(nodoAbajo);
        }
        if((mapa[profundidadStack[ultimaPos].posI][profundidadStack[ultimaPos].posJ - 1] != 1) && (profundidadStack[ultimaPos].padre->posJ != profundidadStack[ultimaPos].posJ - 1)){
            Nodo nodoIzquierda(profundidadStack[ultimaPos].posI, profundidadStack[ultimaPos].posJ - 1, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Izquierda");
            profundidadStack.push_back(nodoIzquierda);
        }
        if((mapa[profundidadStack[ultimaPos].posI - 1][profundidadStack[ultimaPos].posJ] != 1) && (profundidadStack[ultimaPos].padre->posI != profundidadStack[ultimaPos].posI - 1)){
            Nodo nodoArriba(profundidadStack[ultimaPos].posI - 1, profundidadStack[ultimaPos].posJ, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Arriba");
            profundidadStack.push_back(nodoArriba);
        }
        if((mapa[profundidadStack[ultimaPos].posI][profundidadStack[ultimaPos].posJ + 1] != 1) && (profundidadStack[ultimaPos].padre->posJ != profundidadStack[ultimaPos].posJ + 1)){
            Nodo nodoDerecha(profundidadStack[ultimaPos].posI, profundidadStack[ultimaPos].posJ + 1, municion, &profundidadStack[ultimaPos], profundidadStack[ultimaPos].profundidad + 1, 0, "Derecha");
            profundidadStack.push_back(nodoDerecha);

        }
        i++;
    }

    if(i >= 10000){
        std::vector<int> posSolucion;
        posSolucion.resize(0);
        return posSolucion;
    }
    cout<<"Meta encontrada: "<<profundidadStack[ultimaPos].posI<<" "<<profundidadStack[ultimaPos].posJ<<" "<<profundidadStack[ultimaPos].profundidad<<endl;

    Nodo solucion = profundidadStack[ultimaPos];
    Nodo * padres = solucion.padre;
    std::vector<int> posSolucion;
    posSolucion.resize(0);
    posSolucion.push_back(solucion.posI);
    posSolucion.push_back(solucion.posJ);
    while(padres->padre != NULL){
        posSolucion.push_back(padres->posI);
        posSolucion.push_back(padres->posJ);
        if(padres->padre != NULL){
            padres = padres->padre;
        }else{
            posSolucion.push_back(padres->posI);
            posSolucion.push_back(padres->posJ);
        }

    }
    posSolucion.push_back(padres->posI);
    posSolucion.push_back(padres->posJ);

    return posSolucion;
}
*/

#include "general.h"

dll* crearDLL(){
    dll *lista = (dll *) malloc(sizeof(dll));
    lista->inicio = lista->fin = NULL;
    lista->tamano = 0;
    return lista;
}

nodedll *crearNodo(void *elemento, size_t tamano){
    nodedll *nodo = (nodedll *) malloc(sizeof(nodedll));
    nodo->elemento = elemento;
    nodo->tamano = tamano;
    nodo->anterior = nodo->siguiente = NULL;
    return nodo;
}

unsigned long getTamano(dll *lista){
    return lista->tamano;
}

bool addFirst(dll *lista, void *elemento, size_t tamano){
    if(checkListAndElementIfNull(lista,elemento)) return false;
    nodedll *nuevo = crearNodo(elemento, tamano);
    if(isEmpty(lista)) addWhenEmpty(lista,nuevo);
    else{
        lista->inicio->anterior = nuevo;
        nuevo->siguiente = lista->inicio;
        lista->inicio = nuevo;
    }
    lista->tamano++;
    return true;

}

bool addLast(dll *lista, void *elemento, size_t tamano){
    if(checkListAndElementIfNull(lista,elemento)) return false;
    nodedll *nuevo = crearNodo(elemento, tamano);
    if(isEmpty(lista)) addWhenEmpty(lista,nuevo);
    else{
        lista->fin->siguiente = nuevo;
        nuevo->anterior = lista->fin;
        lista->fin = nuevo;
    }
    lista->tamano++;
    return true;
}

bool insertDLL(dll *lista, void *elemento, size_t tamano, unsigned long posicion){
    if(checkListAndElementIfNull(lista,elemento) || !checkPosicion(lista,posicion) || isEmpty(lista)) return false;
    nodedll *nuevo = crearNodo(elemento, tamano);
    long pos = 0;
    for(nodedll *temp = lista->inicio; temp != NULL; temp = temp->siguiente){
        if(pos == posicion){
            if(temp == lista->inicio){
                temp->anterior = nuevo;
                nuevo->anterior = NULL;
                nuevo->siguiente = temp;
                lista->inicio = nuevo;
            }else{
                nodedll *anterior = temp->anterior;
                anterior->siguiente = nuevo;
                temp->anterior = nuevo;
                nuevo->anterior = anterior;
                nuevo->siguiente = temp;
            }
            lista->tamano++;
            return true;
        }
        pos++;
    }
    return false;
}

void* getElementByIndex(dll *lista,unsigned long posicion){
    return checkIFNULL((void *) lista) || isEmpty (lista) || !checkPosicion(lista,posicion) ? NULL:findByIndex(lista,posicion);
}

long getIndex(dll *lista, void *elemento, size_t tamano){
    return checkListAndElementIfNull(lista,elemento) || isEmpty (lista) ? -1:findByElement(lista,elemento, tamano);
}

void* removeFirst(dll *lista){
    if(checkIFNULL((void *) lista) || isEmpty(lista)) return NULL;
    nodedll *temporal = lista->inicio->siguiente;
    void *elemento = lista->inicio->elemento;
    free(lista->inicio);
    lista->tamano--;
    if(isEmpty(lista)) setFirstLastToNull(lista);
    else lista->inicio = temporal;
    return elemento;
}

void* removeLast(dll *lista){
    if(checkIFNULL((void *) lista) || isEmpty(lista)) return NULL;
    nodedll *temporal = lista->fin->anterior;
    void *elemento = lista->fin->elemento;
    free(lista->fin);
    lista->tamano--;
    if(isEmpty(lista)) setFirstLastToNull(lista);
    else lista->fin = temporal;
    return elemento;

}

void* removeDLL(dll *lista, unsigned long posicion){
    if(checkIFNULL((void *) lista) || !checkPosicion(lista,posicion) || isEmpty(lista)) return NULL;
    long pos = 0;
    for(nodedll *temp = lista->inicio; temp != NULL; temp = temp->siguiente){
        if(pos == posicion){
            void *elemento = temp->elemento;
            if(lista->inicio == lista->fin){
                setFirstLastToNull(lista);
            }else if(temp == lista->inicio){
                lista->inicio = temp->siguiente;
            }else if(temp == lista->fin){
                lista->fin = temp->anterior;
            }else{
                nodedll *anterior = temp->anterior;
                nodedll *siguiente = temp->siguiente;
                anterior->siguiente = siguiente;
                siguiente->anterior = anterior;
            }
            free(temp);
            lista->tamano--;
            return elemento;
        }
        pos++;
    }
    return false;
}


bool destroyDLL(dll *lista){
    if(isEmpty(lista)){
        free(lista);
        return true;
    }
    return false;
}

bool checkPosicion(dll *lista,unsigned long posicion){
    return posicion >= 0 && posicion < lista->tamano;
}

bool checkListAndElementIfNull(dll *lista, void *elemento){
    return checkIFNULL((void *) lista) || checkIFNULL(elemento);
}

bool checkIFNULL(void *puntero){
    return puntero == NULL;
}

bool isEmpty(dll *lista){
    return lista->tamano == 0;
}

void addWhenEmpty(dll *lista, nodedll *nodo){
    lista->inicio = lista->fin = nodo;
}

void setFirstLastToNull(dll *lista){
    lista->inicio = lista->fin = NULL;
}

void *findByIndex(dll *lista, unsigned long posicion){
    unsigned long contador = 0;
    for(nodedll *temp = lista->inicio; temp != NULL; temp = temp->siguiente){
        if(contador == posicion) return temp->elemento;
        contador++;
    }
    return NULL;
}

long findByElement(dll *lista, void *elemento, size_t tamano){
    long posicion = 0;
    for(nodedll *temp = lista->inicio; temp != NULL; temp = temp->siguiente){
        if(checkIfEquals(temp->elemento,elemento,temp->tamano,tamano)) return posicion;
        posicion++;
    }
    return -1;
}

//Asumir que la DLL solo almacene un tipo de dato
bool checkIfEquals(void *a, void *b, size_t tamanoA, size_t tamanoB){
    return tamanoA == tamanoB ? recorrerPunteros(a,b,tamanoA):false;
}

bool recorrerPunteros(void *a, void *b, size_t tamano){
    unsigned char *p1 = (unsigned char *) a;
    unsigned char *p2 = (unsigned char *) b;
    for(size_t tam = 0; tam < tamano; tam++){
        if(*p1 != *p2) return false;
        p1++;
        p2++;
    }
    return true;
}

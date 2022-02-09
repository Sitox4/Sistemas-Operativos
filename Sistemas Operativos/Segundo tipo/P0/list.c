#include "list.h"

static struct nodo *crearNodo(){
    struct nodo *tmp = malloc(sizeof(struct nodo));
    if (tmp == NULL){
        printf("memoria agotada\n"); 
        exit(EXIT_FAILURE);
    }
    return tmp;
}

/* ============= FUNCIONES DE NUESTRA LISTA ============= */ 
lista crearLista(){
    struct nodo *l = crearNodo();
    l -> sig = NULL;
    return l;
}

void insertElement(void *x, posicion p){
    struct nodo *tmp = crearNodo();
    tmp->elem = x; tmp -> sig = p -> sig;
    p -> sig = tmp;
}
static posicion buscarant(lista l, void *x, int(*comp)(const void *, const void *)){
    struct nodo *p = l;
    while (p->sig != NULL && 0 != (*comp)(p->sig->elem, x)){
        p = p -> sig;
    }
        return p;
}
static int esultimoelemento(struct nodo *p){
    return (p -> sig == NULL);
}
void removeElement(lista l, void *x, int (*comp)(const void *, const void *)){
    struct nodo *tmp, *p = buscarant(l,x,comp);
    if (!esultimoelemento(p)){
        tmp = p ->sig;
        p->sig = tmp->sig;
        free(tmp);
    }
}
#include <stdlib.h>
#include <stdio.h>
#define LNULL NULL
#include <stdbool.h>
#include <string.h>

typedef struct tNode *tItemL;
typedef struct tNode *tPosL;
struct nodo {
    void *elem; struct nodo *sig;
};
typedef struct nodo *posicion;
typedef struct nodo *lista;

static struct nodo *crearNodo();
lista crearlista();
void insertElement();
static int esultimoelemento(struct nodo *p);
static posicion buscarant(lista l, void *x, int(*comp)(const void *, const void *));
void removeElement(lista l, void *x, int (*comp)(const void *, const void *));
 

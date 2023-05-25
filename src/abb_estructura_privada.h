#ifndef ABB_ESTRUCTURA_PRIVADA_H_
#define ABB_ESTRUCTURA_PRIVADA_H_

#include "abb.h"

struct nodo_abb {
	void *elemento;
	struct nodo_abb *izquierda;
	struct nodo_abb *derecha;
};

struct abb {
	nodo_abb_t *nodo_raiz;
	abb_comparador comparador;
	size_t tamanio;
};

typedef struct vector_nodos_estatico {
	void **vector;
	size_t tope;
	size_t posicion;
} vector_nodos_estatico_t;

#endif // ABB_ESTRUCTURA_PRIVADA_H_

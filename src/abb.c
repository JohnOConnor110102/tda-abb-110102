#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

const int ARBOL_SIN_NODOS = 0;
const int ELEMENTOS_IGUALES = 0;

nodo_abb_t *crear_nodo(void *elemento)
{
	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
	if (nodo == NULL)
		return NULL;

	nodo->elemento = elemento;
	nodo->derecha = NULL;
	nodo->izquierda = NULL;
	return nodo;
}

abb_t *abb_insertar_rec(abb_t *arbol, nodo_abb_t *nodo_a_insertar,
			nodo_abb_t *nodo_actual)
{
	if (arbol == NULL || nodo_a_insertar == NULL)
		return NULL;

	if (abb_vacio(arbol)) {
		arbol->nodo_raiz = nodo_a_insertar;
		arbol->tamanio++;
		return arbol;
	}

	if (arbol->comparador(nodo_a_insertar->elemento,
			      nodo_actual->elemento) > ELEMENTOS_IGUALES) {
		if (nodo_actual->derecha == NULL) {
			nodo_actual->derecha = nodo_a_insertar;
			arbol->tamanio++;
			return arbol;
		}
		return abb_insertar_rec(arbol, nodo_a_insertar,
					nodo_actual->derecha);
	} else if (arbol->comparador(nodo_a_insertar->elemento,
				     nodo_actual->elemento) <=
		   ELEMENTOS_IGUALES) {
		if (nodo_actual->izquierda == NULL) {
			nodo_actual->izquierda = nodo_a_insertar;
			arbol->tamanio++;
			return arbol;
		}
		return abb_insertar_rec(arbol, nodo_a_insertar,
					nodo_actual->izquierda);
	}
	return NULL;
}

void abb_destruir_todo_rec(abb_t *arbol, void (*destructor)(void *),
			   nodo_abb_t *nodo_actual)
{
	if (arbol == NULL || nodo_actual == NULL)
		return;

	if (abb_tamanio(arbol) == ARBOL_SIN_NODOS) {
		free(arbol);
		return;
	}
	if (nodo_actual->izquierda != NULL) {
		abb_destruir_todo_rec(arbol, destructor,
				      nodo_actual->izquierda);
	}
	if (nodo_actual->derecha != NULL) {
		abb_destruir_todo_rec(arbol, destructor, nodo_actual->derecha);
	}
	if (destructor != NULL)
		destructor(nodo_actual->elemento);

	free(nodo_actual);
	arbol->tamanio--;

	if (abb_tamanio(arbol) == ARBOL_SIN_NODOS) {
		free(arbol);
		return;
	}
	return;
}

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == NULL)
		return NULL;

	abb_t *abb = malloc(sizeof(abb_t));
	if (abb == NULL)
		return NULL;

	abb->nodo_raiz = NULL;
	abb->comparador = comparador;
	abb->tamanio = 0;

	return abb;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	nodo_abb_t *nodo_a_insertar = crear_nodo(elemento);

	return abb_insertar_rec(arbol, nodo_a_insertar, arbol->nodo_raiz);
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return elemento;
}

bool abb_vacio(abb_t *arbol)
{
	if (arbol == NULL || abb_tamanio(arbol) == ARBOL_SIN_NODOS)
		return true;

	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL)
		return 0;

	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	if (arbol == NULL)
		return;

	abb_destruir_todo(arbol, NULL);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL)
		return;

	abb_destruir_todo_rec(arbol, destructor, arbol->nodo_raiz);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}

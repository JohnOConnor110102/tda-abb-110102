#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

const int ARBOL_SIN_NODOS = 0;
const int ARBOL_UN_ELEMENTO = 1;

nodo_abb_t *crear_nodo(void *elemento)
{
	nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
	if (!nodo)
		return NULL;

	nodo->elemento = elemento;
	return nodo;
}

nodo_abb_t *abb_insertar_rec(abb_t *arbol, nodo_abb_t *nodo_a_insertar,
			     nodo_abb_t *nodo_actual)
{
	if (!nodo_a_insertar)
		return NULL;

	if (!nodo_actual) {
		arbol->tamanio++;
		return nodo_a_insertar;
	}
	int comparacion = arbol->comparador(nodo_a_insertar->elemento,
					    nodo_actual->elemento);
	if (comparacion > 0)
		nodo_actual->derecha = abb_insertar_rec(arbol, nodo_a_insertar,
							nodo_actual->derecha);
	else
		nodo_actual->izquierda = abb_insertar_rec(
			arbol, nodo_a_insertar, nodo_actual->izquierda);

	return nodo_actual;
}

nodo_abb_t *extraer_mas_derecho(nodo_abb_t *nodo_actual, void **extraido)
{
	if (!nodo_actual->derecha) {
		*extraido = nodo_actual->elemento;
		nodo_abb_t *nodo_actual_izquierda = nodo_actual->izquierda;
		free(nodo_actual);
		return nodo_actual_izquierda;
	}
	nodo_actual->derecha =
		extraer_mas_derecho(nodo_actual->derecha, extraido);
	return nodo_actual;
}

nodo_abb_t *abb_quitar_rec(abb_t *arbol, void *elemento,
			   nodo_abb_t *nodo_actual, void **eliminado)
{
	if (!nodo_actual)
		return NULL;

	int comparacion = arbol->comparador(nodo_actual->elemento, elemento);
	if (comparacion == 0) {
		nodo_abb_t *nodo_actual_derecha = nodo_actual->derecha;
		nodo_abb_t *nodo_actual_izquierda = nodo_actual->izquierda;
		*eliminado = nodo_actual->elemento;
		arbol->tamanio--;

		if (nodo_actual->derecha && nodo_actual->izquierda) {
			void *elemento_predecesor_inorden = NULL;
			nodo_actual->izquierda = extraer_mas_derecho(
				nodo_actual->izquierda,
				&elemento_predecesor_inorden);
			nodo_actual->elemento = elemento_predecesor_inorden;

			return nodo_actual;
		} else {
			free(nodo_actual);
			if (nodo_actual_derecha)
				return nodo_actual_derecha;

			return nodo_actual_izquierda;
		}
	}
	if (comparacion > 0)
		nodo_actual->izquierda = abb_quitar_rec(
			arbol, elemento, nodo_actual->izquierda, eliminado);

	if (comparacion < 0)
		nodo_actual->derecha = abb_quitar_rec(
			arbol, elemento, nodo_actual->derecha, eliminado);

	return nodo_actual;
}

nodo_abb_t *abb_buscar_rec(abb_t *arbol, void *elemento,
			   nodo_abb_t *nodo_actual)
{
	if (!nodo_actual)
		return NULL;

	int comparacion = arbol->comparador(nodo_actual->elemento, elemento);
	if (comparacion < 0)
		return abb_buscar_rec(arbol, elemento, nodo_actual->derecha);

	if (comparacion > 0)
		return abb_buscar_rec(arbol, elemento, nodo_actual->izquierda);

	return nodo_actual;
}

bool rellenar_vector(void *elemento, void *_vector)
{
	vector_nodos_estatico_t *vector = _vector;
	if (vector->posicion >= vector->tope)
		return false;

	vector->vector[vector->posicion] = elemento;
	vector->posicion++;
	return true;
}

bool abb_con_cada_elemento_inorden(nodo_abb_t *raiz,
				   bool (*funcion)(void *, void *), void *aux,
				   size_t *contador)
{
	if (!raiz)
		return true;

	bool continuar = abb_con_cada_elemento_inorden(raiz->izquierda, funcion,
						       aux, contador);
	if (!continuar)
		return false;

	(*contador)++;
	if (!funcion(raiz->elemento, aux))
		return false;

	return abb_con_cada_elemento_inorden(raiz->derecha, funcion, aux,
					     contador);
}

bool abb_con_cada_elemento_preorden(nodo_abb_t *raiz,
				    bool (*funcion)(void *, void *), void *aux,
				    size_t *contador)
{
	if (!raiz)
		return true;

	(*contador)++;
	if (!funcion(raiz->elemento, aux))
		return false;

	bool continuar = abb_con_cada_elemento_preorden(raiz->izquierda,
							funcion, aux, contador);
	if (!continuar)
		return false;

	return abb_con_cada_elemento_preorden(raiz->derecha, funcion, aux,
					      contador);
}

bool abb_con_cada_elemento_postorden(nodo_abb_t *raiz,
				     bool (*funcion)(void *, void *), void *aux,
				     size_t *contador)
{
	if (!raiz)
		return true;

	bool continuar = abb_con_cada_elemento_postorden(
		raiz->izquierda, funcion, aux, contador);
	if (!continuar)
		return false;
	abb_con_cada_elemento_postorden(raiz->derecha, funcion, aux, contador);
	(*contador)++;
	return funcion(raiz->elemento, aux);
}

void abb_destruir_todo_rec(abb_t *arbol, void (*destructor)(void *),
			   nodo_abb_t *nodo_actual)
{
	if (!arbol)
		return;

	if (abb_tamanio(arbol) == ARBOL_SIN_NODOS) {
		free(arbol);
		return;
	}
	if (!nodo_actual)
		return;

	abb_destruir_todo_rec(arbol, destructor, nodo_actual->izquierda);
	abb_destruir_todo_rec(arbol, destructor, nodo_actual->derecha);
	if (destructor)
		destructor(nodo_actual->elemento);

	free(nodo_actual);
	arbol->tamanio--;
	if (abb_tamanio(arbol) == ARBOL_SIN_NODOS)
		free(arbol);

	return;
}

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;

	abb_t *abb = calloc(1, sizeof(abb_t));
	if (!abb)
		return NULL;

	abb->comparador = comparador;
	return abb;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;

	arbol->nodo_raiz =
		abb_insertar_rec(arbol, crear_nodo(elemento), arbol->nodo_raiz);
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;
	void *eliminado = NULL;
	arbol->nodo_raiz =
		abb_quitar_rec(arbol, elemento, arbol->nodo_raiz, &eliminado);

	return eliminado;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol || abb_tamanio(arbol) == ARBOL_SIN_NODOS)
		return NULL;
	nodo_abb_t *nodo_elemento_buscado =
		abb_buscar_rec(arbol, elemento, arbol->nodo_raiz);
	if (nodo_elemento_buscado)
		return nodo_elemento_buscado->elemento;

	return NULL;
}

bool abb_vacio(abb_t *arbol)
{
	return (!arbol || abb_tamanio(arbol) == 0);
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol)
		return 0;

	return arbol->tamanio;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion)
		return 0;

	size_t contador = 0;
	switch (recorrido) {
	case INORDEN:
		abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux,
					      &contador);
		break;
	case PREORDEN:
		abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux,
					       &contador);
		break;
	case POSTORDEN:
		abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux,
						&contador);
		break;
	default:
		break;
	}

	return contador;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !array)
		return 0;

	vector_nodos_estatico_t vector_a_rellenar;
	vector_a_rellenar.vector = array;
	vector_a_rellenar.tope = tamanio_array;
	vector_a_rellenar.posicion = 0;
	abb_con_cada_elemento(arbol, recorrido, rellenar_vector,
			      &vector_a_rellenar);
	return vector_a_rellenar.posicion;
}

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol, NULL);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;

	abb_destruir_todo_rec(arbol, destructor, arbol->nodo_raiz);
}

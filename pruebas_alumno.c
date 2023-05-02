#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

int comparador(void *_elemento1, void *_elemento2)
{
	if (!_elemento1 && !_elemento2) {
		return 0;
	}
	int *elemento1 = _elemento1;
	int *elemento2 = _elemento2;
	return *elemento1 - *elemento2;
}
void destructor(void *_elemento)
{
	if (_elemento) {
		int *elemento = _elemento;
		(*elemento)++;
	}
}

void se_crea_correctamente_un_abb()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(!abb_crear(NULL),
		     "No se puede crear un abb con un comparador NULL.");
	pa2m_afirmar(arbol != NULL, "Se puede crear un abb.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El arbol tiene tamaño 0.");
	pa2m_afirmar(!arbol->nodo_raiz, "El nodo raiz es NULL.");
	pa2m_afirmar(arbol->comparador == comparador,
		     "El comparador es valido.\n");
	abb_destruir(arbol);
}

void se_inserta_correctamente_el_nodo_raiz()
{
	int diez = 10;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	pa2m_afirmar(arbol->tamanio == 1 && arbol->nodo_raiz &&
			     arbol->nodo_raiz->elemento == &diez,
		     "Se inserta correctamente el nodo raiz.\n");
	abb_destruir(arbol);
}

void se_inserta_correctamente_un_elemento_en_abb()
{
	int diez = 10;
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_insertar(NULL, &diez) == NULL,
		     "No se puede insertar en un arbol NULL.");
	pa2m_afirmar(abb_insertar(arbol, NULL) == arbol,
		     "Se puede insertar un elemento NULL.");
	pa2m_afirmar(arbol->tamanio == 1,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void se_insertan_correctamente_varios_elementos()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	abb_t *abb = abb_crear(comparador);
	abb_insertar(abb, &diez);
	abb_insertar(abb, &cinco);
	abb_insertar(abb, &quince);
	abb_insertar(abb, &dos);
	abb_insertar(abb, &siete);
	abb_insertar(abb, &doce);
	abb_insertar(abb, &diecisiete);
	pa2m_afirmar(abb_tamanio(abb) == 7,
		     "Se actualiza correctamente el tamaño del arbol.");
	nodo_abb_t *nodo_actual = abb->nodo_raiz;
	pa2m_afirmar(nodo_actual->elemento == &diez,
		     "El 1er elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->izquierda->elemento == &cinco,
		     "El 2do elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->derecha->elemento == &quince,
		     "El 3er elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->izquierda->izquierda->elemento == &dos,
		     "El 4to elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->izquierda->derecha->elemento == &siete,
		     "El 5to elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->derecha->izquierda->elemento == &doce,
		     "El 6to elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(
		nodo_actual->derecha->derecha->elemento == &diecisiete,
		"El 7mo elemento insertado esta en su posicion correcta.\n");
	abb_destruir(abb);
}

void se_quita_correctamente_un_elemento_de_abb()
{
	int diez = 10;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, NULL);
	pa2m_afirmar(abb_quitar(NULL, &diez) == NULL,
		     "No se puede quitar un elemento de un arbol NULL.");

	pa2m_afirmar(abb_quitar(arbol, NULL) == NULL,
		     "Se puede quitar un elemento NULL.");
	pa2m_afirmar(arbol->tamanio == 0,
		     "Se actualiza correctamente el tamaño del arbol.");
	pa2m_afirmar(
		arbol->nodo_raiz == NULL,
		"El nodo raiz del arbol es NULL luego de eliminar el unico elemento del arbol.\n");
	abb_destruir(arbol);
}

void se_quita_correctamente_raiz_hoja()
{
	int diez = 10;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	pa2m_afirmar(abb_quitar(arbol, &diez) == &diez,
		     "Se quita correctamente el nodo raiz siendo hoja.");
	pa2m_afirmar(abb_buscar(arbol, &diez) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo_raiz es NULL.");
	pa2m_afirmar(arbol->tamanio == 0,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void se_quita_correctamente_raiz_con_hijo_derecho()
{
	int diez = 10, quince = 15;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &quince);
	pa2m_afirmar(
		abb_quitar(arbol, &diez) == &diez,
		"Se quita correctamente el nodo raiz con un hijo derecho.");
	pa2m_afirmar(abb_buscar(arbol, &diez) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(arbol->nodo_raiz->elemento == &quince,
		     "Se actualiza correctamente el nodo raiz.");
	pa2m_afirmar(arbol->tamanio == 1,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void se_quita_correctamente_raiz_con_hijo_izquierdo()
{
	int diez = 10, cinco = 5;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	pa2m_afirmar(
		abb_quitar(arbol, &diez) == &diez,
		"Se quita correctamente el nodo raiz con un hijo izquierdo.");
	pa2m_afirmar(abb_buscar(arbol, &diez) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(arbol->nodo_raiz->elemento == &cinco,
		     "Se actualiza correctamente el nodo raiz.");
	pa2m_afirmar(arbol->tamanio == 1,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void se_quita_correctamente_raiz_con_dos_hijos()
{
	int diez = 10, cinco = 5, quince = 15;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	pa2m_afirmar(abb_quitar(arbol, &diez) == &diez,
		     "Se quita correctamente el nodo raiz con dos hijos.");
	pa2m_afirmar(abb_buscar(arbol, &diez) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->elemento == &cinco,
		"Se actualiza correctamente el nodo raiz con el predecesor inorden.");
	pa2m_afirmar(
		arbol->nodo_raiz->derecha->elemento == &quince,
		"El nuevo nodo raiz mantiene el hijo derecho del original.");
	pa2m_afirmar(arbol->tamanio == 2,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void se_quitan_correctamente_nodos()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	pa2m_afirmar(abb_quitar(arbol, &diecisiete) == &diecisiete,
		     "Se quita correctamente un nodo hoja.");
	pa2m_afirmar(abb_buscar(arbol, &diecisiete) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->derecha->derecha == NULL,
		"Se actualiza correctamente el puntero al nodo quitado en NULL.");
	pa2m_afirmar(arbol->tamanio == 6,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	pa2m_afirmar(abb_quitar(arbol, &cinco) == &cinco,
		     "Se quita correctamente un nodo con dos hijos.");
	pa2m_afirmar(abb_buscar(arbol, &cinco) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->izquierda->elemento == &dos,
		"Se actualiza correctamente el nodo eliminado con el predecesor inorden.");
	pa2m_afirmar(
		arbol->nodo_raiz->izquierda->derecha->elemento == &siete,
		"El predecesor inorden mantiene el hijo derecho del original.");
	pa2m_afirmar(arbol->tamanio == 5,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	pa2m_afirmar(abb_quitar(arbol, &dos) == &dos,
		     "Se quita correctamente un nodo con hijo derecho.");
	pa2m_afirmar(abb_buscar(arbol, &dos) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->izquierda->elemento == &siete,
		"Se actualiza correctamente el valor en posicion del nodo eliminado con el de su hijo derecho.");
	pa2m_afirmar(arbol->tamanio == 4,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	pa2m_afirmar(abb_quitar(arbol, &quince) == &quince,
		     "Se quita correctamente un nodo con hijo izquierdo.");
	pa2m_afirmar(abb_buscar(arbol, &quince) == NULL,
		     "No se encuenctra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->derecha->elemento == &doce,
		"Se actualiza correctamente el valor en posicion del nodo eliminado con el de su hijo izquierdo.");
	pa2m_afirmar(arbol->tamanio == 3,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void se_busca_correctamante_un_elemento()
{
	int diez = 10, cinco = 5;
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_buscar(NULL, &diez) == NULL,
		     "No se puede buscar un elemento en un arbol NULL.");
	abb_insertar(arbol, &diez);
	pa2m_afirmar(abb_buscar(arbol, &diez) == &diez,
		     "Se busca correctamente un elemento de un arbol.");
	pa2m_afirmar(abb_buscar(arbol, &cinco) == NULL,
		     "Devuelve NULL si se busca un elemento inexistente.\n");
	abb_destruir(arbol);
}

void se_buscan_correctamente_varios_elementos()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	pa2m_afirmar(abb_buscar(arbol, &diez) == &diez,
		     "Se busca el 1er elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &cinco) == &cinco,
		     "Se busca el 2do elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &quince) == &quince,
		     "Se busca el 3er elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &dos) == &dos,
		     "Se busca el 4to elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &siete) == &siete,
		     "Se busca el 5to elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &doce) == &doce,
		     "Se busca el 6to elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &diecisiete) == &diecisiete,
		     "Se busca el 7mo elemento del arbol y se encuentra.\n");
	abb_destruir(arbol);
}

void se_obtiene_correctamente_estado_con_abb_vacio()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_vacio(NULL) == true,
		     "Devuelve true con un arbol NULL.");
	pa2m_afirmar(abb_vacio(arbol) == true,
		     "Devuelve true con un arbol vacío.");
	abb_insertar(arbol, &diez);
	pa2m_afirmar(abb_vacio(arbol) == false,
		     "Devuelve false con un arbol con un elemento.");
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	pa2m_afirmar(abb_vacio(arbol) == false,
		     "Devuelve false con un arbol con varios elementos.");
	abb_destruir(arbol);
}

void se_obtiene_correctamente_tamanio_de_abb()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_tamanio(NULL) == 0, "Devuelve 0 si el arbol es NULL.");
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "Un arbol vacío tiene tamaño 0.\n");
	abb_insertar(arbol, &diez);
	pa2m_afirmar(abb_tamanio(arbol) == 1,
		     "Se interta un elemento y el tamaño es 1.");
	abb_insertar(arbol, &cinco);
	pa2m_afirmar(abb_tamanio(arbol) == 2,
		     "Se interta un elemento y el tamaño es 2.");
	abb_insertar(arbol, &quince);
	pa2m_afirmar(abb_tamanio(arbol) == 3,
		     "Se interta un elemento y el tamaño es 3.");
	abb_insertar(arbol, &dos);
	pa2m_afirmar(abb_tamanio(arbol) == 4,
		     "Se interta un elemento y el tamaño es 4.");
	abb_insertar(arbol, &siete);
	pa2m_afirmar(abb_tamanio(arbol) == 5,
		     "Se interta un elemento y el tamaño es 5.");
	abb_insertar(arbol, &doce);
	pa2m_afirmar(abb_tamanio(arbol) == 6,
		     "Se interta un elemento y el tamaño es 6.");
	abb_insertar(arbol, &diecisiete);
	pa2m_afirmar(abb_tamanio(arbol) == 7,
		     "Se interta un elemento y el tamaño es 7.");
	abb_destruir(arbol);
}

bool suma_uno_todo(void *_elemento, void *_get_ignored)
{
	if (!_elemento)
		return false;

	int *elemento = _elemento;
	(*elemento)++;
	return true;
}

bool suma_uno_hasta_siete(void *_elemento, void *_get_ignored)
{
	if (!_elemento)
		return false;

	int *elemento = _elemento;
	(*elemento)++;
	if (*elemento == 7)
		return false;

	return true;
}

void se_aplica_correctamente_con_cada_elemento()
{
	abb_recorrido diez = 10;
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, suma_uno_todo,
					   NULL) == 0,
		     "Devuelve 0 con un arbol NULL.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, &diez) == 0,
		     "Devuelve 0 con una función NULL.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, diez, suma_uno_hasta_siete,
					   NULL) == 0,
		     "Devuelve 0 con un recorrido inválido.");
	abb_insertar(arbol, &diez);
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, suma_uno_todo,
					   NULL) != 0,
		     "Se puede invocar con un aux NULL.\n");
	abb_destruir(arbol);
}

void se_aplica_correctamente_con_cada_elemento_INORDEN()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, suma_uno_todo,
					   &diez) == 0,
		     "Devuelve 0 con un arbol NULL iterando INORDEN.");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, &diez) == 0,
		     "Devuelve 0 con una función NULL iterando INORDEN.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, suma_uno_todo,
					   &diez) == 0,
		     "Devuelve 0 con un arbol vacío iterando INORDEN.");
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, INORDEN, suma_uno_todo, NULL) == 7,
		"Se aplica la función la cantidad de veces correcta iterando INORDEN todo el arbol.");
	pa2m_afirmar(
		diez == 11 && cinco == 6 && dos == 3 && siete == 8 &&
			quince == 16 && doce == 13 && diecisiete == 18,
		"Se aplica la función a cada uno de los elementos iterando INORDEN todo el arbol.");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, INORDEN, suma_uno_hasta_siete,
				      NULL) == 2,
		"Se aplica la función la cantidad de veces correcta iterando INORDEN parte del arbol.");
	pa2m_afirmar(
		cinco == 7 && dos == 4 && siete == 8,
		"Se aplica la función a los elementos correctos iterando INORDEN parte del arbol.\n");
	abb_destruir(arbol);
}

void se_aplica_correctamente_con_cada_elemento_PREORDEN()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	pa2m_afirmar(abb_con_cada_elemento(NULL, PREORDEN, suma_uno_todo,
					   &diez) == 0,
		     "Devuelve 0 con un arbol NULL iterando PREORDEN.");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, NULL, &diez) == 0,
		     "Devuelve 0 con una función NULL iterando PREORDEN.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, suma_uno_todo,
					   &diez) == 0,
		     "Devuelve 0 con un arbol vacío iterando PREORDEN.");
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, PREORDEN, suma_uno_todo, NULL) ==
			7,
		"Se aplica la función la cantidad de veces correcta iterando PREORDEN todo el arbol.");
	pa2m_afirmar(
		diez == 11 && cinco == 6 && dos == 3 && siete == 8 &&
			quince == 16 && doce == 13 && diecisiete == 18,
		"Se aplica la función a cada uno de los elementos iterando PREORDEN todo el arbol.");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, PREORDEN, suma_uno_hasta_siete,
				      NULL) == 2,
		"Se aplica la función la cantidad de veces correcta iterando PREORDEN parte del arbol.");
	pa2m_afirmar(
		cinco == 7 && siete == 8 && dos == 3,
		"Se aplica la función a los elementos correctos iterando PREORDEN parte del arbol.\n");
	abb_destruir(arbol);
}

void se_aplica_correctamente_con_cada_elemento_POSTORDEN()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	pa2m_afirmar(abb_con_cada_elemento(NULL, POSTORDEN, suma_uno_todo,
					   &diez) == 0,
		     "Devuelve 0 con un arbol NULL iterando POSTORDEN.");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, NULL, &diez) == 0,
		     "Devuelve 0 con una función NULL iterando POSTORDEN.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, suma_uno_todo,
					   &diez) == 0,
		     "Devuelve 0 con un arbol vacío iterando POSTORDEN.");
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, POSTORDEN, suma_uno_todo, NULL) ==
			7,
		"Se aplica la función la cantidad de veces correcta iterando POSTORDEN todo el arbol.");
	pa2m_afirmar(
		diez == 11 && cinco == 6 && dos == 3 && siete == 8 &&
			quince == 16 && doce == 13 && diecisiete == 18,
		"Se aplica la función a cada uno de los elementos iterando POSTORDEN todo el arbol.");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, POSTORDEN, suma_uno_hasta_siete,
				      NULL) == 3,
		"Se aplica la función la cantidad de veces correcta iterando POSTORDEN parte del arbol.");
	pa2m_afirmar(
		cinco == 7 && siete == 9 && dos == 4,
		"Se aplica la función a los elementos correctos iterando POSTORDEN parte del arbol.\n");
	abb_destruir(arbol);
}

void se_recorre_correctamente_un_abb()
{
	int diez = 10;
	void *array[7];
	pa2m_afirmar(abb_recorrer(NULL, INORDEN, array, 7) == 0,
		     "Devuelve 0 con un arbol NULL.");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, 7) == 0,
		     "Devuelve 0 con un arbol vacío.");
	abb_insertar(arbol, &diez);
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, NULL, 7) == 0,
		     "Devuelve 0 con un array NULL.");
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, 0) == 0,
		     "Devuelve 0 con un array de tamaño 0");
	pa2m_afirmar(abb_recorrer(arbol, diez, array, 7) == 0,
		     "Devuelve 0 con un recorrido inválido.");
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, 7) != 0,
		     "Se puede invocar con parámetros válidos.\n");
	abb_destruir(arbol);
}

void se_recorre_correctamente_un_abb_INORDEN()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	void *array[7];
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	size_t contador = abb_recorrer(arbol, INORDEN, array, 7);
	pa2m_afirmar(contador != 0,
		     "Se puede recorrer el abb en recorrido INORDEN.");
	pa2m_afirmar(
		contador == 7,
		"Devuelve la cantidad correcta de elementos almacenados iterando INORDEN.");
	pa2m_afirmar(
		array[0] == &dos,
		"El 1er elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[1] == &cinco,
		"El 2do elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[2] == &siete,
		"El 3er elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[3] == &diez,
		"El 4to elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[4] == &doce,
		"El 5to elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[5] == &quince,
		"El 6to elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[6] == &diecisiete,
		"El 7mo elemento del vector es el correcto iterando INORDEN.\n");
	abb_destruir(arbol);
}

void se_recorre_correctamente_un_abb_PREORDEN()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	void *array[7];
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	size_t contador = abb_recorrer(arbol, PREORDEN, array, 7);
	pa2m_afirmar(contador != 0,
		     "Se puede recorrer el abb en recorrido PREORDEN.");
	pa2m_afirmar(
		contador == 7,
		"Devuelve la cantidad correcta de elementos almacenados iterando PREORDEN.");
	pa2m_afirmar(
		array[0] == &diez,
		"El 1er elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[1] == &cinco,
		"El 2do elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[2] == &dos,
		"El 3er elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[3] == &siete,
		"El 4to elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[4] == &quince,
		"El 5to elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[5] == &doce,
		"El 6to elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[6] == &diecisiete,
		"El 7mo elemento del vector es el correcto iterando PREORDEN.\n");
	abb_destruir(arbol);
}

void se_recorre_correctamente_un_abb_POSTORDEN()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	void *array[7];
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	size_t contador = abb_recorrer(arbol, POSTORDEN, array, 7);
	pa2m_afirmar(contador != 0,
		     "Se puede recorrer el abb en recorrido POSTORDEN.");
	pa2m_afirmar(
		contador == 7,
		"Devuelve la cantidad correcta de elementos almacenados iterando POSTORDEN.");
	pa2m_afirmar(
		array[0] == &dos,
		"El 1er elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[1] == &siete,
		"El 2do elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[2] == &cinco,
		"El 3er elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[3] == &doce,
		"El 4to elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[4] == &diecisiete,
		"El 5to elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[5] == &quince,
		"El 6to elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[6] == &diez,
		"El 7mo elemento del vector es el correcto iterando POSTORDEN.\n");
	abb_destruir(arbol);
}

void suma_uno_todo_destructor(void *_elemento)
{
	if (!_elemento)
		return;

	int *elemento = _elemento;
	(*elemento)++;
	return;
}

void se_destruye_todo_correctamente()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	abb_insertar(arbol, &doce);
	abb_insertar(arbol, &diecisiete);
	abb_destruir_todo(NULL, suma_uno_todo_destructor);
	pa2m_afirmar(diez == 10, "No hace nada con un arbol NULL.");
	abb_destruir_todo(arbol, suma_uno_todo_destructor);
	pa2m_afirmar(diez == 11 && cinco == 6 && dos == 3 && siete == 8 &&
			     quince == 16 && doce == 13 && diecisiete == 18,
		     "Se aplica la función a todos los elementos del arbol.\n");
}

void pruebas_tda_abb()
{
	pa2m_nuevo_grupo("Pruebas `abb_crear`");
	se_crea_correctamente_un_abb();
	pa2m_nuevo_grupo("Pruebas `abb_insertar`");
	se_inserta_correctamente_un_elemento_en_abb();
	se_inserta_correctamente_el_nodo_raiz();
	se_insertan_correctamente_varios_elementos();
	pa2m_nuevo_grupo("Pruebas `abb_quitar`");
	se_quita_correctamente_un_elemento_de_abb();
	se_quita_correctamente_raiz_hoja();
	se_quita_correctamente_raiz_con_hijo_derecho();
	se_quita_correctamente_raiz_con_hijo_izquierdo();
	se_quita_correctamente_raiz_con_dos_hijos();
	se_quitan_correctamente_nodos();
	pa2m_nuevo_grupo("Pruebas `abb_buscar`");
	se_busca_correctamante_un_elemento();
	se_buscan_correctamente_varios_elementos();
	pa2m_nuevo_grupo("Pruebas `abb_vacio`");
	se_obtiene_correctamente_estado_con_abb_vacio();
	pa2m_nuevo_grupo("Pruebas `abb_tamanio`");
	se_obtiene_correctamente_tamanio_de_abb();
	pa2m_nuevo_grupo("Pruebas `abb_con_cada_elemento`");
	se_aplica_correctamente_con_cada_elemento();
	se_aplica_correctamente_con_cada_elemento_INORDEN();
	se_aplica_correctamente_con_cada_elemento_PREORDEN();
	se_aplica_correctamente_con_cada_elemento_POSTORDEN();
	pa2m_nuevo_grupo("Pruebas `abb_recorrer`");
	se_recorre_correctamente_un_abb();
	se_recorre_correctamente_un_abb_INORDEN();
	se_recorre_correctamente_un_abb_PREORDEN();
	se_recorre_correctamente_un_abb_POSTORDEN();
	pa2m_nuevo_grupo("Pruebas `abb_destruir_todo`");
	se_destruye_todo_correctamente();
}

int main()
{
	pa2m_nuevo_grupo(
		"======================== PRUEBS TDA ABB ========================");
	pruebas_tda_abb();

	return pa2m_mostrar_reporte();
}

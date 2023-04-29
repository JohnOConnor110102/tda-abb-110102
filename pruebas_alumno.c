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

/* abb_t *crear_abb_con_elementos()
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
	return abb;
} */

void se_inserta_correctamente_un_elemento_en_abb()
{
	int diez = 10;
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_insertar(NULL, &diez) == NULL,
		     "No se puede insertar en un arbol NULL.");
	pa2m_afirmar(abb_insertar(arbol, NULL) == arbol,
		     "Se puede insertar un elemento NULL.");
	pa2m_afirmar(arbol->tamanio == 1,
		     "Se actualia correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void se_insertan_varios_elementos_correctamente()
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

void se_quita_correctamente_nodos()
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

void pruebas_tda_abb()
{
	pa2m_nuevo_grupo("Pruebas `abb_crear`");
	se_crea_correctamente_un_abb();
	pa2m_nuevo_grupo("Pruebas `abb_insertar`");
	se_inserta_correctamente_un_elemento_en_abb();
	se_inserta_correctamente_el_nodo_raiz();
	se_insertan_varios_elementos_correctamente();
	pa2m_nuevo_grupo("Pruebas `abb_quitar`");
	se_quita_correctamente_un_elemento_de_abb();
	se_quita_correctamente_raiz_hoja();
	se_quita_correctamente_raiz_con_hijo_derecho();
	se_quita_correctamente_raiz_con_hijo_izquierdo();
	se_quita_correctamente_raiz_con_dos_hijos();
	se_quita_correctamente_nodos();
}

int main()
{
	pa2m_nuevo_grupo(
		"======================== PRUEBS TDA ABB ========================");
	pruebas_tda_abb();
	abb_t *arbol = abb_crear(comparador);

	//abb_insertar(arbol, &diez);
	//abb_insertar(arbol, &cinco);
	//abb_insertar(arbol, &quince);
	//abb_insertar(arbol, &dos);
	//abb_insertar(arbol, &siete);
	//abb_insertar(arbol, &doce);
	//abb_insertar(arbol, &diecisiete);

	abb_destruir_todo(arbol, destructor);
	/* int contador = 0;

	pa2m_afirmar(
		contador == 6,
		"Llamar abb_destruir_todo aplica el destructor la cantidad de veces adecuada."); */

	abb_t *abb = abb_crear(comparador);
	void *array[7];

	abb_recorrer(abb, PREORDEN, array, 7);

	abb_destruir(abb);
	return pa2m_mostrar_reporte();
}

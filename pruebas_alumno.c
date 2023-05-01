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
}

int main()
{
	pa2m_nuevo_grupo(
		"======================== PRUEBS TDA ABB ========================");
	pruebas_tda_abb();

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

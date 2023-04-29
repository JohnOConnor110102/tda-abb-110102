#include "pa2m.h"
#include "src/abb.h"

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
int main()
{
	int diez = 10, cinco = 5, dos = 2, siete = 7, quince = 15, doce = 12,
	    diecisiete = 17;
	pa2m_nuevo_grupo(
		"\n======================== PRUEBS TDA ABB ========================");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_tamanio(arbol) == 0,
		     "El arbol creado tiene tamanio 0");

	//abb_insertar(arbol, &diez);
	abb_insertar(arbol, &cinco);
	//abb_insertar(arbol, &quince);
	abb_insertar(arbol, &dos);
	abb_insertar(arbol, &siete);
	//abb_insertar(arbol, &doce);
	//abb_insertar(arbol, &diecisiete);

	pa2m_afirmar(abb_quitar(arbol, &dos) != NULL,
		     "Puedo eliminar un nodo hoja");
	abb_insertar(arbol, &dos);
	pa2m_afirmar(abb_quitar(arbol, &dos) == &dos,
		     "Se devuelve el elemento correcto.");
	pa2m_afirmar(abb_buscar(arbol, &dos) == NULL,
		     "El elemento eliminado no existe mas.");

	abb_destruir_todo(arbol, destructor);
	/* int contador = 0;

	pa2m_afirmar(
		contador == 6,
		"Llamar abb_destruir_todo aplica el destructor la cantidad de veces adecuada."); */

	abb_t *abb = abb_crear(comparador);
	void *array[7];
	abb_insertar(abb, &diez);
	abb_insertar(abb, &cinco);
	abb_insertar(abb, &quince);
	abb_insertar(abb, &dos);
	abb_insertar(abb, &siete);
	abb_insertar(abb, &doce);
	abb_insertar(abb, &diecisiete);
	abb_recorrer(abb, PREORDEN, array, 7);
	for (size_t i = 0; i < 7; i++) {
		printf("nro en posicion %lu: %p\n", i, array[i]);
	}
	abb_destruir(abb);
	return pa2m_mostrar_reporte();
}

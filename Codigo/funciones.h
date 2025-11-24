#ifndef FUNCIONES_H
#define FUNCIONES_H

lectura leer_entradas(int cant_nodos, int instancia_nodos, int cant_usuarios, int instancia_usuarios);
void funcion_evaluacion(solucion* solucion_actual, nodos* nodo, usuario* usuario);
void crear_solucion_aleatoria (solucion *i_temp, nodos* nodo, usuario* usuario);
int int_rand (int a, int b);
void escribir_salida(solucion * mejor_solucion, usuario * usuario, ofstream & res);
void opt_2(solucion * solucion_actual, solucion * candidata_solucion, nodos* nodo, usuario* usuario, int pos1, int pos2, int debug);
void eliminacion(solucion * solucion_actual, solucion * candidata_solucion, nodos* nodo, usuario* usuario, int nodo_eliminar, int debug);
void addition(solucion * solucion_actual, solucion * candidata_solucion, nodos* nodo, usuario* usuario, int nodo_agregar, int debug);
void swap(solucion * solucion_actual, solucion * candidata_solucion, nodos* nodo, usuario* usuario, int pos_nodo_swapear, int debug);
void exchange(solucion * solucion_actual, solucion * candidata_solucion, nodos* nodo, usuario* usuario, int pos_nodo_swapear, int debug);

#endif
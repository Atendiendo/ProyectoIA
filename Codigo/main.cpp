#include "includes.h"
#include "globales.h"
#include "funciones.h"

int main() {
    int cant_nodos, instancia, cant_usuarios;
    cout << "Ingresar cantidad de nodos, instancia y cantidad de usuarios, separados por un espacio en blanco." << endl;
    cin >> cant_nodos >> instancia >> cant_usuarios;
    leer_entradas(cant_nodos, instancia, cant_usuarios);
    return 0;
}
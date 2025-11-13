#include "includes.h"
#include "globales.h"
#include "funciones.h"

int main() {
    int semilla = 0; //Luego permitir meter semilla a mano
    int debug = 1; //Luego permitir debug a mano
    int restart = 0, Mr = 10, iteracion; //Lo mismo
    int cant_nodos, instancia, cant_usuarios;
    cout << "Ingresar cantidad de nodos, instancia y cantidad de usuarios, separados por un espacio en blanco." << endl;
    cin >> cant_nodos >> instancia >> cant_usuarios;
    lectura resultado_lectura;
    resultado_lectura = leer_entradas(cant_nodos, instancia, cant_usuarios);

    nodos nodos_leidos;
    nodos_leidos = resultado_lectura.nodos_leidos;
    vector<usuario> usuarios_list;
    usuarios_list = resultado_lectura.usuarios;

    solucion solucion_actual(__INT_MAX__, cant_nodos), candidata_solucion(__INT_MAX__, cant_nodos), mejor_candidata(__INT_MAX__, cant_nodos), mejor_solucion(0, cant_nodos);

    //Por ahora solo usuario 1
    //semilla aleatoria
    srand48 (semilla);
    bool optimo_local;
    //Solucion inicial
    crear_solucion_aleatoria(&solucion_actual, &nodos_leidos, &usuarios_list[0]);

    mejor_solucion=solucion_actual;
    if(debug) cout<<"Restart | Iteracion | Solucion-Actual \t\t\t\t |Vecindario \t\t\t\t\t  |Mejor-solucion"<<endl;   
    if(debug) cout<<"-------------------------------------------------------------------------------------";
    if(debug) cout<<"-------------------------------------------------------------------------------------"<<endl;
    for(restart=0;restart<Mr;restart++){
        optimo_local=false;
        iteracion=0;
        do{
        if(debug) cout<<"   "<<restart+1 <<" \t     "<<iteracion+1<<"\t\t"<<solucion_actual<<endl;
        //time_t ini_it=time(NULL);
        mejor_candidata=solucion_actual;
        //Aca tirar un if para definir el tipo de movimiento
        for(int current=0;current<solucion_actual.tour.size();current++){
            if(debug) cout<<"\t\t\t\t  \t\t\t";
            //Aca se define el vecindario
            //Aca ver lo de los demas movimientos
            //SWaP(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[0], current, current+1, 1);
            eliminacion(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[0], current, 1);
            if(debug) cout<<"\t"<< candidata_solucion<<endl;
            if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                mejor_candidata=candidata_solucion;
        }
        iteracion++;
        if(debug) getchar();
        if(mejor_candidata.aptitud>solucion_actual.aptitud) //Maximizacion
            solucion_actual=mejor_candidata;
        else
            optimo_local=true;
        }while(!optimo_local);
        if(solucion_actual.aptitud > mejor_solucion.aptitud)
            mejor_solucion = solucion_actual;
        if(debug) cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"<<mejor_solucion<<endl;
        crear_solucion_aleatoria(&solucion_actual, &nodos_leidos, &usuarios_list[0]);
        if(debug) getchar();
    }
    if(debug) cout<<"-------------------------------------------------------------------------------------"<<endl;

    return 0;
}
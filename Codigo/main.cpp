#include "includes.h"
#include "globales.h"
#include "funciones.h"

int main(int argc, char *argv[]) {
    int semilla, debug, Mr, iteracion;
    int cant_nodos, instancia, cant_usuarios;
    //cout << "Ingresar cantidad de nodos, instancia, cantidad de usuarios, semilla, numero de restarts, debug separados por un espacio en blanco." << endl;
    //cin >> cant_nodos >> instancia >> cant_usuarios >> semilla >> Mr >> debug;

    cant_nodos = atoi(argv[1]);
    instancia = atoi(argv[2]);
    cant_usuarios = atoi(argv[3]);
    semilla = atoi(argv[4]);
    Mr = atoi(argv[5]);
    debug = atoi(argv[6]);

    lectura resultado_lectura;
    resultado_lectura = leer_entradas(cant_nodos, instancia, cant_usuarios);
    //Archivo salida
    ofstream res;
    res.open("sol_" + to_string(cant_nodos) + "_instancia_" + to_string(instancia) + ".txt");

    nodos nodos_leidos;
    nodos_leidos = resultado_lectura.nodos_leidos;
    vector<usuario> usuarios_list;
    usuarios_list = resultado_lectura.usuarios;

    solucion solucion_actual(__INT_MAX__, cant_nodos), candidata_solucion(__INT_MAX__, cant_nodos), mejor_candidata(__INT_MAX__, cant_nodos), mejor_solucion(0, cant_nodos);

    //semilla aleatoria
    srand48 (semilla);
    bool optimo_local;

    //Iterar sobre usuarios
    for (int i = 0; i < cant_usuarios; i++) {
        if(debug) cout<<"USUARIO NUMERO: " << i << endl;
        //Solucion inicial
        crear_solucion_aleatoria(&solucion_actual, &nodos_leidos, &usuarios_list[i]);

        mejor_solucion=solucion_actual;
        if(debug) cout<<"Restart | Iteracion | Solucion-Actual \t\t\t\t |Vecindario \t\t\t\t\t  |Mejor-solucion"<<endl;   
        if(debug) cout<<"-------------------------------------------------------------------------------------";
        if(debug) cout<<"-------------------------------------------------------------------------------------"<<endl;
        for(int restart=0;restart<Mr;restart++){
            optimo_local=false;
            iteracion=0;
            do{
            if(debug) cout<<"   "<<restart+1 <<" \t     "<<iteracion+1<<"\t\t"<<solucion_actual<<endl;
            //time_t ini_it=time(NULL);
            mejor_candidata=solucion_actual;
            //Aca tirar un if para definir el tipo de movimiento
            for(int current=1;current<solucion_actual.tour.size();current++){
                if(debug) cout<<"\t\t\t\t  \t\t\t";
                //Aca se define el vecindario
                //Aca ver lo de los demas movimientos
                //SWaP(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[0], current, current+1, debug);
                eliminacion(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], current, debug);
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
            crear_solucion_aleatoria(&solucion_actual, &nodos_leidos, &usuarios_list[i]);
            if(debug) getchar();
        }
        if(debug) cout<<"-------------------------------------------------------------------------------------"<<endl;
        escribir_salida(&mejor_solucion, &usuarios_list[i], res);
        cout << "Mejor solucion usuario " << i << endl;
        cout << mejor_solucion << endl;
    }
    res.close();

    

    return 0;
}
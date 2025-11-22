#include "includes.h"
#include "globales.h"
#include "funciones.h"

int main(int argc, char *argv[]) {
    int semilla, debug, Mr, iteracion;
    int cant_nodos, instanciaNodos, instanciaUsuarios, cant_usuarios;
    //cout << "Ingresar cantidad de nodos, instancia, cantidad de usuarios, semilla, numero de restarts, debug separados por un espacio en blanco." << endl;
    //cin >> cant_nodos >> instancia >> cant_usuarios >> semilla >> Mr >> debug;

    cant_nodos = atoi(argv[1]);
    instanciaNodos = atoi(argv[2]);
    cant_usuarios = atoi(argv[3]);
    instanciaUsuarios = atoi(argv[4]);
    semilla = atoi(argv[5]);
    Mr = atoi(argv[6]);
    debug = atoi(argv[7]);

    lectura resultado_lectura;
    resultado_lectura = leer_entradas(cant_nodos, instanciaNodos, cant_usuarios, instanciaUsuarios);
    //Archivo salida
    ofstream res;
    res.open("sol_" + to_string(cant_nodos) + "_instancia_" + to_string(instanciaUsuarios) + ".txt");

    nodos nodos_leidos;
    nodos_leidos = resultado_lectura.nodos_leidos;
    vector<usuario> usuarios_list;
    usuarios_list = resultado_lectura.usuarios;

    solucion solucion_actual(__INT_MAX__, cant_nodos), candidata_solucion(__INT_MAX__, cant_nodos), mejor_candidata(__INT_MAX__, cant_nodos), mejor_solucion(0, cant_nodos);

    //semilla aleatoria
    srand48 (semilla);
    bool optimo_local;
    int movimiento;

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

            //Si se sobrepasa tiempo maximo, eliminar nodos
            if (solucion_actual.factibilidad == 'I' && solucion_actual.tour.size() > 2) {
                for(int current=1;current<solucion_actual.tour.size();current++){
                    if(debug) cout<<"\t\t\t\t  \t\t\t";
                    eliminacion(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], current, debug);
                    if(debug) cout<<"\t"<< candidata_solucion<<endl;
                    if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                        mejor_candidata=candidata_solucion;
                }
            } else {
                //Elegir tipo movimiento
                movimiento = int_rand(0,4);
                switch (movimiento) {
                    case 0:
                        //Ejecutar opt_2
                        for(int current=1;current<solucion_actual.tour.size() - 1;current++){
                            if(debug) cout<<"\t\t\t\t  \t\t\t";
                            opt_2(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], current, current+1, debug);
                            if(debug) cout<<"\t"<< candidata_solucion<<endl;
                            if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                                mejor_candidata=candidata_solucion;
                        }
                        break;
                    case 1:
                        //Ejecutar addition si se puede
                        if (solucion_actual.nodos_no_visitados.size() > 0) {
                            for (int j = 0; j < solucion_actual.nodos_no_visitados.size(); j++) {
                                if(debug) cout<<"\t\t\t\t  \t\t\t";
                                addition(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], j, debug);
                                if(debug) cout<<"\t"<< candidata_solucion<<endl;
                                if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                                    mejor_candidata=candidata_solucion;
                            }
                        } else { //Si no se puede ejecutar eliminacion
                            for(int current=1;current<solucion_actual.tour.size();current++){
                                if(debug) cout<<"\t\t\t\t  \t\t\t";
                                eliminacion(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], current, debug);
                                if(debug) cout<<"\t"<< candidata_solucion<<endl;
                                if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                                    mejor_candidata=candidata_solucion;
                            }
                        }
                        break;
                    case 2:
                        //Ejecutar swap
                        for(int current=1;current<solucion_actual.tour.size();current++){
                            if(debug) cout<<"\t\t\t\t  \t\t\t";
                            swap(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], current, debug);
                            if(debug) cout<<"\t"<< candidata_solucion<<endl;
                            if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                                    mejor_candidata=candidata_solucion;
                        }
                        break;
                    case 3:
                        //Ejecutar exchange
                        for(int current=1;current<solucion_actual.nodos_no_visitados.size();current++){
                            if(debug) cout<<"\t\t\t\t  \t\t\t";
                            exchange(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], current, debug);
                            if(debug) cout<<"\t"<< candidata_solucion<<endl;
                            if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                                    mejor_candidata=candidata_solucion;
                        }
                        break;
                    case 4:
                        //Ejecutar eliminacion si se puede
                        if (solucion_actual.tour.size() > 2) {
                            for(int current=1;current<solucion_actual.tour.size();current++){
                                if(debug) cout<<"\t\t\t\t  \t\t\t";
                                eliminacion(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], current, debug);
                                if(debug) cout<<"\t"<< candidata_solucion<<endl;
                                if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                                    mejor_candidata=candidata_solucion;
                            }
                        } else { //Si no se puede ejecutar addition
                            for (int j = 0; j < solucion_actual.nodos_no_visitados.size(); j++) {
                                if(debug) cout<<"\t\t\t\t  \t\t\t";
                                addition(&solucion_actual, &candidata_solucion, &nodos_leidos, &usuarios_list[i], j, debug);
                                if(debug) cout<<"\t"<< candidata_solucion<<endl;
                                if(candidata_solucion.aptitud > mejor_candidata.aptitud)
                                    mejor_candidata=candidata_solucion;
                            }
                        }
                        break;
                }
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
        cout << endl;
    }
    res.close();

    

    return 0;
}
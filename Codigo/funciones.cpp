#include "includes.h"
#include "globales.h"
#include "funciones.h"

lectura leer_entradas(int cant_nodos, int instancia, int cant_usuarios){
    ifstream nodos_file("Instancias/nodos/" + to_string(cant_nodos) + "_instancia_" + to_string(instancia) + ".txt");
    if (!nodos_file.is_open()) {
        cerr << "Error: No se pudo abrir/no existe el archivo de nodos." << endl;
        exit(1);
    }

    ifstream users_file("Instancias/usuarios/" + to_string(cant_nodos) + "_instancia_" + to_string(instancia) + "_" +
    to_string(cant_usuarios) + "us.txt");
    if (!users_file.is_open()) {
        cerr << "Error: No se pudo abrir/no existe el archivo de usuarios." << endl;
        exit(1);
    }

    //Lectura nodos
    nodos nodos_leidos;
    nodos_file >> nodos_leidos.num_nodos;

    nodos_leidos.tiempos_nodos.resize(nodos_leidos.num_nodos);
    for (int i = 0; i < nodos_leidos.num_nodos; i++) nodos_file >> nodos_leidos.tiempos_nodos[i];

    nodos_leidos.ventanas_nodos.resize(
        nodos_leidos.num_nodos,
        vector<int>(2)
    );
    for (int i = 0; i < nodos_leidos.num_nodos; i++) {
        nodos_file >> nodos_leidos.ventanas_nodos[i][0] >> nodos_leidos.ventanas_nodos[i][1];
    }

    nodos_leidos.matriz_tiempos.resize(
        nodos_leidos.num_nodos,
        vector<int>(nodos_leidos.num_nodos)
    );
    for (int i = 0; i < nodos_leidos.num_nodos; i++) {
        for (int j = 0; j < nodos_leidos.num_nodos; j++) {
            nodos_file >> nodos_leidos.matriz_tiempos[i][j];
        }
    }
    
    //Lectura usuarios
    int num_usuarios;
    users_file >> num_usuarios;

    vector<usuario> usuarios_list(num_usuarios);
    for (int i = 0; i < num_usuarios; i++) {
        usuarios_list[i].beneficio_nodos.resize(nodos_leidos.num_nodos);
        usuarios_list[i].beneficio_arcos.resize(
            nodos_leidos.num_nodos, 
            vector<int>(nodos_leidos.num_nodos)
        );

        users_file >> usuarios_list[i].tiempo_max;
        for (int j = 0; j < nodos_leidos.num_nodos; j++) {
            users_file >> usuarios_list[i].beneficio_nodos[j];
        }
        for (int k = 0; k < nodos_leidos.num_nodos; k++) {
            for (int l = 0; l < nodos_leidos.num_nodos; l++) {
                users_file >> usuarios_list[i].beneficio_arcos[k][l];
            }
        }
    }

    lectura resultado_lectura;
    resultado_lectura.nodos_leidos = nodos_leidos;
    resultado_lectura.usuarios = usuarios_list;
    return resultado_lectura;

    /*
    //Imprimir
    //Nodos
    cout << "---Nodos---\n";
    cout << "Numero nodos: " << nodos_leidos.num_nodos << endl;
    cout << "Tiempos nodos:\n";
    for (int i = 0; i < nodos_leidos.num_nodos; i++) {
        cout << nodos_leidos.tiempos_nodos[i] << " ";
    }
    cout << "\nVentanas de tiempo nodos:\n";
    for (int i = 0; i < nodos_leidos.num_nodos; i++) {
        cout << nodos_leidos.ventanas_nodos[i][0] << ":" << nodos_leidos.ventanas_nodos[i][1] << " ";
    }
    cout << "\nMatriz tiempos nodos\n";
    for (int i = 0; i < nodos_leidos.num_nodos; i++) {
        for (int j = 0; j < nodos_leidos.num_nodos; j++) {
            cout << nodos_leidos.matriz_tiempos[i][j] << " ";
            if (j == nodos_leidos.num_nodos - 1) cout << endl;
        }
    }
    
    cout << "\n";
    //Usuarios
    cout << "---Usuarios---\n";
    cout << "Numero usuarios: " << num_usuarios << endl;
    for (int i = 0; i < num_usuarios; i++) {
        cout << "Usuario numero: " << i << ", Tiempo maximo: " << usuarios_list[i].tiempo_max << endl;
        cout << "Beneficio nodos: " << endl;
        for (int j = 0; j < nodos_leidos.num_nodos; j++){
            cout << usuarios_list[i].beneficio_nodos[j] << " ";
            if (j == nodos_leidos.num_nodos - 1) cout << endl;
        }
        cout << "Matriz tiempos\n";
        for (int k = 0; k < nodos_leidos.num_nodos; k++) {
            for (int l = 0; l < nodos_leidos.num_nodos; l++) {
                cout << usuarios_list[i].beneficio_arcos[k][l] << " ";
                if (l == nodos_leidos.num_nodos - 1) cout << endl;
            }
        }
        cout << endl;
    }
    */
}

void funcion_evaluacion(solucion* solucion_actual, nodos* nodo, usuario* usuario){
    solucion_actual->factibilidad = 'F';
    //Maximizar valoraciones
    int aptitud = 0, cant_nodos;
    cant_nodos = solucion_actual->tour.size();

    int tiempo_servicio = 0, penalizacion = 0;
    int nodo_actual, nodo_siguiente;
    for (int i = 0; i < cant_nodos; i++) {
        nodo_actual = solucion_actual->tour[i];
        if (i != cant_nodos-1) nodo_siguiente = solucion_actual->tour[i + 1];
        //Sumar beneficio nodos
        aptitud += usuario->beneficio_nodos[nodo_actual];
        //Sumar beneficio arcos
        if (i != cant_nodos-1) aptitud += usuario->beneficio_arcos[nodo_actual][nodo_siguiente];
        //Sumar tiempo nodos
        tiempo_servicio += nodo->tiempos_nodos[nodo_actual];
        //Sumar tiempo arcos
        if (i != cant_nodos-1) tiempo_servicio += nodo->matriz_tiempos[nodo_actual][nodo_siguiente];
        //Si se llega antes de la ventana toca esperar
        if (tiempo_servicio < nodo->ventanas_nodos[nodo_actual][0]) {
            tiempo_servicio += nodo->ventanas_nodos[nodo_actual][0] - tiempo_servicio;
        }
        //Si no se finaliza el servicio en la ventana se penaliza segun el tiempo
        if (nodo->tiempos_nodos[nodo_actual] > nodo->ventanas_nodos[nodo_actual][1]) {
            penalizacion += nodo->tiempos_nodos[nodo_actual] - nodo->ventanas_nodos[nodo_actual][1];
            //Marcar infactible
            solucion_actual->factibilidad = 'I';
        }
    }
    //Sumar arco hasta el primer nodo
    int ultimo_nodo = solucion_actual->tour.back();
    aptitud += usuario->beneficio_arcos[ultimo_nodo][solucion_actual->tour[0]];
    tiempo_servicio += nodo->matriz_tiempos[ultimo_nodo][solucion_actual->tour[0]];
    //Penalizar si se sobrepasa el tiempo maximo
    if (tiempo_servicio > usuario->tiempo_max) {
        penalizacion += tiempo_servicio - usuario->tiempo_max;
        //Marcar infactible
        solucion_actual->factibilidad = 'I';
    }

    //Restar penalizaciones
    aptitud -= penalizacion;
    solucion_actual->aptitud = aptitud;
    solucion_actual->tiempo_servicio = tiempo_servicio;

    //INCREMENTAR LAS PENALIZACIONES
}

void crear_solucion_aleatoria (solucion *i_temp, nodos* nodo, usuario* usuario){
  int rand;

  i_temp->tour.resize(nodo->num_nodos);
  //creacion de la permutacion aleatoria
  int set[nodo->num_nodos];
  for(int i=0;i<nodo->num_nodos;i++)
    set[i]=i;

  for (int i=0;i<nodo->num_nodos;i++){
    rand=int_rand(0,(nodo->num_nodos-i)); // Un elemento del arreglo (entre 0 y Tinstancia-1 la primera vez y asi...)
    i_temp->tour[i]=set[rand]; 
    set[rand]=set[nodo->num_nodos-i-1];
  }
  //calculo de la aptitud de la solucion
  funcion_evaluacion(i_temp, nodo, usuario);
  return;
}

int int_rand (int a, int b){
  //generacion de numeros aleatorios entre a y b-1
  int retorno=0;
  if (a<b){ 
    retorno=(int)((b-a)*drand48());
    retorno=retorno+a;
  }
  else{
    retorno=(int)((a-b)*drand48());
    retorno=retorno+b;
  }
  return retorno;
}

void SWaP(solucion * solucion_actual, solucion * candidata_solucion, nodos* nodo, usuario* usuario, int pos1, int pos2, int debug){
  int aux;
  //copiar la informacion de solucion actual en candidata a solucion
  pos2=pos2%solucion_actual->tour.size();
  *candidata_solucion=*solucion_actual;
  if(debug) cout<<"\t"<<pos1<<"->"<<pos2;
  //Intercambiar la informacion 
  aux=(candidata_solucion)->tour[pos1];
  (candidata_solucion)->tour[pos1]=(candidata_solucion)->tour[pos2];
  (candidata_solucion)->tour[pos2]=aux;
  //Evaluar solucion
  funcion_evaluacion(candidata_solucion, nodo, usuario);
  return;
}

void eliminacion(solucion * solucion_actual, solucion * candidata_solucion, nodos* nodo, usuario* usuario, int nodo_eliminar, int debug){
  *candidata_solucion=*solucion_actual;
  //Eliminar nodo
  int nodo_eliminado_id = candidata_solucion->tour[nodo_eliminar];
  if (debug) cout<<"\t"<<nodo_eliminado_id<<" Out";
  candidata_solucion->tour.erase(candidata_solucion->tour.begin() + nodo_eliminar);
  //Evaluar solucion
  funcion_evaluacion(candidata_solucion, nodo, usuario);
  return;
}

void escribir_salida(solucion * mejor_solucion, usuario * usuario, ofstream & res){
    res<<mejor_solucion->aptitud<<endl;
    res<<usuario->tiempo_max<<" "<<mejor_solucion->tiempo_servicio<<endl;
    for(int i=0;i<mejor_solucion->tour.size();i++) res<<mejor_solucion->tour[i]<<" ";
    res<<endl<<mejor_solucion->factibilidad<<endl;
    return;
}
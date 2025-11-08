#include "includes.h"
#include "globales.h"
#include "funciones.h"

void leer_entradas(int cant_nodos, int instancia, int cant_usuarios){
    ifstream nodos_file("Instancias/nodos/" + to_string(cant_nodos) + "_instancia_" + to_string(instancia) + ".txt");
    if (!nodos_file.is_open()) {
        cerr << "Error: No se pudo abrir/no existe el archivo de nodos." << endl;
        exit(1);
        return;
    }

    ifstream users_file("Instancias/usuarios/" + to_string(cant_nodos) + "_instancia_" + to_string(instancia) + "_" +
    to_string(cant_usuarios) + "us.txt");
    if (!users_file.is_open()) {
        cerr << "Error: No se pudo abrir/no existe el archivo de usuarios." << endl;
        exit(1);
        return;
    }

    //Lectura nodos
    int num_nodos;
    nodos_file >> num_nodos;

    vector<int> tiempos_nodos(num_nodos);
    for (int i = 0; i < num_nodos; i++) nodos_file >> tiempos_nodos[i];

    vector<vector<int>> ventanas_nodos(
        num_nodos,
        vector<int>(2)
    );
    for (int i = 0; i < num_nodos; i++) {
        nodos_file >> ventanas_nodos[i][0] >> ventanas_nodos[i][1];
    }

    vector<vector<int>> matriz_tiempos(
        num_nodos,
        vector<int>(num_nodos)
    );
    for (int i = 0; i < num_nodos; i++) {
        for (int j = 0; j < num_nodos; j++) {
            nodos_file >> matriz_tiempos[i][j];
        }
    }
    
    //Lectura usuarios
    int num_usuarios;
    users_file >> num_usuarios;

    vector<usuario> usuarios_list(num_usuarios);
    for (int i = 0; i < num_usuarios; i++) {
        usuarios_list[i].beneficio_nodos.resize(num_nodos);
        usuarios_list[i].beneficio_arcos.resize(
            num_nodos, 
            vector<int>(num_nodos)
        );

        users_file >> usuarios_list[i].tiempo_max;
        for (int j = 0; j < num_nodos; j++) {
            users_file >> usuarios_list[i].beneficio_nodos[j];
        }
        for (int k = 0; k < num_nodos; k++) {
            for (int l = 0; l < num_nodos; l++) {
                users_file >> usuarios_list[i].beneficio_arcos[k][l];
            }
        }
    }

    /*
    //Imprimir
    //Nodos
    cout << "---Nodos---\n";
    cout << "Numero nodos: " << num_nodos << endl;
    cout << "Tiempos nodos:\n";
    for (int i = 0; i < num_nodos; i++) {
        cout << tiempos_nodos[i] << " ";
    }
    cout << "\nVentanas de tiempo nodos:\n";
    for (int i = 0; i < num_nodos; i++) {
        cout << ventanas_nodos[i][0] << ":" << ventanas_nodos[i][1] << " ";
    }
    cout << "\nMatriz tiempos nodos\n";
    for (int i = 0; i < num_nodos; i++) {
        for (int j = 0; j < num_nodos; j++) {
            cout << matriz_tiempos[i][j] << " ";
            if (j == num_nodos - 1) cout << endl;
        }
    }
    
    cout << "\n";
    //Usuarios
    cout << "---Usuarios---\n";
    cout << "Numero usuarios: " << num_usuarios << endl;
    for (int i = 0; i < num_usuarios; i++) {
        cout << "Usuario numero: " << i << ", Tiempo maximo: " << usuarios_list[i].tiempo_max << endl;
        cout << "Beneficio nodos: " << endl;
        for (int j = 0; j < num_nodos; j++){
            cout << usuarios_list[i].beneficio_nodos[j] << " ";
            if (j == num_nodos - 1) cout << endl;
        }
        cout << "Matriz tiempos\n";
        for (int k = 0; k < num_nodos; k++) {
            for (int l = 0; l < num_nodos; l++) {
                cout << usuarios_list[i].beneficio_arcos[k][l] << " ";
                if (l == num_nodos - 1) cout << endl;
            }
        }
        cout << endl;
    }
    */
}
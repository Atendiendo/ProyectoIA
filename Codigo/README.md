# Compilacion
- Para compilar usar comando  
    `make`
- Para limpiar archivos usar comando  
    `make clean`

# Instrucciones de uso
- Para ejecutar con las configuraciones del Makefile usar comando  
    `make run`
- Por linea de comando:  
    ./HC+Restart cantNodos instanciaNodos cantUsuarios instanciaUsuarios semilla restarts debug

    - debug=0, no muestra informacion por pantalla

    - Ejemplo:  
    ./HC+Restart 10 0 5 0 1234 10 0
    ./HC+Restart 10 3 3 3 1235 10 1

# Output
- Se genera un archivo txt llamado sol_N_instancia_I.txt, donde N corresponde al numero de nodos del tour, e I es el
    identificador de la instancia para cada uno de los casos de prueba (usuarios):
    - Primera linea: Valor del Tour (suma de valoraciones de nodos y arcos
    pertenecientes al tour generado).
    - Segunda linea : Tiempo total disponible y tiempo empleado en el tour
    - Tercera linea: Nodos pertenecientes al tour
    - Ejemplo:  
    ```
    144  
    116 119  
    4 1 3 2 7   
    140
    130 129
    9 5 3 1 7 
    ```

# Requerimientos
- gcc 13.3.0 o superior
- GNU Make 4.3 o superior
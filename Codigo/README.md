# Compilacion
- Para compilar usar comando  
    `make`
- Para ejecutar usar comando  
    `make run`
- Para limpiar archivos usar comando  
    `make clean`

# Instrucciones de uso
- Se debe ingresar por consola la instancia a considerar, siguiendo el siguiente orden:  
    cantidad_nodos instancia cantidad_usuarios semilla numero_restarts debug
    - debug=0, no muestra informacion por pantalla
    - Ejemplo:  
    10 0 5 123 100 1  
    20 2 5 124 1000 0

# Output
- Se genera un archivo txt llamado sol_CantidadNodos_NumeroDeLaInstancia_instancia.txt,
    donde CantidadNodos corresponde al numero de nodos del tour y NumeroDeLaInstancia corresponde al numero de la instancia. Para
    cada uno de los casos de prueba (usuarios):
    - Primera linea: Valor del Tour (suma de valoraciones de nodos y arcos
    pertenecientes al tour generado).
    - Segunda linea : Tiempo total disponible y tiempo empleado en el tour
    - Tercera linea: Nodos pertenecientes al tour
    - Cuarta linea: Factibilidad del tour
    - Ejemplo:  
    ```
    144  
    116 119  
    4 1 3 2 7   
    I
    140
    130 129
    9 5 3 1 7 
    F
    ```



# Requerimientos
- gcc 13.3.0 o superior
- valgrind 3.22.0 o superior
- GNU Make 4.3 o superior
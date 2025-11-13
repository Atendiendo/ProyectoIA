#ifndef GLOBALES_H
#define GLOBALES_H

struct usuario{
    int tiempo_max;
    vector<int> beneficio_nodos;
    vector<vector<int>> beneficio_arcos;
};

struct nodos{
    int num_nodos;
    vector<int> tiempos_nodos;
    vector<vector<int>> ventanas_nodos;
    vector<vector<int>> matriz_tiempos;
};

struct lectura{
    nodos nodos_leidos;
    vector<usuario> usuarios;
};

class solucion{
    public:
        int aptitud;
        vector<int> tour;
        char factibilidad;

        solucion(int aptitud, int num_nodos){
            this->aptitud = aptitud;
            tour=vector<int>(num_nodos, 1);
            factibilidad = 'F';
        }

        solucion(const solucion &a){
            aptitud=a.aptitud;
            tour=a.tour;
            factibilidad=a.factibilidad;
        }

        solucion& operator=(const solucion &a){
            this->aptitud=a.aptitud;
            this->tour=a.tour;
            this->factibilidad=a.factibilidad;
            return *this;
        }

        int operator==(const solucion &a) const{
            if( this->aptitud != a.aptitud) return 0;
            return 1;
        }

        int operator<(const solucion &a) const{
            if( this->aptitud < a.aptitud ) return 1;
            return 0;
        }
};

inline ostream &operator<<(ostream &output, const solucion &a){
  for(int i=0;i<a.tour.size();i++)
    output<<a.tour[i]<<" ";
  output<<"("<<a.aptitud<<") " << a.factibilidad;
  return output;
};

#endif
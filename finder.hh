#ifndef FINDER_HH
#define FINDER_HH

#include <map>
#include <set>
#include <vector>
#include "geometry.hh"

using namespace std;

template <class T>
class Finder {
public:
    // Modificadoras:
    /**
     * @brief Añade un objeto al sistema buscador.
     * @param t Puntero al objeto a añadir.
     */
    void add(const T* t);

    /**
     * @brief Actualiza la posición de un objeto ya añadido.
     * @param t Puntero al objeto a actualizar.
     */
    void update(const T* t);

    /**
     * @brief Elimina un objeto del buscador.
     * @param t Puntero al objeto a eliminar.
     */
    void remove(const T* t);


    //Consultora:
    /**
     * @brief Devuelve todos los objetos que intersectan con un rectángulo dado.
     * @param qrect Rectángulo consultor.
     */
    set<const T*> query(pro2::Rect qrect) const;

private:
    //Cuadricula espacial que indexa los objetos por celdas.
    map<int, map<int, set<const T*>>> grid;

    //Mapa que asocia cada objeto con las celdas en las que se encuentra.
    map<const T*, vector<pair<int,int>>> object_cells;

    /**
     * @brief Añade un objeto a las celdas correspondientes de la cuadrícula.
     * @param t Puntero al objeto a indexar.
     */
    void add_to_grid(const T* t);
};


#endif

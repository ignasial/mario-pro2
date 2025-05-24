#include "finder.hh"
#include "platform.hh"
#include "coin.hh"

template class Finder<Platform>;
template class Finder<Coin>;


template <class T>
void Finder<T>::add(const T* t) {
    add_to_grid(t);
}

//Elimina la posicon del objeto de las celdas antiguas y se añade a las nuevas
template <class T>
void Finder<T>::update(const T* t) {
    auto it = object_cells.find(t);

    if (it != object_cells.end()) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            grid[it2->first][it2->second].erase(t);
        }

        object_cells.erase(it);
    }
    add_to_grid(t);
}

//Elimina completamente el objeto del sistema
template <class T>
void Finder<T>::remove(const T* t) {
    auto it = object_cells.find(t);
    if (it != object_cells.end()) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            grid[it2->first][it2->second].erase(t);
        }
        object_cells.erase(it);
    }
}

//Devuelve los objetos que intersectan el rectangulo de consulta
template <class T>
set<const T*> Finder<T>::query(pro2::Rect qrect) const {
    set<const T*> result;
    int cell_size = 1000;

    int left_cell = qrect.left / cell_size;
    int right_cell = qrect.right / cell_size;
    int top_cell = qrect.top / cell_size;
    int bottom_cell = qrect.bottom / cell_size;

    //Recorremos las celdas que interecten el rectangulo
    for (int x = left_cell; x <= right_cell; ++x) {
        auto itx = grid.find(x);
        if (itx == grid.end()) {
            continue;
        }

        for (int y = top_cell; y <= bottom_cell; ++y) {
            auto ity = itx->second.find(y);
            if (ity == itx->second.end()) {
                continue;
            }
            //Comprobamos la intersección y añadimos objetos
            for (auto it_obj = ity->second.begin(); it_obj != ity->second.end(); ++it_obj) {
                pro2::Rect r = (*it_obj)->get_rect();
                if (!(r.right < qrect.left || r.left > qrect.right || r.bottom < qrect.top || r.top > qrect.bottom)) {
                    result.insert(*it_obj);
                }
            }
        }
    }
    return result;
}

//Añade el objeto a todas las celdas que ocupe su rectangulo
template <class T>
void Finder<T>::add_to_grid(const T* t) {
    int cell_size = 1000;
    pro2::Rect rect = t->get_rect();

    int left_cell = rect.left / cell_size;
    int right_cell = rect.right / cell_size;
    int top_cell = rect.top / cell_size;
    int bottom_cell = rect.bottom / cell_size;

    vector<pair<int,int>> cells;

    for (int x = left_cell; x <= right_cell; ++x) {
        for (int y = top_cell; y <= bottom_cell; ++y) {
            grid[x][y].insert(t);
            cells.push_back(make_pair(x,y));
        }
    }
    object_cells[t] = cells;

}

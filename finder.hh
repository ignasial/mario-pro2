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
    void add(const T* t);

    void update(const T* t);

    void remove(const T* t);

    set<const T*> query(pro2::Rect qrect) const;

private:
    map<int, map<int, set<const T*>>> grid;
    map<const T*, vector<pair<int,int>>> object_cells;

    void add_to_grid(const T* t);
};


#endif

#include "types.h"
#include "point.h"

using namespace MY_DATA;

template <class T>
Point<T>::Point(T _x, T _y) {
    x = _x;
    y = _y;
}

template class Point<WORD>;

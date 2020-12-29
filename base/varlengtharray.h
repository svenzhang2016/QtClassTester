#ifndef VARLENGTHARRAY_H
#define VARLENGTHARRAY_H

#include "global.h"

#include <QtContainerFwd>
#include <QtAlgorithms>

#include <new>
#include <string.h>

template<class T, int Prealloc>
class QPodList;

// Prealloc = 256 by default, specified in qcontainerfwd.h
template<class T, int Prealloc>
class VarLengthArray
{
public:
    inline explicit VarLengthArray(int size = 0);

private:
    int a; //capacity
    int s; //size
    T *ptr; //data
    union
    {
//        char array[sizeof(qint64) * (((Prealloc *sizeof(T)) / sizeof(qint64)) + 1)];
        char array[Prealloc * sizeof(T)];
        qint64 for_alignment_1;
        double for_alignment_2;
    };
};

template <class T, int Prealloc>
inline VarLengthArray<T, Prealloc>::VarLengthArray(int asize)
    : s(asize)
{
    if(s > Prealloc)
    {
        ptr = reinterpret_cast<T*>(qMalloc(s * sizeof(T)));
        Q_CHECK_PTR(ptr);
        a = s;
    }
    else
    {
        ptr = reinterpret_cast<T*>(array);
        a = Prealloc;
    }
}

#endif // VARLENGTHARRAY_H

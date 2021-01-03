#ifndef PODLIST
#define PODLIST

#include "varlengtharray.h"

template<typename T, int Prealloc>
class PodList : public VarLengthArray<T, Prealloc>
{
    using VarLengthArray<T, Prealloc>::s;
    using VarLengthArray<T, Prealloc>::a;
    using VarLengthArray<T, Prealloc>::ptr;
    using VarLengthArray<T, Prealloc>::realloc;
public:
    inline explicit PodList(int size=0)
        : VarLengthArray<T,Prealloc>(size)
    {}

    inline void insert(int idx, const T &t)
    {
        const int sz = s++;
        if(s == a)
        {
            realloc(s, s<<1);
        }
        ::memmove(ptr + idx + 1, ptr + idx, (sz - idx) * sizeof(T));
        ptr[idx] = t;
    }

    inline void removeAll(const T &t)
    {
        int i = 0;
        for(int j = 0; j < s; ++j)
        {
            if(ptr[j] != t)
            {
                ptr[i++] = ptr[j];
            }
        }
        s = i;
    }

    inline void removeAt(int idx)
    {
        Q_ASSERT(idx >= 0 && idx < s);
        ::memmove(ptr + idx, ptr + idx + 1, (s - idx - 1) * sizeof(T));
        --s;
    }

    inline T takeFirst()
    {
        Q_ASSERT(s > 0);
        T tmp = ptr[0];
        removeAt(0);
        return tmp;
    }
};

#endif // PODLIST


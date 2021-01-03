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

    inline VarLengthArray(const VarLengthArray<T, Prealloc> &other)
        : a(Prealloc), s(0), ptr(reinterpret_cast<T*>(array))
    {
        append(other.constData(), other.size());
    }
    inline ~VarLengthArray()
    {
        if(QTypeInfo<T>::isComplex)
        {
            T *i = ptr +s;
            while(i-- != ptr)
            {
                i->~T();
            }
        }
        if(ptr != reinterpret_cast<T*>(array))
        {
            qFree(ptr);
        }
    }
    inline VarLengthArray<T, Prealloc> &operator=(const VarLengthArray<T, Prealloc> &other)
    {
        if(this != &other){
            clear();
            append(other.constData(), other.size());
        }
        return *this;
    }
    inline void removeLast(){
        Q_ASSERT(s > 0);
        realloc(s - 1, a);
    }
    inline int size() const {return s;}
    inline int count() const {return s;}
    inline bool isEmpty() const {return s == 0;}
    inline void resize(int size);
    inline void clear() {resize(0);}

    inline int capacity() const {return a;}
    inline void reserve(int size);

    inline T &operator [](int idx)
    {
        Q_ASSERT(idx >= 0 && idx < s);
        return ptr[idx];
    }
    inline const T& operator [](int idx) const
    {
        Q_ASSERT(idx >= 0 && idx < s);
        return ptr[idx];
    }
    inline const T &at(int idx) const {return operator [](idx);}
    T value(int i) const;
    T value(int i, const T &defaultValue) const;

    inline void append(const T& t)
    {
        if(s == a)
        {
            realloc(s, s<<1);
        }
        const int idx = s++;
        if(QTypeInfo<T>::isComplex)
        {
            new (ptr + idx) T(t);
        }
        else
        {
            ptr[idx] = t;
        }
    }
    void append(const T* buf, int increment);
    inline VarLengthArray<T, Prealloc> &operator<<(const T &t)
    {
        append(t); return *this;
    }
    inline VarLengthArray<T, Prealloc> &operator+=(const T &t)
    {
        append(t); return *this;
    }
    void prepend(const T &t);
    void insert(int i, const T &t);
    void insert(int i, int n, const T & t);
    void replace(int i, const T &t);
    void remove(int i);
    void remove(int i, int n);

    inline T *data() {return ptr;}
    inline const T *data() const {return ptr;}
    inline const T * constData() const {return ptr;}

    typedef int size_type;
    typedef T value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef qptrdiff difference_type;

    typedef T* iterator;
    typedef const T* const_iterator;

    inline iterator begin() {return ptr;}
    inline const_iterator begin() const {return ptr;}
    inline const_iterator constBegin() const{return ptr;}

    inline iterator end() {return ptr+s;}
    inline const_iterator end() const{return ptr+s;}
    inline const_iterator constEnd() const {return ptr + s;}

    iterator insert(iterator before, int n, const T &x);
    iterator insert(iterator before, const T& x) {return insert(before, 1, x);}
    iterator erase(iterator begin, iterator end);
    inline iterator erase(iterator pos){return erase(pos, pos+1);}

private:
    friend class QpodList<T, Prealloc>;
    void realloc(int size, int alloc);

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
    if(QTypeInfo<T>::isComplex)
    {
        T *i = ptr + s;
        while(i != ptr)
        {
            new (--i)T;
        }
    }
}

template <class T, int Prealloc>
inline void VarLengthArray<T, Prealloc>::resize(int size)
{
    realloc(size, qMax(size, a));
}

template <class T, int Prealloc>
void VarLengthArray<T, Prealloc>::reserve(int size)
{
    if(size > a)
    {
        realloc(s, size);
    }
}

template <class T, int Prealloc>
void VarLengthArray<T, Prealloc>::append(const T *buf, int increment)
{
    Q_ASSERT(buf);
    if(increment <= 0)
    {
        return;
    }
    const int asize = s + increment;
    if(asize >= a)
    {
        realloc(s, qMax(s*2, asize));
    }
    if(QTypeInfo<T>::isComplex)
    {
        while(s < asize)
        {
            new (ptr+(s++))T(*buf++);
        }
    }
    else
    {
        qMemCopy(&ptr[s], buf, increment * sizeof(T));
        s = asize;
    }
}

template <class T, int Prealloc>
void VarLengthArray<T, Prealloc>::realloc(int asize, int aalloc)
{
    Q_ASSERT(aalloc >= asize);
    T *oldPtr = ptr;
    int osize = s;

    const int copySize = qMin(asize, osize);
    if(aalloc != a)
    {
        ptr = reinterpret_cast<T*>(qMalloc(aalloc * sizeof(T)));
        Q_CHECK_PTR(ptr);
        if(ptr)
        {
            s = 0;
            a = aalloc;

            if(QTypeInfo<T>::isStatic)
            {
                QT_TRY{
                    while(s < copySize)
                    {
                        new (ptr + s) T(*(oldPtr + s));
                        (oldPtr + s)->~T();
                        s++;
                    }
                }
                QT_CATCH(...)
                {
                    int sClean = s;
                    while(sClean < osize)
                    {
                        (oldPtr++(sClean++))->~T();
                    }
                    if(oldPtr != reinterpret_cast<T*>(array) && oldPtr != ptr)
                    {
                        qFree(oldPtr);
                    }

                    QT_RETHROW;
                }
            }
            else
            {
                qMemCopy(ptr, oldPtr,  copySize * sizeof(T));
            }
        }
        else
        {
            ptr = oldPtr;
            return ;
        }
    }
    s = copySize;
    if(QTypeInfo<T>::isComplex)
    {
        while(osize > asize)
        {
            (oldPtr+(--osize))->~T();
        }
    }
    if(oldPtr != reinterpret_cast<T*>(array) && oldPtr != ptr)
    {
        qFree(oldPtr);
    }
    if(QTypeInfo<T>::isComplex)
    {
        while(s < asize)
        {
            new (ptr+(s++)) T;
        }
    }
    else
    {
        s = asize;
    }
}

template <class T, int Prealloc>
T VarLengthArray<T, Prealloc>::value(int i) const
{
    if(i < 0 || i >= size()){
        return T();
    }
    return at(i);
}

template <class T, int Prealloc>
T VarLengthArray<T, Prealloc>::value(int i, const T &defaultValue) const
{
    return (i < 0 || i >= size()) ? defaultValue : at(i);
}

template <class T, int Prealloc>
inline void VarLengthArray<T, Prealloc>::insert(int i, const T &t)
{
    Q_ASSERT_X(i >= 0 && i <= s, "VarLengthArray::insert", "index out of range");
    insert(begin() + i, 1, t);
}

template <class T, int Prealloc>
inline void VarLengthArray<T, Prealloc>::insert(int i, int n, const T &t)
{
    Q_ASSERT_X(i >= 0 && i <= s, "VarLengthArray::remove", "index out of range");
    insert(begin() + i, n, t);
}

template<class T, int Prealloc>
inline void VarLengthArray<T, Prealloc>::remove(int i, int n)
{
    erase(begin() + i, begin() + i + 1);
}

template<class T, int Prealloc>
inline void VarLengthArray<T, Prealloc>::prepend(const T &t)
{
    insert(begin(), 1, t);
}

template<class T, int Prealloc>
inline void VarLengthArray<T, Prealloc>::replace(int i, const T &t)
{
    const T copy(t);
    data()[i] = copy;
}

template <class T, int Prealloc>
typename VarLengthArray<T, Prealloc>::iterator VarLengthArray<T, Prealloc>::insert(
        iterator before, size_type n, const T &t)
{
    int offset = int(before - ptr);
    if(n != 0)
    {
        resize(s + n);
        const T copy(t);
        if(QTypeInfo<T>::isStatic)
        {
            T *b = ptr + offset;
            T *j = ptr + s;
            T *i = j - n;
            while(i != b)
            {
                *--i = copy;
            }
        }
        else
        {
            T *b = ptr + offset;
            T *i = b + n;
            memmove(i, b, (s - offset - n) * sizeof(T));
            while(i != b)
            {
                new (--i) T(copy);
            }
        }
    }
    return ptr + offset;
}

template <class T, int Prealloc>
typename VarLengthArray<T, Prealloc>::iterator VarLengthArray<T, Prealloc>::erase(
        iterator abegin, iterator aend)
{
    int f = int(abegin - ptr);
    int l = int(aend - ptr);
    int n = l - f;
    if (QTypeInfo<T>::isComplex)
    {
        qCopy(ptr + l, ptr + s, ptr + f);
        T *i = ptr + s;
        T *b = ptr + s - n;
        while (i != b)
        {
            --i;
            i->~T();
        }
    }
    else
    {
        memmove(ptr + f, ptr + l, (s - l) * sizeof(T));
    }
    s -= n;
    return ptr + f;
}

template <typename T, int Prealloc1, int Prealloc2>
bool operator ==(const VarLengthArray<T, Prealloc1> &l, const VarLengthArray<T, Prealloc2> &r)
{
    if(l.size() != r.size())
    {
        return false;
    }
    for(int i = 0; i < l.size(); i++)
    {
        if(l.at(i) != r.at(i))
        {
            return false;
        }
    }
    return true;
}

template <typename T, int Prealloc1, int Prealloc2>
bool operator !=(const VarLengthArray<T,Prealloc1> &l, const VarLengthArray<T, Prealloc2> &r)
{
    return !(l == r);
}

#endif // VARLENGTHARRAY_H








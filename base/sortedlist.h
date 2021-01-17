#ifndef SORTEDLIST_H
#define SORTEDLIST_H


#include <QObject>
#include <QEvent>
#include <QList>
#include <QMutex>
#include <algorithm>

template <typename T>
class SortedList : public QList<T>
{
public:
    SortedList(): QList<T>(){}

private:
    using QList<T>::append;
    using QList<T>::insert;
};

class PostEvent
{
public:
    QObject *receiver;
    QEvent *event;
    int priority;

    PostEvent() : receiver(0), event(0), priority(0){}
    PostEvent(QObject *r, QEvent *e, int p) : receiver(r), event(e), priority(p){}
};

inline bool operator<(int priority, const PostEvent &pe)
{
    return pe.priority < priority;
}
inline bool operator<(const PostEvent &pe, int priority)
{
    return priority < pe.priority;
}


template <>
class PostEventList : public QList<PostEvent>
{
public:
    int recursion;
    int startOffset;
    int insertionOffset;

    QMutex mutex;

    PostEventList() : QList<PostEvent>(), recursion(0), startOffset(0), insertionOffset(0){}

    void addEvent(const PostEvent& ev){
        int priority = ev.priority;
        if(isEmpty() || last().priority >= priority)
        {
            append(ev);
        }
        else
        {
            PostEventList::iterator at = std::upper_bound(begin() + insertionOffset, end(), priority);
            insert(at, ev);
        }
    }
}


#endif // SORTEDLIST_H


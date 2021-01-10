#ifndef MUTEXTESTER_H
#define MUTEXTESTER_H

#include <QAtomicInt>
#include <QMutex>

class MutexData
{
public:
    QAtomicInt contenders;
    const uint recursive : 1;
    uint reserved : 31;

protected:
    MutexData(QMutex::RecursionMode mode) : recursive(mode == QMutex::Recursive){}
    ~MutexData(){}
};

class MutexTester
{
public:
    MutexTester();
};

#endif // MUTEXTESTER_H

#ifndef ATOMICTESTER_H
#define ATOMICTESTER_H

#include <QObject>
#include <QAtomicInt>
#include <QAtomicPointer>

class AtomicPointer
{
public:

private:
    int i;
};

class AtomicTester : public QObject
{
    Q_OBJECT
public:
    explicit AtomicTester(QObject *parent = 0);

private:
    QAtomicPointer<AtomicPointer*> m_Pointer;
    QAtomicInt m_AtomicInt;

};

#endif // ATOMICTESTER_H

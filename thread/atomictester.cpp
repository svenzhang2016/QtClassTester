#include "atomictester.h"

AtomicTester::AtomicTester(QObject *parent)
    : QObject(parent)
{
//    m_Pointer.fetchAndAddAcquire(1);
    m_AtomicInt.fetchAndAddAcquire(1);
}


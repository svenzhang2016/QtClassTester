#include "util.h"
#include <QEventLoop>
#include <QTimer>

Util::Util()
{

}

void Util::noblockDelay(int mSec)
{
    QEventLoop loop;
    QTimer::singleShot(mSec, &loop, SLOT(quit()));
    loop.exec();
}


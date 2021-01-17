#include "utiltesterdialog.h"
#include "ui_utiltesterdialog.h"
#include <QScopedPointer>
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include <thread>
#include <chrono>
#include "base/util.h"

UtilTesterDialog::UtilTesterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UtilTesterDialog)
{
    ui->setupUi(this);
    timer_ =  new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(stop()));
}

UtilTesterDialog::~UtilTesterDialog()
{
    delete ui;
}

void UtilTesterDialog::noblockDelay_test()
{
    timer_->start(40);
    Util::noblockDelay(10000);
}

void UtilTesterDialog::noblockWait()
{
//        std::this_thread::sleep_for(std::chrono::milliseconds(10000));    never use it ...
    int mSec = 1000000;
    QEventLoop loop;
    QTimer::singleShot(mSec, &loop, SLOT(quit()));
    connect(this, SIGNAL(stopWait()), &loop, SLOT(quit()));
    loop.exec();

    timer_->stop();
    ui->labelTime->setText("current time: " + QDateTime::currentDateTime().toString(Qt::ISODate));
}

void UtilTesterDialog::stop()
{
//    ui->labelTime->setText("current time: " + QDateTime::currentDateTime().toString(Qt::ISODate));
    if(loopTimes_ < 100)
    {
        ui->labelTime->setText("current loop time: " + QString::number(loopTimes_++));
        timer_->start(40);
    }
    else
    {
        loopTimes_ = 0;
        emit stopWait();
    }
}

void UtilTesterDialog::on_pushButtonNoblockDelay_clicked()
{
//    noblockDelay_test();
    timer_->start(40);
    noblockWait();
}

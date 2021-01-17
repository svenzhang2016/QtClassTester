#include "utiltesterdialog.h"
#include "ui_utiltesterdialog.h"
#include <QScopedPointer>
#include <QTimer>
#include <QDateTime>
#include <QLabel>
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

void UtilTesterDialog::stop()
{
    ui->labelTime->setText("current time: " + QDateTime::currentDateTime().toString(Qt::ISODate));
    timer_->start(40);
}

void UtilTesterDialog::on_pushButtonNoblockDelay_clicked()
{
    noblockDelay_test();
}

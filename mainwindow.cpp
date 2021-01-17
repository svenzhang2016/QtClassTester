#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "text/texttesterdialog.h"
#include "test/utiltesterdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    TextTesterDialog d;
    d.exec();
}

void MainWindow::on_pushButtonTest_clicked()
{
    UtilTesterDialog d;
    d.exec();
}

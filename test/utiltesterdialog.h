#ifndef UTILTESTERDIALOG_H
#define UTILTESTERDIALOG_H

#include <QDialog>
#include <QElapsedTimer>

namespace Ui {
class UtilTesterDialog;
}
class QTimer;
class UtilTesterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UtilTesterDialog(QWidget *parent = 0);
    ~UtilTesterDialog();

    void noblockDelay_test();

private slots:
    void stop();

    void on_pushButtonNoblockDelay_clicked();

private:
    Ui::UtilTesterDialog *ui;
    QTimer *timer_;
    QElapsedTimer elapsedTimer_;
};

#endif // UTILTESTERDIALOG_H

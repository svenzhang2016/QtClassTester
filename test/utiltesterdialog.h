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
    void noblockWait();

private slots:
    void stop();

    void on_pushButtonNoblockDelay_clicked();

signals:
    void stopWait();

private:
    Ui::UtilTesterDialog *ui;
    QTimer *timer_;
    QElapsedTimer elapsedTimer_;
    int loopTimes_{0};
};

#endif // UTILTESTERDIALOG_H

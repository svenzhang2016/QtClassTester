#ifndef BASICTIMERTESTER_H
#define BASICTIMERTESTER_H

#include <QBasicTimer>
#include <QWidget>
#include <QObject>

class BasicTimerTesterWidget : public QWidget
{
    Q_OBJECT
public:
    BasicTimerTesterWidget(QWidget *parent = nullptr);
public slots:
    void setText(const QString& newText) {text = newText;}
protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
private:
    QBasicTimer timer;
    QString text;
    int step;
};

class BasicTimerTester : public QObject
{
    Q_OBJECT
public:
    explicit BasicTimerTester(QObject *parent = 0);

    void start();

signals:

public slots:

private:
    QDialog *m_Dialog;
};

#endif // BASICTIMERTESTER_H

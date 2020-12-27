#ifndef TEXTOPTIONTESTER_H
#define TEXTOPTIONTESTER_H

#include <QObject>
#include <QWidget>

class TextOptionWidget : public QWidget
{
public:
    TextOptionWidget();

protected:
    void paintEvent(QPaintEvent *e);
};

class TextOptionTester : public QObject
{
    Q_OBJECT
public:
    explicit TextOptionTester(QObject *parent = 0);
    void show();

private:
    TextOptionWidget *m_Widget{nullptr};
};

#endif // TEXTOPTIONTESTER_H

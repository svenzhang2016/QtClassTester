#ifndef STATICTEXTTESTER_H
#define STATICTEXTTESTER_H

#include <QWidget>
#include <QStaticText>
#include <QPainter>

class StaticTextWidget : public QWidget
{
public:
    StaticTextWidget() : m_StaticText("This is a static text. "){}

protected:
    void paintEvent(QPaintEvent *e)
    {
        QPainter painter(this);
        painter.drawStaticText(0,0,m_StaticText);
    }

private:
    QStaticText m_StaticText;
};

class StaticTextTester
{
public:
    StaticTextTester() : widget(new StaticTextWidget()){}
    void draw()
    {
        widget->show();
    }
private:
    StaticTextWidget *widget;
};

#endif // STATICTEXTTESTER_H

#include "textoptiontester.h"
#include <QPainter>
#include <QTextOption>
#include <QDebug>
#include <QTextObject>

TextOptionWidget::TextOptionWidget()
{
    setGeometry(300,400, 100, 100);
}

void TextOptionWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setPen(Qt::red);

    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
    option.setTabArray(QList<qreal>() << 1 << 2 << 3);
//    option.setTextDirection(Qt::RightToLeft);
    qDebug() << "rect" << rect();
    painter.drawText(rect(),"where there is a will, there is a way....", option);
//    painter.drawText(rect(),"wherethereisawillthere is a way....", option);
}

TextOptionTester::TextOptionTester(QObject *parent)
    : QObject(parent)
    , m_Widget(new TextOptionWidget())
{
}

void TextOptionTester::show()
{
    m_Widget->show();
}

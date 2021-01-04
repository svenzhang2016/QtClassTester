#include "basictimertester.h"
#include <QFontMetrics>
#include <QPainter>
#include <QTimerEvent>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDialog>

BasicTimerTesterWidget::BasicTimerTesterWidget(QWidget *parent)
{
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);

    QFont newFont = font();
    newFont.setPointSize(newFont.pointSize() + 20);
    setFont(newFont);

    step = 0;
    timer.start(60, this); // start
}

void BasicTimerTesterWidget::paintEvent(QPaintEvent *event)
{
    static const int sineTable[16] = {
        0, 38, 71, 92, 100, 92, 71, 38, 0, -38, -71, -92, -100, -92, -71, -38
    };

    QFontMetrics metrics(font());
    int x = (width() - metrics.width(text)) / 2;
    int y = (height() + metrics.ascent() - metrics.descent()) / 2;

    QColor color;

    QPainter painter(this);
    for(int i = 0; i < text.size(); ++i)
    {
        int index = (step + i) % 16;
        color.setHsv((15 - index) * 16, 255, 191); //change index
        painter.setPen(color);
        painter.drawText(x, y - ((sineTable[index] * metrics.height()) / 400), QString(text[i]));   // change position
        x += metrics.width(text[i]);
    }
}

void BasicTimerTesterWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timer.timerId()) // event filter
    {
        ++step; // change step
        update();
    }
    else
    {
        QWidget::timerEvent(event);
    }
}

BasicTimerTester::BasicTimerTester(QObject *parent)
    : QObject(parent)
    , m_Dialog(new QDialog)
{
    BasicTimerTesterWidget *w = new BasicTimerTesterWidget;
    QLineEdit *lineEdit = new QLineEdit;

    QVBoxLayout *layout = new QVBoxLayout(m_Dialog);
    layout->addWidget(w);
    layout->addWidget(lineEdit);

    connect(lineEdit, SIGNAL(textChanged(QString)), w, SLOT(setText(QString)));
    lineEdit->setText("Hello World!");

    m_Dialog->resize(360, 145);
}

void BasicTimerTester::start()
{
    m_Dialog->show();
}



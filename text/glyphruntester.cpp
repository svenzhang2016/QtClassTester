#include "glyphruntester.h"
#include <QGlyphRun>
#include <QTextLayout>
#include <QDialog>
#include <QPainter>
#include <QDebug>

GlyphRunTesterWidget::GlyphRunTesterWidget(QWidget *p)
    :QWidget(p)
{

}

void GlyphRunTesterWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QString text = "hello sven";
    QPoint p(30,30);

    qDebug() << "gfegegwegweg";
    QFont ft = font();
    ft.setPointSize(28);
    setFont(ft);

    QRawFont rawFont = QRawFont::fromFont(painter.font());
    qDebug() << "mmmmmmmmmmmmmmmmmmmmmmmm";
     QVector<quint32> indexes = rawFont.glyphIndexesForString(text);

     qDebug("num indexes: %d\n",indexes.count());
     for(unsigned int i=0; i<indexes.count(); i++)
     {
       QPainterPath path = rawFont.pathForGlyph(indexes[i]);
       painter.translate(QPointF(p.x(), p.y() + i*0));
//       painter.fillPath(path,painter.pen().brush());
       painter.fillPath(path, QBrush(Qt::green));
     }
}

GlyphRunTester::GlyphRunTester(QObject *parent)
   : QObject(parent)
{
    m_Widget = new GlyphRunTesterWidget();
    m_Widget->setGeometry(100,200,400,400);
    m_Widget->show();
}

GlyphRunTester::~GlyphRunTester()
{
    delete m_Widget;
}

void GlyphRunTester::draw()
{
    m_Widget->update();
//    QTextOption opt;
//    opt.setWrapMode(QTextOption::WrapAnywhere);

//    QStringList text;
//    text.append("First line");
//    text.append("Another line");

//   QTextLayout layout;
//   layout.setText(text.join(""));
//    layout.beginLayout();

//    qreal h = 0;
//    for(const auto& line : text)
//    {
//          QTextLine l = layout.createLine();
//          if(!l.isValid())
//             break;
//          l.setNumColumns(line.length());
//          l.setPosition(QPointF(0, h));
//          h += l.height();
//    }

//    layout.endLayout();

//    QPainter painter(m_Dialog);

//    QRawFont rawFont = QRawFont(QString("Glyph Run Tester"), 20);
//    QGlyphRun glyphRun = QGlyphRun();
//    glyphRun.setRawFont(rawFont);

//    painter.drawGlyphRun(QPoint(30,30), glyphRun);
//    m_Dialog->update();
//    QString text = "hello sven";
//    QPoint p(30,30);
//    QPainter *painter = new QPainter(m_Dialog);
//    QRawFont rawFont = QRawFont::fromFont(painter->font());
//     QVector<quint32> indexes = rawFont.glyphIndexesForString(text);

//     painter->save();
//     printf("num indexes: %d\n",indexes.count());
//     for(unsigned int i=0; i<indexes.count(); i++){
//       QPainterPath path = rawFont.pathForGlyph(indexes[i]);
//       painter->translate(QPointF(p.x(), p.y() + i*0));
//       painter->fillPath(path,painter->pen().brush());
//     }
//     painter->restore();
}

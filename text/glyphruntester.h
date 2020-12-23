#ifndef GLYPHRUNTESTER_H
#define GLYPHRUNTESTER_H

#include <QObject>
#include <QWidget>

class GlyphRunTesterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GlyphRunTesterWidget(QWidget *p = 0);
protected:
    void paintEvent(QPaintEvent *e);
private:
};

class GlyphRunTester : public QObject
{
    Q_OBJECT
public:
    explicit GlyphRunTester(QObject *parent = 0);
    ~GlyphRunTester();
    void draw();

private:
    GlyphRunTesterWidget *m_Widget;
};

#endif // GLYPHRUNTESTER_H

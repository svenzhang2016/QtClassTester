#ifndef TEXTOBJECTTESTER_H
#define TEXTOBJECTTESTER_H


#include <QMap>

class QTextObject;
class QTextFrame;

class TextObjectTester
{
public:
    TextObjectTester();
    void clear();

private:
    mutable QTextFrame *m_Frame;
    QMap<int, QTextObject*> m_Objects;
};

#endif // TEXTOBJECTTESTER_H

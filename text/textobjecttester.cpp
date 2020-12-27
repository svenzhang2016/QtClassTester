#include "textobjecttester.h"

TextObjectTester::TextObjectTester()
{

}

void TextObjectTester::clear()
{
    QMap<int, QTextObject*>::Iterator objectIt = m_Objects.begin();
    while(objectIt != m_Objects.end())
    {
        if(*objectIt != m_Frame)
        {
            delete *objectIt;
            objectIt = m_Objects.erase(objectIt);
        }
        else
        {
            ++objectIt;
        }
    }
}


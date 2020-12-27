#ifndef TEXTTESTERDIALOG_H
#define TEXTTESTERDIALOG_H

#include <QDialog>

namespace Ui {
class TextTesterDialog;
}
class GlyphRunTester;
class StaticTextTester;
class TextOptionTester;
class TextTesterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextTesterDialog(QWidget *parent = 0);
    ~TextTesterDialog();

private slots:
    void on_pushButtonGlyphRun_clicked();

    void on_pushButtonStaticText_clicked();


    void on_pushButtonTextOption_clicked();

private:
    Ui::TextTesterDialog *ui;
    GlyphRunTester *m_GlyphRunTester;
    StaticTextTester *m_StaticTextTester;
    TextOptionTester *m_TextOptionTester;
};

#endif // TEXTTESTERDIALOG_H

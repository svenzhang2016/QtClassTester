#ifndef TEXTTESTERDIALOG_H
#define TEXTTESTERDIALOG_H

#include <QDialog>

namespace Ui {
class TextTesterDialog;
}
class GlyphRunTester;
class TextTesterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextTesterDialog(QWidget *parent = 0);
    ~TextTesterDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TextTesterDialog *ui;
    GlyphRunTester *m_GlyphRunTester;
};

#endif // TEXTTESTERDIALOG_H

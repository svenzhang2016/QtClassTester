#include "texttesterdialog.h"
#include "ui_texttesterdialog.h"
#include "glyphruntester.h"

TextTesterDialog::TextTesterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextTesterDialog)
{
    ui->setupUi(this);
}

TextTesterDialog::~TextTesterDialog()
{
    delete ui;
}

void TextTesterDialog::on_pushButton_clicked()
{
     m_GlyphRunTester = new GlyphRunTester(this);
     m_GlyphRunTester->draw();
}

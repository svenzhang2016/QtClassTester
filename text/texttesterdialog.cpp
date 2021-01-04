#include "texttesterdialog.h"
#include "ui_texttesterdialog.h"
#include "glyphruntester.h"
#include "statictexttester.h"
#include "textoptiontester.h"
#include "basictimertester.h"

TextTesterDialog::TextTesterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextTesterDialog)
{
    ui->setupUi(this);
}

TextTesterDialog::~TextTesterDialog()
{
    delete ui;
    if(m_StaticTextTester) delete m_StaticTextTester;
}

void TextTesterDialog::on_pushButtonGlyphRun_clicked()
{
     m_GlyphRunTester = new GlyphRunTester(this);
     m_GlyphRunTester->draw();
}

void TextTesterDialog::on_pushButtonStaticText_clicked()
{
    m_StaticTextTester = new StaticTextTester();
    m_StaticTextTester->draw();
}

void TextTesterDialog::on_pushButtonTextOption_clicked()
{
    m_TextOptionTester = new TextOptionTester();
    m_TextOptionTester->show();
}

void TextTesterDialog::on_pushButton_clicked()
{
    m_BasicTimerTester = new BasicTimerTester();
    m_BasicTimerTester->start();
}

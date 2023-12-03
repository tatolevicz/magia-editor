#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <ScintillaEdit.h>
#include <SciLexer.h>
#include <ILexer.h>
#include <Lexilla.h>

#include "MyStyles.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto lexNum = GetLexerCount();
    qDebug() << "Num of lexers: " << lexNum;

    char name[20];
    for(int i = 0; i < lexNum; i++){
        GetLexerName(i,name, 20);
        qDebug() << "Lexer available: " << name;
    }

    auto editor = new ScintillaEdit(this);

    auto lex = CreateLexer("lua");
    if(lex != nullptr)
        qDebug() << "Agora deu!!";


    editor->resize(QSize(this->width(), this->height()));
    editor->setWrapMode(SC_WRAP_WORD);

    editor->setILexer((sptr_t)(void*)lex);


    mystyles::editor::setDefaultStyle(editor);
    mystyles::lua::setDefaultStyle(editor);

}

MainWindow::~MainWindow()
{
    delete ui;
}


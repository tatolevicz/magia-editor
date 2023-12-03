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

    _editor = new ScintillaEdit(this);

    auto lex = CreateLexer("lua");
    if(lex != nullptr)
        qDebug() << "Agora deu!!";


    _editor->resize(QSize(this->width(), this->height()));
    _editor->setWrapMode(SC_WRAP_WORD);

    _editor->setILexer((sptr_t)(void*)lex);


    mystyles::editor::setDefaultStyle(_editor);
    mystyles::lua::setDefaultStyle(_editor);

    _editor->autoCSetMaxWidth(50);
    _editor->autoCSetMaxHeight(10);



    // Conectar sinais e slots para eventos de digitação
    connect(_editor, &ScintillaEdit::charAdded, this, &MainWindow::onCharAdded);

}

void MainWindow::onCharAdded(int ch) {
    // Implementação de lógica de quando mostrar o autocomplete
    if (ch == '(' || ch == ' ') {
        _editor->markerAdd(0, 1);  // 10 é o número da linha, 0 é o índice do marcador

        // Exemplo: mostrar autocomplete após '(' ou ' '
        showAutocomplete();
    }
    else {
        _editor->markerDelete(0, 1);
    }
}

void MainWindow::showAutocomplete() {
    // Exemplo de fonte de dados para autocomplete (palavras-chave Lua)
    QStringList luaKeywords = {"function", "end", "if", "then", "else", "for", "while", "do", "repeat", "until"};
    QString wordList = luaKeywords.join(" ");

    // Exibir lista de autocomplete
    _editor->autoCShow(0,wordList.toUtf8().data());
}


MainWindow::~MainWindow()
{
    delete ui;
}


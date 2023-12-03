#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <ScintillaEdit.h>
#include <SciLexer.h>
#include <ILexer.h>
#include <Lexilla.h>

#include "MyStyles.h"
#include <sol/sol.hpp>
#include <regex>

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


    //lua setup
    _lua = std::make_shared<sol::state>();
    _lua->open_libraries(sol::lib::base);
}

void MainWindow::onCharAdded(int ch) {
    // Implementação de lógica de quando mostrar o autocomplete
    if (ch == '(' || ch == ' ') {
//        _editor->markerAdd(0, 1);  // 10 é o número da linha, 0 é o índice do marcador

        // Exemplo: mostrar autocomplete após '(' ou ' '
        showAutocomplete();
    }
    else {
//        _editor->markerDelete(0, 1);
    }

    int length = _editor->textLength();
    std::string script = _editor->getText(length).toStdString();
    qDebug() << "Char added: " << script;
    int errorLine = validateLuaScript(script);
    updateErrorMaker(errorLine);
}

void MainWindow::showAutocomplete() {
    // Exemplo de fonte de dados para autocomplete (palavras-chave Lua)
    QStringList luaKeywords = {"function", "end", "if", "then", "else", "for", "while", "do", "repeat", "until"};
    QString wordList = luaKeywords.join(" ");

    // Exibir lista de autocomplete
    _editor->autoCShow(0,wordList.toUtf8().data());
}

void MainWindow::updateErrorMaker(int errorLine) {
    // Primeiro, remova todos os marcadores de erro existentes
    _editor->markerDeleteAll(1);

    // Se houver um erro, adicione o marcador de erro na linha correspondente
    if (errorLine != -1) {
        _editor->markerAdd(errorLine-1, 1);
    }
}

int MainWindow::validateLuaScript(const std::string& script) {
    try {
        _lua->script(script);
    } catch (const sol::error& e) {
        std::string errorMsg = e.what();
        int lineError = extractErrorLine(errorMsg);
        return lineError;
    }
    return -1;
}

int MainWindow::extractErrorLine(const std::string& erroMsg) {
    // Implemente a lógica para extrair o número da linha do erro
    // Isso pode variar dependendo do formato da mensagem de erro do Lua
    // Por exemplo, você pode usar expressões regulares ou outras técnicas de análise de string
//    qDebug() << "Error mgs: " << erroMsg;

    std::regex standard(R"(\]:([0-9]+):)"); // Padrão para capturar o número da linha
    std::smatch results;

    if (std::regex_search(erroMsg, results, standard) && results.size() > 1) {
        return std::stoi(results[1].str()); // Converte o número da linha para inteiro
    }

    return -1; // Retorna -1 se não encontrar o número da linha
}

MainWindow::~MainWindow()
{
    delete ui;
}


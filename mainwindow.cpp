#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <ScintillaEdit.h>
#include <SciLexer.h>
#include <ILexer.h>
#include <Lexilla.h>
#include "MyStyles.h"
#include <sol/sol.hpp>
#include <regex>
#include <QTimer>
#include <QResizeEvent>

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

    assert(lex != nullptr);

    _editor->resize(QSize(this->width(), this->height()));
    _editor->setWrapMode(SC_WRAP_WORD);

    _editor->setILexer((sptr_t)(void*)lex);


    mystyles::editor::setDefaultStyle(_editor);
    mystyles::lua::setDefaultStyle(_editor);

    _editor->autoCSetMaxWidth(50);
    _editor->autoCSetMaxHeight(10);

    // Conectar sinais e slots para eventos de digitação
    connect(_editor, &ScintillaEdit::charAdded, this, &MainWindow::onCharAdded);
    connect(_editor, &ScintillaEdit::modified, this, &MainWindow::scriptModified);
    connect(_editor, &ScintillaEdit::marginClicked, this, &MainWindow::onMarginClicked);


    //lua setup
    _lua = std::make_shared<sol::state>();
    _lua->open_libraries(sol::lib::base);

    // syntax timer setup
    _syntaxTimer = new QTimer(this);
    _syntaxTimer->setInterval(1000); // 1000 ms = 1 segundo
    connect(_syntaxTimer, &QTimer::timeout, this, &MainWindow::syntaxTimerTimeout);
}

//resize editor
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    // Obtenha as novas dimensões da janela
    QSize newSize = event->size();
    _editor->resize(newSize);

// Ajuste o tamanho do seu widget filho com base no newSize
// Exemplo: seuWidgetFilho->resize(newSize.width(), newSize.height());

// Ou ajuste a posição e o tamanho de acordo com a lógica específica
}

void MainWindow::syntaxTimerTimeout() {
    int length = _editor->textLength();
    std::string script = _editor->getText(length).toStdString();
    int errorLine = validateLuaScript(script);
    updateErrorMaker(errorLine);
}

void MainWindow::scriptModified(Scintilla::ModificationFlags type,
                    Scintilla::Position position,
                    Scintilla::Position length,
                    Scintilla::Position linesAdded,
                    const QByteArray &text,
                    Scintilla::Position line,
                    Scintilla::FoldLevel foldNow,
                    Scintilla::FoldLevel foldPrev)
{
    _syntaxTimer->start();
}
void MainWindow::onMarginClicked(Scintilla::Position position,
                     Scintilla::KeyMod modifiers,
                     int margin){
    // Obter a linha que foi clicada
    int lineClicked = _editor->send(SCI_LINEFROMPOSITION, position, 0);
    qDebug() << "Margin clicked on line " << lineClicked;
    // Alternar dobradura na linha
    _editor->send(SCI_TOGGLEFOLD, lineClicked);
}


void MainWindow::onCharAdded(int ch) {
    // Implementação de lógica de quando mostrar o autocomplete
    if (ch == '(' || ch == ' ') {
//        _editor->markerAdd(0, 1);  // 10 é o número da linha, 0 é o índice do marcador
        // Exemplo: mostrar autocomplete após '(' ou ' '
        showAutocomplete();
    }
    else if(ch == '\n'){
        onNewLine();
    }
    else {
//        _editor->markerDelete(0, 1);
    }
}

void MainWindow::onNewLine() {
    //TODO::just testsing -> this can work but need a lot of tests
//    int currentLine = _editor->send(SCI_LINEFROMPOSITION, _editor->send(SCI_GETCURRENTPOS));
//    int lineIndentation = 2;//_editor->send(SCI_GETLINEINDENTATION, currentLine);
//    _editor->send(SCI_SETLINEINDENTATION, currentLine + 1, lineIndentation);
//    _editor->send(SCI_GOTOPOS, _editor->send(SCI_POSITIONFROMLINE, currentLine + 1) + lineIndentation);
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

    sol::load_result result = _lua->load(script);
    if (!result.valid()) {
        sol::error err = result;
        std::string errorMsg = err.what();

        // Extrair e retornar o número da linha do erro (implemente esta função)
        return extractErrorLine(errorMsg);
    }

    return -1; // Retorna -1 se a sintaxe estiver correta
}

int MainWindow::extractErrorLine(const std::string& erroMsg) {

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


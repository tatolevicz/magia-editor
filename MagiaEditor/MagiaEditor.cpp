//
// Created by Arthur Motelevicz on 05/12/23.
//

#include "MagiaEditor.h"
#include "MgStyles.h"

#include <SciLexer.h>
#include <ILexer.h>
#include <Lexilla.h>
#include <sol/sol.hpp>
#include <QTimer>
#include <regex>

namespace mg{
    MagiaEditor::MagiaEditor(QWidget *parent):
    ScintillaEdit(parent){}

    void MagiaEditor::setup(){
        auto lexNum = GetLexerCount();
        qDebug() << "Num of lexers: " << lexNum;

        char name[20];
        for(int i = 0; i < lexNum; i++){
            GetLexerName(i,name, 20);
            qDebug() << "Lexer available: " << name;
        }

        auto lex = CreateLexer("lua");

        assert(lex != nullptr);

        this->resize(QSize(this->width(), this->height()));
        this->setWrapMode(SC_WRAP_WORD);

        this->setILexer((sptr_t)(void*)lex);

        mg::styles::editor::setDefaultStyle(this);
        mg::styles::lua::setDefaultStyle(this);

        this->autoCSetMaxWidth(50);
        this->autoCSetMaxHeight(10);

        // Conectar sinais e slots para eventos de digitação
        connect(this, &ScintillaEdit::charAdded, this, &MagiaEditor::onCharAdded);
        connect(this, &ScintillaEdit::modified, this, &MagiaEditor::scriptModified);
        connect(this, &ScintillaEdit::marginClicked, this, &MagiaEditor::onMarginClicked);
        connect(this, &ScintillaEdit::dwellStart, this, &MagiaEditor::idleMouseStart);
        connect(this, &ScintillaEdit::dwellEnd, this, &MagiaEditor::idleMouseEnd);

        //lua setup
        _lua = std::make_shared<sol::state>();
        _lua->open_libraries(sol::lib::base);

        // syntax timer setup
        _syntaxTimer = new QTimer(this);
        _syntaxTimer->setInterval(800); // 1000 ms = 1 segundo
        connect(_syntaxTimer, &QTimer::timeout, this, &MagiaEditor::syntaxTimerTimeout);

        this->setMouseDwellTime(200);
    }

    MagiaEditor::~MagiaEditor(){}

    void MagiaEditor::syntaxTimerTimeout() {
        int length = this->textLength();
        std::string script = this->getText(length).toStdString();
        int errorLine = validateLuaScript(script);
        updateErrorMaker(errorLine);
    }

    void MagiaEditor::scriptModified(Scintilla::ModificationFlags type,
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

    void MagiaEditor::onMarginClicked(Scintilla::Position position,
                                     Scintilla::KeyMod modifiers,
                                     int margin){
        // Obter a linha que foi clicada
        int lineClicked = this->send(SCI_LINEFROMPOSITION, position, 0);
        qDebug() << "Margin clicked on line " << lineClicked;
        // Alternar dobradura na linha
        this->send(SCI_TOGGLEFOLD, lineClicked);
    }


    void MagiaEditor::onCharAdded(int ch) {
        // Implementação de lógica de quando mostrar o autocomplete
        if (ch == '(' || ch == ' ') {
            // Exemplo: mostrar autocomplete após '(' ou ' '
            showAutocomplete();
        }
        else if(ch == '\n'){
            onNewLine();
        }
        else {
        }
    }

    void MagiaEditor::onNewLine() {
        //TODO::just testsing -> this can work but need a lot of tests
//    int currentLine = this->send(SCI_LINEFROMPOSITION, this->send(SCI_GETCURRENTPOS));
//    int lineIndentation = 2;//this->send(SCI_GETLINEINDENTATION, currentLine);
//    this->send(SCI_SETLINEINDENTATION, currentLine + 1, lineIndentation);
//    this->send(SCI_GOTOPOS, this->send(SCI_POSITIONFROMLINE, currentLine + 1) + lineIndentation);
    }

    void MagiaEditor::showAutocomplete() {
        // Exemplo de fonte de dados para autocomplete (palavras-chave Lua)
        QStringList luaKeywords = {"function", "end", "if", "then", "else", "for", "while", "do", "repeat", "until"};
        QString wordList = luaKeywords.join(" ");

        // Exibir lista de autocomplete
        this->autoCShow(0,wordList.toUtf8().data());
    }

    void MagiaEditor::updateErrorMaker(int errorLine) {

        // Primeiro, remova todos os marcadores de erro existentes
        this->markerDeleteAll(styles::Markers::ERROR);

        // Se houver um erro, adicione o marcador de erro na linha correspondente
        if (errorLine != -1) {
            this->markerAdd(errorLine-1, 1);
        }
    }

    int MagiaEditor::validateLuaScript(const std::string& script) {

        sol::load_result result = _lua->load(script);
        if (!result.valid()) {
            sol::error err = result;
            std::string errorMsg = err.what();

            // Extrair e retornar o número da linha do erro (implemente esta função)
            return extractErrorLine(errorMsg);
        }

        return -1; // Retorna -1 se a sintaxe estiver correta
    }

    int MagiaEditor::extractErrorLine(const std::string& errorMsg) {
        _currentError = errorMsg;

        std::regex standard(R"(\]:([0-9]+):)"); // Padrão para capturar o número da linha
        std::smatch results;

        if (std::regex_search(errorMsg, results, standard) && results.size() > 1) {
            return std::stoi(results[1].str()); // Converte o número da linha para inteiro
        }

        _currentError = "";
        return -1; // Retorna -1 se não encontrar o número da linha
    }


    void MagiaEditor::idleMouseStart(int x, int y){
        int pos = positionFromPoint(x, y);
        int line = lineFromPosition(pos);

        int markerMask = send(SCI_MARKERGET, line);
        int errorMask = (1 << styles::Markers::ERROR);
        if (markerMask & errorMask) {
            // Seu código para mostrar o calltip
            callTipShow(pos, _currentError.c_str());
        }
    }

    void MagiaEditor::idleMouseEnd(int x, int y){
        send(SCI_CALLTIPCANCEL);
    }
    
}
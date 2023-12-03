#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ScintillaEdit.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace sol {
    class state;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void syntaxTimerTimeout();
    ScintillaEdit *_editor;
    void onCharAdded(int ch);
    void scriptModified(Scintilla::ModificationFlags type,
                        Scintilla::Position position,
                        Scintilla::Position length,
                        Scintilla::Position linesAdded,
                        const QByteArray &text,
                        Scintilla::Position line,
                        Scintilla::FoldLevel foldNow,
                        Scintilla::FoldLevel foldPrev);

    void showAutocomplete();
    void updateErrorMaker(int errorLine);
    int extractErrorLine(const std::string& error);
    int validateLuaScript(const std::string& script);
    std::shared_ptr<sol::state> _lua{nullptr};

    QTimer* _syntaxTimer{nullptr};


};
#endif // MAINWINDOW_H

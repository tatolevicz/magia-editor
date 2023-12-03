#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace sol {
    class state;
}

class ScintillaEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ScintillaEdit *_editor;
    void onCharAdded(int ch);
    void showAutocomplete();
    void updateErrorMaker(int errorLine);
    int validateLuaScript(const std::string& script);
    int extractErrorLine(const std::string& error);
    std::shared_ptr<sol::state> _lua{nullptr};


};
#endif // MAINWINDOW_H

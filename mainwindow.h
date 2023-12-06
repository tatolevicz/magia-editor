#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ScintillaEdit.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace mg{
    class MagiaEditor;
}

namespace sol {
    class state;
}

class QPlainTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    mg::MagiaEditor* _editor{nullptr};
    QPlainTextEdit* _console{nullptr};
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QResizeEvent>
#include <MagiaEditor.h>
#include "CustomPlainTextEdit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _editor = new mg::MagiaEditor(this);
    _editor->setup();

    _console = new CustomPlainTextEdit(this);
    _console->setReadOnly(true);
    _console->setMaximumHeight(100);
    _console->setStyleSheet("background-color: black; color: white; padding: 10px;");
    _console->setFont(QFont("Courier New", 16));
//    _console->resize(this->width(), 100);
    _console->move(0, this->height() - 100);
    _editor->setPrintCallback([this](const std::string& print){
        QMetaObject::invokeMethod(this, [this, print](){
            _console->appendPlainText(print.c_str());
        });
    });

}

//resize editor
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    QSize newSize = event->size();
    _editor->resize(newSize.width(), newSize.height() - 100);
    _console->resize(newSize.width(), 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


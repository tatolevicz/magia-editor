#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QResizeEvent>
#include <MagiaEditor.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _editor = new mg::MagiaEditor(this);
    _editor->setup();
}

//resize editor
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    QSize newSize = event->size();
    _editor->resize(newSize);
}

MainWindow::~MainWindow()
{
    delete ui;
}


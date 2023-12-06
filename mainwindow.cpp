#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QResizeEvent>
#include <MagiaEditor.h>
#include "CustomPlainTextEdit.h"
#include <QVBoxLayout>
#include <QToolBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* centralWidget = new QWidget(this);  // Widget central
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);  // Layout vertical
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    _editor = new mg::MagiaEditor(centralWidget);
    _editor->setup();

    _console = new CustomPlainTextEdit(centralWidget);
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


    QToolBar* toolBar = new QToolBar("Control Bar", this);
    toolBar->setStyleSheet("background-color: #24283B;  border-right: 1px solid #24283B;");
    toolBar->setIconSize(QSize(16, 16));  // Define o tamanho dos ícones
    toolBar->setMovable(false);  // Torna a barra de ferramentas não-movível
    addToolBar(toolBar);  // Adiciona a barra de ferramentas à janela principal

    QWidget* spacerLeft = new QWidget();
    spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacerLeft);


    QAction* playAction = toolBar->addAction(QIcon(":/resources/images/play_active.svg"), "Play");
    QAction* debugAction = toolBar->addAction(QIcon(":/resources/images/debug_active.svg"), "Debug");
    QAction* stopAction = toolBar->addAction(QIcon(":/resources/images/stop_active.svg"), "Stop");


    QWidget* spacerRight = new QWidget();
    spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacerRight);

    connect(playAction, &QAction::triggered, this, &MainWindow::onPlayClicked);
    connect(debugAction, &QAction::triggered, this, &MainWindow::onDebugClicked);
    connect(stopAction, &QAction::triggered, this, &MainWindow::onStopClicked);

    layout->addWidget(_editor);
    layout->addWidget(_console);

    setCentralWidget(centralWidget);  // Define o widget central da janela


    connect(_editor, &mg::MagiaEditor::scriptFinished, this,
    [](bool success, const std::string& msg){
        qDebug() << "Script finished with success: " << success << " and message: " << msg.c_str();
    });
}

//resize editor
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

//    QSize newSize = event->size();
//    _editor->resize(newSize.width(), newSize.height() - 100);
//    _console->resize(newSize.width(), 100);
}

void MainWindow::onPlayClicked() {
   qDebug() << "Código para iniciar a execução do script";
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        action->setIcon(QIcon(":/resources/images/play_inactive.svg"));
    }

    _editor->execute();
}

void MainWindow::onDebugClicked() {
    qDebug() << "Código para iniciar o debugging";
    QAction* action = qobject_cast<QAction*>(sender());
    if (action) {
        action->setIcon(QIcon(":/resources/images/debug_running.svg"));
    }
    _editor->executeDebug();
}

void MainWindow::onStopClicked() {
    qDebug() << "Código para parar a execução ou o debugging";
}

MainWindow::~MainWindow()
{
    delete ui;
}


//
// Created by Arthur Motelevicz on 06/12/23.
//

#include "MagiaEditorWidget.h"
#include <MagiaEditor.h>
#include <QVBoxLayout>
#include <QToolBar>
#include <QVBoxLayout>
#include "ConsoleOutput.h"

namespace mg{
    MagiaEditorWidget::MagiaEditorWidget(QWidget *parent) : QWidget(parent) {

        _centralWidget = new QWidget(this);  // Widget central
        auto* layout = new QVBoxLayout(_centralWidget);  // Layout vertical
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        _editor = new mg::MagiaEditor(_centralWidget);
        _editor->setup();

        _editor->setPrintCallback([this](const std::string& print){
            QMetaObject::invokeMethod(this, [this, print](){
                _console->appendPlainText(print.c_str());
            });
        });

        _scriptToolBar = new QToolBar("Control Bar", this);
        _scriptToolBar->setStyleSheet("background-color: #24283B;  border-right: 1px solid #24283B;");
        _scriptToolBar->setIconSize(QSize(16, 16));  // Define o tamanho dos ícones
        _scriptToolBar->setMovable(false);  // Torna a barra de ferramentas não-movível


        auto* spacerLeft = new QWidget();
        spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _scriptToolBar->addWidget(spacerLeft);

        QAction* playAction = _scriptToolBar->addAction(QIcon(":/resources/images/play_active.svg"), "Play");
        QAction* debugAction = _scriptToolBar->addAction(QIcon(":/resources/images/debug_active.svg"), "Debug");
        QAction* stopAction = _scriptToolBar->addAction(QIcon(":/resources/images/stop_active.svg"), "Stop");

        auto* spacerRight = new QWidget();
        spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _scriptToolBar->addWidget(spacerRight);

        layout->addWidget(_scriptToolBar);  // Adiciona a barra de ferramentas à janela principal

        connect(playAction, &QAction::triggered, this, &MagiaEditorWidget::onPlayClicked);
        connect(debugAction, &QAction::triggered, this, &MagiaEditorWidget::onDebugClicked);
        connect(stopAction, &QAction::triggered, this, &MagiaEditorWidget::onStopClicked);

        layout->addWidget(_editor);

        auto* bottomWidget = new QWidget(this);
        bottomWidget->setMaximumHeight(150);

        auto* bottomLayout = new QHBoxLayout(this);
        bottomWidget->setLayout(bottomLayout);
        bottomLayout->setContentsMargins(0, 0, 0, 0);
        bottomLayout->setSpacing(0);

        //debug toolbar
        _debugToolBar = new QToolBar("Debug Bar", this);
        _debugToolBar->setOrientation(Qt::Vertical);
        _debugToolBar->setStyleSheet("background-color: #24283B;  border-right: 1px solid #24283B;");
        _debugToolBar->setIconSize(QSize(14, 14));  // Define o tamanho dos ícones
        _debugToolBar->setMovable(false);  // Torna a barra de ferramentas não-movível

        auto* stepOverAction = new QAction(QIcon(":/resources/images/step_over_active.svg"), "Step Over", this);
        auto* stepIntoAction = new QAction(QIcon(":/resources/images/continue_active.svg"), "Step Into", this);

        _debugToolBar->addAction(stepOverAction);
        _debugToolBar->addAction(stepIntoAction);

        connect(stepOverAction, &QAction::triggered, this, &MagiaEditorWidget::onStepOver);
        connect(stepIntoAction, &QAction::triggered, this, &MagiaEditorWidget::onContinue);

        bottomLayout->addWidget(_debugToolBar);

        _console = new ConsoleOutput(bottomWidget);
        _console->setReadOnly(true);
        _console->setMaximumHeight(150);
        _console->setStyleSheet("background-color: black; color: white; padding: 10px;");
        _console->setFont(QFont("Courier New", 16));
        _console->move(0, this->height() - 150);

        bottomLayout->addWidget(_console);

        layout->addWidget(bottomWidget);

        connect(_editor, &mg::MagiaEditor::scriptFinished, this,
        [](bool success, const std::string& msg){
            qDebug() << "Script finished with success: " << success << " and message: " << msg.c_str();
        });
    }



    void MagiaEditorWidget::onPlayClicked() {
        qDebug() << "Código para iniciar a execução do script";
        QAction* action = qobject_cast<QAction*>(sender());
        if (action) {
            action->setIcon(QIcon(":/resources/images/play_inactive.svg"));
        }

        _editor->execute();
    }

    void MagiaEditorWidget::onDebugClicked() {
        qDebug() << "Código para iniciar o debugging";
        QAction* action = qobject_cast<QAction*>(sender());
        if (action) {
            action->setIcon(QIcon(":/resources/images/debug_running.svg"));
        }
        _editor->executeDebug();
    }

    void MagiaEditorWidget::onStopClicked() {
        qDebug() << "Código para parar a execução ou o debugging";
        _editor->stopExecution();
    }

    void MagiaEditorWidget::onStepOver() {
        qDebug() << "Código para avançar uma linha";
        _editor->stepExecution();
    }

    void MagiaEditorWidget::onContinue() {
        qDebug() << "Código para continuar a execução ou o debugging";
        _editor->continueExecution();
    }

    QWidget* MagiaEditorWidget::getCentralWidget(){
        return _centralWidget;
    }


}
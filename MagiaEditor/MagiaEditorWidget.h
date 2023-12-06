//
// Created by Arthur Motelevicz on 06/12/23.
//

#ifndef TESTSCINTILLACMAKE_MAGIAEDITORWIDGET_H
#define TESTSCINTILLACMAKE_MAGIAEDITORWIDGET_H

#include <QWidget>

class QToolBar;

namespace mg {
    class MagiaEditor;
    class ConsoleOutput;

    class MagiaEditorWidget : public QWidget {
        Q_OBJECT
    public:
        MagiaEditorWidget(QWidget* parent = nullptr);
    public slots:
        void onStepOver();
        void onContinue();
        void onPlayClicked();
        void onDebugClicked();
        void onStopClicked();
        void onScriptPaused();
        void onScriptFinished();

        QWidget* getCentralWidget();
    private:
        void updateActions();
        QAction* _playAction;
        QAction* _debugAction;
        QAction* _stopAction;
        QAction* _stepOverAction;
        QAction* _continueAction;

        void setupActions();
        void connectActions();

        MagiaEditor* _editor{nullptr};
        ConsoleOutput* _console{nullptr};
        QToolBar *_scriptToolBar;
        QToolBar *_debugToolBar;
        QWidget* _centralWidget{nullptr};
    };
}
#endif //TESTSCINTILLACMAKE_MAGIAEDITORWIDGET_H
